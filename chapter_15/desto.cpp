#include <stdio.h>
#include <iostream>
#include <fcntl.h>
using namespace std;

int main(){
    FILE *fp;
    int fd = open("data.dat", O_WRONLY | O_CREAT | O_TRUNC);    //利用文件描述符来操作文件
    if (fd == -1){
        cout << "File open error" << endl;
        return -1;
    }

    fp = fdopen(fd, "w");       //将文件描述符转换为对应的FILE指针
    fputs("Network CPP programming\n", fp);
    fclose(fp);
    return 0;
}