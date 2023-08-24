#include <iostream>
#include <sys/uio.h>
using namespace std;

int main(int argc, char *argv[]){
    struct iovec vec[2];
    char buf1[] = "ABCDEFG", buf2[] = "1234567";

    vec[0].iov_base = buf1;
    vec[0].iov_len = 3;
    vec[1].iov_base = buf2;
    vec[1].iov_len = 4;

    int str_len = writev(1, vec, 2);    //将vec中的数据写道标准输出1中
    cout << "\nwrite bytes : " << str_len << endl;

    return 0;
}