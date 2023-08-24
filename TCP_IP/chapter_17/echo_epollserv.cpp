#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <sys/socket.h>
using namespace std;

#define BUF_SIZE 100
#define EPOLL_SIZE 50

int main(int argc, char *argv[]){
    if (argc != 2){
        cout << "Usage : <port>" << endl;
        return -1;
    }

    int serv_sock, clnt_sock;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_size;
    char buf[BUF_SIZE];

    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1){
        cout << "server create socket error" << endl;
        return -1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        cout << "server bind socket error" << endl;
        return -1;
    }

    if (listen(serv_sock, 5) == -1){
        cout << "server listen socket error" << endl;
        return -1;
    }

    //实现基于epoll的多路复用

    int epfd = epoll_create(EPOLL_SIZE);		//使用epoll_create()函数创建了一个epoll实例，并将返回的文件描述符赋值给整型变量epfd
    struct epoll_event *ep_events = new epoll_event[EPOLL_SIZE];    //等价于ep_events = malloc(sizeof(struct epoll_event) * EPOLL_SIZE)，在这里使用的是C++中的写法  	保存发生事件的文件描述符集合的结构体地址

    struct epoll_event event; 	  //监视对象的事件类型
    event.events = EPOLLIN;       //监听可读事件。这意味着当指定的文件描述符有可读数据时，内核会通知程序处理。
    event.data.fd = serv_sock;    //将serv_sock的文件描述符与事件相关联。当监听到serv_sock上的EPOLLIN事件时，内核将通知程序处理serv_sock上的数据

    epoll_ctl(epfd, EPOLL_CTL_ADD, serv_sock, &event);
    //epoll例程epfd中注册文件描述符serv_sock，主要目的是监视参数event中的事件

    while (1){
        int event_cnt = epoll_wait(epfd, ep_events, EPOLL_SIZE, -1);

        if (event_cnt == -1){
            cout << "epoll_wait error" << endl;
            break;
        }

        for (int i = 0 ; i < event_cnt; i++){
            //第i个发生事件的文件描述符ep_event[i].data.fd
            if (ep_events[i].data.fd == serv_sock){     
                clnt_size = sizeof(clnt_addr);
                clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_size);
                if (clnt_sock == -1){
                    cout << "server accept error" << endl;
                    break;
                }
                event.events = EPOLLIN;		//将客户端的读事件也加入到epoll中进行监听
                event.data.fd = clnt_sock;
                epoll_ctl(epfd, EPOLL_CTL_ADD, clnt_sock, &event);  //将clnt_sock上发生的读事件加入监听
                cout << "connect client : " << clnt_sock << endl;
            }else{
                int str_len = read(ep_events[i].data.fd, buf, BUF_SIZE);
                if (str_len == 0){
                    epoll_ctl(epfd, EPOLL_CTL_DEL, ep_events[i].data.fd, NULL);	//从例程epfd中删除文件描述符
                    close(ep_events[i].data.fd);
                    cout << "closed client : " << ep_events[i].data.fd << endl;
                }else   
                    write(ep_events[i].data.fd, buf, str_len);
            }
        }
    }

    delete [] ep_events;	//使用new[]创建需要使用delete[]释放
    close(clnt_sock), close(epfd);
    return 0;
}