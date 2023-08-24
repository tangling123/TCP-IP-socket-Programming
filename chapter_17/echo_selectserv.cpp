#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <algorithm>
using namespace std;

#define BUF_SIZE 100

//将第10章的read、write函数改为标准I/O函数

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

    //实现基于select的多路复用
    fd_set reads, temp;
    int fd_max = -1;

    FD_ZERO(&reads);
    FD_SET(serv_sock, &reads);
    fd_max = serv_sock;

    struct timeval timeout;
    while (1){
        temp = reads;
        timeout.tv_sec = 5, timeout.tv_usec = 0;

        int fd_num = select(fd_max+1, &temp, 0, 0, &timeout);

        if (fd_num == -1){
            cout << "select error" << endl;
            return -1;
        }else if (fd_num == 0){
            cout << "Time out..." << endl;
            continue;
        }

        for (int i = 0 ; i <= fd_max; i++){
            if (FD_ISSET(i, &temp)){
                if (i == serv_sock){
                    clnt_size = sizeof(clnt_sock);
                    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_size);
                    if (clnt_sock == -1){
                        cout << "server accept error" << endl;
                        break;
                    }
                    fd_max = max(fd_max, clnt_sock);
                    FD_SET(clnt_sock, &reads);
                    cout << "connect client : " << i << endl;
                }else{
                    int str_len = read(i, buf, BUF_SIZE);
                    if (str_len == 0){
                        FD_CLR(i, &reads);
                        close(i);
                        cout << "closed client : " << i << endl;
                    }else   
                        write(i, buf, str_len);

                    // 替换为标准I/O函数
                    // FILE *readfp = fdopen(i, "r");
                    // FILE *writefp = fdopen(i, "w"); 
                    // if (!feof(readfp)){
                    //     fgets(buf, BUF_SIZE, readfp);
                    //     fputs(buf, writefp);
                    //     fflush(writefp);
                    // }else{
                    //     FD_CLR(i, &reads);  //将文件描述符i从集合reads中移除
                    //     fclose(readfp), fclose(writefp);
                        
                    //     cout << "closed client : " << i << endl;
                    // }
                }
            }
        }
    }

    close(clnt_sock), close(serv_sock);
    return 0;
}