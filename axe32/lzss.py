import sys
import json


def read():
    a = sys.argv[1]
    with open(a, 'rb') as f:
        return f.read()


def write(filename, s):
    with open(filename, 'wb+') as f:
        f.write(s)


def read_lzss():
    a = sys.argv[1]
    with open(a, 'r') as f:
        file = json.load(f)
    return file


def re_lzss(output):
    file = read_lzss()
    results = bytes()
    for i in file:
        if isinstance(i, list):
            start, offset = i
            results += results[start: start + offset]
        else:
            results += bytes.fromhex(i)
    write(output, results)


def lzss():
    file = read()
    a = []
    for i in file:
        a.append('{:02x}'.format(i))
    size = len(a)

    results = []
    left = ''
    min_length = 6
    i = 0
    while i < size:
        j = i + min_length
        t = 0
        while j < size and len(''.join(a[i: j])) < len(left):
            sub = ''.join(a[i: j])
            index = left.find(sub)
            if index >= 0:
                t = (int(index / 2), int(len(sub) / 2))
            else:
                break
            j += 1

        if t != 0:
            results.append(t)
            left += ''.join(a[i: i + t[1]])
            i += t[1]
        else:
            results.append(a[i])
            left += a[i]
            i += 1
    filename = sys.argv[1].split('.')[0] + '.lzss'
    with open(filename, 'w+') as f:
        json.dump(results, f)


def main():
    if len(sys.argv) == 2:
        lzss()
    elif len(sys.argv) == 3:
        re_lzss(sys.argv[2])


if __name__ == '__main__':
    main()
