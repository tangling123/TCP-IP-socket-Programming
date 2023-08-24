#include <iostream>
#include <arpa/inet.h>
using namespace std;

int main(int argc, char *argv[]){
    const char* string = "1.2.3.4";
    struct sockaddr_in addr;

    if (!inet_aton(string, &addr.sin_addr))
        //parameters: IP address string, struct in_addr* addr
        cout << "Error occured" << endl;
    else
        printf("Net ordered integer addr:%x\n", ntohl(addr.sin_addr.s_addr));

    return 0;
}