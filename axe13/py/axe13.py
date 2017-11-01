from enum import Enum


variables = {}


class Type(Enum):
    auto = 0  # auto 就是 6 个单字符符号, 用来方便写代码的
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
    yes = 12
    no = 13
    add = 14
    sub = 15
    mul = 16
    div = 17
    mod = 18
    equ = 19
    noequ = 20
    more = 21
    less = 22
    log = 23
    choice = 24
    set = 25


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
            'log': Type.log
        }
        if token_type == Type.auto:
            self.type = d[token_value]
        else:
            self.type = token_type
        self.value = token_value

    def __repr__(self):
        return '({})'.format(self.value)


def string_end(code, index):
    """
    code = "abc"
    index = 1
    """
    s = ''
    offset = index + 1
    log('code', code, index)
    while offset < len(code):
        c = code[offset]
        if c == '"':
            # 找到了字符串的结尾
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
    # 寻找注释的结尾
    offset = index
    while offset < len(code):
        if code[offset] != '\n':
            offset += 1
        else:
            offset += 1
            break
    return offset


def keyword_end(code, index):
    # 判断关键词并返回关键字和结束的坐标
    offset = index
    if code[offset - 1: offset + 3] == 'true':
        offset += 3
        return 'True', offset
    elif code[offset - 1: offset + 4] == 'false':
        offset += 4
        return 'False', offset
    elif code[offset - 1: offset + 3] == 'null':
        offset += 3
        return 'None', offset
    elif code[offset - 1: offset + 2] == 'log':
        offset += 2
        return 'log', offset
    elif code[offset - 1: offset + 1] == 'if':
        offset += 1
        return 'if', offset
    elif code[offset - 1: offset + 2] == 'yes':
        offset += 2
        return 'yes', offset
    elif code[offset - 1: offset + 1] == 'no':
        offset += 1
        return 'no', offset
    elif code[offset - 1: offset + 2] == 'set':
        offset += 2
        return 'set', offset
    else:
        # 错误字符则程序报错
        pass


def json_tokens(code):
    length = len(code)
    tokens = []
    spaces = [' ', '\n', '\t']
    digits = '1234567890'
    # 当前下标
    i = 0
    start = 0
    while i < length:
        c = code[i]
        if c in ['[', ']']:
            if start < i:
                tokens.append(code[start: i])
            tokens.append(c)
            i += 1
            start = i
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
        elif c in spaces:
            if start < i:
                tokens.append(code[start: i])
            i += 1
            start = i
        else:
            i += 1
    return tokens

    # while i < length:
    #     # 先看看当前应该处理啥
    #     c = code[i]
    #     i += 1
    #     if c in spaces:
    #         # 空白符号要跳过, space
    #         continue
    #     elif c in ':,{}[]+-*/%=!><':
    #         # 处理 n 种单个符号
    #         t = Token(Type.auto, c)
    #         tokens.append(t)
    #     elif c == '"':
    #         # 处理字符串
    #         s, offset = string_end(code, i)
    #         i = offset + 1
    #         t = Token(Type.string, s)
    #         tokens.append(t)
    #     elif c in digits:
    #         # 处理数字, 现在不支持小数和负数
    #         end = 0
    #         for offset, char in enumerate(code[i:]):
    #             if char not in digits:
    #                 end = offset
    #                 break
    #         n = int(code[i - 1:i + end])
    #         i += end
    #         t = Token(Type.number, n)
    #         # log('token', type(n))
    #         tokens.append(t)
    #     elif c in 'tfnylis':
    #         # 处理关键词 true, false, null, yes, no, log
    #         s, offset = keyword_end(code, i)
    #         i = offset
    #         if s == 'True':
    #             t = Token(Type.true, s)
    #         elif s == 'False':
    #             t = Token(Type.false, s)
    #         elif s == 'None':
    #             t = Token(Type.null, s)
    #         elif s == 'log':
    #             t = Token(Type.log, s)
    #         elif s == 'if':
    #             t = Token(Type.choice, s)
    #         elif s == 'yes':
    #             t = Token(Type.yes, s)
    #         elif s == 'no':
    #             t = Token(Type.no, s)
    #         elif s == 'set':
    #             t = Token(Type.set, s)
    #         if t is not None:
    #             tokens.append(t)
    #     elif c == ';':
    #         # 处理注释
    #         i = notes_tokens(code, i)
    #     else:
    #         # 出错了
    #         pass
    # return tokens


def accounting(code):
    symbol = {
        '+': apply_sum,
        '-': apply_sub,
        '*': apply_mul,
        '/': apply_div,
        '%': apply_mod,
    }
    function_name = symbol[code[0].value]
    i = 2
    length = len(code)
    result = code[1].value
    while i < length:
        if code[i].type == Type.number:
            result = function_name(result, code[i].value)
            i += 1
        elif code[i].type == Type.bracketLeft:
            count = 1
            for index, j in enumerate(code[i + 1:]):
                if j.type == Type.bracketLeft:
                    count += 1
                elif j.type == Type.bracketRight:
                    count -= 1
                    if count == 0:
                        end = index
                        result = function_name(result, apply_tokens(code[i: end + i + 2], variables))
                        i += len(code[i: end + i + 2])
                    else:
                        pass
                else:
                    continue
        else:
            i += 1
    return result


def compare(code):
    symbol = {
        '=': apply_equal,
        '!': apply_not_equal,
        '>': apply_more,
        '<': apply_less
    }
    function_name = symbol[code[0].value]
    if function_name(code) is True:
        return Type.yes
    else:
        return Type.no


def apply_sum(a, b):
    return a + b


def apply_sub(a, b):
    return a - b


def apply_mul(a, b):
    return a * b


def apply_div(a, b):
    return a / b


def apply_mod(a, b):
    return a % b


def apply_equal(code):
    return code[1].value == code[2].value


def apply_not_equal(code):
    return code[1].value != code[2].value


def apply_more(code):
    return code[1].value > code[2].value


def apply_less(code):
    return code[1].value < code[2].value


def find_statement(tokens, start_index):
    count = 0
    j = start_index
    end = start_index
    statement = []
    if tokens[j].type == Type.bracketLeft:
        count += 1
        j += 1
        while j < len(tokens):
            if tokens[j].type == Type.bracketRight:
                count -= 1
                if count == 0:
                    statement = tokens[start_index: j + 1]
                    end = j
                    break
                else:
                    j += 1
            else:
                j += 1
    else:
        statement.append(tokens[j])
        end = j
    return statement, end


def apply_log(tokens):
    i = 2
    while i < len(tokens) - 1:
        print(tokens[i].value)
        i += 1


def apply_if(tokens):
    condition, condition_end = find_statement(tokens, 2)
    statement_yes, yes_end = find_statement(tokens, condition_end + 1)
    statement_no, no_end = find_statement(tokens, yes_end + 1)
    if condition[0].type == Type.yes:
        return apply_tokens(statement_yes, variables)
    elif condition[0].type == Type.no:
        return apply_tokens(statement_no, variables)
    elif apply_tokens(condition, variables) == Type.yes:
        return apply_tokens(statement_yes, variables)
    else:
        return apply_tokens(statement_no, variables)


def pop_list(stack):
    l = []
    while stack[-1] != '[':
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
        token = token_list[i]
        i += 1
        if token == ']':
            list_token = pop_list(l)
            l.append(list_token)
        else:
            l.append(token)
    return l


def apply_exp(exp, vs):
    # 根据token的关键词是log/if/公式/set 进行不同的操作
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
        # return Type.null
    elif exp[0].type == Type.choice:
        result = apply_if(exp)
        return result
    elif exp[0].type == Type.set:
        vs[exp[1].value] = exp[2].value
    else:
        return symbol[exp[0].value](exp)


def apply_ast(ast, vs):
    i = 0
    while i < len(ast) - 1:
        i += 1
        apply_exp(ast[i], vs)
    return apply_exp(ast[i], vs)


def apply(code, vs):
    """
    code 是一个字符串

    0, 每个表达式都是一个值, 操作符(可以认为是函数)和操作数(可以认为是参数)用空格隔开
    1, ; 到行末是单行注释, 没有多行注释
    2, 支持 + - * / % 五种基本数学操作和 = ! > < 四种逻辑操作(相等 不等 大于 小于)
        逻辑操作的结果是布尔值 yes 和 no(这 2 个是关键字)
    3, 支持表达式嵌套
    4, 支持内置函数 log, 作用是输出参数字符串
    5, 支持条件表达式 if

    [+ 1 2]         ; 表达式的值是 3
    [* 2 3 4]       ; 表达式的值是 24
    [log "hello"]   ; 输出 hello, 表达式的值是 null(关键字 表示空)
    [+ 1 [- 2 3]]   ; 表达式的值是 0, 相当于普通语法的 1 + (2 - 3)
    [if [> 2 1] 3 4]; 表达式的值是 3
    [if yes
        [log "成功"]
        [log "没成功"]
    ]
    """
    """
    code 是代码字符串，支持定义变量的功能
    code = '''
        [set a 1]
        [set b 2]
        [+ a b]
        '''
    上面三行代码用 set 操作实现了变量定义

    本函数中，vars 是一个字典，包含了所有当前环境中定义的变量和值
    用这样的方式，在全局环境中声明一个 {}
    每个 apply 都传入 vars
    在 set 的时候往里面添加变量和值
    在使用到变量的时候，从 vars 中找变量的值，找不到就是未定义变量

    注意，变量是作为一种新的 token 而存在
    """
    code_tokens = json_tokens(code)
    log('tokens', code, code_tokens)
    ast = ast_from_tokens(code_tokens)
    log('ast', ast)
    return apply_ast(ast, vs)


def test_apply():
    string1 = r'''
[+         ;vuui
1 2 "qwe"
]
'''
    result1 = apply(string1, variables)
    ensure(result1 == 3, 'testApply1')

    string2 = '[< 10 3]'
    result2 = apply(string2, variables)
    ensure(result2 == Type.no, 'testApply2')

    string3 = '[* 2 3 4] ; 表达式的值是 24'
    result3 = apply(string3, variables)
    ensure(result3 == 24, 'testApply3')

    string4 = '[- 1 [+ 2 3] [+ 1 1]]'
    result4 = apply(string4, variables)
    ensure(result4 == -6, 'testApply4')

    string5 = '[log "hello"]   ; 输出 hello, 表达式的值是 null(关键字 表示空)'
    result5 = apply(string5, variables)
    ensure(result5 == Type.null, 'testApply5')

    string6 = '''[if yes
        [log "成功"]
        [log "没成功"]
    ]'''
    result6 = apply(string6, variables)
    ensure(result6 == Type.null, 'testApply6')

    string7 = '''[if [> 2 1] 3 4]'''
    result7 = apply(string7, variables)
    ensure(result7 == 3, 'testApply7')


def test_set():
    code = '''
        [set a 1]
        [set b 2]
        [+ a b]
        '''
    # log(apply(code, variables))
    string1 = r'''
[- 1 [+ 2 3] [+ 1 1]]'''
    log(json_tokens(code))

    log(parsed_ast(json_tokens(code)))


def ensure(condition, message):
    if not condition:
        log('*** 测试失败:', message)


def log(*args):
    print(*args)


def main():
    # test_apply()
    test_set()


if __name__ == '__main__':
    main()
