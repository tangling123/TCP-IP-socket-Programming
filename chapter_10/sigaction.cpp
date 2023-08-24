#include <iostream>
#include <signal.h>
#include <unistd.h>
using namespace std;

void timeout(int sig){
    if (sig == SIGALRM)
        cout << "Time out !" << endl;
    alarm(2);
}

int main(int argc, char *argv[]){
    struct sigaction act;
    act.sa_handler = timeout; //信号处理函数
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    sigaction(SIGALRM, &act, 0);
    alarm(2);

    for (int i = 0; i < 3; i++){
        cout << "wait ..." << endl;
        sleep(100);
    }

    return 0;
}