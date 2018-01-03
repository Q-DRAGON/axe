# coding=utf-8
from PIL import Image
import sys
import json
import os
import struct

"""
作业内容：
本程序使用的图片数据为下面所有的图片
从
https://xiph-media.net/BBB/BBB-360-png/big_buck_bunny_07501.png
到
https://xiph-media.net/BBB/BBB-360-png/big_buck_bunny_07546.png


在以前的作业的基础上，实现一个视频文件格式（只支持黑白视频，不支持声音）
文件格式名为 .uipn 下面是该文件格式的详细描述

注意：多字节数字的存储请搜索 大端和小端
由于大家都是 Intel CPU 所以用操作系统的默认存储方式就好了
Python 中 用 sys 模块的 sys.byteorder 查看

头 4 个字节                'uipn'
版本号（以 '\n' 结尾）      '1.0\n'
图片数量（1 字节）          
视频宽（2 字节）            
视频高（2 字节）

接下来分 2 个部分

第一部分，存储差值图片数据，以第一张图片为关键帧，存储的是完整图片而不是差值

第一张图片的长度（4 字节）
第一张图片的所有数据（写入差值图的 png 图片文件）
第二张图片的长度（4 字节）
第二张图片的所有数据
...
第 n 张图片的长度（4 字节）
第 n 张图片的所有数据


第二部分，存储匹配图块的座标，这里只描述第二张图片的座标存储
一张图片的图块数量从左到右从上到下一共有 m 个
每个图块存储一个 x y 座标
每对 x y 座标用 4 字节存储
一张图片的图块座标信息占用 m * 4 的大小



作业：
把一系列图片编码为一个视频文件
用法如下（用 images 目录里的图片序列生成 gua.uipn 视频文件）
python3 uipn.py encode images gua
"""
def grayimage(path):
    img = Image.open(path).convert('L')
    return img


def encode(path, output):
    # 头
    s = b''
    files = os.listdir(path)
    num = 0
    diffimg = []
    vblockimg = []
    for i in range(len(files)):
        if files[i][-3:] == 'png':
            if files[i][-8:] != 'diff.png':
                num += 1
            else:
                diffimg.append(files[i])
        elif files[i][-6:] == 'vblock':
            vblockimg.append(files[i])
    s = s + b'uipn1.0\n' + struct.pack('<B', num)
    #
    firstimg = os.listdir(path)[0]
    imgname = path + '/' + firstimg
    img = grayimage(imgname)
    w, h = img.size
    s = s + struct.pack('<H', w) + struct.pack('<H', h)
    # 存第一张图
    with open(imgname, 'rb') as f:
        s = s + f.read()
    # 存其余的图
    for i in range(len(diffimg)):
        imgfile = diffimg[i]
        imgpath = path + '/' + imgfile
        with open(imgpath, 'rb') as f:
            s = s + f.read()
    # 存vblock文件
    for i in range(len(vblockimg)):
        vblockfile = vblockimg[i]
        vblockpath = path + '/' + vblockfile
        with open(vblockpath, 'r') as f:
            data = json.load(f)
            for hi in range(len(data)):
                for wi in range(len(data[hi])):
                    x = data[hi][wi]['x']
                    y = data[hi][wi]['y']
                    s += struct.pack('<HH', x, y)
    # 存 s 为最终文件
    with open(output, 'wb+') as f:
        f.write(s)


def main():
    if sys.argv[1] == 'encode':
        path = sys.argv[2]
        name = sys.argv[3]
        output = name + '.uipn'
        encode(path, output)


if __name__ == '__main__':
    main()
