# coding=utf-8
from PIL import Image
import sys
import json


"""

作业截止时间
周日（12.24） 18:00


交作业方式：
作业文件路径为
axe35/video1.py
axe35/b.videoblock


作业内容：
本程序使用的测试图片为下面 2 张图片
分别为 a 和 b
https://xiph-media.net/BBB/BBB-360-png/big_buck_bunny_07501.png
https://xiph-media.net/BBB/BBB-360-png/big_buck_bunny_07502.png


上节课讲过视频编码的原理，就是相似图片对比搜索
本程序只对灰度进行操作
只要对 RGBA 分别操作就是对彩色视频的编码

把 b 划分为 8x8 的图块
对于每一个 b 中的图块，在 a 中查找最相似的图块的座标
因为视频相邻的 2 帧是相似的，所以在 a 中查找时，查找方圆 4 像素或者 8 像素的方块
比如对于 b 中一个图块（座标为 8, 8）在 a 中搜索 x(0-15) y(0-15) 这么大的范围（建议从 8,8 开始搜索比较好）
图块的相似度比较有很多种算法，这里使用最简单的算法，求出[图块中 [每个像素的差的绝对值] 的和]（这种算法叫 SAD，还有 SSD 等，做完作业没事干可自行搜索）
你可以给搜索加上一个终止条件，比如误差小于多少就认为搜索到了而不必一定要找到范围内的最小误差
如果在 a 中搜索后误差过大可以把 b 的这个图块完全存下来

这样我们就可以得到一个二维数组，表示图像 b 的图块信息
数组中每个元素是一个如下的字典，表示一个图块
{
    'x': 图块在 a 中的座标 x，如果为 -1 说明没找到合适的相似图块
    'y': 图块在 a 中的座标 y，如果为 -1 说明没找到合适的相似图块
    'data': 如果没找到相似的图块，这里存 64 字节的像素信息，如果找到，这里是 None
}


以上的算法计算量很大，所以压视频动辄几小时，是非常耗费 CPU 的工作
实际现在的主流编码方案用的算法比我们这个算法高效很多，但这里不做更多介绍


作业：
0，主流算法比如 H.264 用的是很先进的技术，为什么我们这里用很笨的办法来做这件事，请描述你的看法

看法:
最先进的技术总是在更新换代, 所以只追逐最先进的技术不是培养可持续解决问题方法的能力的途径。
用最笨的方法实现压缩的过程, 有助于了解视频压缩最基础的原理和思路, 有助于进一步理解更先进的技术, 也有助于培养从无到有的解决问题的能力。


1，视频文件中的镜头切换的上下 2 帧可能几乎完全不一样，怎么处理，用文字描述

如果判断出上下 2 帧相似度很低, 就将新的图片存为 关键帧 , 以备压缩后续帧的图片使用。


2，实现对图像 big_buck_bunny_07502.png 的编码并以 json 格式写入 b.videoblock 中（路径由参数给出）, 用法如下
    python3 video1.py encode big_buck_bunny_07501.png big_buck_bunny_07502.png b.videoblock

3，实现对 videoblock 文件的解码并写入为新图片（路径由参数给出），用法如下
    python3 video1.py decode b.videoblock big_buck_bunny_07501.png decode.png
"""


def grayimage(path):
    # convert('L') 转为灰度图
    # 这样每个像素点就只有一个灰度数据
    img = Image.open(path).convert('L')
    return img


def sliceimg(img, x1, y1, x2, y2):
    region = (x1, y1, x2, y2)
    return img.crop(region).convert('L')


def similarimg(cropImga, cropImgb):
    dataa = cropImga.getdata()
    datab = cropImgb.getdata()
    border = 500
    result = 0
    for i in range(len(dataa)):
        result += abs(dataa[i] - datab[i])
    if result < border:
        return True
    else:
        return False


def tosequence(img):
    result = []
    w, h = img.size
    pixels = img.load()
    for y in range(h):
        for x in range(w):
            result.append(pixels[x, y])
    return result


def finddata(imga, cropImgb, xa1, ya1):
    xa2 = xa1 + 8
    ya2 = ya1 + 8
    data = None
    for kx in range(16):
        for ky in range(16):
            cropImga = sliceimg(imga, xa1 + kx, ya1 + ky, xa2 + kx, ya2 + ky)
            if similarimg(cropImga, cropImgb):
                data = {
                    'x': xa1 + kx,
                    'y': ya1 + ky,
                    'data': None
                }
    if data is None:
        data = {
            'x': -1,
            'y': -1,
            'data': tosequence(cropImgb),
        }
    return data


def encode(imga, imgb, output):
    wb, hb = imgb.size
    xb = int(wb / 8)
    yb = int(hb / 8)
    result = []
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
            hang.append(finddata(imga, cropImgb, xa1, ya1))
        result.append(hang)
    print('igdu', len(result), len(result[0]))
    with open(output, 'w+') as f:
        json.dump(result, f, indent=2)


def read_file(file):
    with open(file, 'r') as f:
        data = json.load(f)
    return data


def decode(imgfile, imga, imgb):
    newimg = Image.new(imga.mode, imga.size)
    data = read_file(imgfile)
    for i in range(len(data)):
        print(i / len(data), i)
        hang = data[i]
        for j in range(len(hang)):
            if hang[j]['data'] is None:
                x1 = hang[j]['x']
                y1 = hang[j]['y']
                slice = sliceimg(imga, x1, y1, x1 + 8, y1 + 8)
                newimg.paste(slice, (j * 8, i * 8))
            elif hang[j]['data'] is not None:
                datah = hang[j]['data']
                pixels = newimg.load()
                for y in range(8):
                    for x in range(8):
                        pixels[j * 8 + x, i * 8 + y] = datah[y * 8 + x]
    newimg.save(imgb)


def main():
    print(sys.argv)
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
        encode(img1, img2, sys.argv[4])
    elif sys.argv[1] == 'decode':
        path2 = sys.argv[3]
        img2 = grayimage(path2)
        decode(sys.argv[2], img2, sys.argv[4])


if __name__ == '__main__':
    main()
