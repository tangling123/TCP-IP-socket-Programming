#include <iostream>
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

#define BUF_SIZE 30

int main(int argc, char *argv[]){
    int serv_sock;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_size;
    char message[BUF_SIZE];

    if (argc != 2){
        cout << "Usage : <port>" << endl;
        return -1; 
    }

    serv_sock = socket(AF_INET, SOCK_DGRAM, 0);//使用UDP协议
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
    }else
        cout << "Server bind success" << endl;

    while (1){
        //当从客户端收到信息，将信息发送回去
        clnt_size = sizeof(clnt_addr);
        memset(message, 0, sizeof(message));    //清空message数组
        int recv_len = recvfrom(serv_sock, message, BUF_SIZE, 0, (struct sockaddr*)&clnt_addr, &clnt_size);

        cout << "Received :" << message << endl;

        sendto(serv_sock, "Server send:", sizeof("Server send:"), 0, (struct sockaddr*)&clnt_addr, clnt_size);
        sendto(serv_sock, message, recv_len, 0, (struct sockaddr*)&clnt_addr, clnt_size);
    }

    close(serv_sock);
    return 0;
}