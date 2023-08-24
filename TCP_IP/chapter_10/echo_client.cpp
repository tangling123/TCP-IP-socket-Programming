#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
using namespace std;

#define BUF_SIZE 1024

int main(int argc, char* argv[]){
    if (argc != 3){
        cout << "Usage : <IP> <port>" << endl;
        return -1;
    }

    int clnt_sock, str_len;
    sockaddr_in serv_addr;
    char buf[BUF_SIZE];

    //对于客户端而言只有两步：创建套接字、连接到服务端
    clnt_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (clnt_sock == -1){
        cout << "Client socket error" << endl;
        return -1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(clnt_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        cout << "Client connect error" << endl;
        return -1;
    }

    while (1){
        memset(&buf, 0, sizeof(buf));   //每次将buf数组清空
        cout << "Input message(Q to quit): ";

        cin.getline(buf, BUF_SIZE);
        if (strcmp(buf, "Q") == 0)  break;

        write(clnt_sock, buf, strlen(buf));
        str_len = read(clnt_sock, buf, BUF_SIZE-1);
        buf[str_len] = 0;

        cout << buf << endl;
    }

    close(clnt_sock);
    return 0;
}