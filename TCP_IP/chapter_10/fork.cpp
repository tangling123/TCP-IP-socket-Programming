#include <iostream>
#include <unistd.h>
using namespace std;

int gval = 10;

int main(int argc, char* argv[]){
    pid_t pid;
    int lval = 20;
    gval++, lval += 5;

    pid = fork();
    if (pid == 0)   //if children process
        gval += 2, lval += 2;
    else
        gval -= 2, lval -= 2;

    if (pid == 0)
        cout << "Child Proc : " << gval << " " << lval << endl;
    else
        cout << "Parent Proc : " << gval << " " << lval << endl;

    return 0;
}