#include <iostream>
#include <stdio.h>
#include <unistd.h>
using namespace std;

int main(){
    int cfd1, cfd2;
    char str1[] = "Hi~ \n";
    char str2[] = "It's a nice day \n";

    cfd1 = dup(1);      //使用dup复制文件描述符
    cfd2 = dup2(1, 7);  //使用dup2来制定复制后文件符的数值

    cout << "fd1 : " << cfd1 << " fd2 : " << cfd2 << endl;
    write(cfd1, str1, sizeof(str1));
    write(cfd2, str2, sizeof(str2));

    close(cfd1), close(cfd2);
    write(1, str1, sizeof(str1));
    close(1);
    write(1, str2, sizeof(str2));

    return 0;
}