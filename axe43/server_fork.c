/*
作业：
3, 把提供的代码改为多进程方案
    本作业为 server_fork.c
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

void *
processResponse(void *socketFile) {
    int s = *(int *)socketFile;
    char *message = "connection default response - process\n";
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
        printf("count %d\n", count);
        int pid = fork();
        if (pid != 0) {
            printf("pid %d\n", pid);
            processResponse((void *)&clientSocket);
            exit(0);
        }
    }
    return 0;
}
