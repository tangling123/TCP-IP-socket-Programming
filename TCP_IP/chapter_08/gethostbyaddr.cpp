#include <iostream>
#include <netdb.h>
#include <cstring>
#include <arpa/inet.h>
using namespace std;

int main(int argc, char *argv[]){
    if (argc  != 2){
        cout << "Usage : <IP>" << endl;
        return -1;
    }

    struct hostent *host;
    struct sockaddr_in addr;

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);

    host = gethostbyaddr((char*)&addr.sin_addr, 4, AF_INET);

    cout << "Host name : " << host->h_name << endl;

    for (char **alias = host->h_aliases; *alias != NULL; alias++)
        cout << "Alias : " << *alias << endl;

    cout << "Address Type : " << (host->h_addrtype == AF_INET ? "IPv4" : "IPv6") << endl;
    cout << "Address legnth : " << host->h_length << endl;

    for (int i = 0; host->h_addr_list[i] != NULL; i++)
        cout << "IP Address : " << inet_ntoa(*(struct in_addr*)host->h_addr_list[i]) << endl; 


    return 0;
}