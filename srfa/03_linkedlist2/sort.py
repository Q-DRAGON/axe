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
heapsize = 0


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
        for j in range(i + 1, len(a)):
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


def heap_left(i):
    return 2 * i


def heap_right(i):
    return 2 * i + 1


def max_heapify(a, i):
    # 使列表 a 的 i 结点起的子树符合最大堆
    l = heap_left(i)
    r = heap_right(i)
    if l < heapsize and a[l] > a[i]:
        largest = l
    else:
        largest = i
    if r < len(a):
        if r < heapsize and a[r] > a[largest]:
            largest = r
    if largest != i:
        temp = a[i]
        a[i] = a[largest]
        a[largest] = temp
        max_heapify(a, largest)


def build_max_heap(a):
    # 将数组 a 转成最大堆
    global heapsize
    heapsize = len(a)
    for i in range(int((len(a) - 1) / 2), -1, -1):
        max_heapify(a, i)


def heap(a):
    # 利用最大堆方法进行数组排序
    global heapsize
    build_max_heap(a)
    # print('avdadv', a)
    for i in range(int(len(a)) - 1, -1, -1):
        temp = a[0]
        a[0] = a[i]
        a[i] = temp
        heapsize = heapsize - 1
        max_heapify(a, 0)


def partition(a, p, r):
    x = a[r - 1]
    i = p - 1
    for j in range(p, r):
        if a[j - 1] <= x:
            i = i + 1
            a[i - 1], a[j - 1] = a[j - 1], a[i - 1]
    a[i], a[r - 1] = a[r - 1], a[i]
    return i + 1


def quick(a, p, r):
    if p < r:
        q = partition(a, p, r)
        quick(a, p, q - 1)
        quick(a, p + 1, r)
