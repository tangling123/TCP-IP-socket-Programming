#include <iostream>
#include <cstring>
#include <arpa/inet.h>
using namespace std;

int main(){
    struct sockaddr_in addr;
    char* serv_ip = "127.217.168.13";
    char* serv_port = "9190";

    memeset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(atoi(serv_port));
}