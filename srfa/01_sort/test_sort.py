# test_sort.py
import random
import sort


"""
需要你自己补全其他几个测试
"""


def random_array():
    a = list(range(8))
    # shuffle works in place and returns None
    random.shuffle(a)
    return a


def test_bubble():
    a = random_array()
    expected = sorted(a)
    sort.bubble(a)
    s = 'bubble failed ({})'.format(a)
    assert str(expected) == str(a), s


def test_insertion():
    a = random_array()
    expected = sorted(a)
    sort.insertion(a)
    s = 'insertion failed ({})'.format(a)
    assert str(expected) == str(a), s


def test_selection():
    a = random_array()
    expected = sorted(a)
    sort.insertion(a)
    s = 'selection failed ({})'.format(a)
    assert str(expected) == str(a), s


# def test():
#     test_bubble()
#     test_insertion()


if __name__ == '__main__':
    test()
