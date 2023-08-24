#include <iostream>
#include <netdb.h>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
using namespace std;

int main(int argc, char *argv[]){
    int sock;
    int snd_buf, rcv_buf;
    socklen_t len;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1){
        cout << "Socket create error" << endl;
        return -1;
    }

    len = sizeof(snd_buf);
    if (getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void*)&snd_buf, &len) == 1)
        cout << "Get socket option failed" << endl;
    cout << "Output buffer size " << snd_buf << endl;

    if (getsockopt(sock, SOL_SOCKET, SO_RCVBUF, (void*)&rcv_buf, &len) == -1)
        cout << "Get socket option failed" << endl;
    cout << "Imput buffer size " << rcv_buf << endl;

    close(sock);
    return 0;
}