d = {
    'x': 0b00010000,
    'y': 0b00100000,
    'z': 0b00110000,
    'set': 0b00000000,
    'load': 0b00000001,
    'add': 0b00000010,
    'save': 0b00000011
}


def clarify(asm):
    # 处理注释, 并转换为列表
    asm = asm.strip()
    asm = asm.split('\n')
    asm_hang = []
    for i in asm:
        asm_i = i.split(';')[0].strip()
        asm_hang.append(asm_i)
    asm_element = ' '.join(asm_hang)
    return asm_element.split(' ')


def machine_code(asm, diction):
    """
    asm 是汇编语言字符串
    返回 list, list 中每个元素是一个 1 字节的数字
    """
    asm = clarify(asm)
    for index, i in enumerate(asm):
        if i in diction:
            asm[index] = diction[i]
    for index, i in enumerate(asm):
        if isinstance(i, str) and (i[0] == '@'):
            asm[index] = '{:08b}'.format(int(i[1:]))
        else:
            asm[index] = '{:08b}'.format(int(i))
    return asm


def test_machine_code():
    string = '''
set x 1
set y 2
save x @0
save y @1
load @0 x
load @1 y
add x y z
save z @2
'''
    log(machine_code(string, d))


def log(*args):
    print(*args)


def main():
    test_machine_code()


if __name__ == '__main__':
    main()
