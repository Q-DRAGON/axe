import random
from linkedlist2 import *


def init_list():
    x1 = ListNode(1)
    x2 = ListNode(2)
    x3 = ListNode(3)
    x1.next = x2
    x2.next = x3
    return x1


def test_rearrange():
    a1 = init_list()
    a2 = rearrange(a1, 2)
    assert str(2) == str(kth_node(a2, 2).value), 'test_rearrange failed 1'
    assert str(1) == str(kth_node(a2, 1).value), 'test_rearrange failed 2'
    assert str(3) == str(kth_node(a2, 3).value), 'test_rearrange failed 3'


def test_circle_head():
    a1 = init_list()
    assert str(None) == str(circle_head(a1)), 'circle_head failed 1'
    append(a1, 2)
    assert str(None) == str(circle_head(a1)), 'circle_head failed 2'
    last_node(a1).next = a1
    assert str(1) == str(circle_head(a1).value), 'circle_head failed 3'


def test_reorder():
    a1 = init_list()
    append(a1, 4)
    append(a1, 5)
    a = reorder(a1)
    assert str(1) == str(kth_node(a, 1).value), 'reorder failed 1'
    assert str(5) == str(kth_node(a, 3).value), 'reorder failed 2'
    assert str(4) == str(kth_node(a, 5).value), 'reorder failed 3'


def test_rotate_list():
    a1 = init_list()
    a2 = rotate_list(a1, 1)
    assert str(3) == str(kth_node(a2, 1).value), 'rotate_list failed 1'
    assert str(1) == str(kth_node(a2, 2).value), 'rotate_list failed 2'
    assert str(2) == str(kth_node(a2, 3).value), 'rotate_list failed 3'


def test_sort_list():
    a1 = init_list()
    a2 = sort_list(a1)
    assert str(1) == str(kth_node(a2, 1).value), 'sort_list failed 1'
    assert str(2) == str(kth_node(a2, 2).value), 'sort_list failed 2'
    assert str(3) == str(kth_node(a2, 3).value), 'sort_list failed 3'


def test_reverse_mn():
    a1 = init_list()
    a2 = reverse_mn(a1, 2, 3)
    assert str(1) == str(kth_node(a2, 1).value), 'reverse_mn failed 1'
    assert str(3) == str(kth_node(a2, 2).value), 'reverse_mn failed 2'
    assert str(2) == str(kth_node(a2, 3).value), 'reverse_mn failed 3'


def test_deduplication():
    a1 = init_list()
    append(a1, 3)
    a2 = deduplication(a1)
    assert str(1) == str(kth_node(a2, 1).value), 'deduplication failed 1'
    assert str(3) == str(kth_node(a2, 3).value), 'deduplication failed 2'
    assert str(3) == str(length(a2)), 'deduplication failed 3'


def test_add_number():
    a1 = init_list()
    a2 = init_list()
    a3 = add_number(a1, a2)
    assert str(2) == str(kth_node(a3, 1).value), 'add_number failed 1'
    assert str(4) == str(kth_node(a3, 2).value), 'add_number failed 2'
    assert str(6) == str(kth_node(a3, 3).value), 'add_number failed 3'


def test_merge_list_k():
    a1 = init_list()
    a2 = init_list()
    a3 = init_list()
    a4 = merge_list_k(a1, a2, a3)
    assert str(1) == str(kth_node(a4, 1).value), 'merge_list_k failed 1'
    assert str(2) == str(kth_node(a4, 4).value), 'merge_list_k failed 2'
    assert str(3) == str(kth_node(a4, 7).value), 'merge_list_k failed 3'


def test_reverse_list_k():
    a1 = init_list()
    assert str(2) == str(kth_node(reverse_list_k(a1, 2), 1).value), 'reverse_list_k failed 1'
    assert str(1) == str(kth_node(reverse_list_k(a1, 2), 2).value), 'reverse_list_k failed 2'
    assert str(3) == str(kth_node(reverse_list_k(a1, 3), 1).value), 'reverse_list_k failed 3'


if __name__ == '__main__':
    test()
