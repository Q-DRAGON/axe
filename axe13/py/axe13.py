from enum import Enum


variables = {}


class Type(Enum):
    auto = 0  # auto 就是 n 个特定字符符号, 用来方便写代码的
    colon = 1              # :
    comma = 2              # ,
    braceLeft = 3          # {
    braceRight = 4         # }
    bracketLeft = 5        # [
    bracketRight = 6       # ]
    number = 7             # 169
    string = 8             # "name"
    true = 9               # true
    false = 10             # false
    null = 11              # null
    yes = 12               # yes
    no = 13                # no
    add = 14               # +
    sub = 15               # -
    mul = 16               # *
    div = 17               # /
    mod = 18               # %
    equ = 19               # ==
    noequ = 20             # !=
    more = 21              # >
    less = 22              # <
    log = 23               # log
    choice = 24            # if
    set = 25               # set
    var = 26               # variables


class Token(object):
    def __init__(self, token_type, token_value):
        super(Token, self).__init__()
        # 用表驱动法处理 if
        d = {
            ':': Type.colon,
            ',': Type.comma,
            '{': Type.braceLeft,
            '}': Type.braceRight,
            '[': Type.bracketLeft,
            ']': Type.bracketRight,
            '+': Type.add,
            '-': Type.sub,
            '*': Type.mul,
            '/': Type.div,
            '%': Type.mod,
            '=': Type.equ,
            '!': Type.noequ,
            '>': Type.more,
            '<': Type.less,
            'log': Type.log,
            'true': Type.true,
            'false': Type.false,
            'null': Type.null,
            'yes': Type.yes,
            'no': Type.no,
            'if': Type.choice,
            'set': Type.set
        }
        if token_type == Type.auto:
            self.type = d[token_value]
        else:
            self.type = token_type
        self.value = token_value

    def __repr__(self):
        return '({})'.format(self.value)


def string_end(code, index):
    # 寻找字符串的结尾，并返回字符串和结束字符的下标
    s = ''
    offset = index + 1
    while offset < len(code):
        c = code[offset]
        if c == '"':
            # 找到了字符串的结尾，返回不带引号的字符串
            s = code[index + 1: offset]
            return s, offset
        elif c == '\\':
            # 处理转义符, 现在只支持 \"
            if code[offset + 1] == '"':
                s += '"'
                offset += 2
            elif code[offset + 1] == 't':
                s += '\t'
                offset += 2
            elif code[offset + 1] == 'n':
                s += '\n'
                offset += 2
            elif code[offset + 1] == '\\':
                s += '\\'
                offset += 2
            else:
                # 这是一个错误, 非法转义符
                pass
        else:
            s += c
            offset += 1


def notes_tokens(code, index):
    # 寻找注释的结尾的下一个字符的脚标
    offset = index
    while offset < len(code):
        if code[offset] != '\n':
            offset += 1
        else:
            offset += 1
            break
    return offset


def weather_keyword_token(s):
    # 判断字符串s是否是关键词、变量、运算符，如果都不是，则返回字符串token
    keywords = ['log', 'true', 'false',
                'null', 'yes', 'no', 'if', 'set',
                '+', '-', '*', '/', '%',
                '=', '!', '>', '<']
    if s in keywords:
        t = Token(Type.auto, s)
    elif s[0] != '"':
        # 如果不是字符串，则定义为变量
        t = Token(Type.var, s)
    else:
        t = Token(Type.string, s)
    return t


def json_tokens(code):
    # 把字符串转成tokens
    length = len(code)
    tokens = []
    spaces = [' ', '\n', '\t']
    digits = '1234567890'
    # 当前下标
    i = 0
    start = 0
    while i < length:
        c = code[i]
        if c in digits:
            # 处理数字, 现在不支持小数和负数
            end = 0
            for offset, char in enumerate(code[i:]):
                if char not in digits:
                    end = offset
                    break
            n = int(code[i - 1:i + end])
            i += end
            start = i
            t = Token(Type.number, n)
            tokens.append(t)
        elif c == '"':
            # 处理字符串
            s, offset = string_end(code, i)
            i = offset + 1
            start = i
            t = Token(Type.string, s)
            tokens.append(t)
        elif c == ';':
            # 处理注释
            i = notes_tokens(code, i)
            start = i
        elif c in ['[', ']']:
            # 左右括号加自己，加前面的字符串--如果有
            if start < i:
                s = code[start: i]
                t = weather_keyword_token(s)
                tokens.append(t)
                t = Token(Type.auto, c)
                tokens.append(t)
            else:
                t = Token(Type.auto, c)
                tokens.append(t)
            i += 1
            start = i
        elif c in spaces:
            # 处理空格、回车和tab键，跳过空白键并返回前面的关键词/字符串
            if start < i:
                s = code[start: i]
                t = weather_keyword_token(s)
                tokens.append(t)
            i += 1
            start = i
        else:
            i += 1
    return tokens


def pop_list(stack):
    l = []
    while isinstance(stack[-1], list) or stack[-1].value != '[':
        l.append(stack.pop(-1))
    stack.pop(-1)
    l.reverse()
    return l


def parsed_ast(token_list):
    """
    用栈解析 ast
    """
    l = []
    i = 0
    while i < len(token_list):
        token = token_list[i].value
        if token == ']':
            list_token = pop_list(l)
            l.append(list_token)
        else:
            l.append(token_list[i])
        i += 1
    return l


def accounting(code, vs):
    symbol = {
        '+': apply_sum,
        '-': apply_sub,
        '*': apply_mul,
        '/': apply_div,
        '%': apply_mod,
    }
    l = []
    for i in code:
        if isinstance(i, list):
            i = apply_exp(i, vs)
        elif isinstance(i, Token) and i.type == Type.var:
            i = vs[i.value]
        elif isinstance(i, Token) and i.type == Type.number:
            i = i.value
        l.append(i)
    function_name = symbol[l[0].value]
    return function_name(l[1:])


def compare(code, vs):
    symbol = {
        '=': apply_equal,
        '!': apply_not_equal,
        '>': apply_more,
        '<': apply_less
    }
    function_name = symbol[code[0].value]
    if function_name(code) is True:
        return 'yes'
    else:
        return 'no'


def apply_sum(l):
    return sum(l)


def apply_sub(l):
    return l[0] - sum(l[1:])


def apply_mul(l):
    from functools import reduce
    return reduce(lambda a, b: a * b, l)


def apply_div(l):
    return l[0] / apply_mul(l[1:])


def apply_mod(l):
    return l[0] % l[1]


def apply_equal(code):
    return code[1].value == code[2].value


def apply_not_equal(code):
    return code[1].value != code[2].value


def apply_more(code):
    return code[1].value > code[2].value


def apply_less(code):
    return code[1].value < code[2].value


def apply_log(tokens):
    i = 1
    while i < len(tokens):
        print(tokens[i].value)
        i += 1


def return_exp(exp, vs):
    # 如果expression是字符则返回自己的值,如果是list则解析
    if isinstance(exp, list):
        exp = apply_exp(exp, vs)
    else:
        exp = exp.value
    return exp


def apply_if(exp, vs):
    condition = return_exp(exp[1], vs)
    if condition == 'yes':
        return return_exp(exp[2], vs)
    elif condition == 'no':
        return return_exp(exp[3], vs)
    else:
        print('判断语句有误')


def apply_exp(exp, vs):
    # 根据token的关键词是log/if/公式/set 进行不同的操作
    # 待完成：set引用的函数
    symbol = {
        '+': accounting,
        '-': accounting,
        '*': accounting,
        '/': accounting,
        '%': accounting,
        '=': compare,
        '!': compare,
        '>': compare,
        '<': compare
    }
    if exp[0].type == Type.log:
        apply_log(exp)
        return Type.null
    elif exp[0].type == Type.choice:
        result = apply_if(exp, vs)
        return result
    elif exp[0].type == Type.set:
        vs[exp[1].value] = exp[2].value
    else:
        return symbol[exp[0].value](exp, vs)


def apply_ast(ast, vs):
    i = 0
    while i < len(ast) - 1:
        apply_exp(ast[i], vs)
        i += 1
    return apply_exp(ast[i], vs)


def apply(code, vs):
    # apply字符串
    code_tokens = json_tokens(code)
    ast = parsed_ast(code_tokens)
    return apply_ast(ast, vs)


def test_set():
    code1 = '''
[set a 1]
[set b 2]
[* a b]
'''
    ensure(apply(code1, variables) == 2, 'test_set 1 failed')

    code2 = '[* 2 3 4] ; 表达式的值是 24'
    ensure(apply(code2, variables) == 24, 'test_set 2 failed')

    code3 = '[- 1 [+ 2 3] [+ 1 1]]'
    ensure(apply(code3, variables) == -6, 'test_set 3 failed')

    code4 = '[log "hello"]   ; 输出 hello, 表达式的值是 null(关键字 表示空)'
    ensure(apply(code4, variables) == Type.null, 'test_set 4 failed')

    code5 = '''[if yes
        [log "成功"]
        [log "没成功"]
    ]'''
    ensure(apply(code5, variables) == Type.null, 'test_set 5 failed')

    code6 = '''[if [> 2 1] 3 4]'''
    ensure(apply(code6, variables) == 3, 'test_set 6 failed')

    code7 = '[< 10 3]'
    ensure(apply(code7, variables) == 'no', 'test_set 7 failed')


def ensure(condition, message):
    if not condition:
        log('*** 测试失败:', message)


def log(*args):
    print(*args)


def main():
    test_set()


if __name__ == '__main__':
    main()
