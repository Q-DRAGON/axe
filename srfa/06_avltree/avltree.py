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
Class TreeNode:
    def __init__(n):
        self.value = n
        self.parent = None
        self.left = None
        self.right = None


Class AVLTree:
    def __init__():
        self.size = 0
        self.root = None
