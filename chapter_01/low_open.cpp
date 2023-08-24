#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
using namespace std;

int main(){
    int fd = open("data.txt", O_CREAT | O_WRONLY | O_TRUNC);
    if (fd == -1){
        cout << "file open failed" << endl;
    }

    char message[] = "Write some data to file\n";

    if (write(fd, message, sizeof(message)) == -1){
        cout << "write data error" << endl;
        return -1;
    }
    close(fd);
    
    return 0;
}
