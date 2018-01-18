# coding=utf-8
"""
1, 用 py 的多线程模块 threading 实现一个多线程程序
    发送 3000 个 socket 请求到 localhost:3000 并接受响应
    不输出任何数据到终端
    记得 join
    本作业为 socket_test.py

4, 测试 3 种服务器方案的吞吐量（分别是 单进程单线程 多线程 多进程）
    使用命令 time python3 socket_test.py
"""
import threading
import socket


def send_socket():
    address = ('127.0.0.1', 3000)
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect(address)
    s.close()


def main():
    threads = []
    for i in range(1000):
        t = threading.Thread(target=send_socket, name=str(i))
        threads.append(t)
        t.start()
    for t in threads:
        print(t.name)
        t.join()


if __name__ == '__main__':
    main()
