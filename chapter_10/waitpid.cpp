#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main(int argc, char* argv[]){
    int status;

    pid_t pid = fork();

    if (pid == 0){
        sleep(15);  //子进程休眠15s之后返回24
        return 24;
    }else{
        while (waitpid(-1, &status, WNOHANG) == 0){ //当没有子进程结束时返回0，子进程结束时返回其PID
            sleep(3);
            cout << "Sleep 3 sec" << endl;
        }
        
        // while (wait(&status) == 0){              //对于wait函数而言，会一直阻塞在这一行，直到有子进程结束（while循环里面的语句并不会执行）
        //     sleep(3);
        //     cout << "Sleep 3 sec" << endl;
        // }

        if (WIFEXITED(status))
            cout << "Child send " << WEXITSTATUS(status) << endl;
    }

    return 0;
}