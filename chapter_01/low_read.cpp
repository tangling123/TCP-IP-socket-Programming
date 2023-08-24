#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
using namespace std;

int main(){
    int fd = open("data.txt", O_RDONLY);
    if (fd == -1){
        cout << "file open failed" << endl;
    }

    char message[128];

    if (read(fd, message, sizeof(message)) == -1)
        cout << "read data error" << endl;
        
    cout << message << endl;

    close(fd);
    
    return 0;
}
