from tree import *


def make_a_tree():
    n1 = TreeNode(6)
    n2 = TreeNode(5)
    n3 = TreeNode(7)
    n4 = TreeNode(2)
    n5 = TreeNode(5)
    n6 = TreeNode(8)

    n1.left = n2
    n1.right = n3
    n2.left = n4
    n2.right = n5
    n3.right = n6

    return n1


def make_a_tree2():
    n1 = TreeNode(6)
    n2 = TreeNode(5)
    n3 = TreeNode(7)
    n4 = TreeNode(2)
    n5 = TreeNode(5)
    n6 = TreeNode(8)

    n1.right = n2
    n1.left = n3
    n2.right = n4
    n2.left = n5
    n3.left = n6

    return n1


def test_inorder_tree_walk():
    tree = make_a_tree()
    tree.inorder_tree_walk(tree)
    assert str(numbers) == str([2, 5, 5, 6, 7, 8]), 'inorder_tree_walk wrong'


def test_backorder_tree_walk():
    numbers.clear()
    tree = make_a_tree()
    tree.backorder_tree_walk(tree)
    assert str(numbers) == str([2, 5, 5, 8, 7, 6]), 'backorder_tree_walk wrong'


def test_preorder_tree_walk():
    numbers.clear()
    tree = make_a_tree()
    tree.preorder_tree_walk(tree)
    assert str(numbers) == str([6, 5, 2, 5, 7, 8]), 'preorder_tree_walk wrong'


def test_broad_first():
    tree = make_a_tree()
    assert str(tree.broad_first(tree, 6)) == str(True), 'test_broad_first wrong 1'
    assert str(tree.broad_first(tree, 5)) == str(True), 'test_broad_first wrong 2'
    assert str(tree.broad_first(tree, 11)) == str(False), 'test_broad_first wrong 3'


def test_depth_first():
    tree = make_a_tree()
    assert str(tree.depth_first(tree, 6)) == str(True), 'test_depth_first wrong 1'
    assert str(tree.depth_first(tree, 5)) == str(True), 'test_depth_first wrong 2'
    assert str(tree.depth_first(tree, 11)) == str(False), 'test_depth_first wrong 3'


def test_inorder_tree_walk2():
    numbers.clear()
    tree = make_a_tree()
    tree.inorder_tree_walk2()
    assert str(numbers) == str([2, 5, 5, 6, 7, 8]), 'inorder_tree_walk2 wrong'


def test_invert():
    numbers.clear()
    tree = make_a_tree()
    tree2 = tree.invert(tree)
    tree2.inorder_tree_walk(tree2)
    assert str(numbers) == str([8, 7, 6, 5, 5, 2]), 'invert wrong'


def test_pair_or_not():
    numbers.clear()
    tree1 = make_a_tree()
    tree2 = make_a_tree2()

    assert str(tree2.pair_or_not(tree1, tree2)) == str(True), 'pair_or_not wrong'


def test_max_depth():
    tree = make_a_tree()
    assert str(tree.max_depth(tree)) == str(3), 'max_depth wrong'


def test_inorder_and_backorder():
    numbers.clear()
    numbers2.clear()
    tree = make_a_tree()
    tree.inorder_and_backorder(tree)
    assert str(numbers) == str([2, 5, 5, 8, 7, 6]), 'inorder_and_backorder-back wrong'
    assert str(numbers2) == str([6, 5, 2, 5, 7, 8]), 'inorder_and_backorder-pre wrong'


if __name__ == '__main__':
    test()
