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


def test_deque():
    d = Deque()
    d.push_front(1)
    d.push_front(2)
    assert str(d.data) == str([2, 1]), 'deque failed 1'
    d.push_back(3)
    assert str(d.data) == str([2, 1, 3]), 'deque failed 2'
    d.pop_front()
    assert str(d.data) == str([1, 3]), 'deque failed 3'
    d.pop_back()
    assert str(d.data) == str([1]), 'deque failed 4'


def test_stackset():
    s = StackSet()
    s.push(1)
    x1 = s.pop()

    s.push(1)
    s.push(2)
    x2 = s.pop()

    x3 = s.pop()

    assert str(x1) == str(1), 'stackset failed, 1'
    assert str(x2) == str(2), 'stackset failed, 2'
    assert str(x3) == str(1), 'stackset failed, 3'


def test_pop_from():
    s = StackSet()
    s.push(1)
    s.push(2)
    s.push(3)
    s.push(4)
    assert str(s.pop_from(0)) == str(3), 'popfrom failed, 1'
    assert str(s.pop_from(0)) == str(2), 'popfrom failed, 2'
    assert str(s.pop_from(1)) == str(4), 'popfrom failed, 3'


def test_stack4():
    s = Stack4()
    s.push(1)
    assert str(s.min()) == str(1), 'stack4 failed, 1'
    s.push(2)
    s.push(3)
    assert str(s.min()) == str(1), str(s.min())+'stack4 failed, 2'
    s.push(0)
    assert str(s.min()) == str(0), 'stack4 failed, 4'


def test_bracket_suit():
    a = '(a + b * (c % (d / w)))'
    assert str(bracket_suit(a)) == str(True), 'bracket_suit failed 1'
    b = '(a + b * (c % (d / w))'
    assert str(bracket_suit(b)) == str(False), 'bracket_suit failed 2'


def test_bracket_both_suit():
    a = '(a + b * (c % [d / w]))'
    assert str(bracket_both_suit(a)) == str(True), 'bracket_both_suit failed 1'
    b = '(a + b * [c % (d / w)))'
    assert str(bracket_both_suit(b)) == str(False), 'bracket_both_suit failed 2'
    c = '([)]'
    assert str(bracket_both_suit(c)) == str(False), 'bracket_both_suit failed 3'

if __name__ == '__main__':
    test()
