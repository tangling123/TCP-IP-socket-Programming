#include <iostream>
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

#define BUF_SIZE 1024
#define RLT_SIZE 4

int main(int argc, char* argv[]){
    int sock;
    struct sockaddr_in serv_addr;

    if (argc != 3){
        cout << "Usage :" << argv[0] << " <IP> <port>\n";
        return -1;
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1){
        cout << "Client create socket error" << endl;
        return -1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        cout << "Client connect to server error" << endl;
        return -1;
    }else{
        cout << "Client connect to server" << endl;
    }

    int result, opnd_cnt;
    char opmsg[BUF_SIZE];
    cout << "Input expression : " << endl;
    cin.getline(opmsg, BUF_SIZE);       //读取一整行数据

    write(sock, opmsg, strlen(opmsg));  //写到客户端sock中
    read(sock, &result, RLT_SIZE);

    cout << "Operation result: " << result << endl;
    close(sock);

    return 0;
}