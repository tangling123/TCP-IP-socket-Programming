#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

int main(int argc, char* argv[]){
    int sock;
    struct sockaddr_in serv_addr;

    if (argc != 3){
        cout << "Usage : " << argv[0] << "<port>" << endl;
        return -1;
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1){
        cout << "client socket create error" << endl;
        return -1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        cout << "client connect error" << endl;
        return -1;
    }else{
        cout << "Connected" << endl;
    }

    while (1){      //循环
        char str[128];
        cin.getline(str, 128);                                                                                                                                             str;
        if (strcmp(str, "quit") == 0 || strcmp(str, "QUIT") == 0)
            break;;

        write(sock, str, strlen(str));      //从输入设备中读到的数据写到客户端

        int str_len = read(sock, str, 127); //读取客户端的数据
        str[128] = 0;     
                              
        cout << "received: " << str << endl;//str并不是从服务端传过来的数据，而是客户端自己的数据
    }

    close(sock);
    return 0;
}