#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#define BUF_SIZE 3
using namespace std;

int main(int argc, char *argv[]){
    int fd1, fd2, len;
    char buf[BUF_SIZE];

    fd1 = open("news.txt", O_RDONLY);
    fd2 = open("cpy.txt", O_WRONLY | O_CREAT | O_TRUNC);

    //使用write函数和readf函数来复制文件中的内容
    while (len = read(fd1, buf, sizeof(buf)))
    {
        write(fd2, buf, len);
    }

    close(fd1), close(fd2);
    return 0;
}