#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
using namespace std;
#define BUF_SIZE 1024

int main(int argc, char* argv[]){
    int serv_sock, clnt_sock, size = 128;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_size;
    char buf[BUF_SIZE];

    if (argc != 2){
        cout << "Usage : " << argv[0] << "<port>" << endl;
        return -1;
    }


    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1){
        cout << "server socket create error" << endl;
        return -1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        cout << "server socket bind error" << endl;
        return -1;
    }

    if (listen(serv_sock, 5) == -1){
        cout << "server socket listen error" << endl;
        return -1;
    }

    clnt_size = sizeof(clnt_addr);
    
    //和之前的hello_serv不同的地方，在外层使用一个for循环
    for (int i = 1; i <= 5; i++){
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_size);
        if (clnt_sock == -1){
            cout << "server socket accept error" << endl;
            return -1;
        }

        cout << "Hello Client : " << i << endl;

        //使用FILE结构体指针来交换数据，将对应的文件描述符转换为FILE指针来进行操作，可以提高传输的速度
        FILE *readfp = fdopen(clnt_sock, "r");
        FILE *writefp = fdopen(clnt_sock, "w");

        while (!feof(readfp)){
            fgets(buf, BUF_SIZE, readfp);   //从readfp所指的文件中读取BUF_SIZE个字节的数据到buf中
            fputs(buf, writefp);            //将buf中的数据写入到writefp所指的文件中
            fflush(writefp);
        }

        fclose(readfp);
        fclose(writefp);                   //关闭readfp和writefp之后，对应的文件描述符也会被关闭
    }

    close(serv_sock);
    return 0;
}