#include <iostream>
#include <cstring>
#include <signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
using namespace std;

#define BUF_SIZE 30
int send_sock, recv_sock;

void urg_handler(int sig){  //信号处理函数
    char str[BUF_SIZE];
    memset(str, 0, sizeof(str));
    int str_len = recv(recv_sock, str, sizeof(str)-1, MSG_OOB);//MSG_OOB用于传输带外数据
    str[str_len] = 0;
    cout << "Urgent message : " << str << endl;
}

int main(int argc, char *argv[]){
    //类似于服务端接收客户端的链接
    if (argc != 2){
        cout << "Usage : <port>" << endl;
        return -1;
    }

    struct sockaddr_in send_addr, recv_addr;
    socklen_t recv_size;
    char buf[BUF_SIZE];

    send_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (send_sock == -1){
        cout << "Send socket error" << endl;
        return -1;
    }

    memset(&send_addr, 0, sizeof(send_addr));
    send_addr.sin_family = AF_INET;
    send_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    send_addr.sin_port = htons(atoi(argv[1]));

    if (bind(send_sock, (struct sockaddr*)&send_addr, sizeof(send_addr)) == -1){
        cout << "Send bind error" << endl;
        return -1;
    }

    if (listen(send_sock, 5) == -1){
        cout << "Send listen error" << endl;
        return -1;
    }

    recv_size = sizeof(recv_addr);
    recv_sock = accept(send_sock, (struct sockaddr*)&recv_addr, &recv_size);
    if (recv_sock == -1){
        cout << "Recv accept error" << endl;
        return -1;
    }

    cout << "acctpt recv_sock : " << recv_sock << endl;

    fcntl(recv_sock, F_SETOWN, getpid());
    //文件描述符recv_sock指向的套接字引发的SIGURG信号处理进程将变为gitpid函数返回值用作ID的进程

     //注册信号处理函数
    struct sigaction act;
    act.sa_handler = urg_handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    int status = sigaction(SIGURG, &act, 0);
    cout << "status : " << status << endl;

    int str_len;
    while ((str_len = recv(recv_sock, buf, sizeof(buf)-1, 0)) != 0){
        if (str_len == -1)
            continue;;
        buf[str_len] = 0;
        cout << buf << endl;
    }

    close(send_sock), close(recv_sock);
    return 0;
}