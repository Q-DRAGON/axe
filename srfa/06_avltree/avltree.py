"""
本次作业是 avltree 相关的题目
需要注意的是 树和图 是最困难的两块数据结构，请务必认真对待
这样才能掌握好真正有用的算法知识

你需要实现下面三个接口，但是为了实现 avl 的平衡，你需要写一些辅助操作
这个知识理解起来有一定困难性，请多和人讨论
如果无法掌握这个知识，那么图的知识也没可能了

insert
find
remove


有问题多讨论！
自己想出解法是基本没有意义的，最重要的是把这道题的解法过一遍有个印象
想着独创的人最终都学得不太好，因为抓不住重点
我会把一些我认为难的题目直接写出解题思路，不要自己强行硬刚不看思路
"""
import math


numbers = []


class TreeNode(object):
    def __init__(self, n):
        self.value = n
        self.parent = None
        self.left = None
        self.right = None
        self.height = 0

    def inorder_tree_walk(self, x):
        if x is not None:
            self.inorder_tree_walk(x.left)
            numbers.append(x.value)
            self.inorder_tree_walk(x.right)


class AVLTree(object):
    def __init__(self):
        self.size = 0
        self.root = None

    def update_height(self, root):
        maxnum = max(self.get_height(root.left), self.get_height(root.right))
        root.height = 1 + maxnum

    def get_height(self, x):
        if x is None:
            return 0
        else:
            return x.height

    def get_balance(self, root):
        if root is None:
            return 0
        else:
            return self.get_height(root.left) - self.get_height(root.right)

    def left_rotate(self, someTree):
        y = someTree.right
        y_left = y.left
        y.left = someTree
        someTree.right = y_left
        someTree.height = 1 + max(self.get_height(someTree.left), self.get_height(someTree.right))
        y.height = 1 + max(self.get_height(y.left), self.get_height(y.right))
        return y

    def right_rotate(self, someTree):
        y = someTree.left
        y_right = y.right
        y.right = someTree
        someTree.left = y_right
        someTree.height = 1 + max(self.get_height(someTree.left),
                        self.get_height(someTree.right))
        y.height = 1 + max(self.get_height(y.left),
                        self.get_height(y.right))
        return y

    def insert(self, root, key):
        if root is None:
            return TreeNode(key)
        elif key < root.value:
            root.left = self.insert(root.left, key)
        else:
            root.right = self.insert(root.right, key)
        # 更新当前父节点高度
        self.update_height(root)
        # 判断左右差别
        balance = self.get_balance(root)
        # 判断不平衡的类别
        if balance > 1 and key < root.left.value:
            return self.right_rotate(root)
        if balance < -1 and key > root.right.value:
            return self.left_rotate(root)
        if balance > 1 and key > root.left.value:
            root.left = self.left_rotate(root.left)
            return self.right_rotate(root)
        if balance < -1 and key < root.right.value:
            root.right = self.right_rotate(root.right)
            return self.left_rotate(root)
        return root

    def find(self, root, key):
        root_value = root.value
        if key < root_value:
            if root.left is None:
                return False
            else:
                self.find(root.left, key)
        if key > root_value:
            if root.right is None:
                return False
            else:
                self.find(root.right, key)
        return True
