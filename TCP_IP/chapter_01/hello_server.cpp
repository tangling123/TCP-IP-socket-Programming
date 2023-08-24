#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;
//create Hello World server

int main(int argc, char *argv[]){
    int serv_sock, clnt_sock;
    sockaddr_in serv_addr = {0}, clnt_addr = {0};
    socklen_t clnt_size;

    char message[15] = "Hello World\n";
    
    if (argc != 2){
        cout << "Usage : " << argv[0] << "<port>" << endl;
        return -1;
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1){
        cout << "server's socket create error" << endl;
        return -1;
    }
    // cout << "server create socket : " << serv_sock << endl;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        cout << "server bind error" << endl;
        return -1;
    }
    cout << "server bind socket : " << serv_sock << endl;

    if (listen(serv_sock, 5) == -1){
        cout << "server listen error" << endl;
        return -1;
    }

    // cout << "server listen socket : " << serv_sock << endl;
    cout << "server start success" << endl;

    //create client
    clnt_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_size); //clien'r sockrt from accept
    // cout << "server accept socket : " << serv_sock << endl;
    if (clnt_sock == -1){
        cout << "client accept error" << endl;
        return -1;
    }

    cout << "accepted client's connect" << endl;

    write(clnt_sock, message, sizeof(message));     //send message to client
    close(clnt_sock), close(serv_sock);

    return 0;
}