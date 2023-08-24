#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

#define BUF_SIZE 30

int main(int argc, char* argv[]){
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_size;

    if (argc != 2){
        cout << "Usage : <port>" << endl;
        return -1;
    }

    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1){
        cout << "Server create socket error" << endl;
        return -1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        cout << "Server bind socket error" << endl;
        return -1;
    }

    if (listen(serv_sock, 5) == -1){
        cout << "Server listen socket error" << endl;
        return -1;
    }

    clnt_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_size);
    if (clnt_sock == -1){
        cout << "Server accept socket error" << endl;
        return -1;
    }

    FILE* fp = fopen("hello_server.cpp", "rb");
    if (fp == NULL){
        cout << "File open error" << endl;
        return -1;
    }else{
        cout << "FILE open success" << endl;
    }
    
    char buf[BUF_SIZE];

    while (1){
        //将fp文件中的数据全写入clnt_sock客户端
        memset(buf, 0, sizeof(buf));
        int read_cnt = fread(buf, 1, BUF_SIZE, fp);
        if (read_cnt < BUF_SIZE){
            write(clnt_sock, buf, read_cnt);
            break;
        }
        write(clnt_sock, buf, BUF_SIZE);
    }

    shutdown(clnt_sock, SHUT_WR);   //关闭客户端写方向的输出流
    read(clnt_sock, buf, BUF_SIZE); //进入半关闭状态还可以从客户端中读取数据
    cout << "Message from client : " << buf << endl;

    fclose(fp);
    close(clnt_sock);close(serv_sock);

    return 0;
}