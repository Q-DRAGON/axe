"""
作业内容:
本文件包含以下 5 个函数, 函数签名见测试文件
直接看算法导论, 不要看证明, 最重要的是理解原理并实现
多用纸笔勾画好逻辑再代码
insertion
selection
bubble
heap
quick
"""


def insertion(a):
    for j in range(1, len(a)):
        key = a[j]
        i = j - 1
        while i >= 0 and a[i] > key:
            a[i + 1] = a[i]
            i = i - 1
        a[i + 1] = key


def selection(a):
    for i in range(0, len(a) - 1):
        min = i
        for j in range(i + 1, a.length):
            if a[j] < a[min]:
                min = j
        temp = a[i]
        a[i] = a[min]
        a[min] = temp


def bubble(a):
    for i in range(0, len(a) - 1):
        for j in range(len(a) - 1, i, -1):
            if a[j] < a[j - 1]:
                temp = a[j]
                a[j] = a[j - 1]
                a[j - 1] = temp


def heap(a):
    pass


def quick(a):
    pass
