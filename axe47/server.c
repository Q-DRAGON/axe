#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>
// #include<Python.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

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
    int i;
    char *message;
    char request[2000];
    recv(s, request, 2000, 0);
    // 创建 lua 运行环境
    lua_State *L = luaL_newstate();
    // 加载 lua 标准库
    luaL_openlibs(L);
    // 载入 lua 文件并执行
    // 如果出错会打印出错原因
    if(luaL_dofile(L, "server.lua")) {
        printf("LUA ERROR: %s\n", lua_tostring(L, -1));
        return NULL;
    }
    lua_getglobal(L, "luaresponse");
    // double double_re = (double)*request;
    // luaresponse(request);
    lua_pushstring(L, request);
    // 用 lua_pcall 调用一个函数
    // 1 是参数数量
    // 1 是返回值的数量
    // 0 是 lua 中的错误处理函数，这里不提供所以传 0
    // 检查 pcall 的返回值以捕捉调用错误
    if(lua_pcall(L, 1, 1, 0) != 0) {
        printf("LUA ERROR: %s\n", lua_tostring(L, -1));
    }
    // pcall 会吃掉栈中 3 个值（函数 参数1 参数2）
    // 然后 push 一个返回值进去
    const char *answer = lua_tostring(L, -1);
    // 关闭 lua 运行环境
    lua_close(L);
    write(s , answer , strlen(answer));
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
        pthread_t tid;
        pthread_create(&tid, NULL, threadResponse, (void *)&clientSocket);
    }
    return 0;
}
