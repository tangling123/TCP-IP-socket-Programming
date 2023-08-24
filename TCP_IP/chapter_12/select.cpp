#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/select.h>
using namespace std;

#define BUF_SIZE 30

int main(int argc, char *argv[]){
    int fd = 0;
    fd_set reads, temp;
    struct timeval timeout;
    char buf[BUF_SIZE];

    //1、设置文件描述符
    FD_ZERO(&reads);
    FD_SET(fd, &reads);

    while (1){
        //设置超时
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;

        temp = reads;
        //指定监视范围
        int result = select(fd+1, &temp, 0, 0, &timeout);
        if (result == -1){
            cout << "select error" << endl;
            return -1;
        }else if (result == 0){
            cout << "time out!" << endl;
        }else{
            if (FD_ISSET(fd, &temp)){   //fd中有待读取的数据
                int str_len = read(fd, buf, BUF_SIZE);
                buf[str_len] = 0;
                cout << "Message from console : " << buf << endl;
            }
        }
    }

    return 0;
}