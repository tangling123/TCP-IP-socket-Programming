#include <iostream>
#include <cstring>
#include <string>
#include <stack>
#include <unordered_map>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;
#define BUF_SIZE 1024

//在服务端利用两个栈来求解中缀表达式
stack<int> nums;
stack<char> oper;
unordered_map<char, int> mp;

void calculate(stack<int> &nums, stack<char> &ops) {
    //从ops运算符栈中弹出一个运算符，对nums栈顶和次栈顶元素进行运算
    if(nums.size() < 2 || ops.empty())
        return;

    int y = nums.top(); nums.pop();
    int x = nums.top(); nums.pop();
    char oper = ops.top(); ops.pop();

    if (oper == '+')
        nums.push(x + y);
    else if (oper == '-')
        nums.push(x - y);
    else if (oper == '*')
        nums.push(x * y);
    else if (oper == '/')
        nums.push(x / y);
}

void change(string str){
    for (int i = 0, j = i; i < str.size() && j < str.size(); j++){
        //寻找数字
        while (j < str.size() && str[j] >= '0' && str[j] <= '9')
            j++;
        //将对应的数字入栈 
        nums.push(stoi(str.substr(i, j-i)));
        // cout << str.substr(i, j-i) << endl;

        if (j < str.size()){
            //j指向的是一个运算符
            while (oper.size() && mp[oper.top()] >= mp[str[j]]){    //比较当前运算符和栈顶运算符的优先级
                calculate(nums, oper);
            }
            oper.push(str[j]);
        }
        i = j+1;
    }
    while (oper.size()) //将所有的运算符都弹出栈
        calculate(nums, oper);
}

int main(int argc, char *argv[]){
    mp['+'] = mp['-'] = 1;
    mp['*'] = mp['/'] = 2;
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_size;

    if (argc != 2){
        cout << "Usage : <port>" << endl;
        return -1; 
    }

    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1){
        cout << "Server create socket error" << endl;
        return -1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        cout << "Server socket bind address error" << endl;
        return -1;
    }

    if (listen(serv_sock, 5) == -1){
        cout << "Server socket listen error" << endl;
        return -1;
    }

    int result, opnd_cnt;
    char opinfo[BUF_SIZE];

    clnt_size = sizeof(clnt_addr);
    for (int i = 1; i <= 5; i++){
        cout << "Server is serving for " << i << " client" << endl;

        clnt_sock = accept(serv_sock, (struct sockaddr*)&serv_addr, &clnt_size);
        if (clnt_sock == -1){
            cout << "Server accept client error" << endl;
            return -1;
        }

        read(clnt_sock, &opinfo, BUF_SIZE - 1); //从客户端中读取数据
        
        string str = opinfo;    //将opinfo数组转换为string类型，方便计算表达式
        change(str);            //服务端进行计算
        result = nums.top();    //计算得到的结果 
        cout << "result : " << result << endl;  

        write(clnt_sock, (char*)&result, sizeof(result));

        close(clnt_sock);
    }

    close(serv_sock);
    return 0;
}