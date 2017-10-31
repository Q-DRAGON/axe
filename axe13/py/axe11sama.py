class Func(object):
    def __init__(self, func_name):
        super(Func, self).__init__()
        d = {
            '+': self.add_list,
            '-': self.sub_list,
            '*': self.mul_list,
            '/': self.div_list,
            '%': self.mod,
            '=': self.eq,
            '!': self.neq,
            '>': self.gt,
            '<': self.lt,
            'log': self.log,
            'if': self.cond,
        }
        self.f = d.get(func_name)

    def __call__(self, *args, **kwargs):
        return self.f(*args, **kwargs)

    def add_list(self, elements):
        l = self.eval(elements)
        return sum(l)

    def sub_list(self, elements):
        l = self.eval(elements)
        return l[0] - self.add_list(l[1:])

    def mul_list(self, elements):
        l = self.eval(elements)
        mul = 1
        for e in l:
            mul *= e
        return mul

    def div_list(self, elements):
        l = self.eval(elements)
        return l[0] / self.mul_list(l[1:])

    def mod(self, elements):
        l = self.eval(elements)
        return l[0] % self.mul_list(l[1:])

    def eq(self, elements):
        l = self.eval(elements)
        return l[0] == l[1]

    def neq(self, elements):
        return not self.eq(elements)

    def gt(self, elements):
        l = self.eval(elements)
        return l[0] > l[1]

    def lt(self, elements):
        l = self.eval(elements)
        return l[0] < l[1]

    @staticmethod
    def log(elements):
        print(*elements)

    @staticmethod
    def cond(elements):
        # print(elements)
        if elements[0]:
            return apply_ast(elements[1])
        else:
            return apply_ast(elements[2])

    @staticmethod
    def eval(args):
        l = []
        for i in args:
            if isinstance(i, list):
                l.append(apply_ast(i))
            else:
                l.append(i)
        return l


def find_last(array, x):
    array = array[::-1]
    for i, e in enumerate(array):
        if e == x:
            return len(array) - i - 1
    return -1


def ast_from_tokens(tokens):
    l = []
    for i in tokens:
        l.append(i)
        if i == ']':
            start = find_last(l, '[')
            l_right = l[start + 1: -1]
            l = l[:start]
            if len(l) == 0:
                l = l_right
            else:
                l.append(l_right)
    return l


def parse_element(element):
    if element[0] == element[-1] == '"':
        element = element[1: -1]
        # 支持转义
        element = element.replace(r'\"', '\"')
        element = element.replace(r'\t', '\t')
        element = element.replace(r'\n', '\n')
    elif element.isdigit():
        element = int(element)
    elif element in ['yes', 'no']:
        element = element == 'yes'
    return element


def code_tokens(code):
    separator = ['[', ']']
    comment_sign = ';'
    is_commented = False
    tokens = []
    length = len(code)

    for i, e in enumerate(code):
        if e == '\n':
            is_commented = False
        if e == comment_sign:
            is_commented = True
        if is_commented:
            continue
        if e in separator:
            tokens.append(e)
            start = i + 1
            end = start
            while end < length and code[end] not in separator and code[end] != comment_sign:
                end += 1
            expression = code[start: end]
            expression = expression.strip()
            if len(expression) > 0:
                token_exp = expression.split(' ')
                token_exp = [parse_element(i) for i in token_exp]
                tokens.extend(token_exp)
    return tokens


def apply_ast(ast):
    if isinstance(ast, list):
        op, *args = ast
        f = Func(op)
        return f(args)
    else:
        return ast


def apply(code):
    tokens = code_tokens(code)
    print('tokens', tokens)
    ast = ast_from_tokens(tokens)
    print(ast)
    return apply_ast(ast)


def ensure(condition, message):
    if not condition:
        print('测试失败：', message)


def test_apply():
    s1 = r'''
[+ 1 2]         ; 表达式的值是 3
'''
    ensure(apply(s1) == 3, 'test apply 1')

    s2 = r'''
[* 2 3 4]       ; 表达式的值是 24
'''
    ensure(apply(s2) == 24, 'test apply 2')

    s3 = r'''
[log "hello"]   ; 输出 hello, 表达式的值是 null(关键字 表示空)
'''
    ensure(apply(s3) is None, 'test apply 3')

    s4 = r'''
[+ 1 [- 2 3]]   ; 表达式的值是 0, 相当于普通语法的 1 + (2 - 3)
'''
    ensure(apply(s4) == 0, 'test apply 4')

    s5 = r'''
[if [> 2 1] 3 4]; 表达式的值是 3
'''
    ensure(apply(s5) == 3, 'test apply 5')

    s6 = r'''
[if yes
    [log "成功"]
    [log "没成功"]
]
'''
    ensure(apply(s6) is None, 'test apply 6')


def test():
    test_apply()


def main():
    test()


if __name__ == '__main__':
    main()
