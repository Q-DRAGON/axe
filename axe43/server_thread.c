/*
作业：
2, 提供的代码是用多线程实现的并发服务器
    但是这个实现是有 bug 的
    使用作业 1 的程序就可以测出来错误
    请分析并改正这个 bug
    这个 bug 至少有 2 个修复方法
    本作业为 server_thread.c

3, 把提供的代码改为多进程方案
    本作业为 server_fork.c

4, 测试 3 种服务器方案的吞吐量（分别是 单进程单线程 多线程 多进程）
    使用命令 time python3 socket_test.py
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>


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
    listen(s, 5);
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
    return NULL;
}

int
main(int argc, const char *argv[]) {
    unsigned short port = 3000;
    int s = openSocket(port);

    struct sockaddr_in client;
    int size = sizeof(struct sockaddr_in);
    int count = 0;
    while(true) {
        int clientSocket = accept(s, (struct sockaddr *)&client, (socklen_t*)&size);
        count ++;
        printf("%d\n", count);
        pthread_t tid;
        pthread_create(&tid, NULL, threadResponse, (void *)&clientSocket);
        // pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
        // pthread_testcancel();/*the thread can be killed only here*/
        // pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
    }

    return 0;
}
