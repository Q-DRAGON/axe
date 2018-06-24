import random
import sort
from stackqueue import *

def test_stack_queue():
    s = Stack()
    s.push(1)
    s.push(2)
    assert str(s.data) == str([1, 2]), 'stack push wrong'
    s.pop()
    assert str(s.data) == str([1]), 'stack pop wrong'

    q = Queue(5)
    q.enqueue(1)
    q.enqueue(2)
    assert str(q.data) == str([1, 2]), 'queue enqueue wrong'
    q.dequeue()
    assert str(q.data) == str([2]), 'queue dequeue wrong'


def test_stack2():
    s = Stack2(6)
    s.push1(1)
    x1 = s.pop1()

    s.push2(1)
    s.push2(2)
    x2 = s.pop2()

    x3 = s.pop1()

    assert str(x1) == str(1), 'stack2 failed, 1'
    assert str(x2) == str(2), 'stack2 failed, 2'
    assert str(x3) == str(None), 'stack2 failed, 3'


def test_queue2():
    q = Queue2()
    q.enqueue(1)
    q.enqueue(2)
    a1 = q.dequeue()
    assert str(a1) == str(1), 'queue2 wrong 1'
    a2 = q.dequeue()
    assert str(a2) == str(2), 'queue2 wrong 2'
    q.enqueue(3)
    a3 = q.dequeue()
    assert str(a3) == str(3), 'queue2 wrong 3'


def test_stack3():
    s = Stack3()
    s.push(1)
    x1 = s.pop()

    s.push(1)
    s.push(2)
    x2 = s.pop()

    x3 = s.pop()

    assert str(x1) == str(1), 'stack3 failed, 1'
    assert str(x2) == str(2), 'stack3 failed, 2'
    assert str(x3) == str(1), 'stack3 failed, 3'


if __name__ == '__main__':
    test()
