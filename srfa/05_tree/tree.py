"""
本次作业是 tree 相关的题目和 stack queue 相关的应用题目

有问题多讨论！
自己想出解法是基本没有意义的，最重要的是把这道题的解法过一遍有个印象
想着独创的人最终都学得不太好，因为抓不住重点
我会把一些我认为难的题目直接写出解题思路，不要自己强行硬刚不看思路

本次使用下面的结构，和 List 一样是只有节点没有主类
你应该写几个辅助函数方便你写代码和测试
具体哪些辅助函数，不懂就问
"""
from queue import Queue


numbers = []


class Stack(object):
    def __init__(self):
        self.data = []

    def push(self, x):
        self.data.append(x)

    def pop(self):
        return self.data.pop()

    def length(self):
        return len(self.data)

    def last(self):
        return self.data[-1]


class TreeNode:
    def __init__(self, n):
        self.value = n
        self.left = None
        self.right = None

    # 1, 用递归实现二叉树的中序遍历算法
    def inorder_tree_walk(self, x):
        if x is not None:
            self.inorder_tree_walk(x.left)
            numbers.append(x.value)
            self.inorder_tree_walk(x.right)

    # 2, 用递归实现二叉树的后序遍历算法
    def backorder_tree_walk(self, x):
        if x is not None:
            self.backorder_tree_walk(x.left)
            self.backorder_tree_walk(x.right)
            numbers.append(x.value)

    # 3, 用递归实现二叉树的前序遍历算法
    def preorder_tree_walk(self, x):
        if x is not None:
            numbers.append(x.value)
            self.preorder_tree_walk(x.left)
            self.preorder_tree_walk(x.right)

    # 4, 用队列实现广度优先算法，注明时空复杂度
    # 时间复杂度 O(n)，空间复杂度 O(n)
    def broad_first(self, tree, x):
        q = Queue()
        if tree is not None:
            q.put(tree)
        while not q.empty():
            a = q.get()
            if a.left is not None:
                q.put(a.left)
            if a.right is not None:
                q.put(a.right)
            if a.value == x:
                return True
        return False

    # 5, 用栈实现深度优先算法，注明时空复杂度
    # 时间复杂度 O(n)，空间复杂度 O(lgn)
    def depth_first(self, tree, x):
        s = Stack()
        if tree is not None:
            s.push(tree)
        while s.length() != 0:
            a = s.pop()
            if a.value == x:
                return True
            elif a.left is not None:
                s.push(a.left)
            elif a.right is not None:
                s.push(a.right)
        return False

    # 6, 用非递归算法实现二叉树的中序遍历
    def inorder_tree_walk2(self):
        container = Stack()
        tree = self
        container.push(tree)
        while container.length() != 0:
            tree = container.pop()
            if tree.left is not None:
                left = tree.left
                tree.left = None
                container.push(tree)
                container.push(left)
            elif tree.right is not None:
                right = tree.right
                tree.right = None
                container.push(right)
                container.push(tree)
            else:
                numbers.append(tree.value)

    # 7, 递归翻转二叉树
    def invert(self, tree):
        if tree is not None:
            tmp = tree.left
            tree.left = self.invert(tree.right)
            tree.right = self.invert(tmp)
        return tree

    # 8, 检查二叉树是否是镜像对称的
    def pair_or_not(self, tree1, tree2):
        numbers.clear()
        tree1.inorder_tree_walk(tree1)
        a = str(numbers)
        numbers.clear()
        tree2 = tree2.invert(tree2)
        tree2.inorder_tree_walk(tree2)
        b = str(numbers)
        return a == b

    # 9, 给定一个二叉树，找出其最大深度
    def max_depth(self, tree):
        if tree is None:
            return 0
        left_depth = tree.max_depth(tree.left)
        right_depth = tree.max_depth(tree.right)

        if left_depth > right_depth:
            return left_depth + 1
        else:
            return right_depth + 1

# 10, 对于一棵有 n 个节点的二叉树, 请设计在 θ(n) 时间内完成先序遍历算法和后序遍历算法
    # θ(n) 的含义是，去除了常数的 O(n), 也就是说 θ(n) 就是确定的 n
    # 在这里意思是一次遍历得到先序和后序的结果
    

# 11, 选做，能否用栈实现广度优先？优势是什么？
