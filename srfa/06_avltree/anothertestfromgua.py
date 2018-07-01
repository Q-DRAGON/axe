from graphviz import Digraph
from random import randrange

from avl import AVL


"""
mac 上要装 graphviz
一个 brew 一个 py 库

brew install graphviz
pip3 install graphviz
"""


def draw_tree(node, dot):
    n = node
    if n is None:
        return
    nv = n.value
    nname = '{}'.format(nv)
    if n.left:
        v = n.left.value
        name = '{}'.format(v)
        dot.node(name, name)
        # dot.edge(nname, name, )
        dot.edge(nname, name, arrowhead='none')
        # dot.edge(nname, name, constraint='false')
        draw_tree(n.left, dot)
    else:
        name = '{}{}'.format(nname, 'left')
        dot.node(name, name, style='invis')
        # dot.edge(nname, name)
        dot.edge(nname, name, style='invis')
    if n.right:
        v = n.right.value
        name = '{}'.format(v)
        dot.node(name, name)
        dot.edge(nname, name, arrowhead='none')
        draw_tree(n.right, dot)
    else:
        name = '{}{}'.format(nname, 'right')
        dot.node(name, name, style='invis')
        # dot.edge(nname, name)
        dot.edge(nname, name, style='invis')


def test():
    arr = [randrange(11111) for i in range(11130)]
    # arr = [i for i in range(20)]
    # arr = [3, 1, 2, 4]
    avl = AVL(arr)
    # avl.delete(2)
    l = avl.traversal()
    print('init', str(l))
    for n in arr:
        # print('delete ', n)
        avl.delete(n)
        # break
    print('deleted', avl.traversal())
    #
    dot = Digraph(comment='bst')
    # 默认是 pdf
    dot.format = 'png'
    #
    n = avl.root
    v = n.value
    name = '{}'.format(v)
    dot.node(name, name)
    draw_tree(n, dot)
    # dot.render('draw/avl.gv', view=True)



def traversal():
    # a = [i for i in range(20)]
    # a = [randrange(11111) for i in range(1230)]
    a = [3, 1, 2]
    avl = AVL(a)
    l = avl.traversal()
    print(str(l))


if __name__ == '__main__':
    # traversal()
    test()
