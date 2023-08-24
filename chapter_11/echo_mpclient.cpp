#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
using namespace std;

#define BUF_SIZE 1024

void read_routine(int sock, char *buf){
    while (1){
        int str_len = read(sock, buf, BUF_SIZE-1);
        if (str_len == 0)   return ;
        buf[str_len] = 0;
        cout << "Message from server : " << buf << endl;
    }
}

void write_routine(int sock, char *buf){
    while (1){
        memset(buf, 0, sizeof(buf));
        cin.getline(buf, BUF_SIZE-1);
        if (!strcmp(buf, "q\n") || !strcmp(buf, "Q\n")){
            shutdown(sock, SHUT_WR);
            return ;
        }
        write(sock, buf, strlen(buf));
    }
}

int main(int argc, char* argv[]){
    if (argc != 3){
        cout << "Usage : <IP> <address>" << endl;
        return -1;
    }

    int clnt_sock;
    struct sockaddr_in serv_addr;
    socklen_t serv_size;

    clnt_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (clnt_sock == -1){
        cout << "Client create socket error" << endl;
        return -1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(clnt_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        cout << "Client bind socket error" << endl;
        return -1;
    }

    pid_t pid = fork();
    char buf[BUF_SIZE];

    if (pid == 0){
        write_routine(clnt_sock, buf);
    }else{
        read_routine(clnt_sock, buf);
    }

    close(clnt_sock);
    return 0;
}