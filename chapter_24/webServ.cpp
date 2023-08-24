#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
using namespace std;

#define BUF_SIZE 1024
#define SMALL_BUF 100

void* request_handler(void *arg);       //线程的main函数
void send_data(FILE *fp, char *ct, char *file_name);    //向客户端的fp发送数据
char* content_type(char *file);         //文本类型函数
void send_error(FILE *fp);              //向客户端发送出错信息

int main(int argc, char *argv[]){
    if (argc != 2){
        cout << "Usage : <port>" << endl;
        return -1;
    }

    int serv_sock, clnt_sock;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_size;

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

    if (listen(serv_sock, 20) == -1){
        cout << "server listen socket error" << endl;
        return -1;
    }

    pthread_t t_id;

    while (1){
        clnt_size = sizeof(clnt_addr);
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_size);
        if (clnt_sock == -1){
            cout << "server accept client error" << endl;
            return -1;
        }else
            cout << "Connection request : " << inet_ntoa(clnt_addr.sin_addr) << ":" << ntohs(clnt_addr.sin_port) << endl; 
        
        //创建多线程
        pthread_create(&t_id, NULL, request_handler, (void*)&clnt_sock);
        pthread_detach(t_id);
    }

}

void* request_handler(void *arg){
    int clnt_sock = *((int *)arg);

    char req_line[SMALL_BUF];   //请求行    GET /index.html HTTP/1.1
    char method[10], ct[15], file_name[30]; //用来存储请求行的信息 方法 文件类型 文件名

    //分离I/O流
    FILE* clnt_read = fdopen(clnt_sock, "r");
    FILE* clnt_write = fdopen(dup(clnt_sock), "w");

    fgets(req_line, SMALL_BUF, clnt_read);  //从文件中读取SMALL_BUF长的数据到req_line中

    if (strstr(req_line, "HTTP/") == NULL){
        send_error(clnt_write);             //向客户端的输出流write发送出错信息
        fclose(clnt_read);
        fclose(clnt_write);
        return NULL;
    }

    strcpy(method, strtok(req_line, " /"));//strcpy(dest, sour)字符串复制函数   strtok(req_line, " /")返回在req_line中被空格或/分割的第一个子串 
    strcpy(file_name, strtok(NULL, " /")); //strtok在第一次调用时传入字符数组
    strcpy(ct, content_type(file_name));

    if (strcmp(method, "GET") != 0){
        send_error(clnt_write);             //向客户端的输出流write发送出错信息
        fclose(clnt_read);
        fclose(clnt_write);
        return NULL;
    }

    fclose(clnt_read);       //进入半关闭状态
    send_data(clnt_write, ct, file_name);   //向客户端写入数据
    return NULL;
}

void send_data(FILE *fp, char *ct, char *file_name){
    char protocol[] = "HTTP/1.0 200 OK \r\n";
    char server[] = "Server : Linux Web Server\n";
    char cnt_len[] = "Content-length: 2048 \r\n";
    char cnt_type[SMALL_BUF], buf[BUF_SIZE];

    sprintf(cnt_type, "Content-type:%s\r\n\r\n", ct);

    FILE *send_file = fopen(file_name, "w");
    if (send_file == NULL){
        send_error(fp);
        return ;
    }

    //传输头信息，将信息写入到fp中
    fputs(protocol, fp);
    fputs(server, fp);
    fputs(cnt_len, fp);
    fputs(cnt_type, fp);

    //传输请求数据
    while (fgets(buf, BUF_SIZE, send_file) != NULL){
        fputs(buf, fp);
        fflush(fp);
    }

    fflush(fp);
    fclose(fp);
}

char* content_type(char* file){
    char extension[SMALL_BUF], file_name[SMALL_BUF];
    strcpy(file_name, file);

    strtok(file_name, ".");
    strcpy(extension, strtok(NULL, "."));

    if (strcmp(extension, "html") == 0 || strcmp(extension, "htm") == 0){
        return  "text/html";
    }else
        return  "text/plain";
}

void send_error(FILE *fp)
{
    char protocol[] = "HTTP/1.0 400 Bad Request\r\n";
    char server[] = "Server:Linux Web Server \r\n";
    char cnt_len[] = "Content-length:2048\r\n";
    char cnt_type[] = "Content-type:text/html\r\n\r\n";
    char content[] = "<html><head><title>NETWORK</title></head>"
                     "<body><font size=+5><br>发生错误！ 查看请求文件名和请求方式!"
                     "</font></body></html>";
                     
    fputs(protocol, fp);
    fputs(server, fp);
    fputs(cnt_len, fp);
    fputs(cnt_type, fp);
    fflush(fp);
}