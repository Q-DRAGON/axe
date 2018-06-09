"""
本次作业是链表相关的题目
由于面试和很多地方都不是用的 OOP 方式，所以我们的作业也不是用 OOP（融入 群总是必要的）
这里的 class ListNode 只是定义一个结构
所有的函数都是接受一个 ListNode 作为参数，请注意这一点

例外情况自行处理，这里列出常见例外：
    1，传过来的 node 可能是个 None，但不会是其他类型
测试自行编写，每个函数至少 3 个测试用例


最重要的一点：
有问题多讨论！
自己想出解法是基本没有意义的，最重要的是把这道题的解法过一遍有个印象
想着独创的人最终都学得不太好，因为抓不住重点
我会把一些我认为难的题目直接写出解题思路，不要自己强行硬刚不看思路
"""
import math


class ListNode:
    def __init__(self, x):
        self.value = x
        self.next = None


def length(node):
    # 1, 求单链表中节点的个数
    num = 0
    if node is not None:
        while node.next is not None:
            num += 1
            node = node.next
        num += 1
    return num


def last_node(node):
    # 2, 返回单链表的最后一个节点
    if node is not None:
        while node.next is not None:
            node = node.next
    return node


def kth_node(node, n):
    # 3, 返回单链表第 n 个节点
    count = 1
    if node is not None:
        while count < n:
            node = node.next
            count += 1
    return node


def n_last(node, n):
    # 4, 返回单链表倒数第 n 个节点
    m = length(node) - n + 1
    return kth_node(node, m)


def has_x(node, x):
    # 5, 判断单链表中是否有值为 x 的节点
    if node is not None:
        l = length(node)
        for i in range(l):
            if node.value == x:
                return True
            else:
                node = node.next
    return False


def middle(node):
    # 6, 查找单链表的中间节点, 长度为偶数则返回 None
    if node is not None:
        l = length(node)
        if l % 2 == 0:
            return None
        else:
            return kth_node(node, math.floor(l / 2) + 1)


def append(node, x):
    # 7, 给单链表末尾插入一个元素
    a = last_node(node)
    a.next = ListNode(x)


def prepend(node, x):
    # 8, 给单链表头部插入一个元素
    a = ListNode(x)
    a.next = node
    return a


def insert_after(node, n, x):
    # 9, 给单链表第 n 个节点后插入一个元素
    x1 = kth_node(node, n)
    x2 = x1.next
    a = ListNode(x)
    x1.next = a
    a.next = x2


def insert_last_n(node, n, x):
    # 10, 给单链表倒数第 n 个节点前插入一个元素
    l = length(node)
    a = node
    if n != l:
        insert_after(node, l - n, x)
        return a
    else:
        a = prepend(node, x)
        return a


def delete_n(node, n):
    # 11, 删除单链表第 n 个节点
    if node is not None:
        if n > 1:
            x1 = kth_node(node, n - 1)
            x2 = kth_node(node, n + 1)
            x1.next = x2
        elif n == 1:
            node = node.next
    return node


def delete_x(node, x):
    # 12, 删除单链表中值为 x 的节点
    if node is not None:
        for i in range(length(node)):
            if kth_node(node, i + 1).value == x:
                a = delete_n(node, i + 1)
    return a


def delete_last_n(node, n):
    # 13, 删除单链表倒数第 n 个节点
    return delete_n(node, length(node) - n + 1)


def reverse(node):
    # 14, 返回反转后的单链表
    l = length(node)
    for i in range(int( l / 2)):
        kth_node(node, i + 1).value, kth_node(node, l - i).value = kth_node(node, l - i).value, kth_node(node, i + 1).value
    return node


def is_palindrome(node):
    # 15, 判断一个链表是否是回文链表
    l = length(node)
    for i in range(int( l / 2)):
        if kth_node(node, i + 1).value == kth_node(node, l - i).value:
            return True
    return False


def is_circle(node):
    # 16, 判断一个链表是否是环形链表
    # 本题用双指针, a 一次走一格 b 一次走两格，如果相遇说明有环形
    if node.next is None:
        return False
    if node.next.next is None:
        return False
    a = node.next
    b = node.next.next
    while b is not None:
        if a.value == b.value:
            return True
        elif (b.next is not None) and (b.next.next is not None):
            a = a.next
            b = b.next.next
        else:
            return False
    return False


def copy(node):
    # 17, 返回一个单链表的复制
    l = length(node)
    if node is None:
        return None
    a = ListNode(node.value)
    for i in range(l - 1):
        append(a, kth_node(node, i + 2).value)
    return a


def power_copy(node):
    # 18, 返回一个环形链表的复制
    if node is None:
        return None
    a = ListNode(node.value)
    i = 2
    while kth_node(node, i).next != node:
        append(a, kth_node(node, i).value)
        i += 1
    append(a, kth_node(node, i).value)
    kth_node(a, i).next = a
    return a


def merge_list(node1, node2):
    # 19, 合并两个有序链表并保持有序
    a = []
    for i in range(length(node1)):
        a.append(kth_node(node1, i + 1).value)
    for i in range(length(node2)):
        a.append(kth_node(node1, i + 1).value)
    a.sort()
    node = ListNode(a[0])
    for i in range(1, len(a) - 1):
        append(node, a[i + 1])
    return node


def looplength(node):
    if node is None:
        return 0
    len = 1
    while kth_node(node, len).next != node:
        len += 1
    return len


def joseph_list(node, m):
    # 20, 本题是约瑟夫环问题
    # 1, 2, 3 ..., n 这 n 个数字排成一个圆圈, 所以 node 是一个环形链表的表头
    # 从数字 1 开始每次从这个圆圈里删除第 m 个数字
    # 求出这个圆圈里剩下的最后一个数字
    # 被发红包的人的计数
    count = 0
    length = looplength(node)
    # m 的计数
    loop = 0
    i = -1
    hsbk = []
    dead = 9999
    while count < length:
        i += 1
        i %= length
        num = kth_node(node, i + 1)
        if num.value == dead:
            continue
        else:
            loop += 1
            if loop % m == 0:
                hsbk.append(num.value)
                num.value = dead
                count += 1
    return hsbk[-1]
