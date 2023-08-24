#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/wait.h>
using namespace std;

#define BUF_SIZE 32

void read_childproc(int sig){
    //在子进程结束时调用的处理函数，用来输出结束的子进程的PID和返回值
    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG);
    if (WIFEXITED(status)){
        cout << "Remove proc id : " << pid << endl;
        cout << "Child send : " << WEXITSTATUS(status) << endl;
    }
}

int main(int argc, char* argv[]){
    //创建服务端的代码
    if (argc != 2){
        cout << "Usage : <port>" << endl;
        return -1;
    }

    int serv_sock, clnt_sock, str_len;
    sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_size;
    char buf[BUF_SIZE];

    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1){
        cout << "Server socket create error" << endl;
        return -1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        cout << "Server socket bind error" << endl;
        return -1;
    }

    if (listen(serv_sock, 5) == -1){
        cout << "Server socket listen error" << endl;
        return -1;
    }

    //注册信号处理函数
    struct sigaction act;
    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    while (1){
        clnt_size = sizeof(clnt_addr);
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_size);
        if (clnt_sock == -1){
            cout << "Client socket create error" << endl;
            continue;
        }else
            cout << "New client connnected" << endl;

        //通过fork函数来创建子进程为多个客户端提供服务
        pid_t pid = fork();
        if (pid == -1){     //子进程创建失败
            close(clnt_sock);
            continue;
        }

        if (pid == 0){     //利用创建的子进程来向客户端提供服务，将从客户端收到的信息发送回去
            close(serv_sock);   //由于创建的子进程和父进程共享同一份代码和数据，所以在子进程中也会创建一个客户端
            write(clnt_sock, "Server send", sizeof("Server send"));//为了表明数据是从服务端发送过去，而不是客户端读取自己的信息
            while ((str_len = read(clnt_sock, buf, BUF_SIZE)) != 0){
                write(clnt_sock, buf, str_len);
            }
            close(clnt_sock);   //关闭客户端
            cout << "Client disconnected" << endl;
            return 0;
        }else{
            close(clnt_sock);
        }
    }
    
    close(serv_sock);
    return 0;
}