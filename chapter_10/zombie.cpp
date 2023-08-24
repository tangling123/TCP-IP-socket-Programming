#include <iostream>
#include <unistd.h>
using namespace std;

int main(int argc, char *argv[]){
    pid_t pid = fork(); //调用fork函数会创建一个新的子进程，子进程和父进程之间是相互独立执行的

    if (pid == 0){
        cout << "Hi, I am a child  process" << endl;
    }else{
        //在父进程中休眠30s,延缓程序的结束(父进程结束之后，其子进程也会被释放)
        cout << "Child PID : " << pid << endl;
        sleep(30);
    }

    if (pid == 0)
        cout << "End child process" << endl;
    else
        cout << "End parent process" << endl;

    return 0;
}