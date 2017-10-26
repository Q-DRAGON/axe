from enum import Enum


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
    offset = index
    while offset < len(code):
        c = code[offset]
        if c == '"':
            # 找到了字符串的结尾
            # s = code[index:offset]
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
    # 程序出错, 没有找到反引号"
    pass


def keyword_end(code, index):
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
    else:
        # 错误字符则程序报错
        pass


def json_tokens(code):
    length = len(code)
    tokens = []
    spaces = '\r'
    digits = '1234567890'
    # 当前下标
    i = 0
    while i < length:
        # 先看看当前应该处理啥
        c = code[i]
        i += 1
        if c in spaces:
            # 空白符号要跳过, space
            continue
        elif c in ':,{}[]':
            # 处理 6 种单个符号
            t = Token(Type.auto, c)
            tokens.append(t)
        elif c == '"':
            # 处理字符串
            s, offset = string_end(code, i)
            i = offset + 1
            t = Token(Type.string, s)
            tokens.append(t)
        elif c in digits:
            # 处理数字, 现在不支持小数和负数
            end = 0
            for offset, char in enumerate(code[i:]):
                if char not in digits:
                    end = offset
                    break
            n = code[i - 1:i + end]
            i += end
            t = Token(Type.number, n)
            tokens.append(t)
        elif c in 'tfn':
            # 处理 true, false, null
            s, offset = keyword_end(code, i)
            i = offset
            if s == 'True':
                t = Token(Type.true, s)
            elif s == 'False':
                t = Token(Type.false, s)
            elif s == 'None':
                t = Token(Type.null, s)
            else:
                continue
            tokens.append(t)
        else:
            # 出错了
            pass
    return tokens


def parsed_word(next_token):
    # 处理数字、true、false、null
    if next_token.type == Type.number:
        next_value = int(next_token.value)
    elif next_token.type == Type.true:
        next_value = True
    elif next_token.type == Type.false:
        next_value = False
    elif next_token.type == Type.null:
        next_value = None
    else:
        next_value = None
    return next_value


def inner_tokens(i, tokens):
    start = i
    reversed_tokens = tokens[start: -1][::-1]
    if tokens[i].type == Type.braceLeft:
        to_find = Type.braceRight
    else:
        to_find = Type.bracketRight
    end = -1
    for j, ns in enumerate(reversed_tokens):
        if ns.type == to_find:
            end = len(tokens) - j - 1
            break
    new_token = tokens[start: end + 1]
    inside_json = parsed_json(new_token)
    i += len(new_token)
    return inside_json, i


def parsed_brace(tokens):
    d = {}
    i = 0
    while i < len(tokens):
        if tokens[i].value == ':':
            next_token = tokens[i + 1]
            former_token = tokens[i - 1]
            if next_token.type in [Type.number, Type.true, Type.false, Type.null]:
                d[former_token.value] = parsed_word(next_token)
                i += 1
            elif next_token.type in [Type.braceLeft, Type.bracketLeft]:
                inside_json, i = inner_tokens(i + 1, tokens)
                d[former_token.value] = inside_json
            else:
                d[former_token.value] = next_token.value
                i += 1
        else:
            i += 1
    return d


def parsed_bracket(tokens):
    array = []
    i = 1
    while i < len(tokens):
        if tokens[i].type in [Type.number, Type.true, Type.false, Type.null]:
            array.append(parsed_word(tokens[i]))
            i += 1
        elif tokens[i].type in [Type.braceLeft, Type.bracketLeft]:
            inside_json, i = inner_tokens(i, tokens)
            array.append(inside_json)
        elif tokens[i].value in [',', ']'] and tokens[i - 1].value not in ['[', ']', ',', '{', '}']:
            array.append(tokens[i - 1].value)
            i += 1
        else:
            i += 1
    return array


def parsed_json(tokens):
    """
    tokens 是一个包含各种 JSON token 的数组（ json_tokens 的返回值）
    返回解析后的 字典
    """
    if tokens[0].value == '{':
        return parsed_brace(tokens)
    elif tokens[0].value == '[':
        return parsed_bracket(tokens)
    else:
        return tokens


def test_json():
    string1 = r'{"gua": "a\"b","height": 169}'
    num1 = json_tokens(string1)
    ensure(parsed_json(num1) == eval(string1), 'testJson1')

    string2 = r"""
{
    "na\"me": false,
    "slash\\": true,
    "return\n": null,
    "tab\t": 169
}
"""
    import json
    num2 = json_tokens(string2)
    # log(num2)
    # log(parsed_json(num2))
    # log(json.loads(string2))
    ensure(parsed_json(num2) == json.loads(string2), 'testJson2')

    string3 = r"""
{
    "student":
    {
        "a" : 168,
        "b" : 124
    },
    "classroom":
    ["SX101", "SX102", "SX103"]
}"""
    num3 = json_tokens(string3)
    # log(parsed_json(num3))
    # log(json.loads(string3))
    ensure(parsed_json(num3) == json.loads(string3), 'testJson3')


def ensure(condition, message):
    if not condition:
        log('*** 测试失败:', message)


def log(*args):
    print(*args)


def main():
    test_json()


if __name__ == '__main__':
    main()
