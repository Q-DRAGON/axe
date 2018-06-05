import random
from linkedlist1 import *


def init_list():
    x1 = ListNode(1)
    x2 = ListNode(2)
    x3 = ListNode(3)
    x1.next = x2
    x2.next = x3
    return x1


def test_length():
    a1 = init_list()
    assert str(3) == str(length(a1)), 'length failed 1'
    append(a1, 4)
    assert str(4) == str(length(a1)), 'length failed 2'
    append(a1, 5)
    assert str(5) == str(length(a1)), 'length failed 3'


def test_last_node():
    a1 = init_list()
    assert str(3) == str(last_node(a1).value), 'last_node failed 1'
    append(a1, 4)
    assert str(4) == str(last_node(a1).value), 'last_node failed 2'
    append(a1, 5)
    assert str(5) == str(last_node(a1).value), 'last_node failed 3'


def test_kth_node():
    a1 = init_list()
    assert str(1) == str(kth_node(a1, 1).value), 'kth_node failed 1'
    assert str(2) == str(kth_node(a1, 2).value), 'kth_node failed 2'
    assert str(3) == str(kth_node(a1, 3).value), 'kth_node failed 3'


def test_n_last():
    a1 = init_list()
    assert str(1) == str(n_last(a1, 3).value), 'n_last failed 1'
    assert str(2) == str(n_last(a1, 2).value), 'n_last failed 2'
    assert str(3) == str(n_last(a1, 1).value), 'n_last failed 3'


def test_has_x():
    a1 = init_list()
    assert str(True) == str(has_x(a1, 3)), 'has_x failed 1'
    assert str(True) == str(has_x(a1, 1)), 'has_x failed 2'
    assert str(False) == str(has_x(a1, 4)), 'has_x failed 3'


def test_middle():
    a1 = init_list()
    assert str(2) == str(middle(a1).value), 'middle failed 1'
    append(a1, 4)
    assert str(None) == str(middle(a1)), 'middle failed 2'
    append(a1, 5)
    assert str(3) == str(middle(a1).value), 'middle failed 3'


def test_append():
    a1 = init_list()
    assert str(3) == str(last_node(a1).value), 'append failed 1'
    append(a1, 4)
    assert str(4) == str(last_node(a1).value), 'append failed 2'
    append(a1, 5)
    assert str(5) == str(last_node(a1).value), 'append failed 3'


def test_prepend():
    a1 = init_list()
    a1 = prepend(a1, 4)
    assert str(4) == str(a1.value), 'prepend failed 1'
    a1 = prepend(a1, 5)
    assert str(5) == str(a1.value), 'prepend failed 2'
    a1 = prepend(a1, 6)
    assert str(6) == str(a1.value), 'prepend failed 3'


def test_insert_after():
    a1 = init_list()
    insert_after(a1, 3, 4)
    assert str(4) == str(kth_node(a1, 4).value), 'insert_after failed 1'
    insert_after(a1, 2, 5)
    assert str(5) == str(kth_node(a1, 3).value), 'insert_after failed 1'
    insert_after(a1, 1, 6)
    assert str(6) == str(kth_node(a1, 2).value), 'insert_after failed 1'


def test_insert_last_n():
    a1 = init_list()
    a2 = insert_last_n(a1, 1, 4)
    assert str(4) == str(kth_node(a2, 3).value), 'insert_last_n failed 1'
    a3 = insert_last_n(a2, 2, 5)
    assert str(5) == str(kth_node(a3, 3).value), 'insert_last_n failed 2'
    a4 = insert_last_n(a3, 5, 6)
    assert str(6) == str(kth_node(a4, 1).value), 'insert_last_n failed 3'


def test_delete_n():
    a1 = init_list()
    a2 = delete_n(a1, 3)
    assert str(2) == str(length(a2)), 'delete_n failed 1'
    a3 = delete_n(a2, 2)
    assert str(1) == str(length(a3)), 'delete_n failed 2'
    a4 = delete_n(a3, 1)
    assert str(0) == str(length(a4)), 'delete_n failed 3'


def test_delete_x():
    a1 = init_list()
    a2 = delete_x(a1, 3)
    assert str(2) == str(length(a2)), 'delete_x failed 1'
    a3 = delete_x(a1, 2)
    assert str(1) == str(length(a3)), 'delete_x failed 2'
    a4 = delete_x(a1, 1)
    assert str(0) == str(length(a4)), 'delete_x failed 3'


def test_delete_last_n():
    a1 = init_list()
    a2 = delete_last_n(a1, 3)
    assert str(2) == str(length(a2)), 'delete_last_n failed 1'
    a3 = delete_last_n(a2, 2)
    assert str(1) == str(length(a3)), 'delete_last_n failed 2'
    a4 = delete_last_n(a3, 1)
    assert str(0) == str(length(a4)), 'delete_last_n failed 3'


if __name__ == '__main__':
    test()
