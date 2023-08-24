#include <iostream>
#include <netdb.h>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
using namespace std;

int main(int argc, char *argv[]){
    int tcp_sock, udp_sock;
    int sock_type;
    socklen_t optlen;

    tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
    udp_sock = socket(AF_INET, SOCK_DGRAM, 0);

    cout << "SOCK_STREAM : " << SOCK_STREAM << endl;
    cout << "SOCK_DGRAM : " << SOCK_DGRAM << endl;

    optlen = sizeof(sock_type);
    //查看SOL_SOCKET层的SO_TYPE可选项的套接字类型
    if (getsockopt(tcp_sock, SOL_SOCKET, SO_TYPE, (void*)&sock_type, &optlen) == -1){
        cout << "Get sock option failed " << endl;
    }
    cout << "Socket type one : " << sock_type << endl;

    if (getsockopt(udp_sock, SOL_SOCKET, SO_TYPE, (void*)&sock_type, &optlen) == -1){
        cout << "Get sock option failed " << endl;
    }
    cout << "Socket type two : " << sock_type << endl;

    return 0;
}