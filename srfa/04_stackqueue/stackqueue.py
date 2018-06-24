"""
本次作业是 stack queue 相关的初步题目，下次是高级题目
这些题目得用 OOP 的方式做

最重要的一点：
有问题多讨论！
自己想出解法是基本没有意义的，最重要的是把这道题的解法过一遍有个印象
想着独创的人最终都学得不太好，因为抓不住重点
我会把一些我认为难的题目直接写出解题思路，不要自己强行硬刚不看思路

由于 s q 的实现都很简单大家可以不用浪费时间，内部用 list 外面暴露相应的接口就好
"""
# 1, 给 Queue 增加一个 capacity 参数表示队列的容量，让 enqueue 和 dequeue 能处理队列的下溢和上溢
class Stack(object):
    def __init__(self):
        self.data = []

    def push(self, x):
        self.data.append(x)

    def pop(self):
        n = len(self.data) - 1
        a = self.data[n]
        del self.data[n]
        return a

    def length(self):
        return len(self.data)


class Queue(object):
    def __init__(self, n):
        self.data = []
        self.capacity = n

    def enqueue(self, x):
        if len(self.data) < self.capacity:
            self.data.append(x)
        else:
            print('Queue Overflow')

    def dequeue(self):
        if len(self.data) > 0:
            n = self.data[0]
            del self.data[0]
            return n
        else:
            print('Nothing in Queue')

    def length(self):
        return len(self.data)


# 2, 实现如下接口
# s = Stack2(n)
# s.push1
# s.pop1
# s.push2
# s.pop2

# s 包含 2 个 stack
# 内部是用一个长度为 n 的数组实现的
# 2 个 stack 个数之和不为 n 时, 两者都不会出错
# 要求 push 和 pop 的时间复杂度都是 O(1)
class Stack2(object):
    def __init__(self, n):
        self.data = [None] * n
        self.size = n
        self.len1 = 0
        self.len2 = 0

    def push1(self, x):
        if self.len1 + self.len2 < self.size:
            self.data[self.len1] = x
            self.len1 += 1
        else:
            print("Overflow")

    def pop1(self):
        if self.len1 > 0:
            self.len1 -= 1
            x = self.data[self.len1]
            return x
        else:
            return None

    def push2(self, x):
        if self.len1 + self.len2 < self.size:
            self.data[self.size - self.len2 - 1] = x
            self.len2 += 1
        else:
            print("Overflow")

    def pop2(self):
        if self.len2 > 0:
            x = self.data[self.size - self.len2]
            self.len2 -= 1
            return x
        else:
            return None


# 3, 用两个 stack 实现一个 queue, 并分析 dequeue 和 enqueue 的时间复杂度
class Queue2(object):
    def __init__(self):
        self.stack1 = Stack()
        self.stack2 = Stack()

    def enqueue(self, x):
        self.stack1.push(x)

    def dequeue(self):
        len1 = self.stack1.length()
        len2 = self.stack2.length()
        if len1 == 0 and len2 == 0:
            print('Empty Queue')
        elif len2 == 0:
            for i in range(len1):
                a = self.stack1.pop()
                self.stack2.push(a)
        return self.stack2.pop()

# dequeue 的时间复杂度为 O(n)， enqueue 的时间复杂度为 O(1)。

# 4, 用两个 queue 实现一个 stack, 并分析 push 和 pop 的时间复杂度
class Stack3(object):
    def __init__(self):
        self.q1 = Queue(5)
        self.q2 = Queue(5)

    def push(self, x):
        self.q1.enqueue(x)

    def pop(self):
        len1 = self.q1.length()
        for i in range(len1 - 1):
            a = self.q1.dequeue()
            self.q2.enqueue(a)
        result = self.q1.dequeue()
        self.q1, self.q2 = self.q2, self.q1
        return result

# pop 的时间复杂度为 O(n)， push 的时间复杂度为 O(1)。

# 5, 双端队列(deque)是一种插入和删除都可以在两端进行的数据结构,
# 写出 4 个时间复杂度均为 O(1) 的函数
# 分别实现双端队列的两端插入和删除的操作
# 该队列是用一个数组实现的
# deque.push_front
# deque.pop_front
# deque.push_back
# deque.pop_back


# 6, 实现 StackSet, 它内部由多个容量为 3 的 stack 组成, 并且在前一个栈填满时新建一个 stack
# 接口如下
# s = StackSet(n)
# s.push
# s.pop


# 7, 为 StackSet 添加一个 pop_from(index) 方法
# index 是指定的子栈下标


# 8, 设计一个符合下面复杂度的栈
# push    O(1)
# pop     O(1)
# min     O(1) 返回栈中的最小元素


# 9, 给定一个字符串其中包含无数个圆括号和其他字符，使用栈来确定圆括号是匹配的
# 本题不理解题意的话要在 slack、群 中问清楚


# 10, 给定一个字符串其中包含无数个圆括号、方括号和其他字符，使用栈来确定圆括号和方括号是匹配的
# 本题不理解题意的话要在 slack、群 中问清楚
