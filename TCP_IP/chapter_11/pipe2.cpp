#include <iostream>
#include <cstring>
#include <unistd.h>
using namespace std;

#define BUF_SIZE 1024

int main(int argc, char *argv[]){
    int fds[2];
    char buf[BUF_SIZE];
    char str1[] = "Who are you", str2[] = "Tank you for your message";

    pipe(fds);          //建立管道
    pid_t pid = fork();

    if (pid == 0){      //子进程管道中的数据写到fds[1]，再从fds[0]中读取父进程从管道传输过来的数据
        write(fds[1], str1, strlen(str1));

        sleep(2);
        
        memset(&buf, 0, sizeof(buf));
        read(fds[0], buf, BUF_SIZE);
        cout << "Child proc output : " << buf << endl;
    }else{             //在父进程从fds[0]中读取管道传输过来的数据，再利用管道将父进程的数据写到管道
        int str_len = read(fds[0], buf, BUF_SIZE-1);
        buf[str_len] = 0;
        cout << "Parent proc output : " << buf << endl;

        write(fds[1], str2, strlen(str2));
        sleep(3);
    }

    return 0;
}