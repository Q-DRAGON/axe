import sys


def log(*args):
    print(*args)


def read_bmp():
    a = sys.argv[1]
    name = a.split('.', 1)[0]
    with open(a, 'rb') as f:
        f.seek(10)
        s = f.read(4)
        start = int.from_bytes(s, byteorder='little')
        # log(start)
        f.seek(18)
        w = f.read(4)
        width = int.from_bytes(w, byteorder='little')
        # log(width)
        f.seek(22)
        h = f.read(4)
        height = int.from_bytes(h, byteorder='little')
        # log(height)
        f.seek(28)
        b = f.read(2)
        byte = int.from_bytes(b, byteorder='little')
        # log(byte)
        f.seek(start)
        uuzu = []
        for y in range(height):
            row = []
            for x in range(width):
                b = int.from_bytes(f.read(1), byteorder='little')
                g = int.from_bytes(f.read(1), byteorder='little')
                r = int.from_bytes(f.read(1), byteorder='little')
                sum = (r << 24) + (g << 16) + (b << 8) + 255
                row.append(str(sum))
            uuzu.append(row)
        s = 'guaimage\n1.0\n' + str(width) + '\n' + str(height) + '\n'
        return uuzu, s, name


def write_guaimage(s, uuzu_re, name):
    for i in range(len(uuzu_re)):
        s += ' '.join(uuzu_re[i])
        s += '\n'
        filename = str(name) + '.guaimage'
    with open(filename, 'w+') as f:
        f.write(s)


def main():
    uuzu, s, name = read_bmp()
    uuzu_re = uuzu[::-1]
    write_guaimage(s, uuzu_re, name)


if __name__ == '__main__':
    main()
