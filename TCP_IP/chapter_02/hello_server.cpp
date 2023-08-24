#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;
//create Hello World server

int main(int argc, char* argv[]){
    if (argc != 2){
        cout << "Invalid parameters" << endl;
        return -1;
    }

    int serv_sock, clnt_sock;
    sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_size;

    //1 create socket
    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1){
        cout << "server create socket error" << endl;
        return -1;
    }

    //2 bind server's IP and port
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        cout << "server bind error" << endl;
        return -1;
    }

    //3 listen
    if (listen(serv_sock, 5) == -1){
        cout << "server listen error" << endl;
        return -1;
    }

    //4 accept  
    clnt_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_size);
    if (clnt_sock == -1){
        cout << "client accept error" << endl;
        return -1;
    }

    char message[] = "Hello Linux World\n";
    // int send_len = send(clnt_sock, message, sizeof(message) - 1, 0);
    // if (send_len == -1){
    //     cout << "server send message error" << endl;
    //     return -1;
    // }

    //serveral write but one read to receive data
    int writ_len = write(clnt_sock, message, sizeof(message)-1);
    if (writ_len == -1){
        cout << "server send message error" << endl;
        return -1;
    }

    writ_len = write(clnt_sock, message, sizeof(message)-1);
    if (writ_len == -1){
        cout << "server send message error" << endl;
        return -1;
    }

    close(serv_sock);
    close(clnt_sock);
    return 0;
}