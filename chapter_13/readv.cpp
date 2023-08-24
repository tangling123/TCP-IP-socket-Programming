#include <iostream>
#include <sys/uio.h>
using namespace std;

#define BUF_SIZE 100

int main(int argc, char *argv[]){
    struct iovec vec[2];
    char buf1[BUF_SIZE], buf2[BUF_SIZE];

    vec[0].iov_base = buf1, vec[0].iov_len = 5;
    vec[1].iov_base = buf2, vec[1].iov_len = BUF_SIZE;

    int str_len = readv(0, vec, 2);

    cout << "Read bytes : " << str_len << endl;
    cout << "First message : " << buf1 << endl;
    cout << "second message : " << buf2 << endl;

    return 0;
}