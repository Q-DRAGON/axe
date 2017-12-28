# coding=utf-8
from PIL import Image
import sys
import json


"""
在上次作业的基础上，做如下处理
1，videoblock 改为 vblock 文件
2，存储的信息如下，搜索不到匹配图块的时候，存储差值最小的图块
{
    'x': 图块在 a 中的座标 x
    'y': 图块在 a 中的座标 y
}
3，存储一个额外的图片，这个图片存储了 vblock 生成的预测图 b1 和原始图片 b 的差值
差值公式为 (b1 - b) / 2 + 128



作业：
1，实现对图像 big_buck_bunny_07502.png 的编码并以 json 格式写入 b.vblock 中（路径由参数给出）, 用法如下
    python3 video2.py encode big_buck_bunny_07501.png big_buck_bunny_07502.png
    生成 big_buck_bunny_07502.vblock 和 big_buck_bunny_07502.diff.png 两个文件
2，用 vblock 文件和差值图还原为新图片（路径由参数给出），用法如下
    python3 video2.py decode diff big_buck_bunny_07501.png decode.png
    用 vblock diff.png 和上一帧的图片 big_buck_bunny_07501.png 生成解码后的图片 decode.png
3，video3.py 对图片 07501 到 07546 调用 video2.py 进行处理，可以生成一个包含 vblock 和 diff.png 的目录，用法如下
    python3 video3.py
"""

def grayimage(path):
    # convert('L') 转为灰度图
    # 这样每个像素点就只有一个灰度数据
    img = Image.open(path).convert('L')
    return img


def sliceimg(img, x1, y1, x2, y2):
    region = (x1, y1, x2, y2)
    return img.crop(region).convert('L')


def similarity(cropImga, cropImgb):
    dataa = cropImga.load()
    datab = cropImgb.load()
    w, h = cropImgb.size
    result = 0
    for i in range(h):
        for j in range(w):
            result += abs(dataa[j, i] - datab[j, i])
    return result


def mostsimilarimg(cropImga, cropImgb):
    wa, ha = cropImga.size
    gap = 100000000
    mostx = None
    mosty = None
    for i in range(int(ha)):
        for j in range(int(wa)):
            ccropImaga = sliceimg(cropImga, j, i, j + 8, i + 8)
            result = similarity(ccropImaga, cropImgb)
            if result < gap:
                gap = result
                mostx = j
                mosty = i
    return mostx, mosty


def imgtosequence(img):
    result = []
    w, h = img.size
    pixels = img.load()
    for y in range(h):
        for x in range(w):
            result.append(pixels[x, y])
    return result


def tabletosequence(table):
    sequence = []
    for i in range(len(table)):
        for j in range(len(table[i])):
            sequence.append(table[i][j])
    return sequence


def finddata(imga, cropImgb, xa1, ya1):
    xa2 = xa1 + 8
    ya2 = ya1 + 8
    cropimga = sliceimg(imga, xa1, ya1, xa2, ya2)
    mostx, mosty = mostsimilarimg(cropimga, cropImgb)
    data = {
        'x': mostx + xa1,
        'y': mosty + ya1,
    }
    if (mosty + ya1) < 0:
        print('ss', mosty, ya1)
    return data


def diffpngseq(forcast, origin):
    result_seq = []
    for i in range(len(forcast)):
        result_seq.append((forcast[i] - origin[i]) / 2 + 128)
    return result_seq


def encode(imga, imgb, output):
    wb, hb = imgb.size
    xb = int(wb / 8)
    yb = int(hb / 8)
    result = []
    # 遍历imgb的每个小方块
    for i in range(int(yb)):
        print(i/yb)
        hang = []
        for j in range(int(xb)):
            xb1 = 8 * j
            xb2 = xb1 + 8
            yb1 = 8 * i
            yb2 = yb1 + 8
            cropImgb = sliceimg(imgb, xb1, yb1, xb2, yb2)
            xa1 = xb1 - 8
            ya1 = yb1 - 8
            if xa1 < 0:
                xa1 = 0
            if ya1 < 0:
                ya1 = 0
            # 找到imga中小方块对应的数据
            hang.append(finddata(imga, cropImgb, xa1, ya1))
        result.append(hang)
    # 存入json文件
    with open(output, 'w+') as f:
        json.dump(result, f, indent=2)
    # 制作diff图片
    # 先将vblock文件恢复成图片
    resultimg = decode_vblock(output, imga)
    result_seq = resultimg.load()
    imgb_seq = imgb.load()
    diffimg = Image.new(imgb.mode, imgb.size)
    diffpixels = diffimg.load()
    for i in range(hb):
        for j in range(wb):
            diffpixels[j, i] = int((result_seq[j, i] - imgb_seq[j, i]) / 2 + 128)
    name = output.split('.')[0] + '.diff.png'
    diffimg.save(name)


def read_file(file):
    with open(file, 'r') as f:
        data = json.load(f)
    return data


def decode_vblock(imgfile, imga):
    newimg = Image.new(imga.mode, imga.size)
    data = read_file(imgfile)
    for i in range(len(data)):
        print(i / len(data), i)
        hang = data[i]
        for j in range(len(hang)):
            x1 = hang[j]['x']
            y1 = hang[j]['y']
            slice = sliceimg(imga, x1, y1, x1 + 8, y1 + 8)
            newimg.paste(slice, (j * 8, i * 8))
    return newimg


# python3 video2.py decode diff big_buck_bunny_07501.png decode.png
def decode(diff, vblock, origin, output):
    originimg = grayimage(origin)
    forcastimg = decode_vblock(vblock, originimg)
    diffimg = grayimage(diff)
    diffpixels = diffimg.load()
    forcastpixels = forcastimg.load()
    w, h = forcastimg.size
    newimg = Image.new(forcastimg.mode, forcastimg.size)
    newimgpixels = newimg.load()
    for i in range(h):
        for j in range(w):
            newimgpixels[j, i] = forcastpixels[j, i] - (diffpixels[j, i] - 128) * 2
    newimg.save(output)


def main():
    # print(sys.argv)
    # 下面是一段遍历像素并操作的范例
    # 供参考
    # w, h = img1.size
    # threshold = 128
    # pixels = img1.load()
    # for y in range(h):
    #     for x in range(w):
    #         if pixels[x, y] < threshold:
    #             pixels[x, y] = 0
    #         else:
    #             pixels[x, y] = 255
    # img1.save('保存图片样例.png')
    if sys.argv[1] == 'encode':
        path1 = sys.argv[2]
        path2 = sys.argv[3]
        img1 = grayimage(path1)
        img2 = grayimage(path2)
        output = sys.argv[3].split(".")[0] + '.vblock'
        encode(img1, img2, output)
    elif sys.argv[1] == 'decode':
        code = int(sys.argv[3].split(".")[0][-4:]) + 1
        diff = sys.argv[3].split(".")[0][:-4] + str(code) + '.diff.png'
        vblock = sys.argv[3].split(".")[0][:-4] + str(code) + '.vblock'
        decode(diff, vblock, sys.argv[3], sys.argv[4])


if __name__ == '__main__':
    main()
