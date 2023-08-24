#include <iostream>
#include <arpa/inet.h>
using namespace std;

int main(){
    unsigned short host_port = 0x1234, net_port;
    unsigned long host_addr = 0x12345678, net_addr;

    net_port = htons(host_port);
    net_addr = htonl(host_addr);

    printf("Host port : %x\n", host_port);
    printf("Net port : %x\n", net_port);
    printf("host address : %lx\n", host_addr);
    printf("Net address : %lx\n", net_addr);

    return 0;
}