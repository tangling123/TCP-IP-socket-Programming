#include <iostream>
#include <cstring>
#include <unistd.h>
using namespace std;

#define BUF_SIZE 1024

int main(int argc, char *argv[]){
    int fds1[2], fds2[2];
    char buf[BUF_SIZE], str[BUF_SIZE];

    pipe(fds1), pipe(fds2);          //建立管道
    pid_t pid = fork();

    if (pid == 0){      //子进程利用fds1管道来写数据，fds2管道来接收数据
        cout << "Trasmission data by child proc : ";
        cin.getline(str, BUF_SIZE);
        write(fds1[1], str, strlen(str));

        memset(&buf, 0, sizeof(buf));
        read(fds2[0], buf, BUF_SIZE);
        cout << "Child proc output : " << buf << endl;
    }else{             //父进程利用fds1管道来接受数据，fds2管道来写数据
        int str_len = read(fds1[0], buf, BUF_SIZE-1);
        buf[str_len] = 0;
        cout << "Parent proc output : " << buf << endl;

        cout << "Trasmission data by parent proc : ";
        cin.getline(str, BUF_SIZE);
        write(fds2[1], str, strlen(str));
    }

    return 0;
}