#include <iostream>
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

#define BUF_SIZE 30

int main(int argc, char* argv[]){
    int clnt_sock;
    struct sockaddr_in serv_addr;
    socklen_t serv_size;
    char message[BUF_SIZE];

    if (argc != 3){
        cout << "Usage : <IP> <port>" << endl;
        return -1; 
    }

    clnt_sock = socket(AF_INET, SOCK_DGRAM, 0);//UDP协议
    if (clnt_sock == -1){
        cout << "Client create socket error" << endl;
        return -1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    while (1){
        //客户端向服务端发送信息
        cout << "Please input message:" << endl;
        cin.getline(message, BUF_SIZE); //读取一整行
        if (strcmp(message, "quit") == 0 || strcmp(message, "q") == 0)
            break;

        sendto(clnt_sock, message, strlen(message), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
        serv_size = sizeof(serv_addr);

        //在服务端发送了两次数据，相应的客户端也应该读取两次
        serv_size = sizeof(serv_addr);
        int recv_len = recvfrom(clnt_sock, message, BUF_SIZE, 0, (struct sockaddr*)&serv_addr, &serv_size);
        message[recv_len] = 0;
        cout << message;

        recv_len = recvfrom(clnt_sock, message, BUF_SIZE, 0, (struct sockaddr*)&serv_addr, &serv_size);
        message[recv_len] = 0;
        cout << message << endl;
    }

    close(clnt_sock);
    return 0; 
}