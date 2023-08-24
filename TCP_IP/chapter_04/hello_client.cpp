#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;
//create Hello World client

int main(int argc, char *argv[]){
    int sock;
    struct sockaddr_in serv_addr;
    char message[128];
    int str_len;

    if (argc != 3){
        cout << "Usage : " << argv[0] << "<port>" << endl;
        return -1;
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1){
        cout << "clien's socket create error" << endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    //      client_sock        server's addr        sizeof(server's addr)   
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        cout << "clien' connect error" << endl;
        return -1;
    }

    str_len = read(sock, message, sizeof(message));

    if (str_len == -1){
        cout << "clien read error" << endl;
        return -1;
    }
    
    cout << "Message from server : " << message << endl;
    close(sock);

    return 0;
}