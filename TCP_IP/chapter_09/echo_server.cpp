#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;
//create Hello World server

int main(int argc, char* argv[]){
    int serv_sock, clnt_sock, size = 128;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_size;
    char buf[128];

    if (argc != 2){
        cout << "Usage : " << argv[0] << "<port>" << endl;
        return -1;
    }


    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1){
        cout << "server socket create error" << endl;
        return -1;
    }

    //地址再分配
    int option = 1;
    if (setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)) == -1){
        cout << "Reuse address failed" << endl;
    } 

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        cout << "server socket bind error" << endl;
        return -1;
    }

    if (listen(serv_sock, 5) == -1){
        cout << "server socket listen error" << endl;
        return -1;
    }

    clnt_size = sizeof(clnt_addr);
    
    //和之前的hello_serv不同的地方，在外层使用一个for循环
    for (int i = 1; i <= 5; i++){
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_size);
        if (clnt_sock == -1){
            cout << "server socket accept error" << endl;
            return -1;
        }

        cout << "Hello Client : " << i << endl;

        int len;
        //从客户端中读取数据在写回去
        while ((len = read(clnt_sock, buf, size)) != 0){
            cout << "Server received :" << buf << endl;

            write(clnt_sock, buf, len);
            memset(buf, '\0', sizeof(buf));
        }
        close(clnt_sock);
    }

    close(serv_sock);
    return 0;
}