import sys
import json


def log(*args):
    print(*args)

# 码字字典
d = {}
for i in range(256):
    d['{:02x}'.format(i)] = i

# 解码字典
re_d = {}
for i in range(256):
    re_d[i] = '{:02x}'.format(i)


def read():
    a = sys.argv[1]
    with open(a, 'rb') as f:
        return f.read()


def write(filename, s):
    with open(filename, 'wb+') as f:
        f.write(s)


def read_lzw():
    a = sys.argv[1]
    with open(a, 'r') as f:
        file = json.load(f)
    return file


def lzw():
    file = read()
    result = []
    # 标记字典加到哪一位
    count = 256
    p = ''
    for index in range(len(file)):
        c = '{:02x}'.format(file[index])
        pc = p + c
        if pc in d.keys():
            p = pc
        else:
            try:
                result.append(d[p])
            except:
                log(d[p])
            d[pc] = count
            count += 1
            p = c
    result.append(d[p])
    filename = sys.argv[1].split('.')[0] + '.lzw'
    with open(filename, 'w+') as f:
        json.dump(result, f)


def re_lzw(output):
    file = read_lzw()
    log(len(file))
    count = 256
    cw = file[0]
    char_stream = bytes.fromhex(re_d[cw])
    pw = cw
    for index in range(1, len(file)):
        cw = file[index]
        if cw in re_d:
            str_cw = re_d[cw]
            char_stream += bytes.fromhex(str_cw)
            p = re_d[pw]
            c = str_cw[0:2]
            re_d[count] = p + c
            count += 1
        else:
            p = re_d[pw]
            c = p[0:2]
            char_stream = char_stream + bytes.fromhex(p) + bytes.fromhex(c)
            re_d[count] = p + c
            count += 1
        pw = cw
    write(output, char_stream)


def main():
    if len(sys.argv) == 2:
        lzw()
    elif len(sys.argv) == 3:
        re_lzw(sys.argv[2])


if __name__ == '__main__':
    main()
