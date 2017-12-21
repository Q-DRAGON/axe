import numpy as np
import matplotlib.pyplot as plot
from PIL import Image


"""
不会安装依赖库的，搜以下关键词
python 安装 Pillow
python 安装 numpy
python 安装 matplotlib


本程序使用的测试图片为下面这张图片
http://optipng.sourceforge.net/pngtech/img/lena.png
测试图尺寸为 512x512
关于这张 lena 图的来历，自行搜索


本程序对整张图片进行压缩
参考本程序
对图像中的每个 8*8 小格子进行压缩

这个程序只对灰度进行压缩
只要对 RGBA 分别压缩并还原就可以实现对彩色图片的压缩

除了 fft 外还可以使用 dct（jpg 使用的方法）进行变换
但是因为 numpy 提供了 fft2 这个函数所以我们就先用 fft
这个算法的具体细节以后再考虑


作业：
1，补全 filter_image 函数，实现压缩功能
2，实现彩色图像的压缩
3，对图像进行 8*8 分块压缩，我们只考虑图象大小为 8 的整数倍的情况

需要注意的是，我们这个程序对图像压缩后，并未使用 lzw 对其进行编码
但是因为我们丢弃了部分高频数据，所以冗余量肯定是降低了的
lzw 这一步选做
"""


def image_fft(image):
    # 对图像做二维 fft
    a = np.fft.fft2(image)
    return a


def decompress_image(data):
    # 做一个逆 fft2 还原数据
    img = np.fft.ifft2(data)
    return img


def save_image(data, path):
    # 把图片还原并保存到文件中
    # 需要注意的是，fft 变换的结果是一个 [复数] （不懂就搜索，但这里没必要知道）
    # np.uint8 转换的时候，只会转换复数的实部，丢弃复数的虚部（本来也用不着）
    img = Image.fromarray(np.uint8(data))
    img.save(path)


def filter_image(data, ratio=1):
    """
    ratio 是压缩率, 范围是 0 - 1
    1 表示完全不压缩

    本函数会对 fft 变换后的数据进行过滤
    经过二维 fft 变换后，得到的数据是一个系数矩阵
    其中，左上角是低频数据，右下角是高频数据
    根据课上所说，高频数据可以丢弃（设置为 0 就算是丢弃了）
    """
    # 造一个空数组并复制数据
    r = np.zeros_like(data)
    h = len(data)
    w = len(data[0])
    for i, row in enumerate(data):
        for j, n in enumerate(row):
            # 在这里可以根据压缩率选择性地丢弃部分高频数据
            # 请注意，高频数据在右下角
            # r[i, j] 这种用法是 numpy 的用法
            if (i + j) > (h + w) * ratio:
                r[i, j] = 0
            else:
                r[i, j] = n
    return r


def preview(img):
    """
    这里利用 matplotlib 把图像画出来预览
    很好理解
    """
    m, n = 3, 3
    for i in range(m * n):
        # 从 1 到 9 选择画在第 n 个子图
        plot.subplot(m, n, i+1)
        # 这里可以设置不同的过滤等级（压缩等级）
        # 题2 不切小格子
        # de_image = compress(img, 0.1 * i + 0.05)
        # 题3 切小格子
        newimg = Image.new(img.mode, img.size)
        for k in range(int(img.size[0] / 8)):
            for j in range(int(img.size[1] / 8)):
                x1 = 8 * j
                x2 = x1 + 8
                y1 = 8 * k
                y2 = y1 + 8
                region = (x1, y1, x2, y2)
                cropImg = img.crop(region).convert('RGB')
                de_cropImg = compress(cropImg, 0.1 * i + 0.05)
                newimg.paste(de_cropImg, (x1, y1))
        de_image = newimg
        # 画图
        plot.imshow(de_image, cmap=plot.cm.gray)
        plot.grid(False)
        plot.xticks([])
        plot.yticks([])
    # show 是让图像窗口持续停留
    plot.show()


def compressgray(img, ratio):
    data = image_fft(img)
    a = filter_image(data, ratio)
    b = decompress_image(a)
    return np.uint8(b)


def compresscolor(img, ratio):
    img = img.split()
    data0 = image_fft(img[0])
    data1 = image_fft(img[1])
    data2 = image_fft(img[2])
    a0 = filter_image(data0, ratio)
    a1 = filter_image(data1, ratio)
    a2 = filter_image(data2, ratio)
    b0 = decompress_image(a0)
    b1 = decompress_image(a1)
    b2 = decompress_image(a2)
    r = Image.fromarray(np.uint8(b0))
    g = Image.fromarray(np.uint8(b1))
    b = Image.fromarray(np.uint8(b2))
    im = Image.merge('RGB', (r, g, b))
    return im


def compress(img, ratio):
    if img.mode == 'L':
        de_image = compressgray(img, ratio)
    elif img.mode == 'RGB':
        de_image = compresscolor(img, ratio)
    return de_image


def load(path):
    img = Image.open(path)
    # 题1 灰度图
    # img = img.convert('L')
    # 题2 彩色图
    img = img.convert('RGB')
    return img


def main():
    ipath = 'lena.png'
    opath = 'lena2.png'
    img = load(ipath)
    ratio = 0.6
    # 显示9图
    preview(img)
    # 存1图
    de_image = compress(img, ratio)
    save_image(de_image, opath)


if __name__ == '__main__':
    main()
