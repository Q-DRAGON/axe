import random
from avltree import *


def test_avl_insert():
    t = AVLTree()
    t.root = TreeNode(5)

    t.root = t.insert(t.root, 1)
    t.root = t.insert(t.root, 2)
    t.root.inorder_tree_walk(t.root)
    assert str(numbers) == str([1, 2, 5]), 'insert wrong'

    numbers.clear()
    t.root = t.insert(t.root, 3)
    t.root = t.insert(t.root, 4)
    t.root.inorder_tree_walk(t.root)
    assert str(numbers) == str([1, 2, 3, 4, 5]), 'insert 2 wrong'


def test_avl_find():
    t = AVLTree()
    t.root = TreeNode(5)

    t.root = t.insert(t.root, 1)
    t.root = t.insert(t.root, 2)
    assert str(t.find(t.root, 1)) == str(True), 'find wrong'
    assert str(t.find(t.root, 2)) == str(True), 'find 2 wrong'
    assert str(t.find(t.root, 6)) == str(False), 'find 3 wrong'


if __name__ == '__main__':
    test()
