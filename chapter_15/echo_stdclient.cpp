#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;
#define BUF_SIZE 1024

int main(int argc, char* argv[]){
    int clnt_sock;
    struct sockaddr_in serv_addr;
    char buf[BUF_SIZE];

    if (argc != 3){
        cout << "Usage : <IP> <port>" << endl;
        return -1;
    }

    clnt_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (clnt_sock == -1){
        cout << "server socket create error" << endl;
        return -1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(clnt_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        cout << "Connect to server error" << endl;
        return -1;
    }

    FILE *readfp = fdopen(clnt_sock, "r");
    FILE *writefp = fdopen(clnt_sock, "w");

    while (1){
        //客户端从标准输入中获取数据
        cout << "Input message (Q to quit)" << endl;
        cin.getline(buf, BUF_SIZE);

        if (strcmp(buf, "Q") == 0)  break;

        //利用FILE指针来读取文件
        fputs(buf, writefp);
        fflush(writefp);

        fgets(buf, BUF_SIZE, readfp);

        cout << "Message form server : " << buf << endl;
    }

    fclose(readfp), fclose(writefp);
    return 0;
}