from PIL import Image
import sys
import json
import os

# 3，video3.py 对图片 07501 到 07546 调用 video2.py 进行处理，可以生成一个包含 vblock 和 diff.png 的目录，用法如下

def main():
    start = 7501
    end = 7546
    for i in range(start, end):
        s = 'python3 video2.py encode big_buck_bunny_0{}.png big_buck_bunny_0{}.png'.format(i, i + 1)
        os.system(s)


if __name__ == '__main__':
    main()