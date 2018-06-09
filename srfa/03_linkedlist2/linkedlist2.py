from linkedlist1 import *
from sort import *


class ListNode:
    def __init__(self, x):
        self.value = x
        self.next = None


def rearrange(node, x):
    # 1
    # 给一个单链表和一个值 x, 对它进行分割, 使得所有小于 x 的节点都在节点大于或等于 x 之前,
    a = []
    b = []
    for i in range(length(node)):
        k = kth_node(node, i + 1).value
        if k < x:
            a.append(k)
        if k > x:
            b.append(k)
    node0 = ListNode(a[0])
    for i in range(len(a) - 1):
        append(node0, a[i + 1])
    if has_x(node, x):
        append(node0, x)
    for i in range(len(b)):
        append(node0, b[i])
    return node0


def circle_head(node):
    # 2
    # 给一个链表, 返回环形链表中环形开始的节点, 如果没有环形, 返回 None
    if is_circle(node):
        return node
    else:
        return None


def reorder(node):
    # 3
    # 给一个链表, 将原链表 L0 -> L1 -> L2 -> ... -> Ln-1 -> ln 排序为
    # L0 -> L1 -> Ln -> L2 -> Ln-1 -> ...
    # 要求: 不能修改节点的值
    newnode = ListNode(node.value)
    i = 1
    node = delete_n(node, 1)
    while node.next is not None:
        if i == 1:
            append(newnode, node.value)
            node = delete_n(node, 1)
        elif i == -1:
            append(newnode, last_node(node).value)
            node = delete_n(node, length(node))
        i *= -1
    append(newnode, node.value)
    return newnode


def rotate_list(node, k):
    # 4
    # 给一个链表, 将列表向右旋转 k 个下标, 其中 k 是非负数
    # 例子:
    #     Input: 1->2->3->4->5->NULL, k = 2
    #     Output: 4->5->1->2->3->NULL
    #     Input: 0->1->2->NULL, k = 4
    #     Output: 2->0->1->NULL
    len = length(node)
    m = k % len
    qian = len - m
    start = qian + 1
    nn = ListNode(kth_node(node, start).value)
    start += 1
    while start <= len:
        append(nn, kth_node(node, start).value)
        start += 1
    i = 1
    while i <= qian:
        append(nn, kth_node(node, i).value)
        i += 1
    return nn


def sort_list(node):
    # 5
    #     给一个链表, 将链表排序
    #     要求: 时间复杂度为 O(n log n)
    a = []
    nn = ListNode(node.value)
    while node.next is not None:
        a.append(node.value)
        node = node.next
    a.append(last_node(node).value)
    quick(a, 1, len(a))
    for i in range(1, len(a)):
        append(nn, a[i])
    return nn


def reverse_node(node):
    a = []
    while node.next is not None:
        a.append(node.value)
        node = node.next
    a.append(last_node(node).value)
    b = a.reverse()
    nn = ListNode(b[0])
    for i in range(1, len(b)):
        append(nn, b[i])


def nodetolist(node):
    a = []
    while node.next is not None:
        a.append(node.value)
        node = node.next
    a.append(last_node(node).value)
    return a


def listtonode(list):
    nn = ListNode(list[0])
    for i in range(1, len(list)):
        append(nn, list[i])
    return nn


def reverse_mn(node, m, n):
    # 6
    # 给一个单链表和正整数 m, n(m < n), 从 m 到 n 开始反转
    a = nodetolist(node)
    a1 = a[:m - 1]
    if n + 1 < len(a):
        a3 = a[n + 1:]
    else:
        a3 = []
    a2 = a[m - 1: n]
    a2.reverse()
    if len(a3) == 0:
        a1.extend(a2)
    else:
        a1.extend(a2).extend(a3)
    mn = listtonode(a1)
    return mn


def deduplication(node):
    # 7
    # 给一个有序的单链表, 删除所有有重复 value 的节点, 只留下原始列表中不同的 value
    a = [node.value]
    for i in range(1, length(node)):
        if kth_node(node, i + 1).value in a:
            delete_n(node, i + 1)
        else:
            a.append(kth_node(node, i + 1).value)
    return node


def add_number(a, b):
    # 8
    # 给两个非空且长度不一定相同的单链表, 表示两个非负整数
    # 数字以相反的顺序存储(个位在前), 每个节点都包含一个 value, 将两个 value 相加并返回链表
    alist = nodetolist(a)
    blist = nodetolist(b)
    c = []
    if len(alist) < len(blist):
        for i in range(len(alist)):
            c.append(a[i] + b[i])
        for i in range(len(alist), len(blist)):
            c.append(blist[i])
    else:
        for i in range(len(blist)):
            c.append(alist[i] + blist[i])
        for i in range(len(blist), len(alist)):
            c.append(alist[i])
    for i in range(len(c) - 1):
        if c[i] >= 10:
            c[i] -= 10
            c[i + 1] += 1
    return listtonode(c)


def merge_list_k(*args):
    # 9
    # 合并 k 个有序链表并保证有序，要求时间复杂度最优，不会就讨论，乱写没价值
    # args 是一个包含 k 个链表的数组
    k = args
    if len(k) < 2:
        return k[0]
    else:
        n = merge_list(k[0], k[1])
    for i in range(2, len(k)):
        n = merge_list(n, k[i])
    return n


def reverse_list_k(node, k):
    # 10
    # k 个一组反转链表(25)
    #     给一个链表, 以每 k 个为一组来翻转链表
    #     例子:
    #         Given this linked list: 1->2->3->4->5
    #
    #         k = 2, return: 2->1->4->3->5
    #
    #         k = 3, return: 3->2->1->4->5
    m = 1
    n = m + k - 1
    while n <= length(node):
        node1 = reverse_mn(node, m, n)
        m = m + k
        n = n + k
    return node1
