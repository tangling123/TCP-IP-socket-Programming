#include <iostream>
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

#define BUF_SIZE 30

int main(int argc, char *argv[]){
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_size;
    char message[30];

    if (argc != 2){
        cout << "Usage : " << argv[0] << "<port>" << endl;
        return -1;
    }

    serv_sock = socket(AF_INET, SOCK_DGRAM, 0); //Using UDP
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
    }

    //differrnt to TCP, UDP hasn't listen and accept function
    while (1){
        clnt_size = sizeof(clnt_addr);
        int str_len = recvfrom(serv_sock, message, BUF_SIZE, 0, (struct sockaddr*)&clnt_addr, &clnt_size);
        sendto(serv_sock, message, str_len, 0, (struct sockaddr*)&clnt_addr, clnt_size);
    }

    close(serv_sock);
    close(clnt_sock);

    return 0;
}