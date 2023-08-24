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

void read_childproc(int sig){   //用来打印结束的子进程PID和返回值
    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG);
    if (WIFEXITED(status)){
        cout << "Chile PID : " << pid << endl;
        cout << "Child proc send " << WEXITSTATUS(status) << endl;
    }
}

int main(int argc, char* argv[]){
    if (argc != 2){
        cout << "Usage : <IP>";
        return -1;
    }

    int serv_sock, clnt_sock, fds[2], str_len;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_size;
    char buf[BUF_SIZE], msg[BUF_SIZE];

    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1){
        cout << "Server create socket error" << endl;
        return -1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    if (bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1){
        cout << "Server bind socker error" << endl;
        return -1;
    }

    if (listen(serv_sock, 5) == -1){
        cout << "Server listen socker error" << endl;
        return -1;
    }

    //注册信号处理函数
    struct sigaction act;
    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGCHLD, &act, 0);

    //利用管道进行通信
    pipe(fds);
    pid_t pid = fork();
    if (pid == 0){  //第一个子进程用来将管道中读取到的信息保存到文件中
        FILE *fp = fopen("echomsg.txt", "wt");
        for (int i = 0; i < 3; i++){
            str_len = read(fds[0], msg, BUF_SIZE);
            fwrite(buf, 1, str_len, fp);    //被写入的数组指针，被写入元素的大小，写入元素的个数，文件指针
        }
        fclose(fp);
        return 0;
    } 

    while (1){
        //和服务端建立连接
        clnt_size = sizeof(clnt_addr);
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_size);
        if (clnt_sock == -1){
            cout << "Client accept error" << endl;
            continue;
        }else
            cout << "Connected success" << endl;

        //创建第二个子进程，从客户端中读取数据并将数据写到客户端和管道
        pid = fork();
        if (pid == 0){
            close(serv_sock);
            while ((str_len = read(clnt_sock, buf, BUF_SIZE)) != 0){
                write(clnt_sock, buf, str_len);
                write(fds[1], buf, str_len);
            }
            close(clnt_sock);
            cout << "Client disconnected..." << endl;
            return 0;
        }else
            close(clnt_sock);
    }

    close(serv_sock);
    return 0;
}