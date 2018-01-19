/*
作业：
在多线程服务器（不要求线程池）的基础上，实现一个简单的 HTTP 服务器
只支持一个 / 路由（返回一个简单网页（自己定））
其他路由都返回 404
但是，在 C 语言中调用 python 函数来做响应
怎样在 C 语言中调用 python 就是本次作业的主要内容（只支持 python3 以上）
其他细节不做要求
建议：
1，在 Linux 环境下实现，装库比较方便
2，在群里、slack 中互相讨论，跳过垃圾知识
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>
#include<Python.h>

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
    PyObject *pName, *pModule, *pDict, *pFunc;
    PyObject *pArgs, *pValue, *pRequest, *k;
    int i;
    char *message;
    char request[2000];
    recv(s , request , 2000 , 0);
    // printf("request:\n %s\n", request);
    Py_Initialize();

    PyGILState_STATE state = PyGILState_Ensure();

    pRequest = Py_BuildValue("(s)", request);

    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('.')");

    pName = PyUnicode_DecodeFSDefault("response");

    pModule = PyImport_Import(pName);
    Py_XDECREF(pName);

    if (pModule != NULL) {

        pFunc = PyObject_GetAttrString(pModule, "response");

        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(2);
            for (i = 0; i < 2; ++i) {
                pValue = PyLong_FromLong(atoi("1"));
                PyTuple_SetItem(pArgs, i, pValue);
            }
            k = NULL;
            pValue = PyObject_Call(pFunc, pRequest, k);
            Py_XDECREF(pArgs);
            if (pValue != NULL) {
                PyArg_ParseTuple(pValue, "s", &message);
                // printf("Result of call: %s\n", message);
                Py_XDECREF(pValue);
            }
        }
        Py_XDECREF(pFunc);
        Py_XDECREF(pModule);
    }
    Py_XDECREF(pFunc);
    Py_XDECREF(pModule);
    PyGILState_Release(state);
    Py_Finalize();
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
        // printf("sssss\n");
        count ++;
        pthread_t tid;
        pthread_create(&tid, NULL, threadResponse, (void *)&clientSocket);
    }
    return 0;
}
