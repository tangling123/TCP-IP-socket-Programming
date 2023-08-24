#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <cstdlib>
#include <unistd.h>
#include <errno.h>
#include <cstring>
#include <fcntl.h>
#include <string>
#include <iostream>
using namespace std;

#define BUF_SIZE 4096   //读缓冲区的大小

//主状态机的三种可能状态（请求报文的3个部分）
enum CHECK_STATE {      
    CHECK_STATE_REQUESTLINE,//正在在分析请求行
    CHECK_STATE_HEADER,     //正在分析头部字段
    CHECK_STATE_CONTENT     //正在解析请求体
};

//从状态机的三种可能状态（行的读取状态）
enum LINE_STATUS { 
    LINE_OK,            //读取到一个完整的行
    LINE_BAD,           //行出错
    LINE_OPEN           //行数据尚且不完整
};

//服务器处理HTTP请求的结果
enum HTTP_CODE {
    NO_REQUEST,         //请求不完整，需要继续读取客户端数据
    GET_REQUEST,        //获得了一个完整的请求
    BAD_REQUEST,        //客户端请求有语法错误
    FORBIDDEN_REQUEST,  //客户端对资源没有足够的访问权限
    INTERNAL_ERROR,     //服务器内部出错
    CLOSED_CONNCTION    //客户端关闭连接
};

//为了简化问题，我们没有给客户端发送一个完整的HTTP响应报文，而是根据服务器的处理结果发送下面的信息，来表示请求成功或失败
string szret[] = {"I got a correct result\n", "Something wrong"};

//从状态机解析出一行的内容
LINE_STATUS parse_line(char* buffer, int &checked_index, int &read_index){
    /*
    * checked_index指向buffer中当前正在分析的字节，read_index指向客户端数据的尾部的下一个字节，
    * buffer中的[0...checked_index-1]都已经分析完毕，接下来分析bufer[checked_index...read_index-1]
    */

    for (; checked_index < read_index; checked_index++){
        char temp = buffer[checked_index];

        if (temp == '\r'){
            //如果当前字符时回车符，则说明可能读取到一个完整的行
            if (checked_index+1 == read_index){
                //回车符是buffer中最后一个已经被读入的客户端数据，那么这次分析没有读取到一个完整的行，返回LINE_OPEN表示还需要继续读取客户端的数据
                return LINE_OPEN;

            }else if (buffer[checked_index+1] == '\n'){
                //下一个字符是换行符，说明已经读取到了一个完整的行
                buffer[checked_index++] = '\0';
                buffer[checked_index++] = '\0';
                return LINE_OK;

            }else{
                //说明客户端发送的HTTP请求存在语法问题
                return LINE_BAD;
            }

        }else if (temp == '\n'){
            //如果当前读取到的是\n，说明也可能读取到了一个完整的行
            if (checked_index && buffer[checked_index-1] == '\r'){
                buffer[checked_index-1] = '\0';
                buffer[checked_index++] = '\0';
                return LINE_OK;
            }

        }else
            return LINE_BAD;
    }

    //如果所有的内容都分析完也没遇到\r，返回LINE_OPEN，表示还需要继续读取客户端的数据
    return LINE_OPEN;
}

//分析请求行
HTTP_CODE parse_requestline(char * temp, CHECK_STATE &check_state){
    char *url = strpbrk(temp, " \t");   //strpbrk该函数返回temp中第一个匹配字符串中空格或\t的字符，如果未找到字符则返回 NULL。
    if (!url)
        //如果请求行中没有空白字符或\t字符，则HTTP请求有问题
        return BAD_REQUEST;

    *url = '\0';
    url++;

    char * method = temp;
    if (strcmp(method, "GET") == 0 || strcmp(method, "get") == 0){
        //只支持GET方法
        cout << "The request method is GET\n";
    }else
        return BAD_REQUEST;

    url += strspn(url, " \t");

    char* version = strpbrk(url, " \t");
    if (!version)
        return BAD_REQUEST;
    *version++ = '\0';
    version += strspn(version, " \t");
    if (strcmp(version, "http/1.1") == 0 || strcmp(version, "HTTP/1.1") == 0)
        return BAD_REQUEST;

    // if 
}