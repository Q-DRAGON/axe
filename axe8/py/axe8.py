def log(*args):
    print(*args)


# 实现 json_tokens 函数
# json_string 是一个 JSON 格式字符串
def json_tokens(json_string):
    """
    在作业 7 的基础上增加 2 个功能
    1，把数字识别为数字
    2，字符串中以转义符形式支持双引号，例如 "a\"b" 会被识别为 a"b
    """
    results = []
    keywords = '{}:,[]'
    ints = '1234567890'
    length = len(json_string)

    # for i in range(length):
    i = 0
    while i < length:
        # 是标点
        if json_string[i] in keywords:
            results.append(json_string[i])
            i += 1
        # 是空格
        elif json_string[i] == ' ':
            i += 1
        # 是字符串
        elif json_string[i] == '"':
            s = json_string[i:]
            nextquo = 1
            end = s.find('"', nextquo)
            # log(s[end + 1])
            # 根据引号后面的字符判断引号是否是结束引号
            while s[end + 1] not in [":", ",", "}", "]"] and end != -1:
                nextquo += 1
                # log("nextquo", nextquo)
                end = s.find('"', nextquo)
                # log('end', end)
            word = s[1:end]
            results.append(word)
            i += end + 1
        # 是整数
        elif json_string[i] in ints:
            new_string = json_string[i:]
            count = 0
            while count < len(new_string) and new_string[count] in ints:
                count += 1
            num = new_string[:count]
            num_int = int(num)
            results.append(num_int)
            i = i + count
    return results


def parsed_json(tokens):
    """
    tokens 是一个包含各种 JSON token 的数组（ json_tokens 的返回值）
    返回解析后的 字典
    例如
    ["{", "name", ":", "gua", "}"]
    会返回如下字典
    {
        'name': 'gua',
    }

    需要支持字典 数组 字符串 数字
    不要求支持嵌套字典和嵌套数组
    """
    if tokens[0] == '{':
        dict = {}
        for i, s in enumerate(tokens):
            if tokens[i] == ':':
                dict[tokens[i - 1]] = tokens[i + 1]
        return dict
    elif tokens[0] == '[':
        array = []
        for i, s in enumerate(tokens):
            if tokens[i] in [',', ']'] and tokens[i - 1] not in ['[', ']']:
                array.append(tokens[i - 1])
        return array


pass


def test_json_tokens():
    string1 = '{"gua": "a\"b","height": 169}'
    num1 = ["{", "gua", ":", "a\"b", ",", "height", ":", 169, "}"]
    # log(json_tokens(string1))
    ensure(json_tokens(string1) == num1, 'testJsonTokens1')

    string2 = '[{"student": 1}, {"student": 2}]'
    num2 = ["[", "{", "student", ":", 1, "}", ",", "{", "student", ":", 2, "}", "]"]
    ensure(json_tokens(string2) == num2, 'testJsonTokens2')

    string3 = '{}'
    num3 = ["{", "}"]
    ensure(json_tokens(string3) == num3, 'testJsonTokens3')


def test_parsed_jason():
    string1 = '{"a\"b": "gua","height": 169}'
    num1 = json_tokens(string1)
    dict1 = {
        'height': 169,
        'a"b': 'gua'
    }
    ensure(parsed_json(num1) == dict1, 'testParsedJson 1')

    string2 = '["tom", "jerry"]'
    num2 = json_tokens(string2)
    array2 = ["tom", "jerry"]
    ensure(parsed_json(num2) == array2, 'testParsedJson 2')

    string3 = '{}'
    num3 = json_tokens(string3)
    dict3 = {}
    ensure(parsed_json(num3) == dict3, 'testParsedJson 3')


def ensure(condition, message):
    if not condition:
        log('*** 测试失败:', message)


def main():
    test_json_tokens()
    test_parsed_jason()


if __name__ == '__main__':
    main()
