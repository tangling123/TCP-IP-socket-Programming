#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

int main(int argc, char *argv[]){
    int clnt_sock;
    struct sockaddr_in serv_addr;
    sockaddr_in serv_size;

    if (argc != 3){
        cout << "Usage : " << argv[0] << " <IP> <port>" << endl;
        return -1;
    }

    clnt_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (clnt_sock == -1){
        cout << "Client socket create error" << endl;
        return -1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(clnt_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        cout << "Clint connect to srever error" << endl;
        return -1;
    }else{
        cout << "Client connected" << endl;
    }

    while (1){
        char str[128];
        cin.getline(str, 128);                                                                                                                                             str;
        if (strcmp(str, "quit") == 0 || strcmp(str, "QUIT") == 0)
            break;;

        int str_len = write(clnt_sock, str, strlen(str));       //写到客户端的数据长度

        int recv_len = 0;
        while (recv_len < str_len){
            int recv_cnt = read(clnt_sock, &str[recv_len], 25);//当前接收到的数据长度

            if (recv_cnt == -1){
                cout << "Client receive error" << endl;
                return -1;
            }

            recv_len += recv_cnt;
        }

        str[128] = 0;
        cout << "recevied:" << str << endl;

    }

    close(clnt_sock);
    return 0;
}