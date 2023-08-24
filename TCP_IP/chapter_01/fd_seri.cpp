#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
using namespace std;

int main(){
    int fd1 = open("data.txt", O_RDONLY);
    int fd2 = socket(AF_INET, SOCK_STREAM, 0);
    int fd3 = socket(AF_INET, SOCK_STREAM, 0);
    
    cout << fd1 << " " << fd2 << " " << fd3 << endl;
    return 0;
}
