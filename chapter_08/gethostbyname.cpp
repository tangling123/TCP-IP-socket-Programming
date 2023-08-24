#include <iostream>
#include <netdb.h>
#include <arpa/inet.h>
using namespace std;

int main(int argc, char* argv[]){
    if (argc != 2){
        cout << "Usage: <addr>" << endl;
        return -1;
    }

    struct hostent *host;
    host = gethostbyname(argv[1]);
    if (host == NULL){
        cout << "Falied to get host informantion for" << argv[1] << endl;
        return -1;
    }

    cout << "Host name : " << host->h_name << endl;

    for (char ** alias = host->h_aliases; *alias != NULL; alias++)
        cout << "Alias : " << *alias << endl;

    cout << "Address type : " << (host->h_addrtype == AF_INET ? "IPv4" : "IPv6") << endl;
    cout << "Address length : " << host->h_length << " bytes " << endl;

    for (int i = 0; host->h_addr_list[i] != NULL; i++)
        cout << "IP address " << i+1 << ": " << inet_ntoa(*(struct in_addr*)host->h_addr_list[i]) << endl;

    /*
    在inet_ntoa(*(struct in_addr*)host->h_addr_list[i])中实际上进行了三步
    host->h_addr_list[i]指向了第i个IP地址
    (struct in_addr*)转换为in_addr结构体指针
    最后对结构体指针解引用，将参数传递给inet_ntoa
    通过inet_ntoa可以将IP地址从网络字节序转换为主机字节序，并以点分十进制的形式输出
    */

    return 0;
}