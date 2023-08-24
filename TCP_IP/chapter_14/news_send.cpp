#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
using namespace std;

#define TTL 64
#define BUF_SIZE 30

int main(int argc, char *argv[]){
    if (argc != 3){
        cout << "Usage : <GroupIP> <PORT>" << endl;
        return -1;
    }

    int send_sock;
    struct sockaddr_in mul_addr;
    char buf[BUF_SIZE];

    send_sock = socket(AF_INET, SOCK_DGRAM, 0); //使用UDP的方式进行多播传输
    if (send_sock == -1){
        cout << "Send create socket error" << endl;
        return -1;
    }

    memset(&mul_addr, 0, sizeof(mul_addr));
    mul_addr.sin_family = AF_INET;
    mul_addr.sin_addr.s_addr = inet_addr(argv[1]);
    mul_addr.sin_port = htons(atoi(argv[2]));

    int time_live = TTL;    //设置生存时间TTL
    setsockopt(send_sock, IPPROTO_IP, IP_MULTICAST_TTL, &time_live, sizeof(time_live));
    
    FILE *fp = fopen("news.txt", "r");
    if (fp == NULL){
        cout << "fopen error" << endl;
        return -1;
    }

    while (!feof(fp)){
        fgets(buf, BUF_SIZE, fp);   //从文件指针fp中读取BUF_SIZE长的数据到buf中
        sendto(send_sock, buf, strlen(buf), 0, (struct sockaddr*)&mul_addr, sizeof(mul_addr));  //使用多播
        sleep(2);
    }

    fclose(fp), close(send_sock);
    return 0;
}