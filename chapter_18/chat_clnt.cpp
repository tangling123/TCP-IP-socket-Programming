#include <iostream>
#include <thread>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
using namespace std;

#define BUF_SIZE 100
#define NAME_SIZE 20

char name[NAME_SIZE] = "[DEFAULT]";
char msg[BUF_SIZE];

void* send_msg(void *arg){  //利用线程将客户端的输入输出进行分离
    int sock = *((int *)arg);
    char name_msg[NAME_SIZE + BUF_SIZE];
    while (1){
        cin.getline(msg, BUF_SIZE);
        if (strcmp(msg, "Q") == 0 || strcmp(msg, "q") == 0){
            close(sock);
            exit(0);
        }
        sprintf(name_msg, "%s %s", name, msg);
        write(sock, name_msg, strlen(name_msg));    //向sock写入name_msg
    }
    return NULL;
}

void* recv_msg(void *arg){
    int sock = *((int *)arg);
    char name_msg[NAME_SIZE + BUF_SIZE];
    while (1){
        int str_len = read(sock, name_msg, NAME_SIZE + BUF_SIZE - 1);
        if (str_len == -1)
            return (void*) -1;
        name_msg[str_len] = 0;
        cout << name_msg << endl;                   //读取来自sock的消息
    }
    return NULL;
}

int main(int argc, char *argv[]){
    if (argc != 4){
        cout << "Usage : <IP> <port> <name>" << endl;
        return -1;
    }

    int clnt_sock;
    struct sockaddr_in serv_addr;

    sprintf(name, "[%s]", argv[3]);     //user name

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
        cout << "client connect to server error" << endl;
    }

    pthread_t send_thread, recv_thread;

    pthread_create(&send_thread, NULL, send_msg, (void*)&clnt_sock);
    pthread_create(&recv_thread, NULL, recv_msg, (void*)&clnt_sock);

    /*
    pthread_detach(send_thread);
    pthread_detach(recv_thread);
    将代码修改，那么客户端会立即结束
    */ 

    pthread_join(send_thread, NULL);
    pthread_join(recv_thread, NULL);

    close(clnt_sock);
    return 0;
}