#include <iostream>
#include <arpa/inet.h>
using namespace std;

int main(int argc, char* argv[]){
    const char* addr1 = "1.2.3.4";
    const char* addr2 = "1.2.3.256";

    unsigned long conv_addr = inet_addr(addr1);
    //成功时返回32位大端整数值，失败时返回INADDR_NONE
    if (conv_addr == INADDR_NONE){
        cout << "Error occured" << endl;
    }else{
        printf("Net ordered integer addr:%lx\n", conv_addr);
    }

    conv_addr = inet_addr(addr2);
    if (conv_addr == INADDR_NONE){
        cout << "Error occured" << endl;
    }else{
        printf("Net ordered integer addr:%lx\n", conv_addr);
    }

    return 0;
}