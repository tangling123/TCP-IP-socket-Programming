#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

#define BUF_SIZE 30

int main(int argc, char *argv[]){
    if (argc != 3){
        cout << "Usage : <port>" << endl;
        return -1;
    }

    int send_sock;
    struct sockaddr_in recv_addr;

    send_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (send_sock == -1){
        cout << "Send create socket error" << endl;
        return -1;
    }

    memset(&recv_addr, 0, sizeof(recv_addr));
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    recv_addr.sin_port = htons(atoi(argv[2]));

    if ((connect(send_sock, (struct sockaddr*)&recv_addr, sizeof(recv_addr))) == -1){
        cout << "Send connect error" << endl;
        return -1;
    }

    send(send_sock, "123", strlen("123"), 0);

    close(send_sock);
    return 0;
}