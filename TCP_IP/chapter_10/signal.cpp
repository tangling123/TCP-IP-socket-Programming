#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

void timeout(int sig){
    if (sig == SIGALRM){
        cout << "Time out!" << endl;
    }
    alarm(2);   //每隔2s产生一个SIGALRM信号
    //第一次在main函数中产生一个SIGALRM信号时调用timeout函数，timeout函数每隔2s产生一个SIGALRM信号
}

void keycontrol(int sig){
    if (sig == SIGINT)
        cout << "CTRL + C pressed" << endl;
}

int main(int argc, char* argv[]){
    signal(SIGALRM, timeout);
    signal(SIGINT, keycontrol);

    alarm(2);   //预约2s后产生SIGALRM信号

    for (int i = 0; i < 3; i++){
        cout << "wait ..." << endl;
        sleep(100);
    }

    return 0;
}