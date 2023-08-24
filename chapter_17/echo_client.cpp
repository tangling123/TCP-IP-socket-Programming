#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
using namespace std;

#define BUF_SIZE 100

int main(int argc, char *argv[]){
    if (argc != 3){
        cout << "Usage : <IP> <port>" << endl;
        return -1;
    }

    int clnt_sock;
    struct sockaddr_in serv_addr;
    char msg[BUF_SIZE];

    clnt_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (clnt_sock == -1){
        cout << "client create socket error" << endl;
        return -1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(clnt_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        cout << "client connect error" << endl;
        return -1;
    }else
        cout << "connected ..." << endl;

    // FILE *readfp = fdopen(clnt_sock, "r");
    // FILE *writefp = fdopen(clnt_sock, "w");

    while (1){
        cout << "Please input message (Q to quit): " << endl;
        cin.getline(msg, BUF_SIZE);

        if (strcmp(msg, "Q") == 0)  break;

        write(clnt_sock, msg, strlen(msg));

        int str_len = read(clnt_sock, msg, BUF_SIZE);
        msg[str_len] = 0;
        cout << "received from server : " << msg << endl;
        // 将上述代码替换为标准I/O函数

        // fputs(msg, writefp);
        // fflush(writefp);
        // fgets(msg, BUF_SIZE, readfp);
        // cout << "received from server : " << msg << endl;
    }

    close(clnt_sock);
    // fclose(readfp), fclose(writefp);

    return 0;
}