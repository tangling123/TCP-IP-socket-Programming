#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
using namespace std;

void read_childproc(int sig){
    int status;
    //等待任意子进程的终止，如果没有终止的子进程也不会进入阻塞状态，成功时返回子进程的ID或0
    pid_t id = waitpid(-1, &status, WNOHANG);   //在子进程结束的时候调用该函数，所以id返回的是结束子进程ID
    if (WIFEXITED(status)){                     
        cout << "Remove proc id " << id << endl;
        cout << "Child send " << WEXITSTATUS(status) << endl;
    }
}

int main(int argc, char *argv[]){
    //注册SIGCHLD信号对应的处理器
    struct sigaction act;
    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);  //传入的是地址
    act.sa_flags = 0;
    sigaction(SIGCHLD, &act, 0);    

    pid_t pid = fork();
    if (pid == 0){      //第一个子进程休眠10s，返回12
        cout << "Hi, I'm a child process" << endl;
        sleep(10);
        return 12;
    }else{              //父进程
        cout << "Child proc id " << pid << endl;
        pid = fork();
        if (pid == 0){  //第二个子进程，休眠10s，返回24
            cout << "Hi, I'm a child process" << endl;
            sleep(10);
            exit(24);
        }else{
            cout << "Child proc id " << pid << endl;
            for (int i = 0; i < 5; i++){
                cout << "wait ..." << endl;
                sleep(5);
            }
        }
    }

    return 0;
}