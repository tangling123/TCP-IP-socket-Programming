#include <iostream>
#include <fcntl.h>
#include <stdio.h>
using namespace std;

int main(int argc, char *argv[]){
    int fd = open("open.dat", O_WRONLY | O_CREAT | O_TRUNC);
    if (fd == -1){
        cout << "File open error" << endl;
        return -1;
    }

    cout << "First file descriptor : " << fd << endl;
    FILE *fp = fdopen(fd, "w");
    fputs("Network CPP programming\n", fp);
    cout << "Second file descriptor : " << fileno(fp) << endl;

    return 0;
}