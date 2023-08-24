#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main(int argc, char *argv[]){
    int status;

    pid_t pid = fork();

    if (pid == 0){
        return 3;   //第一个子进程直接返回3
    }else{
        cout << "Child PID : " << pid << endl;
        pid = fork();   //父进程创建第二个子进程

        if (pid == 0){
            exit(7);
        }else{
            cout << "Child PID : " << pid << endl;
            wait(&status);  //阻塞直到有一个子进程终止

            if (WIFEXITED(status))    //子进程正常返回时，打印子进程的返回值
                cout << "Child send one : " << WEXITSTATUS(status) << endl;

            wait(&status);

            if (WIFEXITED(status))
                cout << "Child send two : " << WEXITSTATUS(status) << endl;

            sleep(30);
        }
    }
    
    return 0;
}