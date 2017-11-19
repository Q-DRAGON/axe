class GuaVFS():
    '''
    0-4     GUAFS (guacoding3编码)
    5-9     填 0，暂时不使用这 5 个字节
    10      根目录的文件信息（文件信息的描述在下方，一共 19 字节）


    文件信息，19字节
    10-19 文件名                  10 字节，第一个字节表示文件名的字符串长度
    20 文件类型                   1 字节，0 表示文件，1 表示目录
    21-22 文件长度（目录子文件数量） 2 字节
    23-24 父目录地址              2 字节，0 表示没有父目录（只有根目录 / 是 0）
    25-26 同目录下一个文件的地址    2 字节（只支持 64K 容量的硬盘），0 表示没有下一个文件了
    27-28 文件内容开始的地址       2 字节，如果文件类型是目录则表示第一个子文件的文件信息地址

    文件内容，大小不定
    文件信息地址            2 字节，反向指向文件信息
    '''
    def __init__(self):
        self.gua_coding = {
            0: None,
            10: '.',
            11: ',',
            12: ' ',
            13: '$',
            14: '￥',
        }
        for i in range(10):
            self.gua_coding[15 + i] = i
        for i in range(26):
            self.gua_coding[25 + i] = chr(65 + i)
        self.path = 'disk.guavfs'

    def decode(self, data):
        """将gua_coding编码转成可读数据"""
        s = ''
        for i in data:
            s += self.gua_coding[i]
        return s

    def encode(self, data):
        """将可读数据转成gua_coding编码"""
        return self.find_k_by_v(data)

    def find_k_by_v(self, data_v):
        for k, v in self.gua_coding.items():
            if v == data_v:
                return k

    def read_file(self, path):
        """ 返回disk所有内容 """
        data = []
        with open(path, 'r') as f:
            while True:
                e = f.read(8)
                if not e:
                    break
                data.append(int(e, 2))
        self.data = data

    @staticmethod
    def save_to_file(path, data):
        """将data存入path下的文件中"""
        with open(path, 'w') as f:
            for i in data:
                f.write('{:0>8b}'.format(i))

    def raw_head_to_encode(self, head):
        result = []
        for i in head[:5]:
            result.append(self.encode(i))
        for i in head[5:]:
            result.append(i)
        return result

    def raw_to_encode(self, data, file_start):
        """将文件数据用gua_coding编码"""
        result = []
        result.append(data[file_start])
        # 文件名10字节
        for i in data[file_start + 1: file_start + 10]:
            result.append(self.encode(i))
        # 文件类型1 字节，0 表示文件，1 表示目录
        for i in data[file_start + 10: file_start + 19]:
            result.append(i)
        start = data[file_start + 17] * 256 + data[file_start + 18]
        length = data[file_start + 11] * 256 + data[file_start + 12]
        for i in data[start: start + 2]:
            result.append(i)
        for i in data[start + 2: start + length]:
            result.append(self.encode(i))
        return result

    def find_father(self, path):
        """ 寻找上一级目录的文件信息起始位置"""
        url = path.split('/')
        url = [i for i in url if i != ''][: -1]
        start = 10
        for i in url:
            file_name = self.decode(self.data[start + 1: start + 1 + self.data[start]])
            next_file = self.data[start + 15] * 256 + self.data[start + 16]
            while i != file_name and next_file != 0:
                start = next_file
                file_name = self.decode(self.data[start + 1: start + 1 + self.data[start]])
        return start

    def make_dir(self, path):
        """ 创建目录, path 中不存在的目录都会被创建 """
        start = self.find_father(path)
        new_file_start = len(self.data)
        self.data[start + 17] = new_file_start // 256
        self.data[start + 18] = new_file_start % 256
        self.data[start + 15] = new_file_start // 256
        self.data[start + 16] = new_file_start % 256
        new_file_name = path.split('/')[-1]
        new_file = [len(new_file_name)]
        for i in new_file_name:
            new_file.append(self.encode(i))
        while len(new_file) < 19:
            new_file.append(0)
        self.data += new_file

    def remove_path(self, path):
        """ 删除路径, 如果参数是个目录则递归删除 """
        start = self.find_father(path)
        self.data[start + 17] = 0
        self.data[start + 18] = 0
        self.data[start + 15] = 0
        self.data[start + 16] = 0

    def list(self, path):
        """ 返回 path 下所有的子文件，以列表形式 """
        url = path.split('/')
        url = [i for i in url if i != '']
        files = []
        if len(url) == 0:
            start = 10
            next_start = self.data[start + 15] * 256 + self.data[start + 16]
            files.append(self.decode(self.data[11: self.data[10] + 11]))
            while next_start != 0:
                next_name_len = self.data[next_start]
                files.append(self.decode(self.data[next_start + 1: next_start + 1 + next_name_len]))
                start = next_start
                next_start = self.data[start + 15] * 256 + self.data[start + 16]
        return files

    def write(self, path, content):
        """ 把 content 写入 path 中, content为字符的字符串 """
        data = self.data
        file_start = self.find_file_start(data, path, 10)
        content_start = data[file_start + 17] * 256 + data[file_start + 18]
        s = []
        for i in content:
            s.append(self.encode(i))
        length = len(s)
        data[file_start + 11] = (length + 2) // 256
        data[file_start + 12] = (length + 2) % 256
        index = 0
        while index < length:
            if content_start + 2 + index < len(data):
                data[content_start + 2 + index] = s[index]
                index += 1
            else:
                data.append(s[index])
                index += 1
        self.save_to_file(self.path, self.data)

    def find_file_start(self, data, filename, start):
        """ 通过文件名,查找该文件信息的起始地址 """
        length = data[start]
        name = ''.join(self.decode(data[start + 1: start + 1 + length]))
        if name == filename:
            return start
        else:
            start = data[25] * 256 + data[26]
            return self.find_file_start(data, filename, start)

    def read(self, path):
        """ 返回 path 中给定的这个文件的内容 """
        data = self.data
        file_start = self.find_file_start(data, path, 10)
        content_len = data[file_start + 11] * 256 + data[file_start + 12]
        content_start = data[file_start + 17] * 256 + data[file_start + 18]
        content = self.decode(data[content_start + 2: content_start + content_len])
        return content

def log(*args):
    print(*args)

raw_data = [
    'G', 'U', 'A', 'F', 'S', 0, 0, 0, 0, 0,
    5, 'A', '.', 'T', 'X', 'T', None, None, None, None,
    0, 0, 6, 0, 0, 0, 0, 0, 29, 0, 10,
    'T', 'E', 'S', 'T'
]

test_data = [
    31, 45, 25, 30, 43, 0, 0, 0, 0, 0,
    5, 25, 10, 44, 48, 44, 0, 0, 0, 0,
    0, 0, 6, 0, 0, 0, 0, 0, 29, 0, 10,
    44, 29, 43, 44
]

def main():
    gua_vfs = GuaVFS()

    """将数据数据转码并二进制存入文件中"""
    # encode_data_head = gua_vfs.raw_head_to_encode(raw_data[:10])
    # encode_data = gua_vfs.raw_to_encode(raw_data, 10)
    # data = encode_data_head + encode_data
    # gua_vfs.save_to_file('disk.guavfs', data)

    """读出文件中的数据"""
    gua_vfs.read_file(gua_vfs.path)
    log('测试read函数,返回A.TXT的内容:', gua_vfs.read('A.TXT'))

    """写入文件数据，需要每次修改数据"""
    gua_vfs.write('A.TXT', 'DDDDD')
    log('测试write函数,返回A.TXT修改后的内容:', gua_vfs.read('A.TXT'))

    """读取路径下的文件列表"""
    log('测试list函数,返回根目录下的文件列表:', gua_vfs.list('/'))

    """添加目录"""
    gua_vfs.make_dir('/B.TXT')
    log('测试make_dir函数,根目录下添加B.TXT:', gua_vfs.list('/'))

    """删除目录"""
    gua_vfs.remove_path('/B.TXT')
    log('测试remove_path函数,根目录下删除B.TXT:', gua_vfs.list('/'))


if __name__ == '__main__':
    main()
