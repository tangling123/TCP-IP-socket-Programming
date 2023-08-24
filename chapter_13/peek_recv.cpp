#include <iostream>
#include <cstring>
#include <signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
using namespace std;

#define BUF_SIZE 30

int main(int argc, char *argv[]){
    if (argc != 2){
        cout << "Usage : <port>" << endl;
        return -1;
    }

    int recv_sock, send_sock;
    struct sockaddr_in send_addr, recv_addr;
    socklen_t recv_size;
    char buf[BUF_SIZE];

    send_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (send_sock == -1){
        cout << "Send socket error" << endl;
        return -1;
    }

    memset(&send_addr, 0, sizeof(send_addr));
    send_addr.sin_family = AF_INET;
    send_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    send_addr.sin_port = htons(atoi(argv[1]));

    if (bind(send_sock, (struct sockaddr*)&send_addr, sizeof(send_addr)) == -1){
        cout << "Send bind error" << endl;
        return -1;
    }

    if (listen(send_sock, 5) == -1){
        cout << "Send listen error" << endl;
        return -1;
    }

    recv_size = sizeof(recv_addr);
    recv_sock = accept(send_sock, (struct sockaddr*)&recv_addr, &recv_size);
    if (recv_sock == -1){
        cout << "Recv accept error" << endl;
        return -1;
    }

    int str_len;
    //从send中读取数据
    while (1){
        str_len = recv(recv_sock, buf, BUF_SIZE, MSG_PEEK | MSG_DONTWAIT);
        if (str_len > 0)    break;
    }

    buf[str_len] = 0;
    cout << "Buffering : " << buf << endl;

    //再次读取缓冲区中的数据
    memset(&buf, 0, sizeof(buf));   
    str_len = recv(recv_sock, buf, BUF_SIZE, 0);
    buf[str_len] = 0;
    cout << "Read again : " << buf << endl;

    close(send_sock), close(recv_sock);
    return 0;
}