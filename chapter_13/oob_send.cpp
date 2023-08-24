#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

#define BUF_SIZE 30

int main(int argc, char *argv[]){
    if (argc != 3){
        cout << "Usage : <IP> <port>" << endl;
        return -1;
    }

    int sock;
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1){
        cout << "Send create socket error" << endl;
        return -1;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) == -1){
        cout << "Send connect error" << endl;
        return -1;
    }

    write(sock, "123", strlen("123"));          //利用write函数向sock发送数据
    send(sock, "4", strlen("4"), MSG_OOB);      //利用send函数来传输紧急消息
    write(sock, "567", strlen("567"));  
    send(sock, "890", strlen("890"), MSG_OOB);

    close(sock);
    return 0;
}