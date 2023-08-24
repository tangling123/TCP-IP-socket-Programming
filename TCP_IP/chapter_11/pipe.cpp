#include <iostream>
#include <cstring>
#include <unistd.h>
using namespace std;

#define BUF_SIZE 1024

int main(int argc, char *argv[]){
    int fds[2];
    char buf[BUF_SIZE];
    char str[BUF_SIZE];

    pipe(fds);          //建立管道
    pid_t pid = fork();

    if (pid == 0){      //子进程管道中的数据写到fds[1]
        cout << "Trasmission data : ";
        cin.getline(str, BUF_SIZE);
        write(fds[1], str, strlen(str));
    }else{             //在父进程从fds[0]中读取管道传输过来的数据
        memset(buf, 0, sizeof(buf));
        int str_len = read(fds[0], buf, BUF_SIZE-1);
        buf[str_len] = 0;
        cout << "Receive data by pipe : " << buf << endl;
    }

    return 0;
}