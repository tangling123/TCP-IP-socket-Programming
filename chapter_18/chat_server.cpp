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
#define MAX_CLNT 256

//全局变量  临界区
int clnt_cnt, clnt_socks[MAX_CLNT];
pthread_mutex_t mutex;

void send_msg(char *msg, int len){  //向所有的客户端发送信息
    pthread_mutex_lock(&mutex);

    for (int i = 0; i < clnt_cnt; i++){
        write(clnt_socks[i], msg, len);
    }

    pthread_mutex_unlock(&mutex);
}

void* handle_clnt(void *arg){   //利用handle_clnt向所有连接的客户端发送消息
    int clnt_sock = *((int *)arg);
    int str_len = 0;
    char msg[BUF_SIZE];

    while ((str_len = read(clnt_sock, msg, sizeof(msg))) != 0)
        send_msg(msg, str_len);
        
    pthread_mutex_lock(&mutex);  //在互斥量上加锁

    //临界区
    for (int i = 0; i < clnt_cnt; i++){
        if (clnt_socks[i] == clnt_sock){    //移除clnt_sock客户端
            while (i+1 < clnt_cnt){
                clnt_socks[i] = clnt_socks[i+1];
                i++;
            }
            break;
        }
    }
    clnt_cnt--;

    pthread_mutex_unlock(&mutex);

    close(clnt_sock);
    return NULL;
}

int main(int argc, char *argv[]){
    if (argc != 2){
        cout << "Usage : <port>" << endl;
        return -1;
    }

    int serv_sock, clnt_sock;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_size;

    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1){
        cout << "server create socket error" << endl;
        return -1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        cout << "server bind socket error" << endl;
        return -1;
    }

    if (listen(serv_sock, 5) == -1){
        cout << "server listen socket error" << endl;
        return -1;
    }

    pthread_t t_id;

    while (1){
        clnt_size = sizeof(clnt_addr);

        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_size);
        if (clnt_sock == -1){
            cout << "server accept socket error" << endl;
            return -1;
        }

        pthread_mutex_lock(&mutex);     //利用互斥量来进行加锁

        clnt_socks[clnt_cnt++]  = clnt_sock;

        pthread_mutex_unlock(&mutex);

        //创建线程
        pthread_create(&t_id, NULL, handle_clnt, (void*)&clnt_sock);
        pthread_detach(t_id);

        cout << "connected client ip : " << inet_ntoa(clnt_addr.sin_addr) << endl;  //以点分十进制的形式输出IP地址
    }
}