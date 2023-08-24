#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;
//create Hello World server

int main(int argc, char* argv[]){
    int sock;
    sockaddr_in serv_addr;
    char buf[128] = "";

    if (argc != 3){
        cout << "Invalid parameters" << endl;
        return -1;
    }

    //for client only two thing: create socket and connect to server
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1){
        cout << "client socket error" << endl;
        return -1;
    }

    //connect to server
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        cout << "client connect error" << endl;
        return -1;
    }

    for (int i = 1; i < 5000; i++)
        cout << i << " ";
    int recv_len = recv(sock, buf, sizeof(buf), 0);
    if (recv_len == -1){
        cout << "client receive error" << endl;
        return -1;
    }

    // cout << "recv function received message : " << buf << endl;

    // int read_len = read(sock, buf, sizeof(buf));
    // if (recv_len == -1){
    //     cout << "client receive error" << endl;
    //     return -1;
    // }

    // cout << "read function received message : " << buf << endl;
    close(sock);

    return 0;
}