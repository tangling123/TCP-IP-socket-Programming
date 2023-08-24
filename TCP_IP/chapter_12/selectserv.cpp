#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <algorithm>
using namespace std;

#define BUF_SIZE 100

int main(int argc, char *argv[]){
    if (argc != 2){
        cout << "Usage : <port>" << endl;
        return -1;
    }

    int serv_sock, clnt_sock;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_size;
    char buf[BUF_SIZE];

    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1){
        cout << "Server create socket error" << endl;
        return -1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        cout << "Server bind socket error" << endl;
        return -1;
    }

    if (listen(serv_sock, 5) == -1){
        cout << "Server listen socket error" << endl;
        return -1;
    }

    int fd_max = -1;
    fd_set reads, temp;

    //设置文件描述符
    FD_ZERO(&reads);
    FD_SET(serv_sock, &reads);
    fd_max = max(fd_max, serv_sock);
    struct timeval timeout;

    while (1){
        timeout.tv_sec = 5, timeout.tv_usec = 0;
        temp = reads;

        int result = select(fd_max+1, &temp, 0, 0, &timeout);
        if (result == -1){
            cout << "select error" << endl;
            break;
        }else if (result == 0){
            cout << "Time out ..." << endl;
            continue;
        }

        for (int i = 0; i <= fd_max; i++){
            if (FD_ISSET(i, &temp)){    //套接字文件描述符在集合temp中
                if (i == serv_sock){    //服务端的套接字发生了变化
                    clnt_size = sizeof(clnt_addr);
                    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_size);
                    // if (clnt_sock == -1){
                    //     cout << "Server accept client connect error" << endl;
                    //     continue;
                    // }
                    FD_SET(clnt_sock, &reads);  //将客户端的套接字加入到reads中
                    fd_max = max(fd_max, clnt_sock);
                    cout << "Connect client : " << clnt_sock << endl;
                }else{
                    int str_len = read(i, buf, BUF_SIZE);
                    if (str_len == 0){      //到达文件末尾EOF,断开连接
                        FD_CLR(i, &reads);
                        close(i);
                        cout << "Closed client " << i << endl;
                    }else   
                        write(i, buf, str_len);
                }
            }
        }
    }

    close(serv_sock);
    return 0;
}