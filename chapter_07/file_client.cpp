#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

#define BUF_SIZE 30

int main(int argc, char *argv[]){
    int clnt_sock;
    struct sockaddr_in serv_addr;

    if (argc != 3){
        cout << "Usage : <IP> <port>" << endl;
        return -1;
    }

    clnt_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (clnt_sock == -1){
        cout << "Client create socket" << endl;
        return -1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(clnt_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        cout << "Client connect socket" << endl;
        return -1;
    } 

    FILE* fp = fopen("receive.dat", "wb");
    if (fp == NULL){
        cout << "File open error" << endl;
        return -1;
    }else{
        cout << "FILE open success" << endl;
    }

    int read_cnt;
    char buf[BUF_SIZE];

    while (read_cnt = read(clnt_sock, buf, sizeof(serv_addr)) != 0){
        fwrite((void*)buf, 1, read_cnt, fp);
    }

    cout << "Received file data" << endl;
    write(clnt_sock, "Thank you", 10);

    fclose(fp);
    close(clnt_sock);

    return 0;
}