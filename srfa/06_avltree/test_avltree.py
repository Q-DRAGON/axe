import random
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


if __name__ == '__main__':
    test()
