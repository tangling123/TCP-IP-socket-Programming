#include <iostream>
#include <unistd.h>
using namespace std;

int main() {
    pid_t pid = fork(); // 创建子进程

    if (pid == -1) {
        cout << "Error: failed to create child process!" << endl;
    }
    else if (pid == 0) {
        // 子进程执行的代码
        cout << "I'm the child process. My PID is " << getpid() << endl;
    }
    else {
        // 父进程执行的代码
        cout << "I'm the parent process. My PID is " << getpid() << endl;
    }

    cout << "This message is printed by both processes." << endl;

    return 0;
}
