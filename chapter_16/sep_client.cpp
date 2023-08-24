#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
using namespace std;
#define BUF_SIZE 1024

int main(int argc, char *argv[]){
    if (argc != 3){
        cout << "Usage : <IP> <port>" << endl;
        return -1;
    }

    int clnt_sock;
    struct sockaddr_in serv_addr;
    char buf[BUF_SIZE];

    clnt_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (clnt_sock == -1){
        cout << "client create socket error" << endl;
        return -1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(clnt_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        cout << "client connect error" << endl;
        return -1;
    }

    FILE *readfp = fdopen(clnt_sock, "r");
    FILE *writefp = fdopen(clnt_sock, "w");

    while (1){
        //读取来自服务端的信息并输出
        if (fgets(buf, BUF_SIZE, readfp) == NULL)
            break;
        cout << buf;
        fflush(stdout);
    }

    //向readfp指针写入感谢信息
    fputs("FROM CLIENT : Thank you! \n", writefp);
    fflush(writefp);
    
    fclose(readfp), fclose(writefp);
    return 0;
}