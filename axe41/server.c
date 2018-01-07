/*
作业：
在提供的代码的基础上，把服务器改造成多线程的并发（并发指同时处理多个事）服务器


代码功能：
本代码是一个很简单的 socket server
运行后，对于任何连上来的 socket 都发送一个默认的字符串作为响应
运行后，可以通过开新终端用以下命令来测试服务器响应
curl localhost:3000

因为我们的回应不是 http 协议的格式，所以 curl 不会主动关闭连接
你可以注意到同一时刻只有一个 curl 能够被处理
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include <pthread.h>

int c;



void *
response(void *args) {
    int so = c;
    char *message = "connection default response\n";
    write(so , message, strlen(message));
    return NULL;
}

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

// int
// makeclient(int s, struct sockaddr_in client, int size){
// // makeclient(){
//     int c = accept(s, (struct sockaddr *)&client, (socklen_t*)&size);
//     return c;
// }

// void
// multiThread(){
//     int n = 5;
//     pthread_t tid1[n];
//     pthread_t tid2[n];
//     for (int i = 0; i < n; i++) {
//         pthread_create(&tid1[i], NULL, makeclient, NULL);
//         int c = makeclient(s, client, size);
//         pthread_create(&tid2[i], NULL, response, NULL);
//     }
// }

int
main(int argc, const char *argv[]) {
    unsigned short port = 3000;
    int s = openSocket(port);

    struct sockaddr_in client;
    int size = sizeof(struct sockaddr_in);
    while(true) {
        // multiThread();
        // int c = makeclient(s, client, size);
        c = accept(s, (struct sockaddr *)&client, (socklen_t*)&size);
        // multiThread();
        printf("accept and process\n");
        pthread_t tid;
        pthread_create(&tid, NULL, response, NULL);
        // printf("线程tid%s\n", tid);
        // response();
    }

    return 0;
}
