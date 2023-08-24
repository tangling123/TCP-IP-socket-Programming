#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

#define BUF_SIZE 30

int main(int argc, char* argv[]){
    int sock;
    struct sockaddr_in serv_addr;
    socklen_t serv_size;

    if (argc != 3){
        cout << "Usage : <IP> <port>" << endl;
        return -1;
    }

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == -1){
        cout << "Client create socket error" << endl;
        return -1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    while (1){
        char message[30];
        cout << "Input quit or q to end client" << endl;
        cin.getline(message, BUF_SIZE);

        if (strcmp(message, "quit") == 0 || strcmp(message, "q") == 0)
            break;

        sendto(sock, message, strlen(message), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
        serv_size = sizeof(serv_addr);
        
        int str_len = recvfrom(sock, message, BUF_SIZE, 0, (struct sockaddr*)&serv_addr, &serv_size);
        message[str_len] = 0;
        cout << "Receive message from server : " << message << endl;
    }

    close(sock);

    return 0;
}