#include <iostream>
#include <cstring>
#include <arpa/inet.h>
using namespace std;

int main(int argc, char *argv[]){
    char *str_ptr, *res;
     char arr[20];
    struct sockaddr_in addr1, addr2, addr3;

    addr1.sin_addr.s_addr = htonl(0x01020304);
    addr2.sin_addr.s_addr = htonl(0x01010101);
    addr3.sin_addr.s_addr = htonl(0x01020102);

    str_ptr = inet_ntoa(addr1.sin_addr);
    res = str_ptr;
    printf("Dotted-Decimal notation1: %s\n",str_ptr);
    printf("Dotted-Decimal notation2: %s\n",res);

    inet_ntoa(addr2.sin_addr);
    printf("Dotted-Decimal notation3: %s\n",str_ptr);

    inet_ntoa(addr3.sin_addr);
    strcpy(arr, str_ptr);
    printf("Dotted-Decimal notation4: %s\n",str_ptr);
    printf("Dotted-Decimal notation5: %s\n",arr);

    return 0;
}
