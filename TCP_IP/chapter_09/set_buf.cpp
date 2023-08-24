#include <iostream>
#include <netdb.h>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
using namespace std;

int main(int argc, char *argv[]){
    int sock, snd_buf = 3 * 1024, rcv_buf = 3 * 1024;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    //SO_RCVBUF接收方向的输入缓冲，首先将I/O缓冲区大小更改为3K，为了验证缓冲区的更改在进行读取
    if (setsockopt(sock, SOL_SOCKET, SO_RCVBUF, &rcv_buf, sizeof(rcv_buf)) == -1){
        cout << "Set socket option failed" << endl;
    }

    socklen_t len = sizeof(rcv_buf);
    if (getsockopt(sock, SOL_SOCKET, SO_RCVBUF, &rcv_buf, &len) == -1){
        cout << "Get socket option failed" << endl;
    }else{
        cout << "Input buffer size : " << rcv_buf << endl;
    }

    //SO_SNDBUF接收方向的输出缓冲
    if (setsockopt(sock, SOL_SOCKET, SO_SNDBUF, &snd_buf, sizeof(snd_buf)) == -1){
        cout << "Set socket option failed" << endl;
    }

    len = sizeof(snd_buf);
    if (getsockopt(sock, SOL_SOCKET, SO_SNDBUF, &snd_buf, &len) == -1){
        cout << "Get socket option failed" << endl;
    }else{
        cout << "Output buffer size : " << snd_buf << endl;
    }

    close(sock);
    return 0;
}