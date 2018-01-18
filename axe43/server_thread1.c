/*
作业截止时间
周四（01.011） 22:00


交作业方式：
作业文件路径为
axe43/socket_test.py
axe43/server_thread.c
axe43/server_fork.c


作业：
1, 用 py 的多线程模块 threading 实现一个多线程程序
    发送 3000 个 socket 请求到 localhost:3000 并接受响应
    不输出任何数据到终端
    记得 join
    本作业为 socket_test.py

2, 提供的代码是用多线程实现的并发服务器
    但是这个实现是有 bug 的
    使用作业 1 的程序就可以测出来错误
    请分析并改正这个 bug
    这个 bug 至少有 2 个修复方法
    本作业为 server_thread.c

    答：warning 有两处：
    第一处 void * threadResponse(void *socketFile) 的返回值应该为 NULL
    第二处 pthread_create(&tid, NULL, threadResponse, (void *)clientSocket);
        最后一个参数有误，(void *) 应该接 clientSocket 的地址，而不是 clientSocket 本身
        此处应该是导致 server 报错 segmentation fault 退出的原因。

3, 把提供的代码改为多进程方案
    本作业为 server_fork.c

4, 测试 3 种服务器方案的吞吐量（分别是 单进程单线程 多线程 多进程）
    使用命令 time python3 socket_test.py

    单进程单线程：
    0.23s user 0.37s system 40% cpu 1.493 total
    但是有较高风险发生 [Errno 54] Connection reset by peer
    多线程：
    0.41s user 0.48s system 46% cpu 1.916 total
    多进程：
    0.54s user 0.62s system 50% cpu 2.300 total

*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>

int count = 0;
pthread_mutex_t m;

int
openSocket(unsigned short port) {
    int s = socket(AF_INET, SOCK_STREAM, 0);
    // 消除端口占用错误
    const int option = 1;
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (const void *)&option , sizeof(int));
    //
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(port);
    //
    bind(s, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    listen(s, 256);
    //
    printf("listening at port %d\n", port);
    return s;
}

void *
threadResponse(void *socketFile) {
    int s = *(int *)socketFile;
    char *message = "connection default response\n";
    write(s , message , strlen(message));
    close(s);
    // pthread_mutex_unlock(&m);
    return NULL;
}

void
response(int socketFile) {
    int s = socketFile;
    char *message = "connection default response\n";
    write(s , message , strlen(message));
}

int
main(int argc, const char *argv[]) {
    unsigned short port = 3000;
    int s = openSocket(port);
    pthread_mutex_init(&m, NULL);

    struct sockaddr_in client;
    int size = sizeof(struct sockaddr_in);
    while(true) {
        // pthread_mutex_lock(&m);
        int clientSocket = accept(s, (struct sockaddr *)&client, (socklen_t*)&size);
        // response(clientSocket);
        pthread_t tid;
        pthread_create(&tid, NULL, threadResponse, (void *)&clientSocket);
        count++;
        printf("accept and process, id: %d\n", count);
    }

    return 0;
}
