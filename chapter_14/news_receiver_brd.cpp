#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
using namespace std;

#define BUF_SIZE 30

int main(int argc, char *argv[]){
    if (argc != 3){
        cout << "Usage : <GroupIP> <PORT>" << endl;
        return -1;
    }

    int recv_sock;
    struct sockaddr_in addr;
    char buf[BUF_SIZE];

    recv_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (recv_sock == -1){
        cout << "Recv create socket error" << endl;
        return -1;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(atoi(argv[2]));

    if (bind(recv_sock, (struct sockaddr*)&addr, sizeof(addr)) == -1){
        cout << "Recv bind socket error" << endl;
        return -1;
    }

    struct ip_mreq join_addr;   //加入多播组
    join_addr.imr_multiaddr.s_addr = inet_addr(argv[1]);    //加入组的IP地址
    join_addr.imr_interface.s_addr = htonl(INADDR_ANY);     //加入该组的套接字所属主机的IP地址

    setsockopt(recv_sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &join_addr, sizeof(join_addr));    //设置套接字选项，加入多播组

    while (1){
        int str_len = recvfrom(recv_sock, buf, BUF_SIZE, 0, NULL, 0);   //不需要知道传输数据的主机地址信息，将最后两个参数设为NULL和0
        if (str_len < 0)    break;
        buf[str_len] = 0;
        cout << buf << endl;
    }

    close(recv_sock);
    return 0;
}