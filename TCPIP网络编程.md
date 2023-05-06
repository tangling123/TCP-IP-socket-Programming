# TCP/IP网络编程



## 第1章 理解网络编程和套接字



### 1.1  理解网络编程和套接字

**网络编程，就是编写程序使得联网的计算机可以相互交换数据。**

在C++中，套接字（Socket）是一种用于在不同计算机之间进行网络通信的机制，是网络数据传输用的软件设备。



**构建接电话套接字**

- **1、调用socket函数（安装电话机）**

  **在C++中，socket()函数是用于创建一个新的套接字的函数**。它的原型如下：

  ```c++
  int socket(int domain, int type, int protocol);
  ```

  参数：

  - `domain`：指定套接字所使用的协议族，例如 `AF_INET` 表示IPv4协议族，`AF_INET6` 表示IPv6协议族，`AF_UNIX` 表示UNIX域协议族等。
  - `type`：指定套接字的类型，例如 `SOCK_STREAM(TCP)` 表示流式套接字，`SOCK_DGRAM(UDP)` 表示数据报套接字等。
  - `protocol`：指定套接字所使用的协议，通常为0，表示使用默认协议。

  该函数返回一个新创建的套接字的描述符，如果创建失败则返回-1。

  套接字描述符是一个整数值，它标识了套接字，可以用于后续的套接字操作。

  

  **示例**

  ```c++
  int serv_sock =  socket(AF_INET, SOCK_STREAM, 0)
  if (serv_sock == -1){
      cout << "server socket error" << endl;
      return -1;
  }
  ```

  

- **2、调用bind函数（分配电话号码）**

  在C++中，**bind函数是用于将一个套接字（socket）与一个特定的地址（IP地址和端口号）绑定起来**。bind函数通常用于服务器程序中，以便客户端能够连接到该服务器的特定IP地址和端口号。

  ```c++
  int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
  ```

  ​	  `sockfd`是指定要绑定的套接字文件描述符，`addr`是指向`sockaddr`结构的指针，该结构包含了IP地址和端口号信息，`addrlen`是该结构的大小。在IPv4中，`sockaddr_in`是`sockaddr`的一种具体实现。

  **示例**

  ```c++
  struct sockaddr_in serv_addr = {0};
  saddr.sin_family = AF_INET;                //IPv4网络协议
  saddr.sin_addr.s_addr = htonl(INADDR_ANY); //本机字节序->网络字节序
  saddr.sin_port = htons(8888);              //绑定端口号
  
  //套接字绑定端口号和IP地址
  if (bind(server,  (struct sockaddr_in*)&saddr, sizeof(saddr)) == -1){
      cout << "server bind error" << endl;
      return -1;
  }
  ```

- **3、调用listen（连接电话线）**

  在C++中，`listen`和`accept`函数通常用于在**服务器端创建和管理网络连接**。

  **`listen`函数用于告知操作系统，服务器准备好接收传入的连接请求**。其函数原型为：

  ```c++
  int listen(int sockfd, int backlog);
  ```

  其中，`sockfd`参数是一个套接字描述符，`backlog`参数表示在未处理连接请求的情况下，操作系统应该将多少个连接请求加入等待队列中。在成功时，`listen`函数返回0，否则返回-1。

  **示例**

  ```c++
  //对服务器端进行监听，每次只服务一个客户端
  if (listen(server, 1) == -1){
      cout << "servre listen error" << endl;
      return -1;
  }
  ```

  

- **4、调用accept函数（拿起话筒）**

  **`accept`函数，服务器端接受客户端连接请求的函数，并创建一个新的套接字描述符，用于与新客户端通信。**其函数原型为：

  ```c++
  int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
  ```

  其中，`sockfd`是对应的socket文件描述符，`addr`是指向`sockaddr`结构体的指针，用于存储客户端的地址信息，`addrlen`是一个指向整型变量的指针，用于存储`addr`所指向的`sockaddr`结构体的大小。

  **当调用accept函数时，它会阻塞程序，直到有客户端连接到服务器端。**一旦有客户端连接到服务器端，accept函数会创建一个新的socket文件描述符，并返回该文件描述符。服务器端可以使用返回的文件描述符与客户端进行通信。

  **需要注意的是，accept函数会改变`addr`和`addrlen`的值，因此在每次调用accept函数之前，必须重新设置它们的值。**

  **示例**

  ```c++
  clnt_size = sizeof(caddr);
  //			 服务器端的套接字    客户端的地址    客户端地址的大小
  client = accept(server, (struct sockadrr*)&clnt_addr, &clnt_size);
  ```

  

**基础**

C++中的`main(int argc, char* argv[])`中的参数是用来接收程序启动时的命令行参数的。

- `argc`代表参数个数，即命令行参数的数量，包括程序本身的名称。因此，如果在命令行中不带任何参数地执行程序，则`argc`的值为1；如果带有一个参数，则`argc`的值为2，以此类推。
- `argv`是一个指向字符指针数组的指针，每个字符指针都指向一个参数字符串。其中，`argv[0]`指向程序的名称，`argv[1]`指向第一个参数，`argv[2]`指向第二个参数，以此类推。

例如，假设我们编写了一个名为`myprogram.cpp`的程序，并在命令行中执行以下命令：

```c++
myprogram arg1 arg2 arg3
```

则`argc`的值为4，`argv`的值如下：

```c++
pythonCopy codeargv[0] = "myprogram";
argv[1] = "arg1";
argv[2] = "arg2";
argv[3] = "arg3";
```

我们可以利用这些参数在程序运行时获取命令行中传递的信息，从而实现更加灵活和智能的程序行为。



**编写"Hello World服务器端"**

```c++
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

    char message[] = "Hello World\n";
    
    if (argc != 2){
        cout << "Usage : " << argv[0] << "<port>" << endl;
        return -1;
    }

    //1 create server's socket
    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1){
        cout << "server's socket create error" << endl;
        return -1;
    }

    //2 bind server's sock with it's IP and port
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        cout << "server bind error" << endl;
        return -1;
    }

    //3 listen, to receive client's request
    if (listen(serv_sock, 5) == -1){
        cout << "server listen error" << endl;
        return -1;
    }

    //4 accept client connet request
    clnt_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_size); //clien'r sockrt from accept
    if (clnt_sock == -1){
        cout << "client accept error" << endl;
        return -1;
    }

    write(clnt_sock, message, sizeof(message));     //send message to client
    close(clnt_sock), close(serv_sock);

    return 0;
}
```



**构建打电话的套接字**

```c++
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;
//create Hello World client

int main(int argc, char *argv[]){
    int sock;
    struct sockaddr_in serv_addr;
    char message[30];
    int str_len;

    if (argc != 3){
        cout << "Usage : " << argv[0] << "<port>" << endl;
        return -1;
    }

    //1 create client's socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1){
        cout << "clien's socket create error" << endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    //2 using connect function send connect request to server
    //      client_sock        server's addr        sizeof(server's addr)   
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        cout << "clien' connect error" << endl;
        return -1;
    }

    str_len = read(sock, message, sizeof(message) - 1);
    if (str_len == -1){
        cout << "clien read error" << endl;
        return -1;
    }

    cout << "Message from server : " << message << endl;
    close(sock);

    return 0;
}
```





### 1.2 基于Linux的文件操作

"Linux 一切皆文件"，表明在Linux操作系统中，几乎所有的系统资源（包括硬件设备、文件、目录等）都被视为文件，并且可以用类似于读写文件的方式来访问和操作它们。

**底层文件访问和文件描述符**

- 底层

  与标准无关的操作系统独立提供的，也就是不依赖于具体的操作系统。

- 文件描述符

  本质上是系统分配给文件或套接字的一个整数，但是这个整数指向系统中对应的一个文件。

  ​																	分配给标准输入输出与标准出错的文件描述符

  | 文件描述符 | 对象     |
  | ---------- | -------- |
  | 0          | 标准输入 |
  | 1          | 标准输出 |
  | 2          | 标准错误 |

  

**打开文件**

```c++
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int open(const char* pathname, int flag)
```

其中，参数pathname是要打开的文件名或路径，flag指定打开文件的方式和行为.

open函数可以使用以下标志（flags）之一或多个：

| 打开模式 | 含义                         |
| -------- | ---------------------------- |
| O_RDONLY | 只读模式打开文件             |
| O_WRONLY | 只写模式打开文件             |
| O_RDWR   | 读写模式打开文件             |
| O_CREAT  | 如果文件不存在，则创建文件   |
| O_TRUNC  | 如果文件已存在，删除现有数据 |
| O_APPEND | 在文件末尾追加数据           |

open函数成功打开文件时，返回一个文件描述符（file descriptor），这个文件描述符可以用于后续的文件操作函数（如read和write函数）。失败时，返回-1。



**关闭文件**

```c++
#include <unistd.h>

int close(int fd)
```

在C++中，close函数是用于关闭一个打开的文件或套接字的函数。

在文件操作中，使用close函数关闭打开的文件描述符（File Descriptor，即文件句柄），以释放操作系统占用的资源，避免资源泄露和浪费。



**将数据写入文件**

在C++中，write函数是用于将数据写入文件描述符的函数，函数原型如下：

```c++
#include <unistd.h>

ssize_t write(int fd, const void *buf, size_t count);
```

其中，参数`fd`为文件描述符，`buf`为要写入的数据缓冲区的地址，`count`为要写入的字节数。

​	`size_t`为unsigned int，`ssize_t`为signed int.

函数返回值为实际写入的字节数，如果返回-1，则表示写入失败。在使用write函数写入数据时，需要注意以下几点：

1. 要写入的文件必须已经打开，文件描述符`fd`必须是一个有效的文件描述符。
2. 写入的数据存放在缓冲区`buf`中，写入的字节数为`count`。
3. 如果写入的字节数小于缓冲区的大小，则有可能只写入了部分数据。此时可以根据返回值判断实际写入的字节数，并且可以使用循环写入的方式来保证所有数据都被写入。
4. 如果写入的数据过多，超过了文件系统或设备的限制，则会写入失败并返回-1。

write函数常用于在C++程序中进行文件操作，例如写入文本文件、写入二进制文件等。

在网络编程中，也常常使用write函数将数据写入到套接字（socket）中，以进行网络通信。

```c++
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
using namespace std;

int main(){
    int fd = open("data.txt", O_CREAT | O_WRONLY | O_TRUNC);
    if (fd == -1){
        cout << "file open failed" << endl;
    }

    char message[] = "Write some data to file\n";

    if (write(fd, message, sizeof(message)) == -1){
        cout << "write data error" << endl;
        return -1;
    }
    close(fd);
    
    return 0;
}
```



**读取文件中的数据**

在C++中，`read()`函数是一个用于从文件描述符中读取数据的系统调用函数。它通常用于读取二进制数据、套接字数据或其他形式的输入数据。

`read()`函数的声明如下：

```c++
#include <unistd.h>

ssize_t read(int fd, void *buf, size_t count);
```

其中，参数`fd`是一个打开的文件描述符，`buf`是一个指向存储读取数据的缓冲区的指针，`count`是需要读取的字节数。

`read()`函数返回值为读取的字节数。如果返回值为0，则表示已经读到文件末尾。如果返回值为-1，则表示发生了错误。

**`read()`函数通常与`write()`函数一起使用，用于从文件或套接字中读取数据并将其发送到另一个文件或套接字中。它也可以与`select()`函数一起使用，以便检查文件描述符上是否有可读数据。**



**文件描述符与套接字**

```c++
int main(){
    int fd1 = open("data.txt", O_RDONLY);
    int fd2 = socket(AF_INET, SOCK_STREAM, 0);
    int fd3 = socket(AF_INET, SOCK_STREAM, 0);
    
    cout << fd1 << " " << fd2 << " " << fd3 << endl;
    //Output:	3 4 5
    return 0;
}
```

文件描述符由小到大的顺序编号





### 1.3 基于Windows平台的实现

**同时学习Linux和Windows的原因**

大多数项目都在Linux的操作系统下开发服务端，在Windows的操作系统下开发客户端。不经如此，有时应用程序还需要在两个平台之间相互切换。在学习网络编程，有必要兼顾Linux和Windows两个操作系统。



**Winsock的初始化**

调用`WSAStartup()`函数来初始化Winsock库，这个函数的原型如下：

```c++
#include <winsock2.h>

int WSAStartup(WORD wVersionRequested, LPWSADATA lpWSAData);
```

- `wVersionRequested`参数指定请求的Winsock库的版本号，一般使用`MAKEWORD(2, 2)`来请求使用2.2版本的Winsock库。
- `lpWSAData`参数指向`WSADATA`结构体，这个结构体包含了Winsock库的信息。

1. **检查返回值是否为0，如果为0表示初始化成功，否则表示初始化失败。**
2. **执行完网络编程之后，需要调用`WSACleanup()`函数来清理Winsock库。**

`WSACleanup()`是一个Windows套接字函数，用于**清理Winsock库资源**。

在使用Winsock库之后，需要调用`WSACleanup()`函数来释放Winsock库资源，**否则可能会出现资源泄漏问题**。

`WSACleanup()`函数的原型如下：

```c++
#include <winsock2.h>

int WSACleanup(void);
```

该函数没有参数，返回值为整数型。当函数执行成功时，返回值为0；否则返回值为`SOCKET_ERROR`。

**一般来说，不需要对函数返回值进行检查。**

在程序中使用Winsock库后，需要在程序结束时调用`WSACleanup()`函数，以确保Winsock库资源被正确释放。如果程序不调用该函数就退出了，Winsock库资源将不会被释放，可能会导致内存泄漏或其他问题。

```c++
#include <winsock2.h>
#include <iostream>
using namespace std;

int main() {
	WSADATA wsaData;

    //		   Winsock version ,  WSADATA pointer
	if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
	{
		cout << "WSAStartup error" << endl;
		return -1;
	}
	...
        
	WSACleanup();

	return 0;
}
```





### 1.4 基于Windows的套接字相关函数及示例

**基于Windows的套接字相关函数**

1. `WSAStartup()`：初始化套接字库。

   ```c++
   int WSAStartup(WORD wVersionRequested, LPWSADATA lpWSAData);
   ```

   成功时返回0，失败时非零值。

2. `socket()`：创建一个套接字。

   ```c++
   SOCKET socket(int af, int type, int protocol);
   ```

   成功时返回套接字句柄，失败时返回INVALID_SOCKET。

3. `bind()`：将套接字绑定到一个特定的IP地址和端口号。

   ```c++
   int bind(SOCKET s, const struct sockaddr* name, int namelen);
   ```

   成功时返回0，失败时返回SOCKET_ERROR。

4. `listen()`：开始监听套接字上的连接请求。

   ```c++
   int listen(SOCKET s, int backlog);
   ```

   成功时返回0，失败时返回SOCKET_ERROR。

5. `accept()`：接受客户端的连接请求，并返回一个新的套接字以用于通信。

   ```c++
   SOCKET accept(SOCKET s, struct sockaddr* addr, int* addrlen);
   ```

   成功时返回0，失败时返回INVALID_SOCKET。

6. `connect()`：与指定的IP地址和端口号的服务器建立连接。

   ```c++
   int connect(SOCKET s, const struct sockaddr* name, int namelen);
   ```

   成功时返回0，失败时返回SOCKET_ERROR。

7. `closesocket()`：关闭套接字。

   ```c++
   int closesocket(SOCKET s);
   ```

   成功时返回0，失败时返回SOCKET_ERROR，一般直接关闭。



**创建基于Windows的服务端和客户端**

服务端

```c++
#include <winsock2.h>
#include <cstring>
#include <iostream>
using namespace std;

int main() {
	WSADATA wsaData;
	SOCKET serv_sock, clnt_sock;
	SOCKADDR_IN serv_addr, clnt_addr;
	int szClntAddr;
	char message[] = "Hello World!\n";

	if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
	{
		cout << "WSAStartup error" << endl;
		return -1;
	}

	serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serv_sock == INVALID_SOCKET)
	{
		cout << "server's socket error" << endl;
		return -1;
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(8888);

	if (bind(serv_sock, (SOCKADDR*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR)
	{
		cout << "server bind error" << endl;
		return -1;
	}

	if (listen(serv_sock, 1) == SOCKET_ERROR)
	{
		cout << "server listen error" << endl;
		return -1;
	}

	//client
	szClntAddr = sizeof(clnt_addr);
	clnt_sock = accept(serv_sock, (SOCKADDR*)&clnt_sock, &szClntAddr);
	if (clnt_sock == INVALID_SOCKET)
	{
		cout << "server accept error" << endl;
		return -1;
	}

	send(clnt_sock, message, sizeof(message), 0);
	closesocket(serv_sock);
	closesocket(clnt_sock);
	WSACleanup();

	return 0;
}
```

客户端

```c++
#include <winsock2.h>
#include <cstring>
#include <iostream>
using namespace std;

int main()
{
	WSADATA wsaData;
	SOCKET sock;
	SOCKADDR_IN serv_addr;

	if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
	{
		cout << "WSAStartup error" << endl;
		return -1;
	}

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		cout << "socket error" << endl;
		return -1;
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_addr.sin_port = htons(8888);
	if (connect(sock, (SOCKADDR*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR)
	{
		cout << "clinet connect error" << endl;
		return -1;
	}

	int strLen;
	char message[128];
	strLen = recv(sock, message, sizeof(message) - 1, 0);

	if (strLen == -1)
	{
		cout << "client receive error" << endl;
		return -1;
	}

	cout << message << endl;
	return -1;

	closesocket(sock);
	WSACleanup();
	return 0;
}
```



**基于Windows的I/O函数**

对于Linux而言，套接字也是文件所以可以使用文件的I/O函数read和write来进行数据传输。而Windows不同，它严格区分文件I/O函数和套接字I/O函数。

1. `send()`：向已连接的套接字发送数据。

   ```c++
   #include <winsock2.h>
   
   int send(SOCKET s, const char* buf, int len, int flags);
   ```

   成功时返回0，失败时返回INVALID_SOCKET。

   其中：

   - `s`：表示数据传输对象链接的套接字句柄值。
   - `buf`：指向要发送的数据缓冲区的指针。
   - `len`：要发送的数据的字节数。
   - `flags`：选项标志，通常设置为0。

   

2. `recv()`：从已连接的套接字接收数据。

   ```c++
   int recv(SOCKET s, char* buf, int len, int flags);
   ```

   其中：

   - `s`：表示套接字的句柄（handle）。
   - `buf`：指向接收缓冲区的指针。
   - `len`：表示接收缓冲区的大小（单位为字节）。
   - `flags`：用于控制`recv`函数的行为，如`MSG_PEEK`表示从缓冲区查看数据而不移除，`MSG_WAITALL`表示必须等待接收到指定长度的数据才返回。







## 第2章 套接字类型与协议设置

### 2.1 套接字协议及数据传输特性

**协议**

协议就是“计算机只对话必备的通信规则”。



**创建套接字**

```c++
#include <sys/socket.h>

SOCKET socket(int af, int type, int protocol);
```

**协议族（Protocol Family）**

| **名称**    | **协议族**           |
| ----------- | -------------------- |
| **PF_INET** | **IPv4互联网协议族** |
| PF_INET6    | IPv6互联网协议族     |
| PF_LOCAL    | 本地通信的UNIX协议族 |
| PF_PACKET   | 底层套接字的协议族   |
| PF_IPX      | IPX Novell协议族     |



套接字类型

- 套接字类型1：面向连接的套接字（SOCK_STREAM)

  - 可靠性（传输过程中数据不会消失）

  - 按序传输数据

  - 传输的数据不存在数据边界（100个糖果分批装，但是可以凑齐100个再接收）

**可靠的、按需传递的、基于字节的面向连接的数据传输方式的套接字**



**套接字缓冲已满，是否意味着数据丢失**

调用read函数从缓冲区读取部分数据，因此缓冲区并不总是满的。但是如果read函数读取的速度比接收速度慢，则缓冲有可能被填满。此时套接字无法再接收数据，但即使这样也不会发生数据丢失，因为传输端套接字将停止传输。也就是说，面向连接的套接字会根据接收端的状态传输数据，如果传输出错还会提供重传服务。因此，面向连接的套接字除特殊情况外不会丢失数据。



- 套接字类型2：面向消息的套接字（SOCK_DGRAM)

  - 强调快速传输而非传输顺序

  - 传输的数据可能丢失也可能损毁

  - 传输的数据有数据边界（意味着接收次数应该和传输次数相同）

  - 限制每次传输数据的大小

**不可靠的、不按序传递的、以数据的高速传输为目的的套接字**



**协议的最终选择**

socket的第三个参数`protocol`：协议（protocol），如`IPPROTO_TCP`代表TCP协议，`IPPROTO_UDP`代表UDP协议，通常设置为0，表示自动选择与套接字类型相对应的协议。



**面向连接的套接字：TCP套接字示例**

在hello_client.cpp中更改read函数调用方式。

```c++
int idx = 0;
//可以一次发送多次接收，也可以多次发送一次接收
while (read_len = read(sock, &message[idx++], 1)) //每次读取一个字节的数据到message[idx]中
{
    if (str_len == -1){
        cout << "clien read error" << endl;
        return -1;
    }
    str_len += read_len;
}

cout << "Message from server :" << message;
cout << "Function read call count : " << str_len << endl;
```





### 2.2 Windows平台下的实现及验证

**windows操作系统的socket函数**

```c++
#include <winsock2.h>

SOCKET socket(int af, int type, int protocol);
```

`socket`函数返回值为新建套接字的句柄，如果返回值为INVALID_SOCKET，则说明套接字创建失败。



**基于Windows的TCP套接字示例**

```c++

```





## 第3章 地址族与数据序列

### 3.1 分配给套接字的IP地址与端口号

IP地址是一种用于在Internet上标识设备（如计算机、路由器等）的数字地址。IP地址是Internet协议（IP）的一部分，它使得设备能够相互通信并在网络上传输数据。每个设备都需要一个唯一的IP地址，类似于邮寄地址或电话号码。

端口号是一个数字，用于标识在一台计算机上运行的特定应用程序或服务的通信端口。**在网络通信中，数据被传输到一个IP地址和端口号的组合，以便将数据发送到正确的应用程序或服务。**

端口号被分配给不同类型的服务或应用程序，以便它们可以在同一台计算机上共存，并且可以通过网络与其他计算机上的应用程序进行通信。例如，Web服务器通常使用端口号80或443，电子邮件服务器通常使用端口号25或587，FTP服务器通常使用端口号21等。



**网络地址**

- IPv4:		4字节地址
- IPv6:        16字节地址

在一个局域网或广域网中，每个设备都有一个唯一的IP地址，用于在网络中标识这个设备。

IP地址由两个部分组成，分别是网络ID和设备ID。

- 网络ID指的是网络的标识符，它用于在网络中标识不同的子网。在一个大型的网络中，通常会划分为多个子网，每个子网都有一个唯一的网络ID，用于区分不同的子网。

- 设备ID指的是设备的标识符，它用于在网络中标识不同的设备。同一个子网中的所有设备都使用相同的网络ID，但每个设备的设备ID是唯一的，用于在子网中标识不同的设备。

先通过网络ID来寻找目的主机所在的子网，再通过设备ID在所在子网中来寻找指定的网络设备。



**网络地址分类与主机地址边界**

Pv4网络地址分类是IPv4协议中对IP地址的一种分类方式，根据网络地址中前几位二进制数的不同，将IPv4地址分为A类、B类、C类、D类和E类五类。

每一类地址都有特定的网络和主机位数分配，下面是每一类地址的详细介绍：

- A类地址：**以0开头的IP地址，网络地址占1个字节，主机地址占3个字节**。A类地址的网络部分有128个，每个网络中有16777214个主机地址可供使用，**A类地址范围从1.0.0.0到126.255.255.255。**
- B类地址：**以10开头的IP地址，网络地址占2个字节，主机地址占2个字节。**B类地址的网络部分有16384个，每个网络中有65534个主机地址可供使用，**B类地址范围从128.0.0.0到191.255.255.255。**
- C类地址：**以110开头的IP地址，网络地址占3个字节，主机地址占1个字节。**C类地址的网络部分有2097152个，每个网络中有254个主机地址可供使用，**C类地址范围从192.0.0.0到223.255.255.255。**
- D类地址：**以1110开头的IP地址，**用于多点广播，不能用于单点通信。D类地址范围从224.0.0.0到239.255.255.255。
- E类地址：**以1111开头的IP地址**，保留地址，不用于常规通信。E类地址范围从240.0.0.0到255.255.255.255。

IPv4地址分类方式现已被CIDR（无类别域间路由）所取代，CIDR可以更灵活地分配IP地址。



**用于区分套接字的端口号**

在计算机网络中，**一个端口号是用来区分不同套接字的唯一标识符**。

套接字是一种抽象的网络通信端点，由一个IP地址和一个端口号组成。

当计算机上的一个程序或进程需要进行网络通信时，它会创建一个套接字，该**套接字会被绑定到一个特定的IP地址和端口号**。端口号通常是由操作系统随机分配的，但也可以由程序员指定。

在一个主机上，可能有多个套接字与同一个目标IP地址和端口号进行通信。这时，通过不同的端口号来区分这些套接字是非常必要的。

当一个数据包到达主机时，它包含了目标IP地址和目标端口号。操作系统根据这个目标端口号来确定将数据包交给哪个套接字进行处理。如果目标端口号与某个套接字绑定的端口号相同，那么该套接字就会处理该数据包。

**因此，通过不同的端口号来区分不同的套接字，就可以保证网络通信的可靠性和正确性。**





### 3.2 地址信息的表示

**表示IPv4地址的结构体**

```c++
struct sockaddr_in
{
    sa_family_t sin_family; //地址族
    uint16_t sin_port;      //16位端口号
    struct in_addr sin_addr;//32位IP地址
    char zero[8];           //不使用
}
```

`sockaddr_in` 是 C++ 中的一个结构体，它用于表示 IPv4 地址和端口号。这个结构体通常用于网络编程中，例如在创建 TCP/IP 或 UDP 网络连接时，需要使用这个结构体来指定目标地址和端口号。

其中`in_addr`结构体的定义如下：

```c++
struct in_addr
{
    in_addr_t s_addr;   //32位IP地址
}
```

​																								数据类型

| 数据类型名称  | 数据类型说明           | 头文件         |
| ------------- | ---------------------- | -------------- |
| `sa_family_t` | 地址族                 | `sys/socket.h` |
| `uint16_t`    | unsigned 16-bit int    | `sys/types.h`  |
| `in_addr_t`   | IP地址，声明为unit32_t | `netinet/in.h` |



**结构体`sockaddr_in`的成员的分析**

`in_addr` 结构体用于表示 IPv4 地址，其中 `s_addr` 字段是一个 32 位无符号整数，用于存储 IPv4 地址。`sockaddr_in` 结构体包含了一个 `in_addr` 结构体和一些其他字段，其中比较重要的是：

- `sin_family` 字段表示地址族，通常设置为 `AF_INET`，表示 IPv4 地址族。

- `sin_port` 字段表示端口号，它是一个 16 位无符号整数，用于存储端口号。

- `sin_addr` 字段表示 IPv4 地址，它是一个 `in_addr` 结构体。

- `sin_zero` 字段用于填充字节，使 `sockaddr_in` 结构体的大小和 `sockaddr` 结构体的大小相同。

  ```c++
  if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
      cout << "server bind error" << endl;
      return -1;
  }
  ```

  上面用到了强制类型转换，`sockaddr_in`是`sockaddr`的一个子类型。

  ```c++
  struct sockaddr
  {
      sa_family_t sin_family;
      char sa_data[14];
  }
  ```

  



### 3.3 网络字节序与地址转换

**字节序与网络字节序**

**字节序（Byte Order）是指在多个字节的数据类型中，不同字节的存储顺序。**

通常情况下，一个多字节数据类型会被存储为多个字节，但是这些字节的存储顺序可能是从最高有效位到最低有效位（Big-Endian，大端序）或者从最低有效位到最高有效位（Little-Endian，小端序）。例如，一个16位整数0x1234在Big-Endian下的存储顺序为0x12 0x34，在Little-Endian下的存储顺序为0x34 0x12。

**网络字节序（Network Byte Order）是指在网络通信中使用的字节序，它是一种固定的字节序，也就是Big-Endian。**

这是因为在网络通信中，不同计算机可能使用不同的字节序，为了避免字节序的不一致性而导致通信错误，网络通信中使用固定的字节序是非常必要的。

因此，在进行网络通信时，需要把本机字节序转换为网络字节序（`htons, htonl`），或者将网络字节序转换为本机字节序（`ntohs, ntohl`）。这样可以确保不同计算机之间的通信的正确性和可靠性。



**字节序转换**

在 C++ 中，可以使用以下两个函数进行字节序转换：

1. `htons()` 和 `ntohs`() 函数：

- `htons()` 函数将 16 位主机字节序转换为网络字节序（大端序）。

- `ntohs()` 函数将网络字节序转换为 16 位主机字节序。

  ```c++
  short host_num = 0x1234; // 4660 in decimal
  unsigned short net_num = htons(host_num);
  ```

2. `htonl() 和 ntohl()` 函数：

- `htonl()` 函数将 32 位主机字节序转换为网络字节序（大端序）。

- `ntohl()` 函数将网络字节序转换为 32 位主机字节序。

  ```c++
  unsigned long host_num = 0x12345678; // 305419896 in decimal
  unsigned long net_num = htonl(host_num);
  ```

这些函数在头文件 `<arpa/inet.h>` 中定义，可以在网络编程中使用。需要注意的是，这些函数只能转换基本数据类型，不能用于结构体等复杂数据类型的字节序转换，需要手动编写转换函数。

```c++
serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);	//主机字节序转换为网络字节序，IP地址是32位，所以使用的是htonl
serv_addr.sin_port = htons(atoi(argv[1]));		//主机字节序转换为网络字节序，端口号是16位，所以使用的是htons
```

示例

```c++
#include <iostream>
#include <arpa/inet.h>
using namespace std;

int main(){
    unsigned short host_port = 0x1234, net_port;
    unsigned long host_addr = 0x12345678, net_addr;

    net_port = htons(host_port);
    net_addr = htonl(host_addr);

    printf("Host port : %x\n", host_port);			//Host port : 1234
    printf("Net port : %x\n", net_port);			//Net port : 3412
    printf("host address : %lx\n", host_addr);		//host address : 12345678
    printf("Net address : %lx\n", net_addr);		//Net address : 78563412
  
    return 0;
}
```

因为主机中按照小端存储的，如果直接发送到网络中可能会出现数据错误。



### 3.4 网络地址的初始化与分配

**将字符串信息转换为网络字节序的整数型**

- 1 `inet_addr`

  **在 C++ 中，`inet_addr` 函数用于将 IPv4 地址从点分十进制格式转换为二进制格式。**该函数在头文件 `<arpa/inet.h>` 中声明，其定义如下：

  ```c++
  #include <arpa/inet.h> 
  
  in_addr_t inet_addr(const char *string);
  ```

  其中，参数 string 是一个表示点分十进制格式的 IPv4 地址的字符串指针。**函数返回一个 32 位无符号整数，表示该 IPv4 地址的二进制格式，成功时返回32位大端整数型值，失败时返回INADDR_NONE。**

  例如，将字符串 "192.168.0.1" 转换为二进制格式，可以调用 `inet_addr` 函数：

  ```c++
  #include <iostream>
  #include <arpa/inet.h>
  using namespace std;
  
  int main(int argc, char* argv[]){
      const char* addr1 = "1.2.3.4";
      const char* addr2 = "1.2.3.256";
  
      unsigned long conv_addr = inet_addr(addr1);
      //成功时返回32位大端整数值，失败时返回INADDR_NONE
      if (conv_addr == INADDR_NONE){
          cout << "Error occured" << endl;
      }else{
          printf("Net ordered integer addr:%lx\n", conv_addr);
      }
  
      conv_addr = inet_addr(addr2);
      if (conv_addr == INADDR_NONE){
          cout << "Error occured" << endl;
      }else{
          printf("Net ordered integer addr:%lx\n", conv_addr);
      }
  
      return 0;
  }
  ```

  输出结果为：

  ```c++
  Net ordered integer addr:4030201
  Error occured
  ```

  需要注意的是，`inet_addr` 函数不支持 IPv6 地址转换。如果需要转换 IPv6 地址，可以使用 `inet_pton` 函数。

  

  

- 2、`inet_aton`

  **在C++中，`inet_aton`函数是用来将IPv4地址的点分十进制字符串表示转换成网络字节序的32位二进制值。**它的函数原型如下：

  ```c++
  #include <arpa/inet.h>
  
  int inet_aton(const char *string, struct in_addr *addr);	// address to int
  ```

  其中，`cp`是指向点分十进制字符串表示的IPv4地址的指针，`inp`是指向`in_addr`结构体的指针，该结构体定义在`netinet/in.h`头文件中，用于存储转换后的二进制值。

  **`inet_aton`函数返回值为`1`表示转换成功，返回值为`0`表示转换失败。**

  例如，下面的代码将字符串表示的IPv4地址转换成二进制值，并打印出来：

  ```c++
  #include <iostream>
  #include <arpa/inet.h>
  using namespace std;
  
  int main(int argc, char *argv[]){
      const char* string = "1.2.3.4";
      struct sockaddr_in addr;
  
      if (!inet_aton(string, &addr.sin_addr))
          //parameters: IP address string, struct in_addr* addr
          cout << "Error occured" << endl;
      else
          printf("Net ordered integer addr:%x\n", ntohl(addr.sin_addr.s_addr));
  
      return 0;
  }
  ```

  在上述代码中，我们首先定义了一个指向字符串表示的IPv4地址的指针`addr_str`，然后定义了一个`sockaddr_in`结构体`addr`用于存储转换后的二进制值。接下来，我们调用`inet_aton`函数将字符串表示的IPv4地址转换成二进制值，并将结果存储在`addr.sin_addr`中。如果转换失败，我们将输出错误信息并返回。如果转换成功，我们将使用`ntohl`函数将32位二进制值从网络字节序转换成主机字节序，并打印出来。

  

  

- 3、`inet_ntoa`

  在C++中，`inet_ntoa()`函数用于将一个IP地址从网络字节序转换为点分十进制格式（即将32位的IPv4地址转换成类似于“192.168.0.1”的形式）。该函数的声明如下：

  ```c++
  #include <arpa/inet.h>
  
  char* inet_ntoa(struct in_addr in);							//int to address
  ```

  其中，`in_addr`结构体表示IPv4地址，包含一个32位无符号整数。`inet_ntoa()`函数接收一个`in_addr`类型的结构体参数`in`，并返回一个指向表示点分十进制格式IP地址的字符数组的指针。

  **需要注意的是：**函数返回的是一个char指针，返回字符串地址意味着字符窗已保存到内存空间中，但该函数并未向程序员要求分配内存，而是在内部申请并保存了字符串。也就说**调用完该函数之后应立即将字符串信息复制到其他内存空间中。因为再次调用`inet_ntoa`函数，可能会覆盖之前保存的字符串信息。**

  

  以下是一个示例程序，展示了如何使用`inet_ntoa()`函数将一个IPv4地址从网络字节序转换为点分十进制格式：

  ```c++
  #include <iostream>
  #include <cstring>
  #include <arpa/inet.h>
  using namespace std;
  
  int main(int argc, char *argv[]){
      char *str_ptr, *res;
       char arr[20];
      struct sockaddr_in addr1, addr2, addr3;
  
      addr1.sin_addr.s_addr = htonl(0x01020304);
      addr2.sin_addr.s_addr = htonl(0x01010101);
      addr3.sin_addr.s_addr = htonl(0x01020102);
  
      str_ptr = inet_ntoa(addr1.sin_addr);
      res = str_ptr;
      printf("Dotted-Decimal notation1: %s\n",str_ptr);
      printf("Dotted-Decimal notation2: %s\n",res);
  
      inet_ntoa(addr2.sin_addr);
      printf("Dotted-Decimal notation3: %s\n",str_ptr);
  
      inet_ntoa(addr3.sin_addr);
      strcpy(arr, str_ptr);
      printf("Dotted-Decimal notation4: %s\n",str_ptr);	//覆盖了之前保存的字符串信息
      printf("Dotted-Decimal notation5: %s\n",arr);
  
      return 0;
  }
  
  ```

  输出：

  ```c++
  Dotted-Decimal notation1: 1.2.3.4
  Dotted-Decimal notation2: 1.2.3.4
  Dotted-Decimal notation3: 1.1.1.1
  Dotted-Decimal notation4: 1.2.1.2
  Dotted-Decimal notation5: 1.2.1.2
  ```

  

**网络地址初始化**

```c++
struct sockaddr_in addr;
char* serv_ip = "127.217.168.13";
char* serv_port = "9190";

memeset(&addr, 0, sizeof(addr));
addr.sin_family = AF_INET;
addr.sin_addr.s_addr = inet_addr(serv_ip);
addr.sin_port = htons(atoi(serv_port));		//atoi() const char* to int
```

**客户端地址信息初始化**

- 服务端

  “请把进入IP为127.217.168.13、9190端口的数据传给我”

- 客户端

  “请连接到127.217.168.13、9190端口”

服务端的准备工作通过bind函数完成，而客户端通过connect来完成。服务端的sockaddr_in结构体变量初始化为赋予服务端IP和套接字的端口号，然后调用bind函数。而客户端，对于sockaddr_in变量，初始化为服务端套接字的IP和端口号，然后调用connect函数。



**INADDR_ANY**

```c++
struct sockaddr_in addr;
char* serv_port = "9190";

memeset(&addr, 0, sizeof(addr));
addr.sin_family = AF_INET;
addr.sin_addr.s_addr = htonl(INADDR_ANY);
addr.sin_port = htons(atoi(serv_port));
```

在C++中，`INADDR_ANY`是一个宏定义，它代表了一个IPv4地址，用于表示本地服务器监听所有可用的网络接口。

具体来说，`INADDR_ANY`定义为0，它被用作**服务器绑定函数**（如`bind()`函数）中的IP地址参数。当将此IP地址作为参数传递给服务器绑定函数时，服**务器将会监听所有可用的网络接口**，无论是通过以太网、无线网络还是其他类型的网络连接。

以下是一个示例程序，展示了如何使用`INADDR_ANY`宏定义将服务器绑定到所有可用的网络接口上：

```c++
c++Copy code#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        std::cerr << "Failed to create socket." << std::endl;
        return -1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    int bind_result = bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (bind_result < 0) {
        std::cerr << "Failed to bind socket to address." << std::endl;
        close(server_socket);
        return -1;
    }

    std::cout << "Server is listening on port 8080." << std::endl;
    // Rest of the server code goes here
    return 0;
}
```

在上述示例中，我们创建了一个TCP服务器套接字，使用`INADDR_ANY`宏定义将服务器绑定到所有可用的网络接口上，并绑定到本地端口号8080上。然后，我们可以继续编写服务器代码，监听客户端连接请求并执行其他操作。



**向套接字分配网络地址**

```c++
#include <sys/socket.h>

int bind(int sockfd, struct sockaddr* myaddr, socklen_t addrlen);
```

其中，`sockfd` 是套接字描述符，`myaddr` 是一个指向 `struct sockaddr` 类型的指针，表示要绑定的 IP 地址和端口号，`addrlen` 是 `addr` 结构体的长度。

`bind()` 函数通常用于**服务器端编程中**，在服务器程序启动时将套接字与指定的 IP 地址和端口号绑定在一起，以便客户端可以连接到该服务器。在绑定过程中，`addr` 可以指定为任意一个合法的 IP 地址和端口号组合，如果指定为 0，表示让操作系统自动分配一个空闲的端口号。

服务端套接字初始化过程：

```c++
sockaddr_in serv_addr;
socklen_t clnt_size;

//create server socket
serv_sock = socket(PF_INET, SOCK_STREAM, 0);
if (serv_sock == -1){
    cout << "server's socket create error" << endl;
    return -1;
}

//server address initialize
memset(&serv_addr, 0, sizeof(serv_addr));
serv_addr.sin_family = AF_INET;
serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
serv_addr.sin_port = htons(atoi(argv[1]));

//allocate address
if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
    cout << "server bind error" << endl;
    return -1;
}
```





## 第4章 基于TCP的服务端/客户端（1）

### 4.1 理解TCP和UDP

TCP(Transmission Control Protocol，传输控制协议)，对数据传输过程的控制。

TCP/IP协议栈是互联网中广泛使用的网络协议，由多个层级组成，每个层级负责不同的功能。以下是TCP/IP协议栈的各个层级：

1. 应用层（Application Layer）：这个层级包含了网络应用程序和服务，如电子邮件、Web浏览器、FTP等。应用程序使用这个层级上的协议来实现数据传输。
2. 传输层（Transport Layer）：这个层级包括了TCP（传输控制协议）和UDP（用户数据报协议）。**TCP提供了可靠的数据传输，UDP则提供了快速的数据传输**。应用程序使用这个层级上的协议来进行数据传输。
3. 网络层（Network Layer）：这个层级包含了IP（互联网协议），负责将数据包从源地址发送到目的地址。IP协议还包括了路由功能，用于将数据包传递到目的地。
4. 数据链路层（Data Link Layer）：这个层级包含了物理地址（MAC地址）和网络适配器等信息，用于将数据包从一个物理网络节点传输到另一个物理网络节点。
5. 物理层（Physical Layer）：这个层级包含了物理传输介质（如电缆、光纤、无线信道等）和物理连接设备（如中继器、集线器等），负责将数据传输到另一个物理网络节点。

TCP/IP协议栈是互联网中最常用的协议栈之一，它提供了一种可靠的、分层的、模块化的网络通信方式，使得不同的应用程序和设备可以互相通信。



### 4.2 实现基于TCP的服务端/客户端

**TCP服务端的默认函数调用顺序**

在TCP服务端上，以下是一般的调用顺序：

1. 创建套接字：使用 `socket()` 系统调用创建一个新的套接字，指定地址族（如 IPv4 或 IPv6）、套接字类型（如 SOCK_STREAM）和协议（如 TCP）。
2. 绑定套接字：使用 `bind()` 系统调用将套接字绑定到一个本地地址和端口上。
3. 监听连接请求：使用 `listen()` 系统调用将套接字设置为监听模式，以便接受传入的连接请求。
4. 接受连接：使用 `accept()` 系统调用接受传入的连接请求，并创建一个新的套接字用于与客户端通信。
5. 通信：使用`read()/write()`新的套接字进行数据传输和通信。
6. 关闭套接字：使用 `close()` 系统调用关闭套接字，释放资源。



**进入等待连接请求状态**

调用bind函数给套接字分配了IP地址和端口号，接下来调用listen函数进入等待连接请求状态。只有调用了listen函数，客户端才能进入课发出连接请求的状态，这时客户端才能调用connect函数（若提前调用将发生错误）。

```c++
#include <sys/socket.h>

int listen(int sockfd, int backlog);
```

其中，`sockfd`参数是服务器端用于监听的套接字描述符，`backlog`参数指定了内核中由此套接字接受的连接请求队列的最大长度。

在调用`listen()`函数之前，需要通过`bind()`函数将套接字绑定到一个本地地址和端口上。`listen()`函数在成功时返回0，失败时返回-1。

**一旦服务器套接字成功调用`listen()`函数并开始监听，它可以通过`accept()`函数接受来自客户端的连接请求，并返回一个新的套接字描述符，用于与客户端进行通信。**

在C++网络编程中，`listen()`函数用于将一个socket设置为被动模式，以便能够接收客户端的连接请求。

具体而言，`listen()`函数在服务器端应用程序中使用，用于监听一个特定的端口，等待客户端的连接请求。它接受两个参数：socket文件描述符和backlog参数。

`backlog`参数指定操作系统在未处理客户端连接请求时允许保持的最大连接数。这个参数的大小应该根据服务器应用程序的负载和系统资源来确定。

当一个客户端尝试连接到服务器时，服务器上的`listen()`函数将返回，并返回一个新的socket文件描述符，该文件描述符将用于与客户端进行通信。服务器应用程序接下来可以使用`accept()`函数来接受客户端连接并创建新的socket来与客户端进行通信。

**总之，`listen()`函数是用于服务器端的，用于等待客户端连接请求并允许服务器处理多个连接。**



**受理客户端连接请求**

在 C++ 网络编程中，accept() 函数是一个用于在服务器端接收客户端连接请求的函数。它接受服务器的套接字文件描述符作为参数，等待客户端连接，并返回一个新的套接字文件描述符，用于与客户端通信。

具体来说，当服务器程序调用 accept() 函数时，它会**阻塞**（即停止执行）并等待客户端的连接请求。当一个客户端连接请求到达服务器时，accept() 函数会返回一个新的套接字文件描述符，该描述符代表与客户端之间的通信。**服务器可以使用这个新的套接字文件描述符与客户端进行通信**，而原来的套接字文件描述符则继续用于等待新的客户端连接请求。

下面是 accept() 函数的基本语法：

```c++
#include <sys/socket.h>

int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
```

其中，`sockfd` 是服务端套接字的文件描述符，`addr` 是一个指向存储**客户端**地址信息的结构体的指针，`addrlen` 是这个结构体的长度。在调用 accept() 函数之前，服务器必须先调用 bind() 函数绑定一个本地地址和端口号，并调用 listen() 函数开始监听客户端连接请求。

需要注意的是，**accept() 函数只有在有客户端连接请求到达时才会返回。如果没有连接请求到达，它将一直阻塞直到有请求到达或者发生错误**。因此，在实际应用中，需要使用多线程或多进程等方法来处理多个客户端连接请求，以避免阻塞整个服务器程序。



**TCP客户端的默认函数调用顺序**

在C++中，TCP客户端的默认函数调用顺序是由具体的程序实现决定的，没有固定的标准顺序。一般来说，TCP客户端程序通常包括以下几个主要函数：

1. socket()函数：创建套接字，返回一个文件描述符，用于后续的数据传输。
2. connect()函数：连接到服务器，与服务器建立TCP连接。
3. send()函数：向服务器发送数据。
4. recv()函数：接收服务器发送的数据。
5. close()函数：关闭套接字，断开与服务器的TCP连接。

在实现TCP客户端程序时，通常会按照上述顺序依次调用这些函数，以完成数据的发送和接收。

在 C++ 网络编程中，`connect()` 函数是用来建立 TCP 连接的，它通常用于**客户端**程序中。

`connect()` 函数的语法如下：

```c++
#incldue <sys/socket.h>

int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

参数说明：

- `sockfd`：需要建立连接的套接字文件描述符。
- `addr`：指向目标**服务器**的 `sockaddr` 结构体指针，其中包括了目标服务器的 IP 地址和端口号信息。
- `addrlen`：`sockaddr` 结构体的长度。

`connect()` 函数的作用是向目标服务器发起连接请求，并在连接成功或失败后返回相应的状态值。如果连接成功，返回值为 0，否则返回 -1，。

`connect()` 函数在执行时会**阻塞**当前线程，直到连接成功或超时，因此在实际编程中通常会使用非阻塞或异步的方式调用该函数。如果需要设置超时时间，可以使用 `setsockopt()` 函数来设置 SO_SNDTIMEO 和 SO_RCVTIMEO 选项。

 



**客户端套接字地址信息在哪？**

客户端的IP地址和端口号在调用connect函数时自动分配，无需调用bind函数。

![TCP Server-Client implementation in C - GeeksforGeeks](C:\Users\hp-pc\Desktop\C++\TCPIP网络编程.assets\Socket_server-1.png)

客户端只能等到服务端调用listen函数之后才能调用connect函数.



### 4.3 实现迭代服务器端/客户端

编写一个回声（echo）服务器/客户端。顾名思义，服务端将客户端传输的字符串数据原封不动的传回客户端，就像回声一样。在此之前，需要解释一下迭代服务器端。



**实现迭代服务器端**

在 Hello World 的例子中，等待队列的作用没有太大意义。如果想继续处理好后面的客户端请求应该怎样扩展代码？最简单的方式就是插入循环反复调用 accept 函数，如图:

![img](C:\Users\hp-pc\Desktop\C++\TCPIP网络编程.assets\68747470733a2f2f692e6c6f6c692e6e65742f323031392f30312f31352f356333643363386132383361642e706e67.png)

可以看出，调用 accept 函数后，紧接着调用 I/O 相关的 read write 函数，然后调用 close 函数。这并非针对服务器套接字，而是针对 accept 函数调用时创建的套接字。



**迭代回声服务器端/客户端**

程序运行的基本方式：

- 服务器端在同一时刻只与一个客户端相连，并提供回声服务。
- 服务器端依次向 5 个客户端提供服务并退出。
- 客户端接受用户输入的字符串并发送到服务器端。
- 服务器端将接受的字符串数据传回客户端，即「回声」
- 服务器端与客户端之间的字符串回声一直执行到客户端输入 quit或者QUIT为止。

以下是服务端与客户端的代码：

服务端：

```c++
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
    
    for (int i = 1; i <= 5; i++){
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_size);
        if (clnt_sock == -1){
            cout << "server socket accept error" << endl;
            return -1;
        }

        cout << "Hello Client : " << i << endl;

        int len;
        while ((len = read(clnt_sock, buf, size)) != 0)
            write(clnt_sock, buf, len);

        close(clnt_sock);
    }

    close(serv_sock);
    return 0;
}
```

客户端

```c++
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

    while (1){
        char str[128];
        cin >> str;
        if (strcmp(str, "quit") == 0 || strcmp(str, "QUIT") == 0)
            break;;
        write(sock, str, strlen(str));
        int str_len = read(sock, str, 127);
        str[128] = 0;
        cout << "Message from server: " << str << endl;
    }

    close(sock);
    return 0;
}
```



### 4.4基于Windows的实现

略

### 4.5 习题 

> 答案来源于ChatGPT。

1. **请你说明 TCP/IP 的 4 层协议栈，并说明 TCP 和 UDP 套接字经过的层级结构差异。**

   答：TCP/IP 协议栈由四个层级组成，分别是：

   - 应用层（Application Layer）：负责应用程序之间的数据传输和交互，如 HTTP、FTP、SMTP 等协议。

   - 传输层（Transport Layer）：负责在网络中传输数据，提供可靠的数据传输服务和错误控制，如 TCP 和 UDP 协议。

   - 网络层（Internet Layer）：负责将数据包从源地址传输到目的地址，进行路由选择和寻址等操作，如 IP 协议。
   - 链路层（Link Layer）：负责实现数据包在物理层面上的传输，如以太网、无线局域网等协议。

   TCP 和 UDP 套接字的层级结构差异在传输层，**TCP 是一种基于连接的面向流的协议，UDP 则是无连接的面向数据报的协议**。因此，它们的套接字传输层级结构存在差异：

   TCP 套接字传输层级结构：

   - 应用层：应用程序
   - 传输层：**TCP 协议**
   - 网络层：IP 协议
   - 链路层：以太网等物理层协议

   UDP 套接字传输层级结构：

   - 应用层：应用程序
   - 传输层：**UDP 协议**
   - 网络层：IP 协议
   - 链路层：以太网等物理层协议

   可以看到，TCP 和 UDP 套接字的应用层、网络层和链路层都是一样的，**唯一的区别在传输层协议**。因此，应用程序只需要调用相应的 TCP 或 UDP 套接字进行数据传输即可。

   

2. **请说出 TCP/IP 协议栈中链路层和IP层的作用，并给出二者关系**

   答：链路层（Link Layer）：链路层是协议栈中最底层的一层，它负责在物理层面上传输数据。**链路层主要的作用是将网络层的 IP 数据报封装成帧，并发送到下一跳的目标设备**。此外，链路层还处理一些错误控制、流量控制、帧同步等问题。

   IP 层（Internet Layer）：IP 层负责在网络中传输数据。**它主要的作用是将应用层的数据报分割成 IP 数据报，并通过路由选择算法将数据报从源地址传输到目的地址**。IP 层还负责处理一些数据包的错误控制、数据包重组、分片等问题。

   链路层和 IP 层的关系是紧密相连的，它们共同构成了协议栈中的底层，协同工作实现数据传输。链路层负责将 IP 数据报封装成帧并发送到下一跳目标设备，IP 层则负责将数据报分割成 IP 数据报并进行路由选择，同时将数据报送到链路层进行发送。在实际传输过程中，链路层和 IP 层的交互是非常频繁的，它们一起工作实现了数据在物理层和网络层之间的传输。

3. **为何需要把 TCP/IP 协议栈分成 4 层（或7层）？开放式回答。**

   答：ARPANET 的研制经验表明，对于复杂的计算机网络协议，其结构应该是层次式的。分层的好处：①隔层之间是独立的②灵活性好③结构上可以分隔开④易于实现和维护⑤能促进标准化工作。

4. **客户端调用 connect 函数向服务器端发送请求。服务器端调用哪个函数后，客户端可以调用 connect 函数？**

   答：服务端调用 listen 函数后，客户端可以调用 connect 函数。因为，服务端调用 listen 函数后，服务端套接字才有能力接受请求连接的信号。

5. **什么时候创建连接请求等待队列？它有何种作用？与 accept 有什么关系？**

   答：服务端调用 listen 函数后，accept函数正在处理客户端请求时， 更多的客户端发来了请求连接的数据，此时，就需要创建连接请求等待队列。以便于在accept函数处理完手头的请求之后，按照正确的顺序处理后面正在排队的其他请求。与accept函数的关系：accept函数受理连接请求等待队列中待处理的客户端连接请求。

6. **客户端中为何不需要调用 bind 函数分配地址？如果不调用 bind 函数，那何时、如何向套接字分配IP地址和端口号？**

   答：在调用 connect 函数时分配了地址，客户端IP地址和端口在调用 connect 函数时自动分配，无需调用标记的 bind 函数进行分配。





## 第5章 基于TCP的服务端/客户端（2）

上一章仅仅是从编程角度学习实现方法，并未详细讨论 TCP 的工作原理。因此，本章将想次讲解 TCP 中必要的理论知识，还将给出第 4 章客户端问题的解决方案。



### 5.1 回声客户端的完美实现

**回声服务器没有问题，只有回声客户端有问题？**

问题不在服务器端，而在客户端，只看代码可能不好理解，因为 I/O 中使用了相同的函数。先回顾一下**服务器端**的 I/O 相关代码：

```c++
while ((str_len = read(clnt_sock, message, BUF_SIZE)) != 0)
    write(clnt_sock, message, str_len);
```

接着是**客户端**代码:

```c++
write(sock, message, strlen(message));
str_len = read(sock, message, BUF_SIZE - 1);
```

二者都在循环调用 read 和 write 函数。实际上之前的回声客户端将 100% 接受自己传输的数据，只不过接收数据时的单位有些问题。扩展客户端代码回顾范围，下面是客户端的代码:

```c++
while (1)
{
    fputs("Input message(Q to quit): ", stdout);
    fgets(message, BUF_SIZE, stdin);

    if (!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
        break;

    write(sock, message, strlen(message));
    str_len = read(sock, message, BUF_SIZE - 1);
    message[str_len] = 0;
    printf("Message from server: %s", message);
}
```

现在应该理解了问题，回声客户端传输的是字符串，而且是通过调用 write 函数一次性发送的。之后还调用一次 read 函数，期待着接受自己传输的字符串，这就是问题所在。



**回声客户端问题的解决办法**

这个问题其实很容易解决，因为可以提前接受数据的大小。若之前传输了20字节长的字符串，则再接收时**循环调用 read 函数读取** 20 个字节即可。既然有了解决办法，那么代码如下：

```c++
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
        //和之前的客户端代码的区别，利用read循环读取，直到读取的字符数>=写入的字符数
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
```

这样修改为了接收所有传输数据而循环调用 read 函数。测试及运行结果可参考第四章。



**如果问题不在于回声客户端：定义应用层协议**

回声客户端可以提前知道接收数据的长度，这在大多数情况下是不可能的。那么此时无法预知接收数据长度时应该如何收发数据？这时需要的是**应用层协议**的定义。在收发过程中定好规则（协议）以表示数据边界，或者提前告知需要发送的数据的大小。服务端/客户端实现过程中逐步定义的规则集合就是应用层协议。

现在写一个小程序来体验应用层协议的定义过程。要求：

1. 服务器从客户端获得多个数组和运算符信息。
2. 服务器接收到数字候对齐进行加减乘运算，然后把结果传回客户端。

例：

1. 向服务器传递3,5,9的同事请求加法运算，服务器返回3+5+9的结果
2. 请求做乘法运算，客户端会收到`3*5*9`的结果
3. 如果向服务器传递4,3,2的同时要求做减法，则返回4-3-2的运算结果。

和书上的代码不同，**我们在这里使用string类来读取中缀表达式来进行计算**，服务端将得到的结果返回给客户端

客户端`op_client.cpp`

```c++
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
    cin.getline(opmsg, BUF_SIZE);       //和书上的代码不同，这里是读取一整行数据

    write(sock, opmsg, strlen(opmsg));  //写到客户端sock中
    read(sock, &result, RLT_SIZE);

    cout << "Operation result: " << result << endl;
    close(sock);

    return 0;
}
```

服务端`op_server.cpp`的代码

```c++
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
        change(str);            //在服务端进行计算
        result = nums.top();    //计算得到的结果 
        cout << "result : " << result << endl;  

        write(clnt_sock, (char*)&result, sizeof(result));

        close(clnt_sock);
    }

    close(serv_sock);
    return 0;
}
```

服务端编译

```c++
g++ op_server.cpp -o op_server
./op_server 8080
```

客户端编译

```c++
g++ op_client.cpp -o op_client
./op_client 127.0.0.1 8080
```

客户端读取数据

```c++
Client connect to server
Input expression : 
1+2-3*4/5
Operation result: 1		//客户端返回的结果
```



### 5.2 TCP原理

**TCP套接字中的I/O缓冲**

TCP 套接字的数据收发无边界。服务器即使调用 1 次 write 函数传输 40 字节的数据，客户端也有可能通过 4 次 read 函数调用每次读取 10 字节。但此处也有一些疑问，服务器一次性传输了 40 字节，而客户端竟然可以缓慢的分批接受。客户端接受 10 字节后，剩下的 30 字节在何处等候呢？

实际上，write 函数调用后并非立即传输数据， read 函数调用后也并非马上接收数据。

**如图所示，write 函数调用瞬间，数据将移至输出缓冲；read 函数调用瞬间，从输入缓冲读取数据。**

![img](C:\Users\hp-pc\Desktop\C++\TCPIP网络编程.assets\68747470733a2f2f692e6c6f6c692e6e65742f323031392f30312f31362f356333656134316364393363362e706e67.png)

I/O 缓冲特性可以整理如下：

- I/O 缓冲在每个 TCP 套接字中单独存在
- I/O 缓冲在创建套接字时自动生成
- 即使关闭套接字也会继续传递输出缓冲中遗留的数据
- 关闭套接字将丢失输入缓冲中的数据

假设发生以下情况，会发生什么事呢？

> 客户端输入缓冲为 50 字节，而服务器端传输了 100 字节。

因为 TCP 不会发生超过输入缓冲大小的数据传输。也就是说，根本不会发生这类问题，因为 TCP 会控制数据流。TCP 中有滑动窗口（Sliding Window）协议，用对话方式如下：

> - A：你好，最多可以向我传递 50 字节
> - B：好的
> - A：我腾出了 20 字节的空间，最多可以接受 70 字节
> - B：好的

数据收发也是如此，因此 TCP 中不会因为缓冲溢出而丢失数据。

**write 函数在数据传输完成时返回。**





[TCP连接管理视频讲解](https://www.bilibili.com/video/BV19E411D78Q?p=64&spm_id_from=pageDriver&vd_source=4c396a7eb4588d54f454e1f3fe6f25bd)

**TCP连接管理**

<img src="C:\Users\hp-pc\Desktop\C++\TCPIP网络编程.assets\image-20230322093746955.png" alt="image-20230322093746955" style="zoom:67%;" />

**TCP的连接建立**

<img src="C:\Users\hp-pc\Desktop\C++\TCPIP网络编程.assets\image-20230322093857159.png" alt="image-20230322093857159" style="zoom:67%;" />

三次握手是 TCP 连接的建立过程。在握手之前，主动打开连接的客户端结束 CLOSE 阶段，被动打开的服务器也结束 CLOSE 阶段，并进入 LISTEN 阶段。随后进入三次握手阶段：

① 首先客户端向服务器发送一个 SYN 包，并等待服务器确认，其中：

- 标志位为 SYN = 1，表示请求建立连接；
- 序号为 seq = x（x 一般取随机数）；
- 随后客户端进入 SYN-SENT 阶段。



② 服务器接收到客户端发来的 SYN 包后，对该包进行确认后结束 LISTEN 阶段，并返回一段 TCP 报文，其中：

- 标志位为 SYN = 1 和 ACK = 1，表示确认客户端的报文 seq 序号有效，服务器能正常接收客户端发送的数据，并同意创建新连接；
  序号为 Seq = y 随机；

- 确认号为 ack = x + 1，表示收到客户端的序号 seq 并将其值加 1 作为自己确认号 ack 的值，随后服务器端进入 SYN-RECV 阶段。

  **其中ack = 收到的seq号 + 传递的字节数 + 1**



③ 客户端接收到发送的 SYN + ACK 包后，**明确了从客户端到服务器的数据传输是正常的**，从而结束 SYN-SENT 阶段。并返回最后一段报文。其中：

- 标志位为 ACK = 1，表示确认收到服务器端同意连接的信号；

- 序号为 seq = x + 1，表示收到服务器端的确认号 ack，并将其值作为自己的序号值；

- 确认号为 ack= y + 1，表示收到服务器端序号 seq，并将其值加 1 作为自己的确认号 ack 的值。

- 随后客户端进入 ESTABLISHED。

  

一旦三次握手完成，TCP连接就建立了。在此之后，双方可以开始通过连接进行数据传输。

**三次握手过程的目的是为了确保连接建立的可靠性和正确性。第一次握手确保客户端和服务器都能够相互通信，第二次握手确保服务器接收到了客户端的请求，并且可以响应它，第三次握手则确保客户端知道服务器已经接受了它的请求，并且可以开始在连接上进行数据传输。**

需要注意的是，三次握手的过程可以防止由于网络问题或恶意攻击导致的连接建立失败，但并不能防止所有的攻击，因此在进行TCP连接时，还需要采取其他安全措施来保护连接的安全和稳定。



**TCP的连接释放**

<img src="C:\Users\hp-pc\Desktop\C++\TCPIP网络编程.assets\image-20230322094028779.png" alt="image-20230322094028779" style="zoom:67%;" />

四次挥手即 TCP 连接的释放，这里假设客户端主动释放连接。在挥手之前主动释放连接的客户端结束 ESTABLISHED 阶段，随后开始四次挥手：

① 首先客户端向服务器发送一段 TCP 报文表明其想要释放 TCP 连接，其中：

- 标记位为 FIN = 1，表示请求释放连接；
- 序号为 seq = u；
- 随后客户端进入 FIN-WAIT-1 阶段，即**半关闭阶段**，并且停止向服务端发送通信数据。



② 服务器接收到客户端请求断开连接的 FIN 报文后，结束 ESTABLISHED 阶段，进入 CLOSE-WAIT 阶段并返回一段 TCP 报文，其中：

- 标记位为 ACK = 1，表示接收到客户端释放连接的请求；

- 序号为 seq = v；

- 确认号为 ack = u + 1，表示是在收到客户端报文的基础上，将其序号值加 1 作为本段报文确认号 ack 的值；

- 随后服务器开始准备释放服务器端到客户端方向上的连接。

- 客户端收到服务器发送过来的 TCP 报文后，确认服务器已经收到了客户端连接释放的请求，随后客户端结束 FIN-WAIT-1 阶段，进入 FIN-WAIT-2 阶段。

  

③ 服务器端在发出 ACK 确认报文后，服务器端会将遗留的待传数据传送给客户端，待传输完成后即经过 CLOSE-WAIT 阶段，便做好了释放服务器端到客户端的连接准备，再次向客户端发出一段 TCP 报文，其中：

- 标记位为 FIN  = 1和 ACK = 1，表示已经准备好释放连接了；
- 序号为 seq = w；
- 确认号 ack = u + 1，表示是在收到客户端报文的基础上，将其序号 seq 的值加 1 作为本段报文确认号 ack 的值。
- 随后服务器端结束 CLOSE-WAIT 阶段，进入 LAST-ACK 阶段。并且停止向客户端发送数据。



④ 客户端收到从服务器发来的 TCP 报文，确认了服务器已经做好释放连接的准备，于是结束 FIN-WAIT-2 阶段，进入 TIME-WAIT 阶段，并向服务器发送一段报文，其中：

- 标记位为 ACK = 1，表示接收到服务器准备好释放连接的信号；
- 序号为 seq= u + 1，表示是在已收到服务器报文的基础上，将其确认号 ack 值作为本段序号的值；
- 确认号为 ack= w + 1，表示是在收到了服务器报文的基础上，将其序号 seq 的值作为本段报文确认号的值。

随后客户端开始在 TIME-WAIT 阶段等待 2 MSL。服务器端收到从客户端发出的 TCP 报文之后结束 LAST-ACK 阶段，进入 CLOSED 阶段。由此正式确认关闭服务器端到客户端方向上的连接。客户端等待完 2 MSL 之后，结束 TIME-WAIT 阶段，进入 CLOSED 阶段，由此完成「四次挥手」。



**如果三次握手的时候每次握手信息对方没有收到会怎么样**

- 若第一次握手服务器未接收到客户端请求建立连接的数据包时，**服务器不会进行任何相应的动作**，而客户端由于在一段时间内没有收到服务器发来的确认报文， 因此会等待一段时间后重新发送 SYN 同步报文，若仍然没有回应，则重复上述过程直到发送次数超过最大重传次数限制后，建立连接的系统调用会返回 -1。
- 若第二次握手客户端未接收到服务器回应的 ACK 报文时，客户端会采取第一次握手失败时的动作，这里不再重复，而**服务器端此时将阻塞在 accept() 系统调用处等待 client 再次发送 ACK 报文**。
- 若第三次握手服务器未接收到客户端发送过来的 ACK 报文，同样会采取类似于客户端的**超时重传机制**，若重传次数超过限制后仍然没有回应，则 accept() 系统调用返回 -1，**服务器端连接建立失败**。但此时客户端认为自己已经连接成功了，因此开始向服务器端发送数据，但是服务器端的 accept() 系统调用已返回，此时没有在监听状态。因此服务器端接收到来自客户端发送来的数据时会发送RST 报文给客户端，消除客户端单方面建立连接的状态。

![image.png](C:\Users\hp-pc\Desktop\C++\TCPIP网络编程.assets\1627570368-YNpFKD-image.png)



**为什么要进行三次握手？两次握手可以吗？**

三次握手的主要目的是确认自己和对方的发送和接收都是正常的，从而保证了双方能够进行可靠通信。**若采用两次握手，当第二次握手后就建立连接的话，此时客户端知道服务器能够正常接收到自己发送的数据，而服务器并不知道客户端是否能够收到自己发送的数据。**

我们知道网络往往是非理想状态的（存在丢包和延迟），当客户端发起创建连接的请求时，如果服务器直接创建了这个连接并返回包含 SYN、ACK 和 Seq 等内容的数据包给客户端，这个数据包因为网络传输的原因丢失了，丢失之后客户端就一直接收不到返回的数据包。由于客户端可能设置了一个超时时间，一段时间后就关闭了连接建立的请求，再重新发起新的请求，而服务器端是不知道的，如果没有第三次握手告诉服务器客户端能否收到服务器传输的数据的话，服务器端的端口就会一直开着，等到客户端因超时重新发出请求时，服务器就会重新开启一个端口连接。长此以往， 这样的端口越来越多，就会造成服务器开销的浪费。



**第 2 次握手传回了 ACK，为什么还要传回 SYN**

SYN是服务端请求连接



**为什么要四次挥手？**

释放 TCP 连接时之所以需要四次挥手，是因为FIN释放连接报文和ACK确认接收报文是分别在两次握手中传输的。 当主动方在数据传送结束后发出连接释放的通知，由于被动方可能还有必要的数据要处理，所以会先返回 ACK 确认收到报文。当被动方也没有数据再发送的时候，则发出连接释放通知，对方确认后才完全关闭TCP连接。

举个例子：A 和 B 打电话，通话即将结束后，A 说“我没啥要说的了”，B回答“我知道了”，但是 B 可能还会有要说的话，A 不能要求 B 跟着自己的节奏结束通话，于是 B 可能又巴拉巴拉说了一通，最后 B 说“我说完了”，A 回答“知道了”，这样通话才算结束。

**简单来说就是因为TCP是全双工的，两个方向的连接需要单独关闭。**



**TCP 和 UDP 的区别**

| 类型 | **是否面向连接** | **传输可靠性** | 传输形式   | **传输效率** | **所需资源** | **应用场景**       | **首部字节** |
| ---- | ---------------- | -------------- | ---------- | ------------ | ------------ | ------------------ | ------------ |
| TCP  | 是               | 可靠           | 字节流     | 低           | 多           | 文件、邮件传输     | 20-60        |
| UDP  | 否               | 不可靠         | 数据报文段 | 高           | 少           | 即时通讯、域名转化 | 8个字节      |

<img src="C:\Users\hp-pc\Desktop\C++\TCPIP网络编程.assets\1619656539-VAbTGx-86A7C211-7128-4183-A636-1D729B1873AF-10750-000002807F7C8929.jpg" alt="86A7C211-7128-4183-A636-1D729B1873AF-10750-000002807F7C8929.jpg" style="zoom:80%;" />



### 5.3 基于Windows的实现

略



### 5.4 习题

1. **请说明 TCP 套接字连接设置的三次握手过程。尤其是 3 次数据交换过程每次收发的数据内容。**

   答：TCP套接字的生命周期主要可分为3个部分: 

   ①与对方套接字**建立连接** 

   ②与对方套接字进行**数据交换** 

   ③**断开**与对方套接字的**连接**。

   其中,在第一步建立连接的阶段,又可细分为3个步骤(即三次握手)：①由主机1给主机2发送初始的SEQ，首次连接请求是关键字是SYN，表示收发数据前同步传输的消息,此时报文的ACK一般为空。②主机2收到报文以后，给主机 1 传递信息，用一个新的SEQ表示自己的序号，然后ACK代表已经接受到主机1的消息，希望接受下一个消息③主机1收到主机2的确认以后，还需要给主机2给出确认，此时再发送一次SEQ和ACK。

2. **TCP 是可靠的数据传输协议，但在通过网络通信的过程中可能丢失数据。请通过 ACK 和 SEQ 说明 TCP 通过和何种机制保证丢失数据的可靠传输。**

   答：通过超时重传机制来保证，如果报文发出去的特定时间内，发送消息的主机没有收到另一个主机的回复，那么就继续发送这条消息，直到收到回复为止。

3. **TCP 套接字中调用 write 和 read 函数时数据如何移动？结合 I/O 缓冲进行说明。**

   答：TCP 套接字调用 write 函数时，数据将移至输出**缓冲**，在适当的时候，传到对方输入缓冲。这时对方将调用 read 函数从输入缓冲中读取数据。

4. **对方主机的输入缓冲剩余 50 字节空间时，若本主机通过 write 函数请求传输 70 字节，请问 TCP 如何处理这种情况？**

   答：在TCP中，当本地主机通过write函数发送数据时，TCP会把这些数据放入发送缓冲区中，并且在TCP协议栈内部，会采用滑动窗口的方式来控制发送数据的流量。当接收主机的输入缓冲区剩余空间不足时，TCP会采用**流量控制技术**来避免数据的丢失和网络拥塞。

   具体来说，当对方主机的输入缓冲区剩余空间不足时，TCP会向本地主机发送一个窗口更新通知（Window Update）。**本地主机接收到窗口更新通知后，会重新计算可发送数据的大小，并将发送缓冲区中剩余的数据保留在本地，直到对方主机有足够的缓冲区空间来接收这些数据为止**。

   因此，在这种情况下，TCP会将70字节的数据放入本地发送缓冲区中，并尝试发送这些数据。当对方主机的输入缓冲区剩余空间不足时，TCP会发送一个窗口更新通知，本地主机接收到窗口更新通知后会重新计算可发送数据的大小，然后保留剩余的20字节数据在本地发送缓冲区中，等待对方主机的输入缓冲区空间有足够的空间后再发送。





## 第6章 基于UDP的服务端/客户端

### 6.1 理解UDP

数据交换过程可以分为通过TCP套接字完成的TCP方式和通过UDP套接字完成的UDP方式。



**UDP套接字的特点**

UDP（User Datagram Protocol）是一种无连接的传输协议，它的套接字具有以下特点：

1. 不可靠性：UDP 不保证数据包的可靠传输。这意味着，如果数据包在传输过程中丢失、重复、延迟或损坏，UDP 不会尝试恢复或重新传输数据包，而是将它们丢弃或交给应用程序处理。
2. 速度快：UDP 比 TCP 更快，因为它不需要进行错误检查和重传数据包等复杂的控制操作。这使得它特别适合于需要快速传输数据的应用程序，如实时游戏和流媒体等。
3. 无连接性：UDP 是一种无连接的传输协议，因此不需要在发送数据之前建立连接。这意味着可以通过单个数据包或数据报发送数据，而无需进行握手或维护状态信息，从而减少网络延迟。
4. 没有拥塞控制：UDP 没有拥塞控制机制，因此在网络拥塞的情况下，它可能会导致数据包丢失或延迟。然而，这也使得 UDP 在高负载情况下可以更快地传输数据。
5. 适合短数据包传输：UDP 适合传输短数据包，因为它的头部较小，只有 8 个字节。这减少了网络带宽的使用和传输延迟。



**UDP内部工作原理**

**IP层的作用是将数据包从源地址发送到目的地址，UDP的作用是根据端口号将传给主机的数据包交付给最终的套接字。**

如图所示：

![img](C:\Users\hp-pc\Desktop\C++\TCPIP网络编程.assets\68747470733a2f2f692e6c6f6c692e6e65742f323031392f30312f31372f356333666432396337306266322e706e67.png)

从图中可以看出，IP 的作用就是让离开主机 B 的 UDP 数据包准确传递到主机 A 。但是把 UDP 数据包最终交给主机 A 的某一 UDP 套接字的过程是由 UDP 完成的。UDP 的最重要的作用就是根据端口号将传到主机的数据包交付给最终的 UDP 套接字。



**UDP的高效使用**

TCP比UDP慢主要有以下两点：

- 收发数据前后需要进行连接设置和清除（建立连接时的三次握手和释放连接时的四次挥手）
- 在收发数据的过程中，为了保证可靠性添加的滑动窗口和流量控制协议



### 6.2 实现基于UDP的服务端/客户端

**UDP的服务端和客户端没有连接**

UDP是无连接的，在收发数据之前并不需要事先建立连接，所以不必调用listen和accept函数。只有创建套接字和数据交换的过程。



**UDP服务端和客户端只需1个套接字**

TCP 中，套接字之间应该是一对一的关系。若要向 10 个客户端提供服务，除了守门的服务器套接字之外，还需要 10 个服务器套接字。但在 UDP 中，不管是服务器端还是客户端都只需要 1 个套接字。只需要一个 UDP 套接字就可以向任意主机传输数据，如图所示：

![img](C:\Users\hp-pc\Desktop\C++\TCPIP网络编程.assets\68747470733a2f2f692e6c6f6c692e6e65742f323031392f30312f31372f356333666437303366336334302e706e67.png)

图中展示了 1 个 UDP 套接字与 2 个不同主机交换数据的过程。也就是说，只需 1 个 UDP 套接字就能和多台主机进行通信。



**基于 UDP 的数据 I/O 函数**

创建好 TCP 套接字以后，传输数据时无需加上地址信息。因为 TCP 套接字将保持与对方套接字的连接。换言之，TCP 套接字知道目标地址信息。但 UDP 套接字不会保持连接状态（UDP 套接字只有简单的邮筒功能），因此每次传输数据时都需要添加目标的地址信息。这相当于寄信前在信件中填写地址。接下来是 UDP 的相关函数：

```c++
#include <sys/socket.h>

ssize_t sendto(int sock, void *buff, size_t nbytes, int flags,
               struct sockaddr *to, socklen_t addrlen);
/*
成功时返回发送的字节数，失败时返回 -1
sock: 用于传输数据的 UDP 套接字
buff: 保存待传输数据的缓冲地址值
nbytes: 待传输的数据长度，以字节为单位
flags: 可选项参数，若没有则传递 0
to: 存有目标地址的 sockaddr 结构体变量的地址值
addrlen: 传递给参数 to 的地址值结构体变量长度
*/
```

> 在 C++ 中，`void*` 是一种通用的指针类型，它可以指向任何类型的数据，但是它没有指定数据类型的大小和解释方式，因此我们不能直接对其进行解引用操作。`void*` 可以通过强制类型转换转换为其他指针类型，在需要指向不同类型的数据时非常有用。

上述函数与之前的 TCP 输出函数最大的区别在于，**此函数需要向它传递目标地址信息**。接下来介绍接收 UDP 数据的函数。UDP 数据的发送并不固定，因此该函数定义为可接受发送端信息的形式，也就是将同时返回 UDP 数据包中的发送端信息。

```c++
#include <sys/socket.h>
ssize_t recvfrom(int sock, void *buff, size_t nbytes, int flags,
                 struct sockaddr *from, socklen_t *addrlen);//最后一个参数是指针类型
/*
成功时返回接收的字节数，失败时返回 -1
sock: 用于传输数据的 UDP 套接字
buff: 保存待传输数据的缓冲地址值
nbytes: 待传输的数据长度，以字节为单位
flags: 可选项参数，若没有则传递 0
from: 存有发送端地址信息的 sockaddr 结构体变量的地址值
addrlen: 保存参数 from 的结构体变量长度的变量地址值。
*/
```

编写 UDP 程序的最核心的部分就在于上述两个函数，这也说明二者在 UDP 数据传输中的地位。



**基于 UDP 的回声服务器端/客户端**

 服务端

```c++
#include <iostream>
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

#define BUF_SIZE 30

int main(int argc, char *argv[]){
    int serv_sock;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_size;
    char message[BUF_SIZE];

    if (argc != 2){
        cout << "Usage : <port>" << endl;
        return -1; 
    }

    serv_sock = socket(AF_INET, SOCK_DGRAM, 0);//使用UDP协议
    if (serv_sock == -1){
        cout << "Server create socket error" << endl;
        return -1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        cout << "Server bind socket error" << endl;
        return -1;
    }else
        cout << "Server bind success" << endl;

    while (1){
        //当从客户端收到信息，将信息发送回去
        clnt_size = sizeof(clnt_addr);
        memset(message, 0, sizeof(message));    //清空message数组
        int recv_len = recvfrom(serv_sock, message, BUF_SIZE, 0, (struct sockaddr*)&clnt_addr, &clnt_size);

        cout << "Received :" << message << endl;

        sendto(serv_sock, "Server send:", sizeof("Server send:"), 0, (struct sockaddr*)&clnt_addr, clnt_size);
        sendto(serv_sock, message, recv_len, 0, (struct sockaddr*)&clnt_addr, clnt_size);
    }

    close(serv_sock);
    return 0;
}
```

客户端

```c++
#include <iostream>
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

#define BUF_SIZE 30

int main(int argc, char* argv[]){
    int clnt_sock;
    struct sockaddr_in serv_addr;
    socklen_t serv_size;
    char message[BUF_SIZE];

    if (argc != 3){
        cout << "Usage : <IP> <port>" << endl;
        return -1; 
    }

    clnt_sock = socket(AF_INET, SOCK_DGRAM, 0);//UDP协议
    if (clnt_sock == -1){
        cout << "Client create socket error" << endl;
        return -1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    while (1){
        //客户端向服务端发送信息
        cout << "Please input message:" << endl;
        cin.getline(message, BUF_SIZE); //读取一整行
        if (strcmp(message, "quit") == 0 || strcmp(message, "q") == 0)
            break;

        sendto(clnt_sock, message, strlen(message), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

        //在服务端发送了两次数据，相应的客户端也应该读取两次
        serv_size = sizeof(serv_addr);
        int recv_len = recvfrom(clnt_sock, message, BUF_SIZE, 0, (struct sockaddr*)&serv_addr, &serv_size);
        message[recv_len] = 0;
        cout << message << endl;

        recv_len = recvfrom(clnt_sock, message, BUF_SIZE, 0, (struct sockaddr*)&serv_addr, &serv_size);
        message[recv_len] = 0;
        cout << message << endl;
    }

    close(clnt_sock);
    return 0; 
}
```



**UDP客户端套接字的地址分配**

仔细观察 UDP 客户端可以发现，UDP 客户端缺少了把IP和端口分配给套接字的过程。**TCP 客户端调用 connect 函数**自动完成此过程，而 UDP 中连能承担相同功能的函数调用语句都没有。究竟在什么时候分配IP和端口号呢？

UDP 程序中，调用 `sendto` 函数传输数据前应该完成对套接字的地址分配工作，因此**调用 bind 函数**。当然，bind 函数在 TCP 程序中出现过，但 bind 函数不区分 TCP 和 UDP，也就是说，在 UDP 程序中同样可以调用。另外，如果调用 **`sendto` 函数**尚未分配地址信息，则在首次调用 `sendto` 函数时给相应套接字自动分配 IP 和端口。而且此时分配的地址一直保留到程序结束为止，因此也可以用来和其他 UDP 套接字进行数据交换。当然，IP 用主机IP，端口号用未选用的任意端口号。

综上所述，**调用 `sendto` 函数时自动分配IP和端口号**，因此，UDP 客户端中通常无需额外的地址分配过程。所以之前的示例中省略了该过程。这也是普遍的实现方式。



### 6.3 UDP 的数据传输特性和调用 connect 函数

存在数据边界的 UDP 套接字

前面说得 TCP 数据传输中不存在数据边界，这表示「数据传输过程中调用 I/O 函数的次数不具有任何意义」

相反，UDP 是具有数据边界，传输中调用 I/O 函数的次数非常重要。因此，输入函数的调用次数和输出函数的调用次数应该完全一致，这样才能保证接收全部已经发送的数据。例如，调用 3 次输出函数发送的数据必须通过调用 3 次输入函数才能接收完。通过一个例子来进行验证：

在上述代码中调用了两次`sendto`和两次`recvfrom`函数



### 6.4 基于Windows的实现

略



### 6.5 习题

1. **UDP 为什么比 TCP 快？为什么 TCP 传输可靠而 TCP 传输不可靠？**

   答：

   UDP 相比 TCP 有以下几个方面的优势，使其通常比 TCP 更快：

   1. 不需要建立连接和维护连接状态，UDP 直接发送数据包，因此 UDP 的头部开销更小，减少了网络传输的数据量。
   2. 没有拥塞控制，不需要等待确认或重传，UDP 可以一直发送数据，因此 UDP 的传输效率更高，特别是在网络拥塞的情况下。
   3. UDP 不保证数据包到达的顺序，也不保证数据包的可靠性。这意味着如果应用程序可以容忍少量的数据丢失或乱序，那么 UDP 可以提供更高的性能。

   TCP 相比 UDP 具有以下几个方面的优势，使其传输更加可靠：

   1. 建立连接和维护连接状态，TCP 可以保证数据的完整性和可靠性，数据传输结束后，TCP 会发送一个 FIN 数据包来结束连接。
   2. 有拥塞控制机制，TCP 会根据网络的情况动态调整发送速率和拥塞窗口，防止网络拥塞和数据包丢失。
   3. TCP 保证数据包的顺序，如果数据包到达的顺序不正确，TCP 会将数据包缓存起来，等待缺失的数据包到达后再按照正确的顺序交给应用程序。

   因此，TCP 传输相对于 UDP 来说更加可靠，但是也会带来一些额外的开销，比如建立连接和维护连接状态等。在应用程序开发中，需要根据具体的需求来选择合适的传输协议。

   

2. **下面不属于 UDP 特点的是？**

   下面加粗的代表此句话正确

   1. **UDP 不同于 TCP ，不存在连接概念，所以不像 TCP 那样只能进行一对一的数据传输。**

   2. 利用 UDP 传输数据时，如果有 2 个目标，则需要 2 个套接字。

   3. UDP 套接字中无法使用已分配给 TCP 的同一端口号

   4. **UDP 套接字和 TCP 套接字可以共存。若需要，可以同时在同一主机进行 TCP 和 UDP 数据传输。**

   5. 针对 UDP 函数也可以调用 connect 函数，此时 UDP 套接字跟 TCP 套接字相同，也需要经过 3 次握手阶段。

      

3. **UDP 数据报向对方主机的 UDP 套接字传递过程中，IP 和 UDP 分别负责哪些部分？**

   答：IP的作用就是让离开主机的 UDP 数据包准确传递到另一个主机。但把 UDP 包最终交给主机的某一 UDP 套接字的过程则是由 UDP 完成的。UDP 的最重要的作用就是根据端口号将传到主机的数据包交付给最终的 UDP 套接字。

   

4. **UDP 一般比 TCP 快，但根据交换数据的特点，其差异可大可小。请你说明何种情况下 UDP 的性能优于 TCP？**

   答：如果收发数据量小但需要频繁连接时，UDP 比 TCP 更高效。

   

5. **客户端 TCP 套接字调用 connect 函数时自动分配IP和端口号。UDP 中不调用 bind 函数，那何时分配IP和端口号？**

   答：在首次调用 sendto 函数时自动给相应的套接字分配IP和端口号。而且此时分配的地址一直保留到程序结束为止。

   

6. **TCP 客户端必须调用 connect 函数，而 UDP 可以选择性调用。请问，在 UDP 中调用 connect 函数有哪些好处？**

   答：要与同一个主机进行长时间通信时，将 UDP 套接字变成已连接套接字会提高效率。因为三个阶段中，第一个阶段和第三个阶段占用了一大部分时间，调用 connect 函数可以节省这些时间。





## 第7章 优雅的断开套接字连接

### 7.1 基于TCP的半关闭

TCP中断开连接的过程比建立连接过程更重要，因为连接过程中一般不会出现大的变数，但是在断开过程中可能发生意想不到的情况，因此应准确掌握。只有掌握了下面要讲解的半关闭(Half-close)，才能明确断开过程。



**单方面断开连接带来的问题**

Linux的`close`函数和Windows的`closesocket`函数意味着完全断开连接。完全断开不仅指无法传输数据，而且也不能接收数据。因此在某些情况下，通信一方单方面的断开套接字连接，显得不太优雅。如图所示：

![img](C:\Users\hp-pc\Desktop\C++\TCPIP网络编程.assets\68747470733a2f2f692e6c6f6c692e6e65742f323031392f30312f31382f356334313261386261613264382e706e67.png)

图中描述的是 2 台主机正在进行双向通信，主机 A 发送完最后的数据后，调用 close 函数断开了最后的连接，之后主机 A 无法再接受主机 B 传输的数据。实际上，**是完全无法调用与接受数据相关的函数**。最终，由主机 B 传输的、主机 A 必须要接受的数据也销毁了。

为了解决这类问题，「只关闭一部分数据交换中使用的流」的方法应运而生。**断开一部分连接是指，可以传输数据但是无法接收，或可以接受数据但无法传输**。顾名思义就是只关闭流的一半。



**套接字和流（Stream）**

两台主机通过套接字建立连接后进入可交换数据的状态，又称「流形成的状态」。也就是把建立套接字后可交换数据的状态看作一种流。

此处的流可以比作水流。水朝着一个方向流动，同样，在套接字的流中，数据也只能向一个方向流动。因此，为了进行双向通信，需要如图所示的两个流：

![img](TCPIP网络编程.assets/68747470733a2f2f692e6c6f6c692e6e65742f323031392f30312f31382f356334313263336261323564642e706e67-16810935908844.png)

一旦两台主机之间建立了套接字连接，每个主机就会拥有单独的输入流和输出流。当然，其中一个主机的输入流与另一个主机的输出流相连，而输出流则与另一个主机的输入流相连。另外，本章讨论的「优雅的断开连接方式」只断开其中 1 个流，而非同时断开两个流。Linux的close函数和Windows的`closesocket`函数将同时断开这两个流，因此与「优雅」二字还有一段距离。



**针对优雅断开的 shutdown 函数**

shutdown 用来关闭其中一个流：

```c++
#include <sys/socket.h>

int shutdown(int sock, int howto);
/*
成功时返回 0 ，失败时返回 -1
sock: 需要断开套接字文件描述符
howto: 传递断开方式信息
*/
```

调用上述函数时，第二个参数决定断开连接的方式，其值如下所示：

- `SHUT_RD` : 断开输入流

  若向 shutdown 的第二个参数传递`SHUT_RD`，则断开输入流，套接字无法接收数据。即使输入缓冲收到数据也会抹去，而且无法调用相关函数。

- `SHUT_WR` : 断开输出流

  如果向 shutdown 的第二个参数传递`SHUT_WR`，则中断输出流，也就无法传输数据。若如果输出缓冲中还有未传输的数据，则将传递给目标主机。

- `SHUT_RDWR` : 同时断开 I/O 流

  最后，若传递关键字`SHUT_RDWR`，则同时中断 I/O 流。这相当于分 2 次调用 shutdown ，其中一次以`SHUT_RD`为参数，另一次以`SHUT_WR`为参数。





**为何要半关闭**

考虑以下情况：

> 一旦客户端连接到服务器，服务器将约定的文件传输给客户端，客户端收到后发送字符串「Thank you」给服务器端。

此处「Thank you」的传递是多余的，这只是用来模拟客户端断开连接前还有数据要传输的情况。此时程序的还嫌难度并不小，因为传输文件的服务器端只需连续传输文件数据即可，而客户端无法知道需要接收数据到何时。客户端也没办法无休止的调用输入函数，因为这有可能导致程序**阻塞**。

> 是否可以让服务器和客户端约定一个代表文件尾的字符？

这种方式也有问题，因为这意味这文件中不能有与约定字符相同的内容。为了解决该问题，服务端应最后向客户端传递 EOF 表示文件传输结束。客户端通过函数返回值接受 EOF ，这样可以避免与文件内容冲突。那么问题来了，服务端如何传递 EOF ？

> 断开输出流时向主机传输 EOF。

当然，调用 close 函数的同时关闭 I/O 流，这样也会向对方发送 EOF 。但此时无法再接受对方传输的数据。换言之，若调用 close 函数关闭流，就无法接受客户端最后发送的字符串「Thank you」。这时需要调用 shutdown 函数，只关闭服务器的输出流。这样既可以发送 EOF ，同时又保留了输入流。下面实现收发文件的服务器端/客户端。

> 半关闭（Half-Close）是指在一个套接字连接中关闭一个方向的通信，而保持另一个方向的通信继续保持开放状态。
>
> 在网络编程中，半关闭通常用于以下情况：
>
> 1. 一个应用程序需要在收到对端所有数据后才能开始处理这些数据。这种情况下，应用程序可以关闭套接字的**写入**方向，以表示它已经发送完数据并且不会再向对端发送数据了。但是，它仍然可以接收来自对端的数据。
> 2. 一个应用程序需要在发送所有数据后等待对端响应。这种情况下，应用程序可以关闭套接字的**读取**方向，以表示它已经接收完对端的数据并且不会再接收数据了。但是，它仍然可以向对端发送数据。
> 3. 在一个长时间运行的连接中，可以在双方都完成了它们的任务后关闭套接字的某个方向。这可以释放资源，提高系统的效率。
>
> **总之，半关闭可以在保持套接字连接的同时，允许一个方向的通信结束，从而实现更加高效的网络编程。**



**基于半关闭的文件传输程序**

上述文件传输服务器端和客户端的数据流可以整理如图：

![img](C:\Users\hp-pc\Desktop\C++\TCPIP网络编程.assets\68747470733a2f2f692e6c6f6c692e6e65742f323031392f30312f31382f356334313332363238306162352e706e67.png)

客户端：

```c++
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

#define BUF_SIZE 30

int main(int argc, char* argv[]){
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
        cout << "Server bind socket error" << endl;
        return -1;
    }

    if (listen(serv_sock, 5) == -1){
        cout << "Server listen socket error" << endl;
        return -1;
    }

    clnt_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_size);
    if (clnt_sock == -1){
        cout << "Server accept socket error" << endl;
        return -1;
    }
    //上述代码是服务端和客户端建立TCP连接

    FILE* fp = fopen("hello_server.cpp", "rb");
    if (fp == NULL){
        cout << "File open error" << endl;
        return -1;
    }else{
        cout << "FILE open success" << endl;
    }
    
    char buf[BUF_SIZE];

    while (1){
        //将fp文件中的数据全写入clnt_sock客户端
        memset(buf, 0, sizeof(buf));
        int read_cnt = fread((void*)buf, 1, BUF_SIZE, fp);
        if (read_cnt < BUF_SIZE){
            write(clnt_sock, buf, read_cnt);
            break;
        }
        write(clnt_sock, buf, BUF_SIZE);
    }

    shutdown(clnt_sock, SHUT_WR);   //关闭客户端写方向的输出流
    read(clnt_sock, buf, BUF_SIZE); //进入半关闭状态还可以从客户端中读取数据
    cout << "Message from client : " << buf << endl;

    fclose(fp);
    close(clnt_sock);close(serv_sock);

    return 0;
}
```

> 在这个特定的代码中，`shutdown(clnt_sock, SHUT_WR)`关闭了`clnt_sock`套接字的写入功能。这意味着在调用`shutdown`函数之后，我们无法向该套接字写入数据，但是可以从该套接字读取数据。通常情况下，当我们不再需要向客户端发送数据时，可以使用`shutdown`函数关闭套接字的写入功能，这可以让客户端知道我们已经完成了数据的发送。

服务端：

```c++
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

#define BUF_SIZE 30

int main(int argc, char *argv[]){
    int clnt_sock;
    struct sockaddr_in serv_addr;

    if (argc != 3){
        cout << "Usage : <IP> <port>" << endl;
        return -1;
    }

    clnt_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (clnt_sock == -1){
        cout << "Client create socket" << endl;
        return -1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(clnt_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        cout << "Client connect socket" << endl;
        return -1;
    } 

    FILE* fp = fopen("receive.dat", "wb");
    if (fp == NULL){
        cout << "File open error" << endl;
        return -1;
    }else{
        cout << "FILE open success" << endl;
    }

    int read_cnt;
    char buf[BUF_SIZE];

    //从clnt_sock套接字中读取数据写入到receive.dat文件中
    while (read_cnt = read(clnt_sock, buf, sizeof(serv_addr)) != 0){
        fwrite(buf, 1, read_cnt, fp);
    }

    cout << "Received file data" << endl;
    write(clnt_sock, "Thank you", 10);

    fclose(fp);
    close(clnt_sock);

    return 0;
}
```



### 7.2 基于Windows的实现

略



### 7.3 习题

1. **解释 TCP 中「流」的概念。UDP 中能否形成流？请说明原因。**

   答：在TCP协议中，**"流"是指在两个通信实体之间传输的连续字节序列**。TCP通过把字节流分割成合适的报文段来进行数据传输，并且提供了可靠的数据传输，可以保证数据按照正确的顺序到达目标机器，并且不会出现丢失、损坏、重复等情况。

   而在UDP协议中，数据被视为独立的数据包，每个数据包都是相互独立的，不会和其他数据包进行关联。因此，UDP中没有"流"的概念，每个数据包都是独立的，可以按照任意顺序到达目标机器，也可能会丢失或重复。UDP提供了无连接、不可靠的数据传输，适用于实时性要求较高，但对数据完整性和可靠性要求较低的应用场景，比如视频和音频流传输。

   总之，TCP协议中的"流"是基于字节序列的有序数据传输机制，而UDP协议中不存在"流"的概念，每个数据包都是独立的。

2. **Linux 中的 close 函数或 Windows 中的 `closesocket`  函数属于单方面断开连接的方法，有可能带来一些问题。什么是单方面断开连接？什么情形下会出现问题？**

   答：单方面断开连接可能会导致一些问题，例如：

   1. 数据丢失：如果一个连接在一方关闭之前有未发送的数据，这些数据将会丢失，而另一方将无法接收到这些数据。
   2. 资源泄漏：如果一个连接在一方关闭之前已经分配了资源（如内存），并且另一方仍然尝试使用该连接，那么这些资源可能会泄漏，导致系统出现不稳定或崩溃。
   3. 半开连接：在某些情况下，一方关闭连接后，另一方仍然认为连接处于打开状态，这种情况被称为“半开连接”。在这种情况下，另一方仍然可以向该连接发送数据，但是由于连接已被关闭，这些数据将被丢弃，而且这种情况可能导致连接的状态不一致，从而影响系统的正常运行。

   因此，**在关闭连接时，应该采用双方面协商的方式来确保连接被正确关闭，而不是单方面断开连接**。例如，在 Linux 中，可以使用 shutdown 函数来向另一方发送一个信号，告诉它连接即将关闭，然后再调用 close 函数来关闭连接。在 Windows 中，可以使用 shutdown 函数和 `closesocket` 函数实现类似的功能。

3. **什么是半关闭？针对输出流执行半关闭的主机处于何种状态？半关闭会导致对方主机接收什么消息？**

   答：半关闭（half-closed）是指在一个连接的一方关闭其输出流（发送方向的数据流），但是仍然可以接收从另一方发送过来的数据。在这种情况下，连接仍然处于打开状态，但是只有一方可以发送数据。

   如果针对输出流执行半关闭的主机，则该主机的输出流将被关闭，但其输入流仍然打开，可以接收来自对方主机的数据。

   **半关闭通常用于允许一个应用程序向另一个应用程序发送一些控制信息或指令，然后等待对方应用程序完成其任务，然后再关闭连接**。例如，一个 FTP 客户端可能会在上传文件完成后半关闭输出流，然后等待 FTP 服务器响应确认信息，确认文件已成功上传，然后再完全关闭连接。

   在半关闭期间，对方主机可以继续向该连接发送数据，而半关闭的主机可以接收这些数据，但是半关闭的主机不能再向对方主机发送数据。如果对方主机尝试向半关闭的主机发送数据，则这些数据将被丢弃，因为输出流已被关闭。一旦对方主机也执行了半关闭，那么连接将完全关闭，两个主机都不能再发送数据。





## 第8章 域名及网络地址

### 8.1 域名系统

域名系统（Domain Name System，DNS）是一种用于将域名（例如www.example.com）映射到其相应IP地址的分布式命名系统。DNS允许用户使用易于记忆的域名来访问Internet上的资源，而不是使用IP地址。在DNS中，每个域名都对应一个IP地址，这个IP地址可以是一个IPv4地址（例如192.0.2.1）或一个IPv6地址（例如2001:db8::1）。



DNS 是对IP地址和域名进行相互转换的系统，其核心是 DNS 服务器

**什么是域名**

域名就是我们常常在地址栏里面输入的地址，将比较难记忆的IP地址变成人类容易理解的信息。

 **DNS 服务器**

相当于一个字典，可以查询出某一个域名对应的IP地址

![img](C:\Users\hp-pc\Desktop\C++\TCPIP网络编程.assets\68747470733a2f2f692e6c6f6c692e6e65742f323031392f30312f31382f356334313835343835396165332e706e67.png)

如图所示，显示了 DNS 服务器的查询路径。

DNS是一个层次结构的系统，由多个DNS服务器组成，这些服务器按照一定的规则进行分级和协作。最高层次的DNS服务器被称为根域名服务器，它们维护了整个域名系统的顶级域名（例如.com、.org等）。下一级是顶级域名服务器，它们负责维护特定顶级域名下的域名（例如example.com）。下一级是权威域名服务器，它们维护了特定域名下的所有记录（例如www.example.com）。

当用户在浏览器中输入一个域名时，浏览器会向本地DNS解析器发出请求，本地DNS解析器会向根域名服务器发出查询，然后沿着层次结构向下查找，直到找到包含所需记录的权威域名服务器。然后，本地DNS解析器将IP地址返回给浏览器，浏览器使用这个IP地址连接到目标服务器。





### 8.2 IP地址和域名之间的转换

**程序中有必要使用域名吗？**

一句话，需要，因为IP地址可能经常改变，而且也不容易记忆，通过域名可以随时更改解析，达到更换IP的目的



**利用域名获取IP地址**

`gethostbyname` 函数是 C++ 中用于获取指定主机名对应的 IP 地址信息的函数。

以下是该函数的函数原型：

```c++
#include  <netdb.h>

struct hostent *gethostbyname(const char *name);
```

该函数接收一个表示主机名的字符串作为参数，返回一个指向 `hostent` 结构体的**指针**。`hostent` 结构体包含了与主机名相关的各种信息，包括主机名、主机别名、主机地址类型和地址列表等。

```c++
struct hostent{
	char * h_name;			//official name of host
	char ** h_aliases;		//alias list
	int h_addrtype;		    //host address type
	int h_length;		    //length of address	
	char ** h_addr_list;	//list of addresses
}
```

- `h_name`：指向主机的 official name 的指针。
- `h_aliases`：指向主机别名列表的指针。别名是一组与主机名相关联的备用名称。例如，"www" 是 "[www.example.com](http://www.example.com/)" 的一个可能的别名。
- `h_addrtype`：主机地址类型，通常为 `AF_INET` 或 `AF_INET6`。
- `h_length`：主机地址的长度，以**字节**为单位。
- `h_addr_list`：指向主机地址列表的指针。该列表包含主机的所有 IP 地址，以网络字节序（big-endian）表示。

调用 `gethostbyname` 函数后，返回的结构体变量如图所示：

<img src="C:\Users\hp-pc\Desktop\C++\TCPIP网络编程.assets\0.476-16798868883647.gif" alt="S0C4 ABEND or Unexpected Results When Trying to Access HOSTENT Structure" style="zoom: 50%;" />

下面的代码通过一个例子来演示 `gethostbyname` 的应用，并说明 `hostent` 结构体变量特性。

```c++
#include <iostream>
#include <netdb.h>
#include <arpa/inet.h>
using namespace std;

int main(int argc, char* argv[]){
    if (argc != 2){
        cout << "Usage: <addr>" << endl;
        return -1;
    }

    struct hostent *host;
    host = gethostbyname(argv[1]);
    if (host == NULL){
        cout << "Falied to get host informantion for" << argv[1] << endl;
        return -1;
    }

    cout << "Host name : " << host->h_name << endl;

    for (char ** alias = host->h_aliases; *alias != NULL; alias++)
        cout << "Alias : " << *alias << endl;

    cout << "Address type : " << (host->h_addrtype == AF_INET ? "IPv4" : "IPv6") << endl;
    cout << "Address length : " << host->h_length << " bytes " << endl;

    for (int i = 0; host->h_addr_list[i] != NULL; i++)
        cout << "IP address " << i+1 << ": " << inet_ntoa(*(struct in_addr*)host->h_addr_list[i]) << endl;

    /*
    在inet_ntoa(*(struct in_addr*)host->h_addr_list[i])中实际上进行了三步
    host->h_addr_list[i]指向了第i个IP地址
    (struct in_addr*)转换为in_addr结构体指针
    最后对结构体指针解引用，将参数传递给inet_ntoa
    通过inet_ntoa可以将IP地址从网络字节序转换为主机字节序，并以点分十进制的形式输出
    */

    return 0;
}
```

将上述代码编译并运行

```c++
g++ gethostbyname.cpp -o gethostbyname

./gethostbyname www.google.com
```

输出：

```c++
Host name : www.google.com
Address type : IPv4
Address length : 4 bytes 
IP address 1: 199.16.156.11
```



**利用IP地址获取域名**

`gethostbyaddr`可以通过IP地址来获取域名信息。

```c++
#include <netdb.h>

struct hostent* gethostbyaddr(const char *addr, socklen_t len, int family);
```

其中，参数说明如下：

- `addr`：指向主机 IP 地址的指针，可以是 IPv4 或 IPv6 地址；
- `len`：主机 IP 地址的长度；
- `type`：指定 `addr` 的地址族，可以是 `AF_INET`（IPv4）或 `AF_INET6`（IPv6）。

该函数返回一个 `hostent` 结构体指针，包含了与主机相关的信息，例如主机名、别名、地址族等。

```c++
#include <iostream>
#include <netdb.h>
#include <cstring>
#include <arpa/inet.h>
using namespace std;

int main(int argc, char *argv[]){
    if (argc  != 2){
        cout << "Usage : <IP>" << endl;
        return -1;
    }

    struct hostent *host;
    struct sockaddr_in addr;

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);

    host = gethostbyaddr((char*)&addr.sin_addr, 4, AF_INET);

    cout << "Host name : " << host->h_name << endl;

    for (char **alias = host->h_aliases; *alias != NULL; alias++)
        cout << "Alias : " << *alias << endl;

    cout << "Address Type : " << (host->h_addrtype == AF_INET ? "IPv4" : "IPv6") << endl;
    cout << "Address legnth : " << host->h_length;

    for (int i = 0; host->h_addr_list[i] != NULL; i++)
        cout << "IP Address : " << inet_ntoa(*(struct in_addr*)host->h_addr_list[i]); 


    return 0;
}
```

将上述代码编译并运行

```c++
g++ gethostbyaddr.cpp -o gethostbyaddr

 ./gethostbyaddr 8.8.8.8
```

输出：

```c++
Host name : dns.google
Address Type : IPv4
Address legnth : 4
IP Address : 8.8.8.8
```





### 8.3 基于Windows的实现

略



### 8.4 习题

1. **下列关于DNS的说法错误的是？**

   答：字体加粗的表示正确答案。

   1. **因为DNS从存在，故可以使用域名代替IP**
   2. DNS服务器实际上是路由器，因为路由器根据域名决定数据的路径
   3. **所有域名信息并非集中与 1 台 DNS 服务器，但可以获取某一 DNS 服务器中未注册的所有地址**
   4. DNS 服务器根据操作系统进行区分，Windows 下的 DNS 服务器和 Linux 下的 DNS 服务器是不同的。

2. **阅读如下对话，并说明东秀的方案是否可行。**

   - 静沫:“东秀吗?我们学校网络中使用的默认DNS服务器发生了故障，无法访问我要投简历的公司主页!有没有办法解决?”
   - 东秀:“网络连接正常，但DNS服务器发生了故障?”
   - 静沫:“恩!有没有解决方法?是不是要去周围的网吧?”东秀:“有那必要吗?我把我们学校的DNS服务器IP地址告诉你，你改一下你的默认DNS服务器地址。”
   - 静沫:“这样可以吗?默认DNS服务器必须连接到本地网络吧!”东秀:“不是!上次我们学校DNS服务器发生故障时，网管就给了我们其他DNS服务器的IP地址呢。”
   - 静沫:“那是因为你们学校有多台DNS服务器!”东秀:“是吗?你的话好像也有道理。那你快去网吧吧!”

   答：东秀的方案是可行的。如果学校有多个DNS服务器，那么静沫只需要将默认DNS服务器地址改为可用的学校DNS服务器的IP地址即可。这种方法通常会被用于DNS服务器故障时的备用方案，而不是仅限于连接到本地网络的默认DNS服务器。因此，静沫可以尝试使用东秀提供的方法来解决无法访问公司主页的问题。

3. **在浏览器地址输入 [www.orentec.co.kr](http://www.orentec.co.kr/) ，并整理出主页显示过程。假设浏览器访问默认 DNS 服务器中并没有关于 [www.orentec.co.kr](http://www.orentec.co.kr/) 的地址信息.**

   答：

   1. 首先，**浏览器**会检查自己的**缓存**中是否已经有了该域名对应的 IP 地址。如果已经存在，则直接使用该 IP 地址，否则继续向下执行。
   2. 浏览器会向**本机的 DNS 缓存**中查询该域名对应的 IP 地址。如果本机缓存中存在，则直接使用该 IP 地址，否则继续向下执行。
   3. 如果本机缓存中不存在该域名对应的 IP 地址，则浏览器会向**本地的 DNS 服务器**发送一个 DNS 查询请求。本地 DNS 服务器一般是由互联网服务提供商（ISP）提供的，它会首先查询自己的缓存，如果本地 DNS 服务器缓存中存在该域名对应的 IP 地址，则直接返回该地址，否则继续向下执行。
   4. 如果本地 DNS 服务器缓存中不存在该域名对应的 IP 地址，则它会向**  **发送一个 DNS 查询请求。根域名服务器是互联网中最高层次的 DNS 服务器，它存储了所有顶级域名（如 `.com`、`.org`、`.net` 等）的 DNS 服务器的 IP 地址。
   5. 根域名服务器将返回一个包含顶级域名服务器的 IP 地址的 DNS 响应报文给本地 DNS 服务器。本地 DNS 服务器会从响应报文中获取顶级域名服务器的 IP 地址，并向其发送一个 DNS 查询请求，请求该域名的 DNS 服务器的 IP 地址。
   6. 顶级域名服务器将返回一个包含该域名的 DNS 服务器的 IP 地址的 DNS 响应报文给本地 DNS 服务器。本地 DNS 服务器会从响应报文中获取该域名的 DNS 服务器的 IP 地址，并向其发送一个 DNS 查询请求，请求该域名的 IP 地址。
   7. 该域名的 DNS 服务器将返回一个包含该域名对应的 IP 地址的 DNS 响应报文给本地 DNS 服务器。本地 DNS 服务器将缓存该域名和 IP 地址的映射关系，并将该响应报文返回给浏览器。
   8. 浏览器将使用该 IP 地址向网站服务器发送一个 HTTP 请求，并等待服务器的响应。网站服务器将返回一个包含 HTML、CSS、JavaScript 等内容的 HTTP 响应报文给浏览器。
   9. 浏览器将解析 HTML、CSS、JavaScript 等内容，并在页面上显示网站的主页。





## 第9章 套接字的多种可选项

套接字就有多种特性，这些特性可通过可选项更改。

### 9.1 套接字可选项和I/O缓冲大小

我们进行套接字编程时往往只关注数据通信，而忽略了套接字具有的不同特性。但是，理解这些特性并根据实际需要进行更改也很重要



**套接字多种可选项**

我们之前写得程序都是创建好套接字之后直接使用的，此时通过默认的套接字特性进行数据通信，这里列出了一些套接字可选项。

| 协议层      | 选项名            | 读取 | 设置 |
| ----------- | ----------------- | ---- | ---- |
| SOL_SOCKET  | SO_SNDBUF         | O    | O    |
| SOL_SOCKET  | SO_RCVBUF         | O    | O    |
| SOL_SOCKET  | SO_REUSEADDR      | O    | O    |
| SOL_SOCKET  | SO_KEEPALIVE      | O    | O    |
| SOL_SOCKET  | SO_BROADCAST      | O    | O    |
| SOL_SOCKET  | SO_DONTROUTE      | O    | O    |
| SOL_SOCKET  | SO_OOBINLINE      | O    | O    |
| SOL_SOCKET  | SO_ERROR          | O    | X    |
| SOL_SOCKET  | SO_TYPE           | O    | X    |
| IPPROTO_IP  | IP_TOS            | O    | O    |
| IPPROTO_IP  | IP_TTL            | O    | O    |
| IPPROTO_IP  | IP_MULTICAST_TTL  | O    | O    |
| IPPROTO_IP  | IP_MULTICAST_LOOP | O    | O    |
| IPPROTO_IP  | IP_MULTICAST_IF   | O    | O    |
| IPPROTO_TCP | TCP_KEEPALIVE     | O    | O    |
| IPPROTO_TCP | TCP_NODELAY       | O    | O    |
| IPPROTO_TCP | TCP_MAXSEG        | O    | O    |

从表中可以看出，套接字可选项是分层的。

- IPPROTO_IP 可选项是IP协议相关事项
- IPPROTO_TCP 层可选项是 TCP 协议的相关事项
- SOL_SOCKET 层是套接字的通用可选项。



**`getsockopt` & `setsockopt`**

几乎可以对上表的所有可选项进行读取(get)和设置(set)。

```c++
#include <sys/socket.h>

int getsockopt(int sock, int level, int optname, void * optval, socklen_t *optlen);
```

其中，参数含义如下：

- `sock`：表示要获取选项值的套接字文件描述符。
- `level`：表示选项所在的协议层。通常情况下为SOL_SOCKET，表示在套接字层获取选项值。
- `optname`：表示要获取的选项名。可选值和对应意义请参考相关文档。
- `optval`：表示选项值缓冲区的指针，用于存储获取到的选项值。
- `optlen`：表示选项值缓冲区的大小，以字节为单位。在调用函数前需要将其初始化为`optval`指向的缓冲区的大小。在函数调用结束后，`optlen`将被设置为实际获取到的选项值的大小。

函数返回值为0表示成功，否则返回-1表示失败。



在C++中，`setsockopt()`函数用于设置套接字选项。它允许您设置套接字的各种属性，例如超时时间、重传次数、缓冲区大小等。以下是该函数的一些基本用法：

```c++
#include <sys/socket.h>

int setsockopt(int sock, int level, int optname, const void *optval, socklen_t optlen);
```

参数说明：

- `sock`：要设置选项的套接字描述符。
- `level`：选项所属的协议层。通常为`SOL_SOCKET`，表示选项适用于套接字级别。
- `optname`：要设置的选项名称。例如`SO_REUSEADDR`表示允许重新使用本地地址。
- `optval`：指向包含选项值的缓冲区的指针。
- `optlen`：选项值缓冲区的大小。



```c++
#include <iostream>
#include <netdb.h>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
using namespace std;

int main(int argc, char *argv[]){
    int tcp_sock, udp_sock;
    int sock_type;
    socklen_t optlen;

    tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
    udp_sock = socket(AF_INET, SOCK_DGRAM, 0);

    cout << "SOCK_STREAM : " << SOCK_STREAM << endl;
    cout << "SOCK_DGRAM : " << SOCK_DGRAM << endl;

    optlen = sizeof(sock_type);
    if (getsockopt(tcp_sock, SOL_SOCKET, SO_TYPE, (void*)&sock_type, &optlen) == -1){
        cout << "Get sock option failed " << endl;
    }
    cout << "Socket type one : " << sock_type << endl;

    if (getsockopt(udp_sock, SOL_SOCKET, SO_TYPE, (void*)&sock_type, &optlen) == -1){
        cout << "Get sock option failed " << endl;
    }
    cout << "Socket type two : " << sock_type << endl;

    return 0;
}
```

**套接字类型只能在创建是决定，以后不能更改**



**`SO_SNDBUF` & `SD_RCVBUF`**

`SO_SNDBUF` 是输入缓冲大小相关可选项， `SD_RCVBUF`是输出缓冲大小输出相关可选项。

有这两个可选项既可以读取当前I/O缓冲大小也可以进行更改。

```c++
#include <iostream>
#include <netdb.h>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
using namespace std;

int main(int argc, char *argv[]){
    int sock, snd_buf = 3 * 1024, rcv_buf = 3 * 1024;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    //SO_RCVBUF接收方向的输入缓冲，首先将I/O缓冲区大小更改为3K，为了验证缓冲区的更改在进行读取
    if (setsockopt(sock, SOL_SOCKET, SO_RCVBUF, &rcv_buf, sizeof(rcv_buf)) == -1){
        cout << "Set socket option failed" << endl;
    }

    socklen_t len = sizeof(rcv_buf);
    if (getsockopt(sock, SOL_SOCKET, SO_RCVBUF, &rcv_buf, &len) == -1){
        cout << "Get socket option failed" << endl;
    }else{
        cout << "Input buffer size : " << rcv_buf << endl;
    }

    //SO_SNDBUF接收方向的输出缓冲
    if (setsockopt(sock, SOL_SOCKET, SO_SNDBUF, &snd_buf, sizeof(snd_buf)) == -1){
        cout << "Set socket option failed" << endl;
    }

    len = sizeof(snd_buf);
    if (getsockopt(sock, SOL_SOCKET, SO_SNDBUF, &snd_buf, &len) == -1){
        cout << "Get socket option failed" << endl;
    }else{
        cout << "Output buffer size : " << snd_buf << endl;
    }

    close(sock);
    return 0;
}
```

输出

```c++
Input buffer size : 6144	//6K
Input buffer size : 6144
```

输出结果和我们预想的不是很相同，缓冲大小的设置需谨慎处理，因此不会完全按照我们的要求进行。



### 8.2 SO_REUSEADDR

在学习 SO_REUSEADDR 可选项之前，应该好好理解 Time-wait 状态。看以下代码的示例：

```c++
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
```

这是一个回声服务器的**服务端**代码，可以配合第四章的 [echo_client.cpp]使用，在这个代码中，客户端通知服务器终止程序。在客户端控制台输入 Q 可以结束程序，向服务器发送 FIN 消息并经过四次握手过程。当然，输入 CTRL+C 也会向服务器传递 FIN 信息。强制终止程序时，由操作系统关闭文件套接字，此过程相当于调用 close 函数，也会向服务器发送 FIN 消息。

这样看不到是什么特殊现象，考虑以下情况：

> 服务器端和客户端都已经建立连接的状态下，向服务器控制台输入 CTRL+C ，强制关闭服务端

如果用这种方式终止程序，如果用同一端口号再次运行服务端，就会输出「bind() error」消息，并且无法再次运行。但是在这种情况下，再过大约 3 分钟就可以重新运行服务端。



**`Time-wait` 状态**

观察以下过程：

![img](C:\Users\hp-pc\Desktop\C++\TCPIP网络编程.assets\68747470733a2f2f692e6c6f6c692e6e65742f323031392f30312f31392f356334326462313832636164652e706e67.png)

假设图中主机 A 是服务器，因为是主机 A 向 B 发送 FIN 消息，故可想象成服务器端在控制台中输入 CTRL+C 。但是问题是，套接字经过四次握手后并没有立即消除，而是要经过一段时间的 Time-wait 状态。当然，只有先断开连接的（先发送 FIN 消息的）主机才经过 Time-wait 状态。因此，若服务器端先断开连接，则无法立即重新运行。套接字处在 Time-wait 过程时，相应端口是正在使用的状态。因此，就像之前验证过的，bind 函数调用过程中会发生错误。

**实际上，不论是服务端还是客户端，都要经过一段时间的 Time-wait 过程。先断开连接的套接字必然会经过 Time-wait 过程，但是由于客户端套接字的端口是任意指定的，所以无需过多关注 Time-wait 状态。**

那到底为什么会有 Time-wait 状态呢，在图中假设，主机 A 向主机 B 传输 ACK 消息（SEQ 5001 , ACK 7502 ）后立刻消除套接字。但是最后这条 ACK 消息在传递过程中丢失，没有传递主机 B ，这时主机 B 就会试图重传。但是此时主机 A 已经是完全终止状态，因此主机 B 永远无法收到从主机 A 最后传来的 ACK 消息。基于这些问题的考虑，所以要设计 Time-wait 状态。



**地址再分配**

Time-wait 状态看似重要，但是不一定讨人喜欢。如果系统发生故障紧急停止，这时需要尽快重启服务起以提供服务，但因处于 Time-wait 状态而必须等待几分钟。因此，Time-wait 并非只有优点，这些情况下容易引发大问题。下图中展示了四次握手时不得不延长 Time-wait 过程的情况。

![img](C:\Users\hp-pc\Desktop\C++\TCPIP网络编程.assets\68747470733a2f2f692e6c6f6c692e6e65742f323031392f30312f31392f356334326465633262613432622e706e67.png)

从图上可以看出，在主机 A 四次握手的过程中，如果最后的数据丢失，则主机 B 会认为主机 A 未能收到自己发送的 FIN 信息，因此重传。这时，收到的 FIN 消息的主机 A 将重启 Time-wait 计时器。因此，如果网络状况不理想， Time-wait 将持续。

解决方案就是在套接字的可选项中更改 SO_REUSEADDR 的状态。适当调整该参数，可将 Time-wait 状态下的套接字端口号重新分配给新的套接字。SO_REUSEADDR 的默认值为 0.这就意味着无法分配 Time-wait 状态下的套接字端口号。因此需要将这个值改成 1 。

```c++
int option = 1;

if (setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)) == -1){
	cout << "Reuse address failed" << endl;
} 
```



### 9.3 TCP_NODELAY

**`Nagle` 算法**

为了防止因数据包过多而发生网络过载，`Nagle` 算法诞生了。它应用于 TCP 层。它是否使用会导致如图所示的差异：

![img](https://camo.githubusercontent.com/d442e8b3be7042d22a23cbcaba67087d127a6f81448e61e1a68fee96423494fa/68747470733a2f2f692e6c6f6c692e6e65742f323031392f30312f31392f356334326531326162633562382e706e67)

图中展示了通过 `Nagle` 算法发送字符串 `Nagle` 和未使用 `Nagle` 算法的差别。可以得到一个结论。

**只有接收到前一数据的 ACK 消息， `Nagle` 算法才发送下一数据。**

TCP 套接字默认使用 `Nagle` 算法交换数据，因此最大限度的进行缓冲，直到收到 ACK 。左图也就是说一共传递 4 个数据包以传输一个字符串。从右图可以看出，发送数据包一共使用了 10 个数据包。由此可知，不使用 `Nagle` 算法将对网络流量产生负面影响。即使只传输一个字节的数据，其头信息都可能是几十个字节。因此，为了提高网络传输效率，必须使用 `Nagle` 算法。

`Nagle` 算法并不是什么情况下都适用，网络流量未受太大影响时，不使用 `Nagle` 算法要比使用它时传输速度快。最典型的就是「传输大文数据」。将文件数据传入输出缓冲不会花太多时间，因此，不使用 `Nagle` 算法，也会在装满输出缓冲时传输数据包。这不仅不会增加数据包的数量，反而在无需等待 ACK 的前提下连续传输，因此可以大大提高传输速度

> Nagle算法是一种用于减少小数据包发送次数的网络优化算法。它在发送数据时将小数据包合并为较大的数据块，以减少网络通信中的流量和延迟。
>
> Nagle算法的原理是将要发送的小数据包缓存起来，直到接收方确认前一个数据包或缓存的数据达到一定大小后再一起发送。这样可以减少网络通信中的流量，提高网络的利用率。但是，如果数据包的发送间隔时间较长或者数据包大小本身就比较大，使用Nagle算法反而会增加延迟。
>
> 因此，在某些情况下禁用Nagle算法可以提高传输效率。例如，对于实时应用程序（如在线游戏或视频聊天）和对延迟敏感的应用程序，禁用Nagle算法可以减少数据传输的延迟，提高应用程序的响应速度。同时，对于需要高吞吐量的应用程序（如文件传输），禁用Nagle算法可以提高数据传输的速率，减少传输时间。



**禁用 `Nagle` 算法**

禁用 `Nagle` 算法应该使用：

```c++
int opt_val = 1;
setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (void *)&opt_val, sizeof(opt_val));
```

通过 TCP_NODELAY 的值来查看`Nagle` 算法的设置状态。

```c++
opt_len = sizeof(opt_val);
getsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (void *)&opt_val, &opt_len);
```

如果正在使用`Nagle` 算法，那么 opt_val 值为 0，如果禁用则为 1.

关于这个算法，可以参考这个回答：[TCP连接中启用和禁用TCP_NODELAY有什么影响？](https://www.zhihu.com/question/42308970/answer/246334766)

> TCP_NODELAY是TCP协议中的一种机制，用于控制TCP报文的延迟发送，其作用是禁用Nagle算法。Nagle算法是为了优化网络传输的，它会将多个小的数据包合并成一个大的数据包，减少网络传输的开销。但是在某些情况下，这种合并会导致一些延迟。
>
> 启用TCP_NODELAY会禁用Nagle算法，这样数据包就可以立即发送，而不必等待其他小数据包的到达。这种方式可以提高网络传输的实时性，减少延迟，适用于一些需要即时响应的场景，如实时视频和音频传输。
>
> 禁用TCP_NODELAY会启用Nagle算法，这样TCP会将多个小的数据包合并成一个大的数据包，减少网络传输的次数，节省带宽。但是这也会增加数据包的延迟，因为TCP必须等待其他小数据包到达后才能发送。
>
> 因此，是否启用TCP_NODELAY应该根据具体情况而定，需要权衡网络传输的实时性和带宽利用率。





## 第10章 多进程服务器端

### 10.1 进程概念及应用

 **并发服务端的实现方法**

**通过改进服务端，使其同时向所有发起请求的客户端提供服务**，以提高平均满意度。而且，网络程序中数据通信时间比 CPU 运算时间占比更大，因此，向多个客户端提供服务是一种有效的利用 CPU 的方式。接下来讨论同时向多个客户端提供服务的并发服务器端。下面列出的是具有代表性的并发服务端的实现模型和方法：

- **多进程服务器**：通过创建多个进程提供服务
- **多路复用服务器**：通过捆绑并统一管理 I/O 对象提供服务
- **多线程服务器**：通过生成与客户端等量的线程提供服务

先是第一种方法：多进程服务器



 **理解进程**

进程的定义如下：

> **进程是计算机中正在执行的程序的实例，是计算机资源分配的基本单位**。每个进程都有自己的地址空间、代码、数据和打开的文件等信息，它们在操作系统的管理下运行，可以与其他进程并发执行。**进程是操作系统资源管理的基本单位，操作系统通过调度进程的执行顺序和分配资源来实现多任务并发处理，以提高系统的效率和资源利用率。**每个进程都有一个唯一的进程标识符（PID），用于操作系统对其进行管理和控制。

假如你下载了一个游戏到电脑上，此时的游戏不是进程，而是程序。只有当游戏被加载到主内存并进入运行状态，这是才可称为进程。



**进程 ID （Process ID, PID）**

在说进程创建方法之前，先要简要说明进程 ID。无论进程是如何创建的，所有的进程都会被操作系统分配一个 ID。此 ID 被称为「进程ID」，其值为大于 2 的整数。1 要分配给操作系统启动后的（用于协助操作系统）首个进程，因此用户无法得到 ID 值为 1 。接下来观察在 Linux 中运行的进程。

![image-20230328212307289](C:\Users\hp-pc\Desktop\C++\TCPIP网络编程.assets\image-20230328212307289-16800097893273.png)

通过ps指令可以查看当前运行的所有进程。



**通过调用fork函数创建进程**

**fork函数可以用于创建多进程服务端**

```c++
#include <unistd.h>

pid_t fork(void);
```

**`fork()`函数调用时，它将当前进程复制一份，创建一个新的子进程。**

父进程和子进程之间的区别在于它们具有**不同的进程ID**，以及在内存中具有不同的地址空间。

`fork()`函数没有参数，它返回两次：

- 在父进程中返回子进程的进程ID
- 在子进程中返回0

在父进程中，可以通过检查`fork()`的返回值来判断子进程是否成功创建。在子进程中，可以直接执行需要的任务。

此处，「父进程」（Parent Process）指原进程，即调用 fork 函数的主体，而「子进程」（Child Process）是通过父进程调用 fork 函数复制出的进程。接下来是调用 fork 函数后的程序运行流程。如图所示：

![The fork() System Call](C:\Users\hp-pc\Desktop\C++\TCPIP网络编程.assets\fork-4.jpg)

![img](C:\Users\hp-pc\Desktop\C++\TCPIP网络编程.assets\68747470733a2f2f692e6c6f6c692e6e65742f323031392f30312f32302f356334336461353431326239302e706e67.png)

从图中可以看出，父进程调用 fork 函数的同时复制出子进程，并分别得到 fork 函数的返回值。**但复制前，父进程将全局变量 `gval` 增加到 11，将局部变量` lval `的值增加到 25，因此在这种状态下完成进程复制**。复制完成后根据 fork 函数的返回类型区分父子进程。**父进程的 `lval `的值增加 1 ，但这不会影响子进程的` lval `值。同样子进程将 `gval `的值增加 1 也不会影响到父进程的 `gval`** 。因为 fork 函数调用后分成了完全不同的进程，只是二者共享同一段代码而已。接下来给出一个例子：

```c++
#include <iostream>
#include <unistd.h>
using namespace std;

int gval = 10;

int main(int argc, char* argv[]){
    pid_t pid;
    int lval = 20;
    gval++, lval += 5; //在fork子进程之前，gval = 11  lval = 25

    pid = fork();
    if (pid == 0)   //if children process
        gval += 2, lval += 2;
    else
        gval -= 2, lval -= 2;

    if (pid == 0)
        cout << "Child Proc : " << gval << " " << lval << endl;
    else
        cout << "Parent Proc : " << gval << " " << lval << endl;

    return 0;
}
```

输出

```c++
Parent Proc : 9 23
Child Proc : 13 27
```

在这里先执行的是父进程，在执行子进程

> 调用`fork()`函数会创建一个新的子进程，该子进程是父进程的副本。子进程从`fork()`函数返回，而父进程也从`fork()`函数返回，两个进程的执行是**相互独立**的。因此，**执行顺序可能会有所不同**，具体取决于操作系统的调度机制。
>
> 在`fork()`函数返回后，父进程和子进程将同时执行下一条指令，但它们各自拥有独立的地址空间和资源。如果需要在父进程和子进程之间进行通信，则需要使用IPC（进程间通信）机制，例如管道、消息队列、共享内存等等。





### 10.2 进程和僵尸进程

文件操作中，关闭文件和打开文件同等重要。同样，进程销毁和进程创建也同等重要。如果未认真对待进程销毁，他们将变成僵尸进程。



 **僵尸（Zombie）进程**

进程的工作完成后（执行完 main 函数中的程序后）应被销毁，但有时这些进程将变成僵尸进程，占用系统中的重要资源。这种状态下的进程称作「僵尸进程」，这也是给系统带来负担的原因之一。

> **僵尸进程（Zombie process）是指一个已经结束运行但其父进程没有回收它的进程**。当一个进程结束运行后，内核会将其转变成僵尸进程，同时向其父进程发送一个SIGCHLD信号。父进程收到这个信号后应该通过调用wait()或waitpid()等函数来回收已经结束运行的子进程，并释放它占用的系统资源。
>
> 如果父进程没有及时回收子进程，那么这个僵尸进程就会一直存在，占用系统资源，直到系统重启或父进程回收它。因此，程序员在编写代码时应该注意处理子进程结束运行的情况，避免出现僵尸进程。

**维基百科**：

> 在类UNIX系统中，僵尸进程是指完成执行（通过exit系统调用，或运行时发生致命错误或收到终止信号所致）但在操作系统的进程表中仍然有一个表项（进程控制块PCB），处于"终止状态"的进程。这发生于子进程需要保留表项以允许其父进程读取子进程的exit status：一旦退出态通过wait系统调用读取，僵尸进程条目就从进程表中删除，称之为"回收（reaped）"。正常情况下，进程直接被其父进程wait并由系统回收。进程长时间保持僵尸状态一般是错误的并导致资源泄漏。
>
> 英文术语zombie process源自丧尸 — 不死之人，隐喻子进程已死但仍然没有被收割。与正常进程不同，kill命令对僵尸进程无效。孤儿进程不同于僵尸进程，其父进程已经死掉，但孤儿进程仍能正常执行，但并不会变为僵尸进程，因为被init（进程ID号为1）收养并wait其退出。
>
> 子进程死后，系统会发送SIGCHLD 信号给父进程，父进程对其默认处理是忽略。如果想响应这个消息，父进程通常在SIGCHLD 信号事件处理程序中，使用wait系统调用来响应子进程的终止。
>
> 僵尸进程被收割后，其进程号(PID)与在进程表中的表项都可以被系统重用。但如果父进程没有调用wait，僵尸进程将保留进程表中的表项，导致了资源泄漏。某些情况下这反倒是期望的：父进程创建了另外一个子进程，并希望具有不同的进程号。如果父进程通过设置事件处理函数为SIG_IGN显式忽略SIGCHLD信号，而不是隐式默认忽略该信号，或者具有SA_NOCLDWAIT标志，所有子进程的退出状态信息将被抛弃并且直接被系统回收。
>
> UNIX命令ps列出的进程的状态（"STAT"）栏标示为 "Z"则为僵尸进程。[1]
>
> 收割僵尸进程的方法是通过kill命令手工向其父进程发送SIGCHLD信号。如果其父进程仍然拒绝收割僵尸进程，则终止父进程，使得`init`进程收养僵尸进程。`init`进程周期执行wait系统调用收割其收养的所有僵尸进程。



**产生僵尸进程的原因**

> 僵尸进程是指在进程结束后，其父进程没有及时回收子进程的资源，导致子进程的进程描述符仍然存在于系统中，但子进程已经不再运行，从而成为了“僵尸进程”。
>
> **产生僵尸进程的主要原因有以下几个：**
>
> 1. **父进程没有调用wait或waitpid等函数来回收子进程的资源**。这可能是因为父进程没有及时处理子进程的退出状态或者没有正确地调用相关函数。
> 2. **父进程被意外终止或者崩溃，导致其无法回收子进程的资源**。这种情况下，子进程的进程描述符会一直存在于系统中，直到系统重启或者手动干预。
> 3. **子进程在退出时，其退出状态没有被及时处理**。这可能是因为父进程没有正确处理SIGCHLD信号或者没有安装该信号处理程序，导致子进程的退出状态没有被及时处理。
>
> 总之，产生僵尸进程的原因主要是因为父进程没有正确处理子进程的退出状态，这可能是由于程序设计上的缺陷或者程序bug导致的。为了避免出现僵尸进程，我们应该在程序设计中充分考虑子进程的退出状态处理。

为了防止僵尸进程的产生，先解释僵尸进程产生的原因。

**利用如下两个示例展示调用fork()函数产生子进程的终止方式：**

- 传递参数并调用**exit**函数
- main函数中执行**return**语句并返回值

**向 exit 函数传递的参数值和 main 函数的 return 语句返回的值都会传递给操作系统。而操作系统不会销毁子进程，直到把这些值传递给产生该子进程的父进程。处在这种状态下的进程就是僵尸进程。**也就是说将子进程变成僵尸进程的正是操作系统。既然如此，僵尸进程何时被销毁呢？

> 应该向创建子进程的父进程传递子进程的 exit 参数值或 return 语句的返回值。

如何向父进程传递这些值呢？操作系统不会主动把这些值传递给父进程。只有父进程主动发起请求（函数调用）的时候，操作系统才会传递该值。换言之，**如果父进程未主动要求获得子进程结束状态值，操作系统将一直保存，并让子进程长时间处于僵尸进程状态**。也就是说，父母要负责收回自己生的孩子。接下来的示例是创建僵尸进程：

```c++
#include <iostream>
#include <unistd.h>
using namespace std;

int main(int argc, char *argv[]){
    pid_t pid = fork(); //调用fork函数会创建一个新的子进程，子进程和父进程之间是相互独立执行的

    if (pid == 0)
        cout << "Hi, I am a child  process" << endl;
    else{
        //在父进程中休眠30s,延缓程序的结束(父进程结束之后，其子进程也会被释放)
        cout << "Child PID : " << pid << endl;
        sleep(30);	//休眠30秒
    }

    if (pid == 0)
        cout << "End child process" << endl;
    else
        cout << "End parent process" << endl;

    return 0;
}
```

输出：

```c++
Child PID : 30776
Hi, I am a child  process
End  child process
End parent process
```

>  利用ps au来查看正在运行的进程，可以看到有个状态为Z+的僵尸进程。
>
> 利用 `./zombie &`可以使程序在后台运行，不用打开新的命令行窗口。



**销毁僵尸进程1：利用wait函数**

C++中的`wait()`函数通常是指在Unix或Linux环境下用于等待子进程结束并获取其退出状态的系统调用。

`wait()`函数可以用于**阻塞**父进程，直到它的一个子进程退出为止。

**当子进程退出时，`wait()`函数将返回子进程的进程ID，并将子进程的退出状态保存在一个整数变量中。**

`wait()`函数的一般形式如下：

```c++
#include <sys/wait.h>

pid_t wait(int* status);
```

- 其中`pid_t`是一个整数类型，代表子进程的进程ID，
- `status`是一个指向整数变量的指针，**用于存储子进程的退出状态**。

如果`wait()`函数成功，则返回子进程的进程ID；如果失败，则返回-1。



需要注意的是，`wait()`函数可能会阻塞父进程，直到有子进程退出。如果父进程同时启动了多个子进程，并且需要等待它们中的一个退出，可以使用`waitpid()`函数来等待指定的子进程退出。

但函数参数指向的单元中还包含其他信息，因此需要用下列宏进行分离：

- WIFEXITED 子进程正常终止时返回「真」
- WEXITSTATUS 返回子进程时的返回值

```c++
if (WIFEXITED(status)){							//子进程是正常终止的
	cout << "Child pass nums : " << WEXITSTATUS(status);   //输出子进程的返回值
}
```

示例

![fork() to execute processes from bottom to up using wait() - GeeksforGeeks](C:\Users\hp-pc\Desktop\C++\TCPIP网络编程.assets\fork-and-wait.png)

```c++
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main(int argc, char *argv[]){
    int status;

    pid_t pid = fork();

    if (pid == 0){
        return 3;   //如果是子进程直接返回3
    }else{
        cout << "Child PID : " << pid << endl;
        pid = fork();   //父进程创建第二个子进程

        if (pid == 0){
            exit(7);
        }else{
            cout << "Child PID : " << pid << endl;
            wait(&status);  //阻塞直到有一个子进程终止
            if (WIFEXITED(status))    //子进程正常返回时，打印子进程的返回值
                cout << "Child send one : " << WEXITSTATUS(status) << endl;

            wait(&status);
            if (WIFEXITED(status))
                cout << "Child send two : " << WEXITSTATUS(status) << endl;

            sleep(30);
        }
    }
    
    return 0;
}
```

输出

```c++
Child PID : 5140
Child PID : 5141
Child send one : 3
Child send two : 7
```

此时，系统中并没有上述 PID 对应的进程，**这是因为调用了 wait 函数，完全销毁了该子进程**。另外两个子进程返回时返回的 3 和 7 传递到了父进程。

这就是通过 wait 函数消灭僵尸进程的方法，调用 wait 函数时，如果没有已经终止的子进程，那么程序将**阻塞（Blocking）**直到有子进程终止，因此要谨慎调用该函数。



**销毁僵尸进程2：使用waitpid函数**

wait函数会引起程序阻塞，还可以考虑调用waitpid函数。这是防止产生僵尸进程的第二种方法，也是防止阻塞的方法

```c++
#include <sys/wait.h>

pid_t waitpid(pid_t pid, int *statloc, int options);
```

其中，`pid` 参数指定要等待的子进程的 ID。如果 `pid` 是-1，则与wait函数相同，可以等待任意子进程终止。如果 `pid` 是 0，则表示等待与调用进程在同一进程组的任何子进程。如果 `pid` 是正数，则表示等待进程 ID 等于 `pid` 的子进程。

- `statloc` 参数是一个指向整数的指针，用于存储子进程的终止状态。

- ` options` 参数是一个位掩码，用于指定其他选项。可以使用以下常量之一或它们的组合：

  - `WNOHANG`：**即使没有终止的子进程也不会进入阻塞状态**，而是返回0并退出函数。

  - `WUNTRACED`：如果子进程已经暂停而不是终止，则也返回。

`waitpid()` 函数的返回值为终止子进程的 ID（或0），如果出现错误，则返回 -1。

```c++
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main(int argc, char* argv[]){
    int status;

    pid_t pid = fork();

    if (pid == 0){
        sleep(15);
        return 24;
    }else{
        while (!waitpid(-1, &status, WNOHANG)){
            sleep(3);
            cout << "Sleep 3 sec" << endl;
        }
        
        if (WIFEXITED(status))
            cout << "Child send " << WEXITSTATUS(status) << endl;
    }

    return 0;
}
```

输出

```c++
Sleep 3 sec
Sleep 3 sec
Sleep 3 sec
Sleep 3 sec
Sleep 3 sec
Child send 24
```

将上述waitpid函数更改为wait

```c++
while (wait(&status) == 0){	//在子进程终止前，将会一直阻塞在这一行
    sleep(3);
    cout << "Sleep 3 sec" << endl;
}
```

输出：

```c++
Child send 24
```

程序阻塞在wait函数，等待子进程终止。当子进程终止时，返回自己的PID，不满足while语句的条件，所以并不会执行while内的循环语句。





### 10.3 信号处理

我们已经知道了进程的创建及销毁的办法，但是还有一个问题没有解决。

> 子进程究竟何时终止？调用 waitpid 函数后要无休止的等待吗？



**向操作系统求助**

子进程终止的识别主体是操作系统，因此，若操作系统能把子进程结束的信息告诉正忙于工作的父进程，将有助于构建更高效的程序

为了实现上述的功能，引入**信号处理机制（Signal Handing）**。**此处「信号」是在特定事件发生时由操作系统向进程发送的消息。另外，为了响应该消息，执行与消息相关的自定义操作的过程被称为「处理」或「信号处理」。**



**信号与 signal 函数**

下面进程和操作系统的对话可以帮助理解信号处理。

> 进程：操作系统，如果我之前创建的子进程终止，就帮我调用 zombie_handler 函数。
>
> 操作系统：好的，如果你的子进程终止，我就帮你调用 zombie_handler 函数，你先把函数要执行的语句写好。

上述的对话，相当于「注册信号」的过程。即进程发现自己的子进程结束时，请求操作系统调用的特定函数。该请求可以通过如下函数调用完成：

[指针函数和函数指针](C:\Users\hp-pc\Documents\Notes\C++\指针带来的弹性.md)

```c++
#include <signal.h>

void (*signal(int signo, void (*func)(int))) (int);
```

- 函数名signal
- 参数`signo`，`void (*fun)(int)`
- 返回值类型，参数类型为int，返回void型函数指针

调用上述函数时，第一个参数为特殊情况信息，第二个参数为特殊情况下将要调用的函数的地址值（指针）。**发生第一个参数代表的情况时，调用第二个参数所指的函数。**下面给出可以在 signal 函数中注册的部分特殊情况和对应的函数。

- SIGALRM：已到通过调用 alarm 函数注册时间
- SIGINT：输入 ctrl+c
- SIGCHLD：子进程终止

接下来编写调用 signal 函数的语句完成如下请求：

> 「子进程终止则调用 mychild 函数」

此时 mychild 函数的参数应为 int ，返回值类型应为 void 。只有这样才能成为 signal 函数的第二个参数。另外，常数 SIGCHLD 定义了子进程终止的情况，应成为 signal 函数的第一个参数。也就是说，signal 函数调用语句如下：

```c++
signal(SIGCHLD, mychild);
```

接下来编写 signal 函数的调用语句，分别完成如下两个请求：

> 1. 已到通过 alarm 函数注册时间，请调用 timeout 函数
> 2. 输入 ctrl+c 时调用 keycontrol 函数

代表这 2 种情况的常数分别为 SIGALRM 和 SIGINT ，因此按如下方式调用 signal 函数。

```c++
signal(SIGALRM, timeout);
signal(SIGINT, keycontrol);
```

以上就是信号注册过程。注册好信号之后，发生注册信号时（注册的情况发生时），操作系统将调用该信号对应的函数。

先介绍 alarm 函数。

```c++
#include <unistd.h>

unsigned int alarm(unsigned int seconds);
// 返回0或以秒为单位的距 SIGALRM 信号发生所剩时间
```

如果调用该函数的同时向它传递一个正整型参数，相应时间后（以秒为单位）将产生 SIGALRM 信号。若向该函数传递为 0 ，则之前对 SIGALRM 信号的预约将取消。如果通过改函数预约信号后未指定该信号对应的处理函数，则（通过调用 signal 函数）终止进程，不做任何处理。

```c++
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

void timeout(int sig){
    if (sig == SIGALRM){
        cout << "Time out!" << endl;
    }
    alarm(2);   //每隔2s产生一个SIGALRM信号
}

void keycontrol(int sig){
    if (sig == SIGINT)
        cout << "CTRL + C pressed" << endl;
}

int main(int argc, char* argv[]){
    signal(SIGALRM, timeout);
    signal(SIGINT, keycontrol);

    alarm(2);	//预约2s之后产生一个SIGALRM信号

    for (int i = 0; i < 3; i++){	//为了查看信号产生和信号处理器的执行，每次提供100秒等待时间
        cout << "wait ..." << endl;
        sleep(100);
    }

    return 0;
}
```

输出：

```c++
wait ...
Time out!
wait ...
Time out!
wait ...
Time out!
```

上述程序在不到10s就执行完毕，如果输入CTRL + C

```c++
wait ...
CTRL + C pressed
wait ...
Time out!
wait ...
Time out!
```



> **发生信号时将唤醒由于调用sleep函数而进入阻塞状态的进程**

调用函数的主体的确是操作系统，但是进程处于睡眠状态时无法调用函数，因此，产生信号时，为了调用信号处理器，将唤醒由于调用 sleep 函数而进入阻塞状态的进程。而且，**进程一旦被唤醒，就不会再进入睡眠状态。即使还未到 sleep 中规定的时间也是如此**。所以上述示例运行不到 10 秒后就会结束，连续输入 CTRL+C 可能连一秒都不到。

**简言之，就是本来系统要睡眠100秒，但是到了 alarm(2) 规定的两秒之后，就会唤醒睡眠的进程，进程被唤醒了就不会再进入睡眠状态了，所以就不用等待100秒。如果把 timeout() 函数中的 alarm(2) 注释掉，就会先输出`wait...`，然后再输出`Time out!` (这时已经跳过了第一次的 sleep(100) 秒),然后就真的会睡眠100秒，因为没有再发出 alarm(2) 的信号。**



**利用sigaction函数进行信号处理！！！** 

前面所学的内容可以防止僵尸进程，还有一个函数，叫做 sigaction 函数，他类似于 signal 函数，而且可以完全代替后者，也更稳定。之所以稳定，是因为：

> signal 函数在 Unix 系列的不同操作系统可能存在区别，但 sigaction 函数完全相同

实际上现在很少用 signal 函数编写程序，他只是为了保持对旧程序的兼容，下面介绍 sigaction 函数，只讲解可以替换 signal 函数的功能。

```c++
#include <signal.h>

int sigaction(int signo, const struct sigaction* act, struct sigaction old act);
```

- signo和signal中的函数一样，代表特殊情况
- 对应于第一个参数的信号处理函数（信号处理器）信息
- 用过此参数获取之前的信号处理函数指针，若不需要则传递0

上述sigaction结构体的定义，位于signal.h头文件中

```c++
struct sigaction{
	void (*sa_handler) (int);	//保存信号处理函数的指针
	sigset_t sa_mask;		    //sa_mask和sa_flags用于指定信号相关的选项和特性
	int sa_flags;
}
```

和signal中的代码逻辑一样，只不过使用sigaction函数

```c++
#include <iostream>
#include <signal.h>
#include <unistd.h>
using namespace std;

void timeout(int sig){
    if (sig == SIGALRM)
        cout << "Time out !" << endl;
    alarm(2);
}

int main(int argc, char *argv[]){
    struct sigaction act;
    act.sa_handler = timeout;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    sigaction(SIGALRM, &act, 0);
    alarm(2);

    for (int i = 0; i < 3; i++){
        cout << "wait ..." << endl;
        sleep(100);
    }

    return 0;
}
```



**利用信号处理技术消灭僵尸进程**

子进程终止时将产生SIGCHLD信号

```c++
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
using namespace std;

void read_childproc(int sig){	//当产生sig信号时调用read_childproc函数
    int status;
    pid_t id = waitpid(-1, &status, WNOHANG);   
    //等待任意子进程的终止，如果没有终止的子进程也不会进入阻塞状态，成功时返回子进程的ID或0
    if (WIFEXITED(status)){
        cout << "Remove proc id " << id << endl;
        cout << "Child send " << WEXITSTATUS(status) << endl;
    }
}

int main(int argc, char *argv[]){
    struct sigaction act;
    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);		//传入的是地址
    act.sa_flags = 0;
    sigaction(SIGCHLD, &act, 0);    //注册SIGCHLD信号对应的处理器

    pid_t pid = fork();
    if (pid == 0){      //子进程
        cout << "Hi, I'm a child process" << endl;
        sleep(10);
        return 12;
    }else{              //父进程
        cout << "Child proc id " << pid << endl;
        pid = fork();  //创建第二个子进程
        if (pid == 0){  
            cout << "Hi, I'm a child process" << endl;
            sleep(10);
            exit(24);
        }else{
            cout << "Child proc id " << pid << endl;
            for (int i = 0; i < 5; i++){	
            //父进程暂停5次，每次休眠5s，当子进程结束时发送SIGCHLD信号，所以实际上父进程中的sleep会被唤醒2次
                cout << "wait ..." << endl;
                sleep(5);
            }
        }
    }

    return 0;
}
```

 输出：

```c++
Child proc id 2766
Hi, I'm a child process
Child proc id 2767
wait ...
Hi, I'm a child process
wait ...
Remove proc id 2766		//第一个子进程结束
Child send 12
Remove proc id 2767		//第二个子进程技术
Child send 24
wait ...
wait ...
wait ...
```

同样，在父进程中的sleep函数会在子进程结束时唤醒，不会休眠5s																																												



### 10.4 基于多任务的并发服务器

**基于进程的并发服务器模型**

之前的回声服务器每次只能同时向 1 个客户端提供服务。因此，需要扩展回声服务器，使其可以同时向多个客户端提供服务。下图是基于多进程的回声服务器的模型。

![img](C:\Users\hp-pc\Desktop\C++\TCPIP网络编程.assets\68747470733a2f2f692e6c6f6c692e6e65742f323031392f30312f32312f356334353336363463646532362e706e67.png)

从图中可以看出，每当有客户端请求时（连接请求），回声服务器都创建子进程以提供服务。如果请求的客户端有 5 个，则将创建 5 个子进程来提供服务，为了完成这些任务，需要经过如下过程：

- 第一阶段：回声服务器端（父进程）通过调用 accept 函数受理连接请求
- 第二阶段：此时获取的**套接字文件描述符**创建并传递给子进程
- 第三阶段：进程利用传递来的文件描述符提供服务



**实现并发服务器**

下面是基于多进程实现的并发的回声服务器的服务端，可以结合第四章的 [echo_client.cpp]回声客户端来运行。

```c++
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/wait.h>
using namespace std;

#define BUF_SIZE 32

void read_childproc(int sig){		//在子进程结束时调用的处理函数，用来输出结束的子进程的PID和返回值
    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG);
    if (WIFEXITED(status)){
        cout << "Remove proc id : " << pid << endl;
        cout << "Child send : " << WEXITSTATUS(status) << endl;
    }
}

int main(int argc, char* argv[]){
    //创建服务端的代码:创建套接字、套接字绑定、监听、接收连接
    if (argc != 2){
        cout << "Usage : <port>" << endl;
        return -1;
    }

    int serv_sock, clnt_sock, str_len;
    sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_size;
    char buf[BUF_SIZE];

    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1){
        cout << "Server socke create error" << endl;
        return -1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        cout << "Server socke bind error" << endl;
        return -1;
    }

    if (listen(serv_sock, 5) == -1){
        cout << "Server socke listen error" << endl;
        return -1;
    }

    while (1){
        clnt_size = sizeof(clnt_addr);
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_size);
        if (clnt_sock == -1){
            cout << "Client socke create error" << endl;
            continue;;
        }else
            cout << "New client connnected" << endl;

        //通过fork函数来创建子进程为多个客户端提供服务
        pid_t pid = fork();
        if (pid == -1){     //子进程创建失败
            close(clnt_sock);
            continue;
        }

        if (pid == 0){     //利用创建的子进程来向客户端提供服务，将从客户端收到的信息发送回去
            close(serv_sock);   //由于创建的子进程和父进程共享同一份代码和数据，所以在子进程中也会创建一个客户端
            write(clnt_sock, "Server send", sizeof("Server send"));//为了表明数据是从服务端发送过去，而不是客户端读取自己的信息
            while ((str_len = read(clnt_sock, buf, BUF_SIZE)) != 0){
                write(clnt_sock, buf, str_len);
            }
            close(clnt_sock);   //关闭客户端
            cout << "Client disconnected" << endl;
            return 0;
        }else{
            close(clnt_sock);	//客户端在子进程和父进程中都要关闭
        }
    }
    
    close(serv_sock);
    return 0;
}
```

和第四章的几乎一样，此时的服务端支持同时给多个客户端进行服务，每有一个客户端连接服务端，就会多开一个子进程，所以可以同时提供服务。



**通过fork函数复制文件描述符**

示例中给出了通过 fork 函数复制文件描述符的过程。父进程将 2 个套接字（一个是服务端套接字另一个是客户端套接字）文件描述符复制给了子进程。

**调用 fork 函数时赋值父进程的所有资源，但是套接字不是归进程所有的，而是归操作系统所有，只是进程拥有代表相应套接字的文件描述符。**通过fork函数复制文件描述符

![img](C:\Users\hp-pc\Desktop\C++\TCPIP网络编程.assets\68747470733a2f2f73322e617831782e636f6d2f323031392f30312f32312f6b5037526a782e706e67.png)

如图所示，**1 个套接字存在 2 个文件描述符时，只有 2 个文件描述符都终止（销毁）后，才能销毁套接字**。如果维持图中的状态，即使子进程销毁了与客户端连接的套接字文件描述符，也无法销毁套接字（服务器套接                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      字同样如此）。因此调用 fork 函数后，要将无关紧要的套接字文件描述符关掉，如图所示：

![img](C:\Users\hp-pc\Desktop\C++\TCPIP网络编程.assets\68747470733a2f2f73322e617831782e636f6d2f323031392f30312f32312f6b5048375a542e706e67.png)





### 10.5 分割TCP的I/O程序

我们已经实现的回声客户端的数据回声方式如下：

> ```c++
> write(clnt_sock, buf, strlen(buf));			//先向客户端中写数据，供服务端读取
> str_len = read(clnt_sock, buf, BUF_SIZE-1); //在服务端中读取数据，并将数据发送回给客户端
> buf[str_len] = 0;
> cout << buf << endl;
> ```
>
> 在默认情况下，read函数在C++中是**阻塞**的，它会一直等待数据从文件描述符（这里是客户端套接字`clnt_sock`）中可用并读取数据，直到读取到指定的字节数（这里是BUF_SIZE-1）或者发生错误（例如连接关闭或超时）。在这个过程中，程序会一直停留在这个阻塞调用处，直到操作系统内核通知可读事件发生。
>
> 
>
> 向服务器传输数据，并等待服务器端回复。无条件等待，直到接收完服务器端的回声数据后，才能传输下一批数据。

传输数据后要等待服务器端返回的数据，因为程序代码中重复调用了 read 和 write 函数。只能这么写的原因之一是，程序在 1 个进程中运行，现在可以创建多个进程，因此可以分割数据收发过程。默认分割过程如下图所示：

![img](C:\Users\hp-pc\Desktop\C++\TCPIP网络编程.assets\68747470733a2f2f73322e617831782e636f6d2f323031392f30312f32312f6b5062686b442e706e67.png)



从图中可以看出，客户端的父进程负责接收数据，额外创建的子进程负责发送数据，**分割后，不同进程分别负责输入输出，这样，无论客户端是否从服务器端接收完数据都可以进程传输**。

分割 I/O 程序的另外一个好处是，**可以提高频繁交换数据的程序性能**，如下图所示：

![img](C:\Users\hp-pc\Desktop\C++\68747470733a2f2f73322e617831782e636f6d2f323031392f30312f32312f6b50627674672e706e67.png)

根据上图显示可以看出，在网络不好的情况下，明显提升速度。





**回声客户端的 I/O 程序分割**

下面是回声客户端的 I/O 分割的代码实现：

```c++
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
using namespace std;

#define BUF_SIZE 1024

void read_routine(int sock, char *buf){		//分割的read函数
    while (1){
        int str_len = read(sock, buf, BUF_SIZE-1);
        if (str_len == 0)   return ;
        buf[str_len] = 0;
        cout << "Message from server : " << buf << endl;
    }
}

void write_routine(int sock, char *buf){	//分割的write函数，从输入中读取数据写到sock套接字中
    while (1){
        memset(buf, 0, sizeof(buf));
        cin.getline(buf, BUF_SIZE-1);
        if (!strcmp(buf, "q\n") || !strcmp(buf, "Q\n")){
            shutdown(sock, SHUT_WR);		//关闭套接字输出方向的写入流
            return ;
        }
        write(sock, buf, strlen(buf));
    }
}

int main(int argc, char* argv[]){
    //客户端:创建套接字、和服务端建立连接
    if (argc != 3){
        cout << "Usage : <IP> <address>" << endl;
        return -1;
    }

    int clnt_sock;
    struct sockaddr_in serv_addr;
    socklen_t serv_size;

    clnt_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (clnt_sock == -1){
        cout << "Client create socket error" << endl;
        return -1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(clnt_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        cout << "Client bind socket error" << endl;
        return -1;
    }

   	//创建子进程来分割I/O程序
    pid_t pid = fork();
    char buf[BUF_SIZE];

    if (pid == 0){
        write_routine(clnt_sock, buf);
    }else{
        read_routine(clnt_sock, buf);
    }

    close(clnt_sock);
    return 0;
}
```

配合刚才的并发服务器进行执行。





### 10.6 习题

1. **下列关于进程的说法错误的是？**

   答：以下加粗的内容为正确的

   1. **从操作系统的角度上说，进程是程序运行的单位**

   2. 进程根据创建方式建立父子关系

   3. **进程可以包含其他进程，即一个进程的内存空间可以包含其他进程**

   4. **子进程可以创建其他子进程，而创建出来的子进程还可以创建其他子进程，但所有这些进程只与一个父进程建立父子关系。**

      

2. **调用 fork 函数将创建子进程，一下关于子进程错误的是？**

   答：以下加粗的内容为正确的

   1. **父进程销毁时也会同时销毁子进程**

   2. **子进程是复制父进程所有资源创建出的进程**

   3. 父子进程共享全局变量

   4. 通过 fork 函数创建的子进程将执行从开始到 fork 函数调用为止的代码。

      

3. **创建子进程时复制父进程所有内容，此时复制对象也包含套接字文件描述符。编写程序验证赋值的文件描述符整数值是否与原文件描述符数值相同。**

   

4. **请说明进程变为僵尸进程的过程以及预防措施。**

   答：

   **进程变为僵尸进程的过程：**

   当一个子进程结束时，其父进程需要调用 `wait()` 或 `waitpid()` 等系统调用来获取子进程的退出状态，以确保子进程的资源得到释放。如果父进程没有对子进程进行处理（即没有调用上述系统调用），子进程会被操作系统保留在进程表中，并处于僵尸状态，此时它已经无法执行任何操作，但它的 PID 和退出状态信息仍然被保留在系统中，占用系统资源。

   

   **预防措施：**
   
   1. 父进程调用 `wait()` 或 `waitpid()` 系统调用来获取子进程的退出状态，释放子进程的资源。
   2. 父进程可以忽略子进程的退出状态，但是需要调用 `signal()` 系统调用来忽略 `SIGCHLD` 信号，否则当子进程结束时，父进程将被中断，这可能会对父进程的正常运行产生影响。
   3. 父进程可以使用 `signal()` 系统调用来注册 `SIGCHLD` 信号处理函数，以异步地获取子进程的退出状态，从而及时释放子进程的资源。
   4. 父进程在 fork() 时可以设置 `SA_NOCLDWAIT` 标志，使得子进程结束时不产生僵尸进程，而是直接释放资源。但是这种方式并不常用，因为在一些情况下需要获取子进程的退出状态，比如判断子进程是否正常退出或者了解子进程执行的结果等。
   
   需要注意的是，如果一个子进程被创建出来，但是父进程在子进程结束前已经退出，那么这个子进程就会成为**孤儿进程**，其父进程 ID 会被置为 1（即 `init` 进程）。在这种情况下，孤儿进程结束时并不会产生僵尸进程，因为 `init` 进程会负责处理孤儿进程的退出状态。







## 第11章 进程间通信

进程间通信，意味着两个不同的进程中可以交换数据

### 11.1 进程间通信的基本概念

 **通过管道实现进程间通信**

下图是基于管道（PIPE）的进程间通信的模型：

![img](TCPIP网络编程.assets/68747470733a2f2f73322e617831782e636f6d2f323031392f30312f32322f6b466c6b30732e706e67.png)

可以看出，为了完成进程间通信，需要创建进程。管道并非属于进程的资源，而是和套接字一样，属于操作系统（也就不是 fork 函数的复制对象）。所以，两个进程通过操作系统提供的内存空间进行通信。下面是创建管道的函数。

```c++
#include <unistd.h>
int pipe(int filedes[2]);
```

成功时返回 0 ，失败时返回 -1

- `filedes[0]`: 通过管道接收数据时使用的文件描述符，即管道**出口**
- `filedes[1]`: 通过管道传输数据时使用的文件描述符，即管道**入口**

> 在 C++ 中，`int pipe(int filedes[2])` 是一个系统调用（system call）函数，用于创建一个无名管道（unnamed pipe），用于在进程之间进行进程间通信（IPC，Inter-Process Communication）。
>
> **函数的参数 `filedes` 是一个整型数组，长度为 2，用于返回两个文件描述符（file descriptor）。`filedes[0]` 是管道的读取端（用于从管道中读取数据），`filedes[1]` 是管道的写入端（用于向管道中写入数据）。**
>
> 管道是一种特殊的文件，可以用于在同一台计算机上的不同进程之间传递数据。一个进程将数据写入管道的写入端，另一个进程从管道的读取端读取数据。这样，两个进程可以通过管道进行通信。

父进程调用函数时将创建管道，同时获取对应于出入口的文件描述符，此时父进程可以读写同一管道。但父进程的目的是与子进程进行数据交换，因此需要将入口或出口中的 1 个文件描述符传递给子进程。下面的例子是关于该函数的使用方法：

```c++
#include <iostream>
#include <cstring>
#include <unistd.h>
using namespace std;

#define BUF_SIZE 1024

int main(int argc, char *argv[]){
    int fds[2];
    char buf[BUF_SIZE];
    char str[BUF_SIZE];

    pipe(fds);          //建立管道
    pid_t pid = fork();

    if (pid == 0){      //子进程管道中的数据写到fds[1]
        cout << "Trasmission data : ";
        cin.getline(str, BUF_SIZE);
        write(fds[1], str, strlen(str));
    }else{             //在父进程从fds[0]中读取管道传输过来的数据
        int str_len = read(fds[0], buf, BUF_SIZE-1);
        buf[str_len] = 0;
        cout << "Receive data by pipe : " << buf << endl;
    }

    return 0;
}
```

<img src="TCPIP网络编程.assets/image-20230403110736999.png" alt="image-20230403110736999" style="zoom:67%;" />

可以从程序中看出，首先创建了一个管道，子进程通过 fds[1] 把数据写入管道，父进程从 fds[0] 再把数据读出来。可以从下图看出：

![img](TCPIP网络编程.assets/68747470733a2f2f73322e617831782e636f6d2f323031392f30312f32322f6b46384137642e706e67.png)

> 如果将上述代码修改为下面的状态，那么会发生什么呢？
>
> ```c++
> write(fds[0], str, strlen(str));
> int str_len = read(fds[1], buf, BUF_SIZE-1);
> ```
>
> 对于父进程来说，直接从管道的入口处`fds[1]`读取数据，read函数会返回-1（出错）





**通过管道进行进程间双向通信**

下图可以看出双向通信模型：

![img](TCPIP网络编程.assets/68747470733a2f2f73322e617831782e636f6d2f323031392f30312f32322f6b46383444652e706e67.png)

<img src="TCPIP网络编程.assets/sharing-pipe.jpg" alt="pipe() System call - GeeksforGeeks" style="zoom:67%;" />

下面是双向通信的示例：

```c++
#include <iostream>
#include <cstring>
#include <unistd.h>
using namespace std;

#define BUF_SIZE 1024

int main(int argc, char *argv[]){
    int fds[2];
    char buf[BUF_SIZE];
    char str1[] = "Who are you", str2[] = "Tank you for your message";

    pipe(fds);          //建立管道
    pid_t pid = fork();

    if (pid == 0){      //子进程管道中的数据写到fds[1]，再从fds[0]中读取父进程从管道传输过来的数据
        write(fds[1], str1, strlen(str1));

        sleep(2);
        
        memset(&buf, 0, sizeof(buf));
        read(fds[0], buf, BUF_SIZE);
        cout << "Child proc output : " << buf << endl;
    }else{             //在父进程从fds[0]中读取管道传输过来的数据，再利用管道将父进程的数据写到管道
        int str_len = read(fds[0], buf, BUF_SIZE-1);
        buf[str_len] = 0;
        cout << "Parent proc output : " << buf << endl;

        write(fds[1], str2, strlen(str2));
        sleep(3);
    }

    return 0;
}
```

如果将子进程中的sleep(2)注释掉，再将代码编译运行，对应的输出：

```c++
Child proc output : Who are you
//由于父进程没有在read中读取到数据，所以会一直阻塞
```

因为数据进入管道后变成了无主数据。也就是**通过 read 函数先读取数据的进程将得到数据**，即使该进程将数据传到了管道。因为，注释第18行会产生问题。第19行，自己成将读回自己在第 17 行向管道发送的数据。结果父进程调用 read 函数后，无限期等待数据进入管道。

当一个管道不满足需求时，就需要创建两个管道，各自负责不同的数据流动，过程如下图所示：

<img src="TCPIP网络编程.assets/68747470733a2f2f73322e617831782e636f6d2f323031392f30312f32322f6b464a5730652e706e67.png" alt="img" style="zoom: 80%;" />

```c++
#include <iostream>
#include <cstring>
#include <unistd.h>
using namespace std;
#define BUF_SIZE 1024

int main(int argc, char *argv[]){
    int fds1[2], fds2[2];
    char buf[BUF_SIZE];
    char str[BUF_SIZE];

    pipe(fds1), pipe(fds2);          //建立管道
    pid_t pid = fork();

    if (pid == 0){      //子进程利用fds1管道来写数据，fds2管道来接收数据
        cout << "Trasmission data by child proc : ";
        cin.getline(str, BUF_SIZE);
        write(fds1[1], str, strlen(str));

        memset(&buf, 0, sizeof(buf));
        read(fds2[0], buf, BUF_SIZE);
        cout << "Child proc output : " << buf << endl;
    }else{             //父进程利用fds1管道来接受数据，fds2管道来写数据
        int str_len = read(fds1[0], buf, BUF_SIZE-1);
        buf[str_len] = 0;
        cout << "Parent proc output : " << buf << endl;

        cout << "Trasmission data by parent proc : ";
        cin.getline(str, BUF_SIZE);
        write(fds2[1], str, strlen(str));
    }

    return 0;
}
```

输出

```c++
Trasmission data by child proc : what are you doning parent 
Parent proc output : what are you doning parent
Trasmission data by parent proc : waiting for you, my son
Child proc output : waiting for you, my son
```





### 10.2 运用进程间通信

**保存消息的回声服务器**

下面对第 10 章的 [echo_mpserv.cpp]进行改进，添加一个功能：

> 将回声客户端传输的字符串按序保存到文件中

实现该任务将创建一个新进程，从向客户端提供服务的进程读取字符串信息，下面是代码：

```c++
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/wait.h>
using namespace std;

#define BUF_SIZE 32

void read_childproc(int sig){   //用来打印结束的子进程PID和返回值
    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG);
    if (WIFEXITED(status)){
        cout << "Chile PID : " << pid << endl;
        cout << "Child proc send " << WEXITSTATUS(status) << endl;
    }
}

int main(int argc, char* argv[]){
    if (argc != 2){
        cout << "Usage : <IP>";
        return -1;
    }

    int serv_sock, clnt_sock, fds[2], str_len;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_size;
    char buf[BUF_SIZE], msg[BUF_SIZE];

    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1){
        cout << "Server create socket error" << endl;
        return -1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    if (bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1){
        cout << "Server bind socker error" << endl;
        return -1;
    }

    if (listen(serv_sock, 5) == -1){
        cout << "Server listen socker error" << endl;
        return -1;
    }

    //注册信号处理函数
    struct sigaction act;
    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGCHLD, &act, 0);

    //利用管道进行通信
    pipe(fds);
    pid_t pid = fork();
    if (pid == 0){  //第一个子进程用来将管道中读取到的信息保存到文件中
        FILE *fp = fopen("echomsg.txt", "wt");
        for (int i = 0; i < 3; i++){
            str_len = read(fds[0], msg, BUF_SIZE);
            fwrite(buf, 1, str_len, fp);    //被写入的数组指针，被写入元素的大小，写入元素的个数，文件指针
        }
        fclose(fp);
        return 0;
    } 

    while (1){
        //和服务端建立连接
        clnt_size = sizeof(clnt_addr);
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_size);
        if (clnt_sock == -1){
            cout << "Client accept error" << endl;
            continue;
        }else
            cout << "Connected success" << endl;

        //创建第二个子进程，从客户端中读取数据并将数据写到客户端和管道
        pid = fork();
        if (pid == 0){
            close(serv_sock);
            while ((str_len = read(clnt_sock, buf, BUF_SIZE)) != 0){
                write(clnt_sock, buf, str_len);
                write(fds[1], buf, str_len);
            }
            close(clnt_sock);
            cout << "Client disconnected..." << endl;
            return 0;
        }else
            close(clnt_sock);
    }

    close(serv_sock);
    return 0;
}
```



### 11.3 习题

1. **什么是进程间通信？分别从概念和内存的角度进行说明。**

   答：进程间通信是指在多进程系统中，进程之间传递数据或共享资源的过程。多个进程之间的通信可以通过操作系统提供的通信机制来实现，常见的通信方式包括**管道、消息队列、共享内存和信号量**等。

   **从概念上来说，进程间通信就是多个进程之间进行交互的过程。进程可以通过发送消息或数据来与其他进程进行通信，从而实现协同工作和资源共享等功能。**

   从内存的角度来看，进程间通信是指不同进程之间共享内存区域的过程。操作系统为每个进程分配了独立的内存空间，**不同进程之间的内存空间是相互独立的**。为了实现进程间通信，操作系统提供了一些机制来共享内存区域，使得不同进程之间可以访问同一块内存区域。比如，共享内存就是一种允许多个进程共享同一块内存的机制，多个进程可以访问同一块共享内存区域，从而实现数据共享和通信的功能。但是，共享内存需要进行锁定和同步操作，以避免不同进程同时对同一块内存区域进行读写而导致的冲突。

   

2. **进程间通信需要特殊的 IPC 机制，这是由于操作系统提供的。进程间通信时为何需要操作系统的帮助？❤**

   答：进程间通信需要操作系统的帮助，主要有以下几个原因：

   1. **进程间内存隔离**：操作系统为每个进程分配独立的内存空间，使得进程之间的内存空间是相互独立的。这样可以避免不同进程之间的内存冲突，提高系统的稳定性和安全性。但是这也就导致了**进程间无法直接共享内存，需要使用操作系统提供的 IPC 机制来实现进程间通信**。
   2. **进程调度和同步**：多个进程同时运行时，**操作系统需要对这些进程进行调度**，以保证它们之间的相对顺序和优先级。此外，**不同进程之间的通信需要进行同步和互斥操作，以避免数据冲突和竞争条件。这些都需要操作系统提供支持和帮助。**
   3. **网络通信和设备管理**：进程间通信不仅可以发生在同一台计算机上，也可以发生在不同的计算机之间，这就需要使用网络通信来实现进程间通信。同时，不同进程可能需要访问共享设备，比如打印机、硬盘等，这也需要操作系统提供支持和帮助。

   综上所述，进程间通信需要操作系统提供支持

   

3. **「管道」是 典型的 IPC 技法。关于管道，请回答以下问题：**

   1. **管道是进程间交换数据的路径。如何创建此路径？由谁创建？**

      答：使用 pipe 函数进行创建，由操作系统创建。父进程调用该函数时将创建管道。

   2. **为了完成进程间通信。2 个进程要同时连接管道。那2 个进程如何连接到同一管道？**

      答：数组中有两个文件描述符，父子进程调用相关函数时，通过 fork 函数，把 1 个文件描述符传递给子进程。

   3. **管道允许 2 个进程间的双向通信。双向通信中需要注意哪些内容？**

      答：向管道传输数据时，先读的进程会把数据取走。简言之，就是数据进入管道候会变成无主数据，所以有时候为了防止错误，需要多个管道来进程通信。





## 第12章 I/O复用

### 12.1 基于I/O服用的服务端

 **多进程服务端的缺点和解决方法**

> 多进程服务端的**缺点**包括：
>
> 1. 内存占用：每个进程都需要占用一定的内存，当进程数量增加时，系统的总内存占用会增加，这可能会导致系统出现内存不足的情况。
> 2. 上下文切换：当进程数量增加时，进程之间的切换也会增加。这可能会导致上下文切换开销增加，从而降低系统性能。
> 3. 稳定性：多进程服务端可能会存在进程崩溃的情况，这可能会导致整个服务不可用，需要对进程崩溃进行监控和重启。
>
> **解决方法：**
>
> 1. 使用**线程池**代替多进程：线程池可以避免每次请求都需要创建一个新的进程的开销，同时也可以限制线程的数量，从而避免内存占用过多和上下文切换的问题。
> 2. 使用**进程池**代替多进程：进程池可以避免每次请求都需要创建一个新的进程的开销，同时也可以限制进程的数量，从而避免内存占用过多和上下文切换的问题。
> 3. 使用**异步IO**代替多进程：异步IO可以避免每个请求都需要创建一个新的进程或线程的开销，同时可以避免上下文切换的问题，从而提高系统性能。
> 4. 对进程崩溃进行监控和重启：使用工具对进程进行监控，并在进程崩溃时进行重启，从而保证服务的稳定性。

为了构建并发服务器，只要有客户端连接请求就会创建新进程。这的确是实际操作中采用的一种方案，但并非十全十美，因为创建进程要付出很大的代价。这需要大量的运算和内存空间，由于每个进程都具有独立的内存空间，所以相互间的数据交换也要采用相对复杂的方法（进程间的通信IPC 属于相对复杂的通信方法）

I/O 复用技术可以解决这个问题。



**理解复用**

「复用」在电子及通信工程领域很常见，向这些领域的专家询问其概念，可能会得到如下答复：

> 在 1 个通信频道中传递多个数据（信号）的技术

「复用」的含义：

> 为了提高物理设备的效率，只用最少的物理要素传递最多数据时使用的技术

上述两种方法的内容完全一致。可以用纸电话模型做一个类比：

<img src="TCPIP网络编程.assets/68747470733a2f2f73322e617831782e636f6d2f323031392f30312f32332f6b41384838312e706e67.png" alt="img" style="zoom:80%;" />

上图是一个纸杯电话系统，为了使得三人同时通话，说话时要同事对着两个纸杯，接听时也需要耳朵同时对准两个纸杯。为了完成 3 人通话，可以进行如下图的改进：

<img src="TCPIP网络编程.assets/68747470733a2f2f73322e617831782e636f6d2f323031392f30312f32332f6b41386267782e706e67.png" alt="img" style="zoom:80%;" />

如图做出改进，就是引入了复用技术。

复用技术的优点：

- 减少连线长度
- 减少纸杯个数

即使减少了连线和纸杯的量仍然可以进行三人同时说话，但是如果碰到以下情况：

> 「好像不能同时说话？」

实际上，因为是在进行对话，所以很少发生同时说话的情况。也就是说，上述系统采用的是**「时分复用」**技术。因为说话人声频率不同，即使在同时说话也能进行一定程度上的区分（杂音也随之增多）。因此，也可以说是「频分复用技术」。



**复用技术在服务器端的应用**

纸杯电话系统引入复用技术之后可以减少纸杯数量和连线长度。**服务器端引入复用技术可以减少所需进程数**。下图是多进程服务端的模型：

![img](TCPIP网络编程.assets/68747470733a2f2f73322e617831782e636f6d2f323031392f30312f32332f6b4147424d362e706e67.png)

下图是引入复用技术之后的模型：

![img](TCPIP网络编程.assets/68747470733a2f2f73322e617831782e636f6d2f323031392f30312f32332f6b414772714f2e706e67.png)

从图上可以看出，引入复用技术之后，可以减少进程数。重要的是，无论连接多少客户端，提供服务的进程只有一个。



### 12.2 理解select函数并实现服务端 ❤

> 在 C++ 中，`select` 函数是用于实现基于 I/O 多路复用的函数，主要用于同时监听多个套接字是否有数据可读、是否可以进行写入等操作。其主要功能如下：
>
> 1. 监听套接字的可读状态：`select` 函数可以对多个套接字描述符进行监听，当某个套接字有数据可读时，`select` 函数将返回该套接字的描述符，从而实现对多个套接字的同时监听。
> 2. 监听套接字的可写状态：`select` 函数还可以对多个套接字描述符进行监听，当某个套接字可以进行写入时，`select` 函数将返回该套接字的描述符，从而实现对多个套接字的同时监听。
> 3. 监听套接字的异常状态：`select` 函数还可以对多个套接字描述符进行监听，当某个套接字发生异常情况时，例如连接被重置或者接收到非法数据等情况，`select` 函数将返回该套接字的描述符，从而实现对多个套接字的同时监听。
> 4. 设置超时时间：`select` 函数还可以设置超时时间，当超时时间到达时，`select` 函数将立即返回，避免长时间的阻塞。
>
> 通过 `select` 函数，我们可以对多个套接字进行监听，并在有数据到来时及时进行处理，从而提高程序的效率。它是实现基于 I/O 多路复用的重要函数之一。

使用select函数时可以将多个文件描述符集中到一起统一监视，项目如下：

- 是否存在套接字接收数据
- 无需则色传输数据的套接字有哪些
- 哪些套接字发生了异常

select 函数的使用方法与一般函数的区别并不大，更准确的说，它很难使用。但是为了实现 I/O 复用服务器端，我们应该掌握 select 函数，并运用于套接字编程当中。认为「select 函数是 I/O 复用的全部内容」也并不为过。select 函数的调用过程如下图所示：

<img src="TCPIP网络编程.assets/68747470733a2f2f73322e617831782e636f6d2f323031392f30312f32332f6b41746452732e706e67.png" alt="img" style="zoom:67%;" />

**利用 select 函数可以同时监视多个文件描述符，并在有数据到来时及时进行处理，从而提高程序的效率。**当然，监视文件描述符可以视为监视套接字。此时首先需要将要监视的文件描述符集中在一起。集中时也要按照监视项（接收、传输、异常）进行区分，即按照上述 3 种监视项分成 3 类。

利用 `fd_set` 数组变量执行此操作，如图所示，该数组是存有0和1的位数组。

<img src="TCPIP网络编程.assets/68747470733a2f2f73322e617831782e636f6d2f323031392f30312f32332f6b41743269342e706e67.png" alt="img" style="zoom:80%;" />

图中最左端的位表示文件描述符 0（所在位置）。如果该位设置为 1，则表示该文件描述符是监视对象。那么图中哪些文件描述符是监视对象呢？很明显，是描述符 1 和 3。**在 `fd_set` 变量中注册或更改值的操作都由下列宏完成：**

- `FD_ZERO(fd_set *fdset)`：将 `fd_set` 变量所指的位全部初始化成0
- `FD_SET(int fd,fd_set *fdset)`：在参数` fdset` 指向的变量中**注册**文件描述符 `fd` 的信息
- `FD_CLR(int fd,fd_set *fdset)`：从参数 `fdset` 指向的变量中**清除**文件描述符 `fd` 的信息
- `FD_ISSET(int fd,fd_set *fdset)`：若参数 `fdset` 指向的变量中**包含**文件描述符 `fd`的信息，则返回「真」

上述函数中，FD_ISSET 用于验证 select 函数的调用结果，通过下图解释这些函数的功能：

<img src="TCPIP网络编程.assets/68747470733a2f2f73322e617831782e636f6d2f323031392f30312f32332f6b414e5237382e706e67.png" alt="img" style="zoom: 67%;" />



**设置检查（监视）范围及超时**

下面是 select 函数的定义：

```c++
#include <sys/select.h>
#include <sys/time.h>

int select(int maxfd, fd_set *readset, fd_set *writeset,
           fd_set *exceptset, const struct timeval *timeout);
/*
成功时返回大于 0 的值，失败时返回 -1
maxfd: 监视对象文件描述符数量
readset: 将所有关注「是否存在待读取数据」的文件描述符注册到 fd_set 型变量，并传递其地址值。
writeset: 将所有关注「是否可传输无阻塞数据」的文件描述符注册到 fd_set 型变量，并传递其地址值。
exceptset: 将所有关注「是否发生异常」的文件描述符注册到 fd_set 型变量，并传递其地址值。
timeout: 调用 select 函数后，为防止陷入无限阻塞的状态，传递超时(time-out)信息
返回值: 发生错误时返回 -1,超时时返回0,。因发生关注的时间返回时，返回大于0的值，该值是发生事件的文件描述符数。
*/
```

如上所述，select 函数用来验证 3 种监视的变化情况，根据监视项声明 3 个 fd_set 型变量，分别向其注册文件描述符信息，并把变量的地址值传递到上述函数的第二到第四个参数。但在此之前（调用 select 函数之前）需要决定下面两件事：

1. 文件描述符的监视（检查）范围是？
2. 如何设定 select 函数的超时时间？

**第一，文件描述符的监视范围和 select 的第一个参数有关**。实际上，select 函数要求通过第一个参数传递监视对象文件描述符的数量。因此，需要得到注册在 `fd_set` 变量中的文件描述符数。但每次新建文件描述符时，其值就会增加 1 ，故只需将最大的文件描述符值加 1 再传递给 select 函数即可。加 1 是因为文件描述符的值是从 0 开始的。

**第二，select 函数的超时时间与 select 函数的最后一个参数有关**，其中 `timeval` 结构体定义如下：

```
struct timeval
{
    long tv_sec;
    long tv_usec;
};
```

本来 select 函数只有在监视文件描述符发生变化时才返回。如果未发生变化，就会进入**阻塞**状态。指定超时时间就是为了防止这种情况的发生。通过上述结构体变量，将秒数填入 `tv_sec` 的成员，将微秒数填入 `tv_usec` 的成员，然后将结构体的地址值传递到 select 函数的最后一个参数。此时，即使文件描述符未发生变化，只要过了指定时间，也可以从函数中返回。不过这种情况下， select 函数返回 0 。因此，可以通过返回值了解原因。如果不想设置超时，则传递 **NULL** 参数。



**调用 select 函数查看结果**

select 返回正整数时，怎样获知哪些文件描述符发生了变化？向 select 函数的第二到第四个参数传递的 `fd_set` 变量中将产生如图所示的变化：

<img src="TCPIP网络编程.assets/68747470733a2f2f73322e617831782e636f6d2f323031392f30312f32332f6b41303664782e706e67.png" alt="img" style="zoom:80%;" />

由图可知，select 函数调用完成后，向其传递的 `fd_set` 变量将发生变化。原来为 1 的所有位将变成 0，但是发生了变化的文件描述符除外。因此，可以认为**值仍为 1 的位置上的文件描述符发生了变化**。



**select函数调用示例**

```c++
#include <iostream>
#include <unistd.h>
#include <sys/time.h>
#include <sys/select.h>
using namespace std;

#define BUF_SIZE 30

int main(){
    fd_set reads, temp;
    char buf[BUF_SIZE];
    struct timeval timeout;

    FD_ZERO(&reads);    //1、设置文件描述符
    FD_SET(0, &reads);  //将输入设备的文件描述符加入到集合reads中

    /*
    timeout.tv_sec = 0;
    timeout.tv_usec = 5 * 1000;
    */

    while (1){         
        temp = reads;
        timeout.tv_sec = 5;     //设置超时
        timeout.tv_usec = 0;

        int result = select(1, &temp, 0, 0, &timeout);  //调用select函数
        if (result == -1){
            cout << "select() error" << endl;
            break;
        }else if (result == 0){
            cout << "Time out" << endl;
        }else{
            if (FD_ISSET(0, &temp)){
                int str_len = read(0, buf, BUF_SIZE);
                buf[str_len] = 0;
                cout << "Message from console : " << buf << endl;
            }
        }
    }

    return 0;
}
```

调用select之后，结构体`timeva`l的成员`tv_sec`和`tv_usev`的值将被替换为超时剩余时间



**实现I/O复用服务端**

下面通过select函数实现I/O服用服务端

```c++
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/select.h>
#include <algorithm>
using namespace std;

#define BUF_SIZE 128

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
        cout << "Server create socket error" << endl;
        return -1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        cout << "Server bind socket error" << endl;
        return -1;
    }

    if (listen(serv_sock, 5) == -1){
        cout << "Server listen socket error" << endl;
        return -1;
    }

    int fd_max = -1;
    fd_set reads, temp;

    //设置文件描述符
    FD_ZERO(&reads);
    FD_SET(serv_sock, &reads);
    fd_max = max(fd_max, serv_sock);
    struct timeval timeout;

    while (1){
        temp = reads;
        //设置超时
        timeout.tv_sec = 5, timeout.tv_usec = 5 * 1000;

        int result = select(fd_max + 1, &temp, 0, 0, &timeout); //注意：使用的是temp集合！
        if (result == -1)   break;
        else if (result == 0) continue;

        for (int i = 0; i <= fd_max; i++){
            if (FD_ISSET(i, &temp)){    //套接字文件描述符在集合temp中
                if (i == serv_sock){    //服务端的套接字发生了变化
                    clnt_size = sizeof(clnt_addr);
                    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_size);
                    if (clnt_sock == -1){
                         cout << "Server accept client connect error" << endl;
                         continue;
                    }
                    FD_SET(clnt_sock, &reads);  //!!!将客户端的套接字加入到reads中
                    fd_max = max(fd_max, clnt_sock);
                    cout << "Connect client : " << clnt_sock << endl;
                }else{
                    int str_len = read(i, buf, BUF_SIZE);
                    if (str_len == 0){      //到达文件末尾EOF,断开连接
                        FD_CLR(i, &reads);
                        close(i);
                        cout << "Closed client " << i << endl;
                    }else   
                        write(i, buf, str_len);
                }
            }
        }
    }
}
```





### 12.3 基于 Windows 的实现

略





###  12.4 习题

1. **请解释复用技术的通用含义，并说明何为 I/O 复用。**

   答：复用技术是指在计算机编程中，**通过某种机制使得多个任务能够共享同一个资源，以提高计算机系统的性能和效率**。这个概念可以应用于许多不同的领域，例如计算机网络、操作系统、数据库系统等等。

   **在计算机编程中，I/O复用是一种常见的复用技术。I/O是指Input/Output，即输入输出。在程序中，常常需要等待某个操作完成后才能进行下一步操作，这个等待的过程就会造成程序的阻塞，浪费计算机的资源。I/O复用技术通过监听多个输入输出流，将它们合并成一个流，并通过一个阻塞式调用来等待它们中的任何一个就绪，从而避免了程序的阻塞。**

   在具体实现上，I/O复用可以通过不同的方式实现，例如使用select、poll或epoll等系统调用。这些系统调用允许程序同时监听多个文件描述符（file descriptor），当其中一个文件描述符就绪时，该调用将返回可读、可写或异常状态。程序可以在这些状态中寻找有用的信息，并据此进行下一步操作，从而避免了对所有文件描述符的轮询。I/O复用技术可以提高程序的性能和效率，特别是在高并发的情况下，对于网络编程、服务器编程等场景尤为重要。

   

2. **多进程并发服务器的缺点有哪些？如何在 I/O 复用服务器中弥补？**

   答：

   ​	多进程并发服务器的缺点主要包括：

   1. **资源占用**：多进程服务器需要为每个连接创建一个新的进程，这会占用大量的系统资源，包括内存、CPU 时间、文件描述符等等。
   2. **进程间通信**：多进程服务器中的进程之间需要进行通信，这增加了通信开销和复杂度，容易出现死锁和竞争条件等问题。
   3. **上下文切换**：多进程服务器中，进程的切换和调度会增加系统的上下文切换次数，降低系统性能和效率。

   相比之下，I/O复用服务器通过监听多个文件描述符，使用一个进程来处理多个连接请求，避免了进程创建、通信、上下文切换等开销，提高了系统的性能和效率。具体而言，可以使用select、poll或epoll等系统调用实现I/O复用服务器，避免了多进程服务器的缺点。此外，还可以使用线程池等技术来进一步提高系统性能和效率，使得服务器可以处理更多的连接请求。

   > 虽然I/O复用技术可以提高程序的性能和效率，但是它也存在一些缺点：
   >
   > 1. 编程复杂度高：I/O复用需要开发者手动维护多个文件描述符，并进行状态判断和事件处理，编程复杂度较高，需要一定的编程技巧和经验。
   > 2. 不适合高并发场景：虽然I/O复用可以避免多进程/多线程服务器的缺点，但是在高并发场景下，仍然可能会遇到瓶颈。例如，如果程序需要监听大量的文件描述符，同时又需要处理大量的连接请求，I/O复用可能会受到限制，无法充分发挥性能优势。
   > 3. 可移植性较差：不同的操作系统对于I/O复用技术的实现方式有所不同，例如select和epoll在不同的操作系统上表现可能会有所差异，需要针对不同的操作系统进行不同的实现，增加了开发和维护的难度。
   >
   > 总之，虽然I/O复用技术可以提高程序的性能和效率，但是也需要考虑到它的缺点，并根据实际情况选择合适的技术方案。

   

3. **复用服务器端需要 select 函数。下列关于 select 函数使用方法的描述错误的是？**

   答：以下加粗的为正确的描述。

   1. 调用 select 函数前需要集中 I/O 监视对象的文件描述符
   2. **若已通过 select 函数注册为监视对象，则后续调用 select 函数时无需重复注册**
   3. 复用服务器端同一时间只能服务于 1 个客户端，因此，需要服务的客户端接入服务器端后只能等待
   4. **与多线程服务端不同，基于 select 的复用服务器只需要 1 个进程。因此，可以减少因创建多进程产生的服务器端的负担**。

   

4. **select 函数的观察对象中应包含服务端套接字（监听套接字），那么应将其包含到哪一类监听对象集合？请说明原因**。

   答：应该包含到**「是否存在待读取数据」**，因为服务器端需要查看套接字中有没有可以读取的数据。





## 第13章 多种I/O函数

### 13.1 `send` & `recv` 函数

**Linux 中的 `send` & `recv`**

首先看 `send` 函数定义：

```c++
#include <sys/socket.h>
ssize_t send(int sockfd, const void *buf, size_t nbytes, int flags);
/*
成功时返回发送的字节数，失败时返回 -1
sockfd: 表示与数据传输对象的连接的套接字和文件描述符
buf: 保存待传输数据的缓冲地址值
nbytes: 待传输字节数
flags: 传输数据时指定的可选项信息
*/
```

下面是 `recv `函数的定义：

```c++
#include <sys/socket.h>
ssize_t recv(int sockfd, void *buf, size_t nbytes, int flags);
/*
成功时返回接收的字节数（收到 EOF 返回 0），失败时返回 -1
sockfd: 表示数据接受对象的连接的套接字文件描述符
buf: 保存接受数据的缓冲地址值
nbytes: 可接收的最大字节数
flags: 接收数据时指定的可选项参数
*/
```

 `send` & `recv`函数的最后一个参数是收发数据的可选项，该选项可以用位或（bit OR）运算符（| 运算符）同时传递多个信息。

 `send` & `recv` 函数的可选项意义：

| 可选项（Option） | 含义                                                         | `send` | `recv` |
| ---------------- | ------------------------------------------------------------ | ------ | ------ |
| MSG_OOB          | 用于传输带外数据（Out-of-band data）                         | O      | O      |
| MSG_PEEK         | 验证输入缓冲中是否存在接受的数据                             | X      | O      |
| MSG_DONTROUTE    | 数据传输过程中不参照本地路由（Routing）表，在本地（Local）网络中寻找目的地 | O      | X      |
| MSG_DONTWAIT     | 调用 I/O 函数时不阻塞，用于使用非阻塞（Non-blocking）I/O     | O      | O      |
| MSG_WAITALL      | 防止函数返回，直到接收到全部请求的字节数                     | X      | O      |



 **MSG_OOB：发送紧急消息**

MSG_OOB 可选项用于创建特殊发送方法和通道以发送紧急消息。下面为 MSG_OOB 的示例代码：

oob_send.cpp代码：

```c++
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

#define BUF_SIZE 30

int main(int argc, char *argv[]){
    if (argc != 3){
        cout << "Usage : <IP> <port>" << endl;
        return -1;
    }

    int sock;
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1){
        cout << "Send create socket error" << endl;
        return -1;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) == -1){
        cout << "Send connect error" << endl;
        return -1;
    }

    write(sock, "123", strlen("123"));
    send(sock, "4", strlen("4"), MSG_OOB);
    write(sock, "567", strlen("567"));
    send(sock, "890", strlen("890"), MSG_OOB);

    close(sock);
    return 0;
}
```

oob_recv.cpp代码：

```c++
#include <iostream>
#include <cstring>
#include <signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
using namespace std;

#define BUF_SIZE 30
int send_sock, recv_sock;

void urg_handler(int sig){  //信号处理函数
    char str[BUF_SIZE];
    memset(str, 0, sizeof(str));
    int str_len = recv(recv_sock, str, sizeof(str)-1, MSG_OOB);//MSG_OOB用于传输带外数据
    str[str_len] = 0;
    cout << "Urgent message : " << str << endl;
}

int main(int argc, char *argv[]){
    //类似于服务端接收客户端的链接
    if (argc != 2){
        cout << "Usage : <port>" << endl;
        return -1;
    }

    struct sockaddr_in send_addr, recv_addr;
    socklen_t recv_size;
    char buf[BUF_SIZE];

    send_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (send_sock == -1){
        cout << "Send socket error" << endl;
        return -1;
    }

    memset(&send_addr, 0, sizeof(send_addr));
    send_addr.sin_family = AF_INET;
    send_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    send_addr.sin_port = htons(atoi(argv[1]));

    if (bind(send_sock, (struct sockaddr*)&send_addr, sizeof(send_addr)) == -1){
        cout << "Send bind error" << endl;
        return -1;
    }

    if (listen(send_sock, 5) == -1){
        cout << "Send listen error" << endl;
        return -1;
    }

    recv_size = sizeof(recv_addr);
    recv_sock = accept(send_sock, (struct sockaddr*)&recv_addr, &recv_size);
    if (recv_sock == -1){
        cout << "Recv accept error" << endl;
        return -1;
    }

    cout << "acctpt recv_sock : " << recv_sock << endl;

    fcntl(recv_sock, F_SETOWN, getpid());
    //文件秒的护肤recv_sock指向的套接字引发的SIGURG信号处理进程将变为gitpid函数返回值用作ID的进程

     //注册信号处理函数
    struct sigaction act;
    act.sa_handler = urg_handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    int status = sigaction(SIGURG, &act, 0);
    cout << "status : " << status << endl;

    int str_len;
    while ((str_len = recv(recv_sock, buf, sizeof(buf)-1, 0)) != 0){
        if (str_len == -1)
            continue;;
        buf[str_len] = 0;
        cout << buf << endl;
        cout << str_len << endl;
    }

    close(send_sock), close(recv_sock);
    return 0;
}
```

从运行结果可以看出，send 是客户端，recv 是服务端，客户端给服务端发送消息，服务端接收完消息之后显示出来。可以从图中看出，每次运行的效果，并不是一样的。



代码中关于:

```c++
fcntl(recv_sock, F_SETOWN, getpid());
```

> 在C++中，`fcntl()`函数用于控制文件描述符的属性。在你提供的代码中，`fcntl()`函数调用的第二个参数为`F_SETOWN`，它用于设置文件描述符的拥有者。第三个参数为`getpid()`，它获取当前进程的进程ID。
>
> 因此，这行代码的作**用是将`recv_sock`这个文件描述符的拥有者设置为当前进程。**通常情况下，如果一个进程打开了一个socket，那么它就成为了这个socket的拥有者，但是如果想让其他进程能够监听这个socket的事件，就需要使用`F_SETOWN`来设置该socket的拥有者。
>
> 在Linux系统中，如果一个socket接收到数据或者发生了某些错误，内核会向socket的拥有者发送一个信号，该信号可以通过注册一个信号处理函数来捕获。因此，在一些网络编程场景中，设置socket的拥有者可以方便地处理网络事件。
>
> 
>
> 文件描述符 recv_sock 指向的套接字引发的 SIGURG 信号处理进程变为 getpid 函数返回值用作 ID 进程.

上述描述中的「处理 SIGURG 信号」指的是「调用 SIGURG 信号处理函数」。但是之前讲过，多个进程可以拥有 1 个套接字的文件描述符。例如，通过调用 fork 函数创建子进程并同时复制文件描述符。此时如果发生 SIGURG 信号，应该调用哪个进程的信号处理函数呢？可以肯定的是，不会调用所有进程的信号处理函数。因此，处理 SIGURG 信号时必须指定处理信号所用的进程，而 getpid 返回的是调用此函数的进程 ID 。上述调用语句指当前为处理 SIGURG 信号的主体。

输出结果，可能出乎意料：

> 通过 MSG_OOB 可选项传递数据时只返回 1 个字节，而且也不快

的确，通过 MSG_OOB 并不会加快传输速度，而通过信号处理函数 urg_handler 也只能读取一个字节。剩余数据只能通过未设置 MSG_OOB 可选项的普通输入函数读取。因为 TCP 不存在真正意义上的「外带数据」。实际上，MSG_OOB 中的 OOB 指的是 Out-of-band ，而「外带数据」的含义是：

> 通过完全不同的通信路径传输的数据

即真正意义上的 Out-of-band 需要通过单独的通信路径高速传输数据，但是 TCP 不另外提供，只利用 TCP 的紧急模式（Urgent mode）进行传输。



**紧急模式工作原理**

MSG_OOB 的真正意义在于督促数据接收对象尽快处理数据。这是紧急模式的全部内容，而 TCP **「保持传输顺序」**的传输特性依然成立。TCP 的紧急消息无法保证及时到达，但是可以要求急救。下面是 MSG_OOB 可选项状态下的数据传输过程，如图：

![img](TCPIP网络编程.assets/68747470733a2f2f692e6c6f6c692e6e65742f323031392f30312f32362f356334626532323238343563632e706e67.png)

上面是:

```
send(sock, "890", strlen("890"), MSG_OOB);
```

图上是调用这个函数的缓冲状态。如果缓冲最左端的位置视作偏移量 0 。字符 0 保存于偏移量 2 的位置。另外，字符 0 右侧偏移量为 3 的位置存有紧急指针（Urgent Pointer）。紧急指针指向紧急消息的下一个位置（偏移量加一），同时向对方主机传递以下信息：

> 紧急指针指向的偏移量为 3 之前的部分就是紧急消息。

也就是说，实际上只用了一个字节表示紧急消息。这一点可以通过图中用于传输数据的 TCP 数据包（段）的结构看得更清楚，如图：

![img](TCPIP网络编程.assets/68747470733a2f2f692e6c6f6c692e6e65742f323031392f30312f32362f356334626565616534366234652e706e67.png)

TCP 数据包实际包含更多信息。TCP 头部包含如下两种信息：

- URG=1：载有紧急消息的数据包
- URG指针：紧急指针位于偏移量为 3 的位置。

指定 MSG_OOB 选项的数据包本身就是紧急数据包，并通过紧急指针表示紧急消息所在的位置。

紧急消息的意义在于督促消息处理，而非紧急传输形式受限的信息。



**检查输入缓冲**

同时设置 MSG_PEEK 选项和 MSG_DONTWAIT 选项，以验证输入缓冲是否存在接收的数据。设置 MSG_PEEK 选项并调用 `recv `函数时，即使**读取了输入缓冲的数据也不会删除**。因此，该选项通常与 MSG_DONTWAIT 合作，用于**以非阻塞方式验证待读数据存在与否**。下面的示例是二者的含义：

peek_send.cpp

```c++
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

#define BUF_SIZE 30

int main(int argc, char *argv[]){
    if (argc != 3){
        cout << "Usage : <port>" << endl;
        return -1;
    }

    int send_sock;
    struct sockaddr_in recv_addr;

    send_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (send_sock == -1){
        cout << "Send create socket error" << endl;
        return -1;
    }

    memset(&recv_addr, 0, sizeof(recv_addr));
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    recv_addr.sin_port = htons(atoi(argv[2]));

    if ((connect(send_sock, (struct sockaddr*)&recv_addr, sizeof(recv_addr))) == -1){
        cout << "Send connect error" << endl;
        return -1;
    }

   	//使用send或者write向send_sock发送数据均可
    send(send_sock, "123", strlen("123"), 0);

    close(send_sock);
    return 0;
}
```

peek_recv.cpp

```c++
#include <iostream>
#include <cstring>
#include <signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
using namespace std;

#define BUF_SIZE 30

int main(int argc, char *argv[]){
    if (argc != 2){
        cout << "Usage : <port>" << endl;
        return -1;
    }

    int recv_sock, send_sock;
    struct sockaddr_in send_addr, recv_addr;
    socklen_t recv_size;
    char buf[BUF_SIZE];

    send_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (send_sock == -1){
        cout << "Send socket error" << endl;
        return -1;
    }

    memset(&send_addr, 0, sizeof(send_addr));
    send_addr.sin_family = AF_INET;
    send_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    send_addr.sin_port = htons(atoi(argv[1]));

    if (bind(send_sock, (struct sockaddr*)&send_addr, sizeof(send_addr)) == -1){
        cout << "Send bind error" << endl;
        return -1;
    }

    if (listen(send_sock, 5) == -1){
        cout << "Send listen error" << endl;
        return -1;
    }

    recv_size = sizeof(recv_addr);
    recv_sock = accept(send_sock, (struct sockaddr*)&recv_addr, &recv_size);
    if (recv_sock == -1){
        cout << "Recv accept error" << endl;
        return -1;
    }

    int str_len;
    //从send中读取数据,利用recv中的MSG_PEEK和MSG_DONTWAIT来读取输入缓冲中的数据
    while (1){
        str_len = recv(recv_sock, buf, BUF_SIZE, MSG_PEEK | MSG_DONTWAIT);
        if (str_len > 0)    break;
    }

    buf[str_len] = 0;
    cout << "Buffering : " << buf << endl;

    //再次读取缓冲区中的数据
    memset(&buf, 0, sizeof(buf));   
    str_len = recv(recv_sock, buf, BUF_SIZE, 0);
    buf[str_len] = 0;
    cout << "Read again : " << buf << endl;

    close(send_sock), close(recv_sock);
    return 0;
}
```





### 13.2 `readv` & `writev` 函数

readv & writev 函数的功能可概括如下：

> **对数据进行整合传输及发送的函数**

也就是说，通过 `writev` 函数可以将分散保存在多个缓冲中的数据一并发送，通过 `readv` 函数可以由多个缓冲分别接收。因此，适用这 2 个函数可以减少 I/O 函数的调用次数。下面先介绍 `writev` 函数。

```c++
#include <sys/uio.h>
ssize_t writev(int filedes, const struct iovec *iov, int iovcnt);
/*
成功时返回发送的字节数，失败时返回 -1
filedes: 表示数据传输对象的套接字文件描述符。但该函数并不仅限于套接字，因此，可以像 read 一样向向其传递文件或标准输出描述符.
iov: iovec 结构体数组的地址值，结构体 iovec 中包含待发送数据的位置和大小信息
iovcnt: 向第二个参数传递数组长度
*/
```

上述第二个参数中出现的数组 iovec 结构体的声明如下：

```c++
struct iovec
{
    void *iov_base; //缓冲地址
    size_t iov_len; //缓冲大小
};
```

下图是该函数的使用方法：

![img](TCPIP网络编程.assets/68747470733a2f2f692e6c6f6c692e6e65742f323031392f30312f32362f356334633631623037643230372e706e67.png)

writev 的第一个参数，是文件描述符，因此向控制台输出数据，ptr 是存有待发送数据信息的 iovec 数组指针。第三个参数为 2，因此，从 ptr 指向的地址开始，共浏览 2 个 iovec 结构体变量，发送这些指针指向的缓冲数据。

下面是 writev 函数的使用方法：

```c++
#include <iostream>
#include <sys/uio.h>
using namespace std;

int main(int argc, char *argv[]){
    struct iovec vec[2];
    char buf1[] = "ABCDEFG", buf2[] = "1234567";

    vec[0].iov_base = buf1;
    vec[0].iov_len = 3;
    vec[1].iov_base = buf2;
    vec[1].iov_len = 4;

    int str_len = writev(1, vec, 2);    //将vec中的数据写道标准输出1中
    cout << "\nwrite bytes : " << str_len << endl;

    return 0;
}
```

readv函数

```c++
#include <iostream>
#include <sys/uio.h>
using namespace std;

#define BUF_SIZE 100

int main(int argc, char *argv[]){
    struct iovec vec[2];
    char buf1[BUF_SIZE], buf2[BUF_SIZE];

    vec[0].iov_base = buf1, vec[0].iov_len = 5;
    vec[1].iov_base = buf2, vec[1].iov_len = BUF_SIZE;

    int str_len = readv(0, vec, 2);

    cout << "Read bytes : " << str_len << endl;
    cout << "First message : " << buf1 << endl;
    cout << "second message : " << buf2 << endl;

    return 0;
}
```

输出

```c#
I like TCP/IP socket programming
Read bytes : 33
First message : I lik
second message : e TCP/IP socket programming
```

从图上可以看出，首先截取了长度为 5 的数据输出，然后再输出剩下的



**合理使用 `readv` & `writev` 函数**

实际上，能使用该函数的所有情况都适用。例如，**需要传输的数据分别位于不同缓冲（数组）时，需要多次调用 write 函数。此时可通过 1 次 `writev` 函数调用替代操作**，当然会提高效率。同样，**需要将输入缓冲中的数据读入不同位置时，可以不必多次调用 read 函数，而是利用 1 次 `readv` 函数就能大大提高效率**。

**其意义在于减少数据包个数**。假设为了提高效率在服务器端明确禁用了 Nagle 算法。其实 `writev` 函数在不采用 Nagle 算法时更有价值，如图：

![img](TCPIP网络编程.assets/68747470733a2f2f692e6c6f6c692e6e65742f323031392f30312f32362f356334633733313332336531392e706e67.png)



### 13.3 基于 Windows 的实现

暂略



### 13.4 习题

1. **下列关于 MSG_OOB 可选项的说法错误的是**？

   答：以下加粗的字体代表说法正确。

   1. MSG_OOB 指传输 Out-of-band 数据，是通过其他路径高速传输数据
   2. MSG_OOB 指通过其他路径高速传输数据，因此 TCP 中设置该选项的数据先到达对方主机
   3. **设置 MSG_OOB 是数据先到达对方主机后，以普通数据的形式和顺序读取。也就是说，只是提高了传输速度，接收方无法识别这一点**。
   4. **MSG_OOB 无法脱离 TCP 的默认数据传输方式，即使脱离了 MSG_OOB ，也会保持原有的传输顺序。该选项只用于要求接收方紧急处理**。

   

2. **利用 readv & writev 函数收发数据有何优点？分别从函数调用次数和 I/O 缓冲的角度给出说明**。

   答：`readv`和`writev`函数是Linux系统提供的用于在一次函数调用中读取或写入多个非连续缓冲区的数据的函数。使用这两个函数可以带来以下优点：

   1. **减少函数调用次数**: 由于这两个函数可以一次性处理多个缓冲区，因此使用它们可以将多次`read`或`write`操作合并成一次函数调用。这样可以减少系统调用次数，减少内核态与用户态之间的切换，提高程序的性能。

   2. **减少数据拷贝**: 由于`readv`和`writev`可以一次性处理多个缓冲区，因此可以避免在应用程序和内核之间进行多次数据拷贝。这样可以减少数据在内存中的复制次数，提高数据传输效率。

   3. **灵活性更高**: `readv`和`writev`函数可以处理非连续的缓冲区，这意味着可以更灵活地组织数据结构，而不必考虑数据在内存中的物理布局。这使得应用程序更容易编写和维护，并提高了代码的可读性和可维护性。

      

   从 I/O 缓冲的角度来看，`readv`和`writev`函数也有一些优点：

   1. **减少缓冲区的数量**: 由于这两个函数可以一次性处理多个缓冲区，因此可以避免创建过多的缓冲区。这可以减少内存的使用，降低应用程序的复杂度。
   2. **减少数据复制**: 由于`readv`和`writev`可以一次性处理多个缓冲区，因此可以避免将数据复制到单个缓冲区中。这可以减少内存的使用，减少应用程序的复杂度，并提高数据传输效率。

   总之，使用`readv`和`writev`函数可以减少函数调用次数，减少数据拷贝和提高应用程序的性能和可维护性。

   

   

3. **通过 recv 函数验证输入缓冲中是否存在数据时（确认后立即返回时），如何设置 recv 函数最后一个参数中的可选项？分别说明各可选项的含义**。

   答：使用 MSG_PEEK 来验证输入缓冲中是否存在待接收的数据。各个可选项的意义参见上面对应章节的表格。





## 第14章 多播与广播

### 14.1 多播

多播（Multicast）方式的数据传输是基于 **UDP** 完成的。因此 ，与 UDP 服务器端/客户端的实现方式非常接近。区别在于，UDP 数据传输以单一目标进行，而多播数据同时传递到加入（注册）特定组的大量主机。换言之，采用多播方式时，可以同时向多个主机传递数据。

> **多播传输是一种将数据包从一个发送方发送到多个接收方的网络传输方式**，其工作原理如下：
>
> 1. 发送方将要传输的数据包标记为多播包，并在数据包头部指定一个多播地址。
> 2. 发送方将多播数据包发送到网络上的一个多播路由器。多播路由器是一种特殊的路由器，它会维护一个多播组的成员列表，并根据该列表将多播数据包转发给所有的组成员。
> 3. 多播路由器会将多播数据包复制成多份，然后将这些副本发送到所有加入该多播组的主机。这样，所有的接收方都可以同时接收到相同的数据包。
> 4. 接收方需要先加入该多播组才能接收到多播数据包。加入多播组的方式通常是使用Internet Group Management Protocol (IGMP)。
> 5. 一旦接收方加入了该多播组，就可以接收到该组的所有多播数据包。
>
> 总的来说，多播传输利用多播路由器将数据包从发送方发送到多个接收方，从而实现高效的数据传输。多播传输可以显著减少网络流量，提高网络效率，同时也可以提高可靠性和节省成本。



**多播的数据传输方式以及流量方面的优点**

**多播的数据传输特点可整理如下：**

- 多播服务器端针对特定多播组，只发送 1 次数据。
- 即使只发送 1 次数据，但该组内的所有客户端都会接收数据
- 多播组数可以在 IP 地址范围内任意增加

多播组是 D 类IP地址（224.0.0.0~239.255.255.255），「加入多播组」可以理解为通过程序完成如下声明：

> 在 D 类IP地址中，我希望接收发往目标 239.234.218.234 的多播数据

多播是基于 UDP 完成的，也就是说，多播数据包的 相同。只是与一般的 UDP 数据包不同。向网络传递 1 个多播数据包时，路由器将复制该数据包并传递到多个主机。像这样，多播需要借助路由器完成。如图所示：

![img](TCPIP网络编程.assets/68747470733a2f2f692e6c6f6c692e6e65742f323031392f30312f32372f356334643331306461613662652e706e67.png)

若通过 TCP 或 UDP 向 1000 个主机发送文件，则共需要传递 1000 次。但是此时如果用多播网络传输文件，则只需要发送一次。这时由 1000 台主机构成的网络中的路由器负责复制文件并传递到主机。就因为这种特性，多播主要用于「多媒体数据实时传输」。

另外，理论上可以完成多播通信，但是不少路由器并不支持多播，或即便支持也因网络拥堵问题故意阻断多播。因此，为了在不支持多播的路由器中完成多播通信，也会使用隧道（Tunneling）技术。

> 多播传输是一种网络数据传输方式，可以在网络中的多个主机之间同时传输相同的数据包。它具有以下优缺点：
>
> 优点：
>
> 1. **减少网络流量**：使用多播传输可以将数据包仅发送一次，而不需要发送多个副本。这可以显著减少网络流量。
> 2. **提高网络效率**：使用多播传输可以减少网络上的数据包数量，从而减少了网络传输的负担，提高了网络的效率。
> 3. **提高可靠性**：使用多播传输可以确保所有接收者都接收到相同的数据包。这可以提高网络的可靠性和数据的一致性。
> 4. **节省成本**：相对于单播和广播传输，使用多播传输可以节省网络带宽和成本。
>
> 缺点：
>
> 1. 需要支持多播的网络：不是所有的网络都支持多播传输，这可能需要网络管理员进行一些配置。
> 2. 需要支持多播的应用程序：不是所有的应用程序都支持多播传输，这需要应用程序进行支持。
> 3. 难以管理：多播传输涉及到多个主机之间的数据传输，这可能会增加管理的复杂性。
> 4. 安全性问题：多播传输可能会暴露敏感数据给未授权的接收者，这可能会对网络安全性造成威胁。



**路由（Routing）和 TTL（Time to Live,生存时间），以及加入组的办法**

为了传递多播数据包，必须设置 TTL 。TTL 是 Time to Live的简写，是决定「数据包传递距离」的主要因素。TTL 用整数表示，并且每经过一个路由器就减一。TTL 变为 0 时，该数据包就无法再被传递，只能销毁。因此，TTL 的值设置过大将影响网络流量。当然，设置过小，也无法传递到目标。

![img](TCPIP网络编程.assets/68747470733a2f2f692e6c6f6c692e6e65742f323031392f30312f32372f356334643339363030303165622e706e67.png)

接下来是 TTL 的设置方法。TTL 是可以通过第九章的**套接字可选项**完成的。与设置 TTL 相关的协议层为 IPPROTO_IP ，选项名为 IP_MULTICAST_TTL。因此，可以用如下代码把 TTL 设置为 64

```c++
int send_sock;
int time_live = 64;
...
send_sock=socket(PF_INET, SOCK_DGRAM, 0);	//使用UDP协议
setsockopt(send_sock,IPPROTO_IP,IP_MULTICAST_TTL,(void*)&time_live,sizeof(time_live);
...
```

加入多播组也通过设置套接字可选项来完成。加入多播组相关的协议层为 IPPROTO_IP，选项名为 IP_ADD_MEMBERSHIP 。可通过如下代码加入多播组：

```c++
int recv_sock;
struct ip_mreq join_adr;
...
recv_sock=socket(PF_INET,SOCK_DGRAM,0);
...
join_adr.imr_multiaddr.s_addr="多播组地址信息";
join_adr.imr_interface.s_addr="加入多播组的主机地址信息";
setsockopt(recv_sock,IPPROTO_IP,IP_ADD_MEMBERSHIP,(void*)&join_adr,sizeof(join_adr);
...
```

下面是 ip_mreq 结构体的定义：

```c++
struct ip_mreq
{
    struct in_addr imr_multiaddr; //写入加入组的IP地址
    struct in_addr imr_interface; //加入该组的套接字所属主机的IP地址
};
```



**实现多播Sender和REceiver**

多播中用「发送者」（以下称为 Sender） 和「接收者」（以下称为 Receiver）替代服务器端和客户端。顾名思义，此处的 Sender 是多播数据的发送主体，Receiver 是需要多播组加入过程的数据接收主体。下面是示例，示例的运行场景如下：

- Sender : 向 AAA 组广播（Broadcasting）文件中保存的新闻信息
- Receiver : 接收传递到 AAA 组的新闻信息。

news_sender.cpp

```c++
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
```

news_receiver.cpp

```c++
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
using namespace std;

#define BUF_SIZE 30

int main(int argc, char *argv[]){
    if (argc != 3){
        cout << "Usage : <GroupIP> <PORT>" << endl;
        return -1;
    }

    int recv_sock;
    struct sockaddr_in addr;
    char buf[BUF_SIZE];

    recv_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (recv_sock == -1){
        cout << "Recv create socket error" << endl;
        return -1;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(atoi(argv[2]));

    if (bind(recv_sock, (struct sockaddr*)&addr, sizeof(addr)) == -1){
        cout << "Recv bind socket error" << endl;
        return -1;
    }

    struct ip_mreq join_addr;   //加入多播组
    join_addr.imr_multiaddr.s_addr = inet_addr(argv[1]);    //加入组的IP地址
    join_addr.imr_interface.s_addr = htonl(INADDR_ANY);     //加入该组的套接字所属主机的IP地址

    setsockopt(recv_sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &join_addr, sizeof(join_addr));    //设置套接字选项，加入多播组

    while (1){
        int str_len = recvfrom(recv_sock, buf, BUF_SIZE, 0, NULL, 0);   //不需要知道传输数据的主机地址信息，将最后两个参数设为NULL和0
        if (str_len < 0)    break;
        buf[str_len] = 0;
        cout << buf << endl;
    }

    close(recv_sock);
    return 0;
}
```

通过结果可以看出，使用 sender 多播信息，通过 receiver 接收广播，如果延迟运行 receiver 将无法接受之前发送的信息。



### 14.2 广播

广播（Broadcast）在「一次性向多个主机发送数据」这一点上与多播类似，但传输数据的范围有区别。多播即使在跨越不同网络的情况下，只要加入多播组就能接受数据。相反，广播只能向同一网络中的主机传输数据。



**广播的理解和实现方法**

广播是向同一网络中的所有主机传输数据的方法。与多播相同，广播也是通过 UDP 来完成的。根据传输数据时使用的IP地址形式，广播分为以下两种：

- 直接广播（Directed Broadcast）
- 本地广播（Local Broadcast）

二者在实现上的差别主要在于IP地址。直接广播的IP地址中除了网络地址外，其余主机地址全部设置成 1。例如，希望向网络地址 192.12.34 中的所有主机传输数据时，可以向 192.12.34.255 传输。换言之，可以采取直接广播的方式向特定区域内所有主机传输数据。

反之，本地广播中使用的IP地址限定为 255.255.255.255 。例如，192.32.24 网络中的主机向 255.255.255.255 传输数据时，数据将传输到 192.32.24 网络中所有主机。

**数据通信中使用的IP地址是与 UDP 示例的唯一区别。默认生成的套接字会阻止广播，因此，只需通过如下代码更改默认设置。**

```
int send_sock;
int bcast;
...
send_sock=socket(PF_INET,SOCK_DGRAM,0);
...
setsockopt(send_sock,SOL_SOCKET,SO_BROADCAST,(void*)&bcast,sizeof(bcast));
...
```



**实现广播数据的 Sender 和 Receiver**

news_sender_brd.cpp

```c++
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
using namespace std;

#define BUF_SIZE 30

int main(int argc, char *argv[]){
    if (argc != 3){
        cout << "Usage : <GroupIP> <PORT>" << endl;
        return -1;
    }

    int send_sock, so_brd = 1;
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
    
    setsockopt(send_sock, SOL_SOCKET, SO_BROADCAST, &so_brd, sizeof(so_brd));
    
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
```

news_receiver_brd.cpp

```c++
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
using namespace std;

#define BUF_SIZE 30

int main(int argc, char *argv[]){
    if (argc != 3){
        cout << "Usage : <GroupIP> <PORT>" << endl;
        return -1;
    }

    int recv_sock;
    struct sockaddr_in addr;
    char buf[BUF_SIZE];

    recv_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (recv_sock == -1){
        cout << "Recv create socket error" << endl;
        return -1;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(atoi(argv[2]));

    if (bind(recv_sock, (struct sockaddr*)&addr, sizeof(addr)) == -1){
        cout << "Recv bind socket error" << endl;
        return -1;
    }

    struct ip_mreq join_addr;   //加入多播组
    join_addr.imr_multiaddr.s_addr = inet_addr(argv[1]);    //加入组的IP地址
    join_addr.imr_interface.s_addr = htonl(INADDR_ANY);     //加入该组的套接字所属主机的IP地址

    setsockopt(recv_sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &join_addr, sizeof(join_addr));    //设置套接字选项，加入多播组

    while (1){
        int str_len = recvfrom(recv_sock, buf, BUF_SIZE, 0, NULL, 0);   //不需要知道传输数据的主机地址信息，将最后两个参数设为NULL和0
        if (str_len < 0)    break;
        buf[str_len] = 0;
        cout << buf << endl;
    }

    close(recv_sock);
    return 0;
}
```



### 14.3 基于 Windows 的实现



### 14.4 习题

1. **TTL 的含义是什么？请从路由器的角度说明较大的 TTL 值与较小的 TTL 值之间的区别及问题。**

   答：TTL 是决定「数据包传递距离」的主要因素。TTL 每经过一个路由器就减一。TTL 变为 0 时，数据包就无法再被传递，只能销毁。因此，TTL设置过大会影响网络流量。当然，设置过小无法传递到目标。

   

2. **多播与广播的异同点是什么？请从数据通信的角度进行说明**。

   答：在「一次性向多个主机发送数据」这一点上与多播类似，但传输的数据范围有区别。多播即使在跨越不同网络的情况下，只要加入多播组就能接受数据。相反，广播只能向同一网络中的主机传输数据。

   

3. **下面关于多播的说法描述错误的是**？

   答：以下内容加粗的为描述正确

   1. 多播是用来加入多播组的所有主机传输数据的协议
   2. 主机连接到同一网络才能加入到多播组，也就是说，多播组无法跨越多个网络
   3. **能够加入多播组的主机数并无限制，但只能有 1个主机（Sender）向该组发送数据**
   4. **多播时使用的套接字是 UDP 套接字，因为多播是基于 UDP 进行数据通信的。**

   

4. **多播也对网络流量有利，请比较 TCP 交换方式解释其原因**

   答：TCP 是必须建立一对一的连接，如果要向1000个主机发送文件，就得传递1000次。但是此时用多播方式传输数据，就只需要发送一次。

   

5. **多播方式的数据通信需要 MBone 虚拟网络。换言之，MBone 是用于多播的网络，但它是虚拟网络。请解释此处的「虚拟网络」**

   答：可以理解为「通过网络中的特殊协议工作的软件概念上的网络」。也就是说， MBone 并非可以触及的物理网络。他是以物理网络为基础，通过软件方法实现的多播通信必备虚拟网络。







## 第15章 套接字和标准I/O

> 预备知识：文件的读写
>
> **`fopen()`函数用于打开文件并返回文件指针。其函数原型如下：**
>
> ```c++
> FILE *fopen(const char *filename, const char *mode);
> ```
>
> 其中，`filename`是要打开的文件名，可以包含路径信息；`mode`是以何种模式打开文件，常见的模式有：
>
> - `"r"`：只读模式
> - `"w"`：只写模式（如果文件存在，则清空文件；如果文件不存在，则创建文件）
> - `"a"`：追加模式（如果文件存在，则将数据追加到文件末尾；如果文件不存在，则创建文件）
> - `"rb"`：二进制只读模式
> - `"wb"`：二进制只写模式
> - `"ab"`：二进制追加模式
>
> `fopen()`函数返回一个指向文件的指针。如果文件打开失败，则返回`NULL`。打开文件后，可以使用`fread()`和`fwrite()`等函数读写文件，使用`fclose()`函数关闭文件。
>
> 
>
> **`feof()`函数用于检测文件是否已经到达文件末尾。其函数原型如下：**
>
> ```c++
> int feof(FILE *stream);
> ```
>
> 其中，`stream`是要检测的文件指针。如果文件已经到达文件末尾，`feof()`函数返回非0值（即真），否则返回0值（即假）。
>
> `feof()`函数通常用于在循环中读取文件时，检测是否已经读取到文件末尾。在循环中，每次读取文件前都要先使用`feof()`函数判断是否已经到达文件末尾，如果是则跳出循环。
>
> 
>
> **`fgets()`函数用于从文件中读取一行数据。其函数原型如下：**
>
> ```c++
> char *fgets(char *str, int size, FILE *stream);
> ```
>
> 其中，`str`是要**存储读取数据的缓冲区**，`size`是**缓冲区的大小**，`stream`是要**读取的文件指针**。
>
> `fgets()`函数从`stream`指向的文件中读取一行数据，将其存储到`str`指向的缓冲区中，并在读取到换行符或者达到指定的缓冲区大小时停止读取。如果读取成功，返回`str`指针；如果读取失败，返回`NULL`指针。
>
> 
>
> **`fputs()`函数用于向文件中写入一行数据。其函数原型如下：**
>
> ```
> c++Copy code
> int fputs(const char *str, FILE *stream);
> ```
>
> 其中，`str`是要**写入的字符串**，`stream`是要**写入的文件指针**。
>
> `fputs()`函数将`str`指向的字符串写入到`stream`指向的文件中，并在字符串结尾处添加换行符。如果写入成功，返回非负整数；如果写入失败，返回负整数。
>
> 



### 15.1 标准 I/O 的优点

**标准 I/O 函数的两个优点**

除了使用 read 和 write 函数收发数据外，还能使用标准 I/O 函数收发数据。下面是标准 I/O 函数的两个优点：

- **标准 I/O 函数具有良好的移植性**
- **标准 I/O 函数可以利用缓冲提高性能**

创建套接字时，操作系统会准备 I/O 缓冲。此缓冲在执行 TCP 协议时发挥着非常重要的作用。此时若使用标准 I/O 函数，将得到额外的缓冲支持。如下图：

![img](TCPIP网络编程.assets/68747470733a2f2f692e6c6f6c692e6e65742f323031392f30312f32392f356335303065353361643961612e706e67.png)

假设使用 fputs 函数进行传输字符串 「Hello」时，首先将数据传递到标准 I/O 缓冲，然后将数据移动到套接字输出缓冲，最后将字符串发送到对方主机。

设置缓冲的主要目的是为了提高性能。从以下两点可以说明性能的提高：

- 传输的数据量
- 数据向输出缓冲移动的次数。

比较 1 个字节的数据发送 10 次的情况和 10 个字节发送 1 次的情况。发送数据时，数据包中含有头信息。头信与数据大小无关，是按照一定的格式填入的。假设头信息占 40 个字节，需要传输的数据量也存在较大区别：

- 1 个字节 10 次：40*10=400 字节
- 10个字节 1 次：40*1=40 字节。



**标准 I/O 函数和系统函数之间的性能对比**

下面是利用系统函数的示例：

```c++
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#define BUF_SIZE 3
using namespace std;

int main(int argc, char *argv[]){
    int fd1, fd2, len;
    char buf[BUF_SIZE];

    fd1 = open("news.txt", O_RDONLY);
    fd2 = open("cpy.txt", O_WRONLY | O_CREAT | O_TRUNC);

    //使用write函数和readf函数来复制文件中的内容
    while (len = read(fd1, buf, sizeof(buf)))
    {
        write(fd2, buf, len);
    }

    close(fd1), close(fd2);
    return 0;
}
```

下面是使用标准 I/O 函数复制文件

```c++
#include <iostream>
using namespace std;
#define BUF_SIZE 3

int main(int argc, char *argv[]){
    char buf[BUF_SIZE];
    FILE *fp1 = fopen("news.txt", "r");
    FILE *fp2 = fopen("cpy.txt", "w");

    while (fgets(buf, BUF_SIZE, fp1) != NULL){
        fputs(buf, fp2);
    }

    fclose(fp1), fclose(fp2);
    return 0;
}
```

对于以上两个代码进行测试，明显基于标准 I/O 函数的代码跑的更快



**标准 I/O 函数的几个缺点**

标准 I/O 函数存在以下几个缺点：

- 不容易进行双向通信
- 有时可能频繁调用 fflush 函数
- 需要以 FILE 结构体指针的形式返回文件描述符。





### 15.2 使用标准I/O函数

创建套接字时返回的是文件描述符，为了使用标准I/O函数，只能将其转换为FILE结构体指针。



**利用`fdopen`函数转换为FILE结构体指针**

可以通过`fdopen`函数将创建套接字时返回的文件描述符转换为标准I/O函数中使用的FILE结构体指针。

```c++
#include <sdtio.h>

FILE * fdopen(int fildes, const char * mode)
```

上述函数的第二个参数和`fopen`函数中的打开模式相同。例如："r"、"w"、"rb"、"wb"

```c++
#include <stdio.h>
#include <iostream>
#include <fcntl.h>
using namespace std;

int main(){
    FILE *fp;
    int fd = open("data.dat", O_WRONLY | O_CREAT | O_TRUNC);    //利用文件描述符来操作文件
    if (fd == -1){
        cout << "File open error" << endl;
        return -1;
    }

    fp = fdopen(fd, "w");       //将文件描述符转换为对应的FILE指针
    fputs("Network CPP programming\n", fp);
    fclose(fp);
    return 0;
}
```



**利用`fileno`函数转换为文件描述符**

```c++
#include <stdio.h>

int fileno(FILE *stream);
```



```c++
#include <iostream>
#include <fcntl.h>
#include <stdio.h>
using namespace std;

int main(int argc, char *argv[]){
    int fd = open("open.dat", O_WRONLY | O_CREAT | O_TRUNC);
    if (fd == -1){
        cout << "File open error" << endl;
        return -1;
    }

    cout << "First file descriptor : " << fd << endl;
    FILE *fp = fdopen(fd, "w");
    fputs("Network CPP programming\n", fp);
    cout << "Second file descriptor : " << fileno(fp) << endl;

    return 0;
}
```

输出

```c++
First file descriptor : 3
Second file descriptor : 3
```





### 15.3 基于套接字的标准I/O函数使用

> 把第四章的回声客户端和回声服务端的内容改为基于标准 I/O 函数的数据交换形式。

服务端 echo_stdserv.cpp

```c++
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
using namespace std;
#define BUF_SIZE 1024

int main(int argc, char* argv[]){
    int serv_sock, clnt_sock, size = 128;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_size;
    char buf[BUF_SIZE];

    if (argc != 2){
        cout << "Usage : " << argv[0] << "<port>" << endl;
        return -1;
    }


    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1){
        cout << "server socket create error" << endl;
        return -1;
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

        //使用FILE结构体指针来交换数据，将对应的文件描述符转换为FILE指针来进行操作，可以提高传输的速度
        FILE *readfp = fdopen(clnt_sock, "r");
        FILE *writefp = fdopen(clnt_sock, "w");

        while (!feof(readfp)){
            fgets(buf, BUF_SIZE, readfp);   //从readfp所指的文件中读取BUF_SIZE个字节的数据到buf中
            fputs(buf, writefp);            //将buf中的数据写入到writefp所指的文件中
            fflush(writefp);
        }

        fclose(readfp);
        fclose(writefp);                   //关闭readfp和writefp之后，对应的文件描述符也会被关闭
    }

    close(serv_sock);
    return 0;
}
```

客户端 echo_stdclient.cpp

```c++
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;
#define BUF_SIZE 1024

int main(int argc, char* argv[]){
    int clnt_sock;
    struct sockaddr_in serv_addr;
    char buf[BUF_SIZE];

    if (argc != 3){
        cout << "Usage : <IP> <port>" << endl;
        return -1;
    }

    clnt_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (clnt_sock == -1){
        cout << "server socket create error" << endl;
        return -1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(clnt_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        cout << "Connect to server error" << endl;
        return -1;
    }

    FILE *readfp = fdopen(clnt_sock, "r");
    FILE *writefp = fdopen(clnt_sock, "w");

    while (1){
        //客户端从标准输入中获取数据
        cout << "Input message (Q to quit)" << endl;
        cin.getline(buf, BUF_SIZE);

        if (strcmp(buf, "Q") == 0)  break;

        //利用FILE指针来读取文件
        fputs(buf, writefp);
        fflush(writefp);

        fgets(buf, BUF_SIZE, readfp);

        cout << "Message form server : " << buf << endl;
    }

    fclose(readfp), fclose(writefp);
    return 0;
}
```



### 15.4 习题

1. **请说明标准 I/O 的 2 个优点。他为何拥有这 2 个优点？**

   答：①具有很高的移植性②有良好的缓冲提高性能。因为这些函数是由 ANSI C 标准定义的。适合所有编程领域。

2. **利用标准 I/O 函数传输数据时，下面的说法是错误的**：

   > 调用 fputs 函数传输数据时，调用后应立即开始发送！

   **为何上述说法是错误的？为达到这种效果应该添加哪些处理过程？**

   答：只是传输到了缓冲中，应该利用 fflush 来刷新缓冲区。







## 第16章 关于I/O流分离的其他内容

### 16.1 分离 I/O 流

「分离 I/O 流」是一种常用表达。有 I/O 工具可区分二者，无论采用哪种方法，都可以认为是分离了 I/O 流。



**2次 I/O 流分离**

之前有两种分离方法：

- 第一种是第 10 章的「TCP I/O 过程」分离。通过调用 fork 函数复制出一个文件描述符，以区分输入和输出中使用的文件描述符。虽然文件描述符本身不会根据输入和输出进行区分，但我们分开了 2 个文件描述符的用途，因此，这也属于「流」的分离。

  ```c++
  if (pid == 0){
  	write_routine(clnt_sock, buf);
  }else{
  	read_routine(clnt_sock, buf);
  }
  ```

- 第二种分离是在第 15 章。通过 2 次 fdopen 函数的调用，创建读模式 FILE 指针（FILE 结构体指针）和写模式 FILE 指针。

  ```c++
  FILE *readfp = fdopen(clnt_sock, "r");
  FILE *writefp = fdopen(clnt_sock, "w");
  ```

- 换言之，我们分离了输入工具和输出工具，因此也可视为「流」的分离。下面是分离的理由。



**分离「流」的好处**

首先是第 10 章「流」的分离目的：

- 通过分开输入过程（代码）和输出过程降低实现难度
- 与输入无关的输出操作可以提高速度

下面是第 15 章「流」分离的目的：

- 为了将 FILE 指针按读模式和写模式加以区分
- 可以通过区分读写模式降低实现难度
- 通过区分 I/O 缓冲提高缓冲性能



**「流」分离带来的 EOF 问题**

第 7 章介绍过 EOF 的传递方法和半关闭的必要性。有一个语句：

```
shutdown(sock,SHUT_WR);
```

当时说过调用 shutdown 函数的基于半关闭的 EOF 传递方法。第十章的 [echo_mpclient.cpp]添加了半关闭的相关代码。但是还没有讲采用` fdopen` 函数怎么半关闭。那么是否是通过 ` fclose` 函数关闭流呢？我们先试试

服务端sep_serv.cpp

```c++
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
using namespace std;
#define BUF_SIZE 1024

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
        cout << "server create socker error" << endl;
        return -1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        cout << "server bind socker error" << endl;
        return -1;
    }

    if (listen(serv_sock, 5) == -1){
        cout << "server listen socker error" << endl;
        return -1;
    }

    clnt_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_size);
    if (clnt_sock == -1){
        cout << "server accept client error" << endl;
        return -1;
    }

    FILE *readfp = fdopen(clnt_sock, "r");
    FILE *writefp = fdopen(clnt_sock, "w");

    //验证使用FILE指针的I/O分离是否能进行半关闭
    fputs("FROM SERVER : Hi~ client ? \n", writefp);
    fputs("I love all of the world \n", writefp);
    fputs("You are awesome! \n", writefp);
    fflush(writefp);

    fclose(writefp);    //关闭写入方向的FILE指针

    fgets(buf, BUF_SIZE, readfp);   //利用readfp指针读取来自客户端的感谢信息
    cout << buf << endl;
    fclose(readfp);

    return 0;
}
```

客户端sep_client.cpp

```c++
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
using namespace std;
#define BUF_SIZE 1024

int main(int argc, char *argv[]){
    if (argc != 3){
        cout << "Usage : <IP> <port>" << endl;
        return -1;
    }

    int clnt_sock;
    struct sockaddr_in serv_addr;
    char buf[BUF_SIZE];

    clnt_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (clnt_sock == -1){
        cout << "client create socket error" << endl;
        return -1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(clnt_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        cout << "client connect error" << endl;
        return -1;
    }

    FILE *readfp = fdopen(clnt_sock, "r");
    FILE *writefp = fdopen(clnt_sock, "w");

    while (1){
        //读取来自服务端的信息并输出
        if (fgets(buf, BUF_SIZE, readfp) == NULL)
            break;
        cout << buf;
        fflush(stdout);
    }

    //向readfp指针写入感谢信息
    fputs("FROM CLIENT : Thank you! \n", writefp);
    fflush(writefp);
    
    fclose(readfp), fclose(writefp);
    return 0;
}
```

客户端输出：

```
FROM SERVER : Hi~ client ? 
I love all of the world 
You are awesome!
```

服务端中并非没有输出





### 16.2 文件描述符的复制和半关闭

**终止「流」时无法半关闭原因**

下面的图描述的是服务端代码中的两个FILE 指针、文件描述符和套接字中的关系。

![img](TCPIP网络编程.assets/68747470733a2f2f692e6c6f6c692e6e65742f323031392f30312f33302f356335313231646138393935352e706e67.png)

从图中可以看到，两个指针都是基于同一文件描述符创建的。因此，针对于任何一个 FILE 指针调用 fclose 函数都会关闭文件描述符，如图所示：

![img](TCPIP网络编程.assets/68747470733a2f2f692e6c6f6c692e6e65742f323031392f30312f33302f356335313232343035313830322e706e67.png)

从图中看到，销毁套接字时再也无法进行数据交换。那如何进入可以进入但是无法输出的半关闭状态呢？如下图所示：

![img](TCPIP网络编程.assets/68747470733a2f2f692e6c6f6c692e6e65742f323031392f30312f33302f356335313232613435633566312e706e67.png)

只需要创建 FILE 指针前先复制文件描述符即可。复制后另外创建一个文件描述符，然后利用各自的文件描述符生成读模式的 FILE 指针和写模式的 FILE 指针。这就为半关闭创造好了环境，因为套接字和文件描述符具有如下关系：

> 销毁所有文件描述符候才能销毁套接字

也就是说，针对写模式 FILE 指针调用 fclose 函数时，只能销毁与该 FILE 指针相关的文件描述符，无法销毁套接字，如下图：

![img](TCPIP网络编程.assets/68747470733a2f2f692e6c6f6c692e6e65742f323031392f30312f33302f356335313233616437646633312e706e67.png)

那么调用 fclose 函数候还剩下 1 个文件描述符，因此没有销毁套接字。那此时的状态是否为半关闭状态？不是！只是准备好了进入半关闭状态，而不是已经进入了半关闭状态。仔细观察，还剩下一个文件描述符。而该文件描述符可以同时进行 I/O 。因此，不但没有发送 EOF ，而且仍然可以利用文件描述符进行输出。



**复制文件描述符**

与调用 fork 函数不同，调用 fork 函数将复制整个进程，此处讨论的是同一进程内完成对完成描述符的复制。如图：

![img](TCPIP网络编程.assets/68747470733a2f2f692e6c6f6c692e6e65742f323031392f30312f33302f356335313235373963343562362e706e67.png)

复制完成后，两个文件描述符都可以访问文件，但是编号不同。



**dup & dup2**

文件描述符的复制方法

```c++
#include <unistd.h>

int dup(int fildes);
int dup2(int fildes, int fildes2);
```

这些函数可以用于创建一个新的文件描述符，它是现有文件描述符的副本，然后使用这个新的文件描述符来访问相同的文件或管道。

-  `dup()`函数接受一个整数参数，它是一个现有文件描述符。`dup()`函数返回一个新的文件描述符，该描述符指向与原始描述符相同的文件或管道。新描述符是系统中可用的最小整数描述符，即未使用的最小整数。

-  `dup2()`函数与`dup()`函数类似，但它接受两个参数。第一个参数是现有文件描述符，第二个参数是新文件描述符的值。如果第二个参数是一个有效的文件描述符，`dup2()`将使用该描述符，否则它将创建一个新的描述符，其值等于第二个参数。

```c++
#include <iostream>
#include <stdio.h>
#include <unistd.h>
using namespace std;

int main(){
    int cfd1, cfd2;
    char str1[] = "Hi~ \n";
    char str2[] = "It's a nice day \n";

    cfd1 = dup(1);      //使用dup复制文件描述符
    cfd2 = dup2(1, 7);  //使用dup2来制定复制后文件符的数值

    cout << "fd1 : " << cfd1 << " fd2 : " << cfd2 << endl;
    write(cfd1, str1, sizeof(str1));
    write(cfd2, str2, sizeof(str2));

    close(cfd1), close(cfd2);		//关闭复制的文件描述符
    write(1, str1, sizeof(str1));	//但是文件描述符1未被关闭，所以还可以进行输出
    close(1);						//关闭文件描述符1
    write(1, str2, sizeof(str2));	//由于文件描述符1已经被关闭，对应的套接字所有的文件描述符都被关闭之后会将相应的套接字也关闭

    return 0;
}
```



**复制文件描述符后“流”的分离**

```c++
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
using namespace std;
#define BUF_SIZE 1024

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
        cout << "server create socker error" << endl;
        return -1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        cout << "server bind socker error" << endl;
        return -1;
    }

    if (listen(serv_sock, 5) == -1){
        cout << "server listen socker error" << endl;
        return -1;
    }

    clnt_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_size);
    if (clnt_sock == -1){
        cout << "server accept client error" << endl;
        return -1;
    }

    FILE *readfp = fdopen(clnt_sock, "r");
    FILE *writefp = fdopen(clnt_sock, "w");

    //验证使用FILE指针的I/O分离是否能进行半关闭
    fputs("FROM SERVER : Hi~ client ? \n", writefp);
    fputs("I love all of the world \n", writefp);
    fputs("You are awesome! \n", writefp);21
    fflush(writefp);

    fclose(writefp);    //关闭写入方向的FILE指针

    fgets(buf, BUF_SIZE, readfp);   //利用readfp指针读取来自客户端的感谢信息
    cout << buf << endl;
    fclose(readfp);

    return 0;
}
```

编译并运行服务端、客户端代码

服务端的输出

```c++
FROM CLIENT : Thank you! 
```



### 16.3 习题

1. **下列关于 FILE 结构体指针和文件描述符的说法错误的是**？

   答：以下加粗内容代表说法正确。

   1. 与 FILE 结构体指针相同，文件描述符也分输入描述符和输出描述符

   2. 复制文件描述符时将生成相同值的描述符，可以通过这 2 个描述符进行 I/O

   3. **可以利用创建套接字时返回的文件描述符进行 I/O ，也可以不通过文件描述符，直接通过 FILE 结构体指针完成**

   4. **可以从文件描述符生成 FILE 结构体指针，而且可以利用这种 FILE 结构体指针进行套接字 I/O**

   5. 若文件描述符为读模式，则基于该描述符生成的 FILE 结构体指针同样是读模式；若文件描述符为写模式，则基于该描述符生成的 FILE 结构体指针同样是写模式

      

2. **EOF 的发送相关描述中错误的是**？

   答：以下加粗内容代表说法正确。

   1. 终止文件描述符时发送 EOF
   2. **即使未完成终止文件描述符，关闭输出流时也会发送 EOF**
   3. 如果复制文件描述符，则包括复制的文件描述符在内，所有文件描述符都终止时才会发送 EOF
   4. **即使复制文件描述符，也可以通过调用 shutdown 函数进入半关闭状态并发送 EOF**





## 第17章 优于select的epoll ❤

### 17.1 epoll 理解及应用

select 复用方法由来已久，因此，利用该技术后，无论如何优化程序性能也无法同时介入上百个客户端。这种 select 方式并不适合以 web 服务器端开发为主流的现代开发环境，所以需要学习 Linux 环境下的 epoll



**基于 select 的 I/O 复用技术速度慢的原因**

> select函数是一种I/O多路复用技术，用于同时监视多个文件描述符的状态。尽管select函数可以用于同时监视多个文件描述符，但它在实际应用中可能会受到一些限制，导致它的性能相对较慢。以下是一些可能导致select函数性能较慢的原因❤：
>
> 1. **每次调用select都需要将监视列表从用户空间拷贝到内核空间，这个过程可能会带来较大的开销。对于大量文件描述符的情况下，这种开销会显得尤为明显。** `temp = reads`
> 2. **select函数只能同时监视一定数量的文件描述符，这个数量通常被限制在1024个左右。如果需要监视更多的文件描述符，则需要通过多次调用select函数来完成，这会导致额外的开销**。
> 3. **select函数返回时需要遍历整个监视列表，以确定哪些文件描述符发生了事件。如果监视列表非常大，这个过程会非常耗时，从而影响整个系统的性能。**
> 4. **select函数支持的事件类型有限，只能监视读、写和异常事件，而不能监视其他类型的事件，如定时器事件等。如果需要监视其他类型的事件，就需要使用其他技术，如epoll或kqueue。**
>
> 总的来说，虽然select函数是一种比较常见的I/O多路复用技术，但它在某些场景下可能会受到一些限制，导致其性能相对较慢。因此，在实际应用中，需要根据具体情况选择最适合的I/O多路复用技术。

第 12 章实现了基于 select 的 I/O 复用技术服务端，其中有不合理的设计如下：

- 调用 select 函数后常见的针对所有文件描述符的循环语句

  ```c++
  for (int i = 0; i <= fd_max; i++)	//54 lines
      if (FD_ISSET(i, &temp))		    //56 lines
  ```

- 每次调用 select 函数时都需要向该函数传递监视对象信息

  ```c++
  temp = reads;	//将监视列表从用户空间拷贝的操作系统的内核空间
  ```

上述两点可以从 [echo_selectserv.cpp] 得到确认，调用 select 函数后，并**不是把发生变化的文件描述符单独集中在一起，而是通过作为监视对象的 `fd_set` 变量的变化，找出发生变化的文件描述符（54,56行），因此无法避免针对所有监视对象的循环语句**。而且，作为监视对象的 `fd_set` 会发生变化，所以调用 select 函数前应该复制并保存原有信息，并在每次调用 select 函数时传递新的监视对象信息。

**select 性能上最大的弱点是：每次传递监视对象信息**，准确的说，select 是监视套接字变化的函数。而套接字是操作系统管理的，所以 select 函数要借助操作系统才能完成功能。select 函数的这一缺点可以通过如下方式弥补：

> 仅向操作系统传递一次监视对象，监视范围或内容发生变化时只通知发生变化的事项

这样就无需每次调用 select 函数时都向操作系统传递监视对象信息，但是前提操作系统支持这种处理方式。Linux 的支持方式是 epoll ，Windows 的支持方式是 IOCP。



**select 也有优点**

select 的兼容性比较高，这样就可以支持很多的操作系统，不受平台的限制，满足以下两个条件使可以使用 select 函数：

- 服务器端接入者少
- 程序应该具有兼容性



**实现 epoll 时必要的函数和结构体**

能够克服 select 函数缺点的 epoll 函数具有以下优点，这些优点正好与之前的 select 函数缺点相反。

- **无需编写以监视状态变化为目的的针对所有文件描述符的循环语句**
- **调用对应于 select 函数的 epoll_wait 函数时无需每次传递监视对象信息。**

下面是 epoll 函数的功能：

- **epoll_create：创建保存 epoll 文件描述符的空间**							`fd_set reads;`
- **epoll_ctl：用于添加、修改或删除需要监听的文件描述符**                `FD_SET、FD_CLR`
- **epoll_wait：与 select 函数类似，等待文件描述符发生变化**           `select`

select 函数中为了保存监视对象的文件描述符，直接声明了 fd_set 变量，但 epoll 方式下的操作系统负责保存监视对象文件描述符，因此需要向操作系统请求创建保存文件描述符的空间，此时用的函数就是 epoll_create 。

此外，为了添加和删除监视对象文件描述符，select 方式中需要 FD_SET、FD_CLR 函数。但在 epoll 方式中，通过 epoll_ctl 函数请求操作系统完成。最后，select 方式下调用 select 函数等待文件描述符的变化，而 epoll 调用 epoll_wait 函数。还有，select 方式中通过 fd_set 变量查看监视对象的状态变化，而 epoll 方式通过如下结构体 epoll_event 将发生变化的文件描述符单独集中在一起。

```c++
struct epoll_event
{
    __uint32_t events;		// Epoll events
    epoll_data_t data;		// User data variable
};

typedef union epoll_data {
    void *ptr;
    int fd;
    __uint32_t u32;
    __uint64_t u64;
} epoll_data_t;
```

**声明足够大的 `epoll_event` 结构体数组后，传递给 `epoll_wait` 函数时，发生变化的文件描述符信息将被填入数组。因此，无需像 select 函数那样针对所有文件描述符进行循环。**



 **epoll_create**

epoll 是从 Linux 的 2.5.44 版内核开始引入的。通过以下命令可以查看 Linux 内核版本：

```c++
cat /proc/sys/kernel/osrelease
```

下面是 epoll_create 函数的原型：

```c++
#include <sys/epoll.h>
int epoll_create(int size);
/*
成功时返回 epoll 的文件描述符，失败时返回 -1
size：epoll 实例的大小
*/
```

调用 epoll_create 函数时创建的文件描述符保存空间称为「epoll 例程」，但有些情况下名称不同，需要稍加注意。通过参数 size 传递的值决定 epoll 例程的大小，但该值只是向操作系统提出的建议。换言之，size 并不用来决定 epoll 的大小，而仅供操作系统参考。**该函数会创建一个`epoll`实例，返回一个整数值作为该实例的文件描述符，可以用于后续的事件监听和控制。**

> Linux 2.6.8 之后的内核将完全忽略传入 epoll_create 函数的 size 函数，因此内核会根据情况调整 epoll 例程大小。但是本书程序并没有忽略 size

epoll_create 函数创建的资源与套接字相同，也由操作系统管理。因此，该函数和创建套接字的情况相同，也会返回文件描述符，也就是说返回的文件描述符主要用于区分 epoll 例程。需要终止时，与其他文件描述符相同，也要调用 close 函数



**epoll_ctl**

**生成例程后，应在其内部注册监视对象文件描述符，此时使用 epoll_ctl 函数**。类似于FD_SET、FD_CLR

```c++
#include <sys/epoll.h>
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
/*
成功时返回 0 ，失败时返回 -1
epfd：用于注册监视对象的 epoll 例程的文件描述符
op：用于指定监视对象的添加、删除或更改等操作
fd：需要注册的监视对象文件描述符
event：监视对象的事件类型
*/
```

与其他 epoll 函数相比，该函数看起来有些复杂，但通过调用语句就很容易理解，假设按照如下形式调用 epoll_ctl 函数：

```c++
epoll_ctl(A, EPOLL_CTL_ADD, B, C);
```

第二个参数 EPOLL_CTL_ADD 意味着「添加」，上述语句有如下意义：

> epoll 例程 A 中注册文件描述符 B ，主要目的是为了监视参数 C 中的事件

再介绍一个调用语句：

```c++
epoll_ctl(A, EPOLL_CTL_DEL, B, NULL);
```

上述语句中第二个参数意味着「删除」，有以下含义：

> 从 epoll 例程 A 中删除文件描述符 B

从上述示例中可以看出，从监视对象中删除时，不需要监视类型，因此向第四个参数可以传递为 NULL

下面是第二个参数的含义：

- **EPOLL_CTL_ADD：将文件描述符注册到 epoll 例程**
- **EPOLL_CTL_DEL：从 epoll 例程中删除文件描述符**
- **EPOLL_CTL_MOD：更改注册的文件描述符的关注事件发生情况**

epoll_event 结构体用于保存事件的文件描述符结合。但也可以在 epoll 例程中注册文件描述符时，用于注册关注的事件。该函数中 epoll_event 结构体的定义并不显眼，因此通过调用语句说明该结构体在 epoll_ctl 函数中的应用。

```c++
struct epoll_event event;
...
event.events = EPOLLIN;		//发生需要读取数据的情况时
event.data.fd = sockfd;
epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &event);
...
```

上述代码将 epfd 注册到 epoll 例程 epfd 中，并在需要读取数据的情况下产生相应事件。接下来给出 epoll_event 的成员 events 中可以保存的常量及所指的事件类型。

- **EPOLLIN：需要读取数据的情况**
- EPOLLOUT：输出缓冲为空，可以立即发送数据的情况
- EPOLLPRI：收到 OOB 数据的情况
- EPOLLRDHUP：断开连接或半关闭的情况，这在边缘触发方式下非常有用
- EPOLLERR：发生错误的情况
- **EPOLLET：以边缘触发的方式得到事件通知**
- EPOLLONESHOT：发生一次事件后，相应文件描述符不再收到事件通知。因此需要向 epoll_ctl 函数的第二个参数传递 EPOLL_CTL_MOD ，再次设置事件。

可通过位或运算同时传递多个上述参数。



**epoll_wait**

下面是函数原型：

```c++
#include <sys/epoll.h>

int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
/*
成功时返回发生事件的文件描述符个数，失败时返回 -1
epfd : 表示事件发生监视范围的 epoll 例程的文件描述符
events : 保存发生事件的文件描述符集合的结构体地址值
maxevents : 第二个参数中可以保存的最大事件数
timeout : 以 1/1000 秒为单位的等待时间，传递 -1 时，一直等待直到发生事件
*/
```

该函数调用方式如下。需要注意的是，第二个参数所指缓冲需要动态分配。

```c++
int event_cnt;
struct epoll_event *ep_events;
...
ep_events = malloc(sizeof(struct epoll_event)*EPOLL_SIZE);	//EPOLL_SIZE是宏常量
...
event_cnt = epoll_wait(epfd, ep_events, EPOLL_SIZE, -1);
...
```

调用函数后，返回发生事件的文件描述符个数，同时在第二个参数指向的缓冲中保存发生事件的文件描述符集合。因此，无需像 select 一样插入针对所有文件描述符的循环。



**基于epoll的回声服务端**

服务端echo_epollserv代码：

```c++
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
                clnt_size = sizeof(clnt_sock);
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
```





### 17.2 条件触发和边缘触发

学习 epoll 时要了解条件触发（Level Trigger）和边缘触发（Edge Trigger）。

> 条件触发是一种基于事件处理的方式，它可以处理任何类型的事件，包括定时器事件、网络事件、IO事件等等。在条件触发模式下，当条件满足时，事件处理函数会被触发执行。因此，条件触发可以灵活处理不同类型的事件，但它需要不断地检查条件是否满足，从而可能会产生一定的性能开销。
>
> 边缘触发是一种高效的事件处理方式，它只在事件发生时才会触发事件处理函数，因此可以减少不必要的事件处理。在边缘触发模式下，当IO事件发生时，操作系统会通知应用程序，并且只会通知一次，而不会重复通知。这种方式可以提高事件处理的效率，避免了不必要的事件处理。
>
> 总的来说，**条件触发和边缘触发都可以用于事件处理，但是条件触发更加通用，可以处理任何类型的事件，但需要不断地检查条件是否满足，可能会产生一定的性能开销；而边缘触发更加高效，只有在事件发生时才会被触发，可以减少不必要的事件处理，提高事件处理的效率。选择哪种方式取决于具体的应用场景。**



**条件触发和边缘触发的区别在于发生事件的时间点**

**条件触发的特性**：

> 条件触发方式中，只要输入缓冲有数据就会一直通知该事件

例如，服务器端输入缓冲收到 50 字节数据时，服务器端操作系统将通知该事件（注册到发生变化的文件描述符）。但是服务器端读取 20 字节后还剩下 30 字节的情况下，仍会注册事件。也就是说，条件触发方式中，只要输入缓冲中还剩有数据，就将以事件方式再次注册。

**边缘触发特性**：

> 边缘触发中输入缓冲收到数据时仅注册 1 次该事件。即使输入缓冲中还留有数据，也不会再进行注册。



**掌握条件触发的事件特性**

下面代码修改自 [echo_epollserv.cpp]。epoll 默认以条件触发的方式工作，因此可以通过该示例验证条件触发的特性。

```c++
#define BUF_SIZE 4      //减少缓冲大小为了阻止服务器端一次性读取接收的数据

cout << "return epoll_wait" << endl;
```

上面的代码把调用 read 函数时使用的缓冲大小缩小到了 4 个字节，插入了验证 epoll_wait 调用次数的验证函数。减少缓冲大小是为了阻止服务器端一次性读取接收的数据。换言之，调用 read 函数后，输入缓冲中仍有数据要读取，而且会因此注册新的事件并从 epoll_wait 函数返回时将循环输出「return epoll_wait」字符串。

服务端输出：

```c++
return epoll wait
connect client : 5
return epoll wait
return epoll wait
return epoll wait
return epoll wait
connect client : 6
return epoll wait
return epoll wait
return epoll wait
return epoll wait
return epoll wait
```

客户端1：

```c++
connected ...
Please input message (Q to quit): 
how are you
received from server : how 
Please input message (Q to quit): 
```

客户端2：

```c++
connected ...
Please input message (Q to quit): 
what are you doing
received from server : what
Please input message (Q to quit): 
```

从结果可以看出，每当收到客户端数据时，都会注册该事件，并因此调用 epoll_wait 函数。



下面的代码是修改后的**边缘触发**方式的代码，仅仅是把上面的代码改为：

```c++
  event.events = EPOLLIN | EPOLLET;
```

服务端的输出：

```c++
return epoll wait
connect client : 5
return epoll wait
return epoll wait
connect client : 6
return epoll wait
```

客户端1：

```c++
connected ...
Please input message (Q to quit): 
how are you
received from server : how 
Please input message (Q to quit):
```

客户端2：

```c++
connected ...
Please input message (Q to quit): 
It's my life
received from server : It's
Please input message (Q to quit): 
```

从上面的例子看出，接收到客户端的消息时，只输出一次「return epoll_wait」字符串，这证明仅注册了一次事件。

**select 模型是以条件触发的方式工作的**。



**边缘触发的服务器端必知的两点**

- 通过 errno 变量验证错误原因
- 为了完成非阻塞（Non-blocking）I/O ，更改了套接字特性。

Linux 套接字相关函数一般通过 -1 通知发生了错误。虽然知道发生了错误，但仅凭这些内容无法得知产生错误的原因。因此，为了在发生错误的时候提额外的信息，Linux 声明了如下全局变量：

```c++
int errno;
```

为了访问该变量，需要引入 `error.h` 头文件，因此此头文件有上述变量的 extren 声明。另外，每种函数发生错误时，保存在 errno 变量中的值都不同。

> read 函数发现输入缓冲中没有数据可读时返回 -1，同时在 errno 中保存 EAGAIN 常量

下面是 Linux 中提供的改变和更改文件属性的办法：

```c++
#include <fcntl.h>

int fcntl(int fields, int cmd, .../* arg */);
/*
成功时返回 cmd 参数相关值，失败时返回 -1
filedes : 属性更改目标的文件描述符
cmd : 表示函数调用目的
arg是可选的操作参数，具体取决于cmd的值
*/
```

从上述声明可以看出 fcntl 有可变参数的形式。如果向第二个参数传递 F_GETFL ，可以获得第一个参数所指的文件描述符属性（int 型）。反之，如果传递 F_SETFL ，可以更改文件描述符属性。若希望将文件（套接字）改为非阻塞模式，需要如下 2 条语句。

```c++
int flag = fcntl(fd, F_GETFL, 0);		//获取fd所指的文件描述符属性

fcntl(fd, F_SETFL, flag | O_NONBLOCK);	//将fd所指的文件描述符属性更改为非阻塞模式
```

通过第一条语句，获取之前设置的属性信息，通过第二条语句在此基础上添加非阻塞 O_NONBLOCK 标志。调用 read/write 函数时，无论是否存在数据，都会形成非阻塞文件（套接字）。

fcntl 函数的适用范围很广：

> - 设置文件描述符标志：通过设置文件描述符标志，可以指定文件的属性，例如是否为非阻塞文件、是否关闭文件执行期间的信号等。使用`F_GETFL`参数获取文件描述符标志，使用`F_SETFL`参数设置文件描述符标志。
> - 获取或设置文件锁：文件锁定可以防止多个进程同时访问文件或文件的某个部分。`fcntl`函数提供了获取或设置文件锁定的功能，使用`F_GETLK`参数获取文件锁定信息，使用`F_SETLK`和`F_SETLKW`参数设置文件锁定。
> - 获取或设置记录锁：记录锁用于在文件中的单个记录或数据块上执行加锁和解锁操作。`fcntl`函数提供了获取或设置记录锁的功能，使用`F_GETLK`参数获取记录锁信息，使用`F_SETLK`和`F_SETLKW`参数设置记录锁。



**实现边缘触发回声服务器端**

通过 errno 确认错误的原因是：边缘触发方式中，接收数据仅注册一次该事件。

因为这种特点，一旦发生输入相关事件时，就应该读取输入缓冲中的全部数据。因此需要验证输入缓冲是否为空。

> read 函数返回 -1，变量 errno 中的值变成 EAGAIN 时，说明没有数据可读。

既然如此，为什么要将套接字变成非阻塞模式？边缘触发条件下，以阻塞方式工作的 read & write 函数有可能引起服务端的长时间停顿。因此，边缘触发方式中一定要采用非阻塞 read & write 函数。

服务端输出：

```c++
return epoll wait
connect client : 5
return epoll wait
return epoll wait
connect client : 6
return epoll wait
```

客户端1：

```c++
connected ...
Please input message (Q to quit): 
how are you
received from server : how are you
Please input message (Q to quit):
```

客户端2：

```c++
connected ...
Please input message (Q to quit): 
It's my life 
received from server : It's my life
Please input message (Q to quit): 
```



 **条件触发和边缘触发孰优孰劣**

> 条件触发和边缘触发是 Linux 中使用的两种不同的事件触发方式。
>
> 条件触发是指在事件就绪时，只要相应的条件成立，就会触发一次事件处理。例如，使用条件触发的 I/O 处理，如果读取缓冲区中还有数据，那么就会一直通知该事件，直到缓冲区为空。条件触发的优点是处理简单，容易实现；缺点是可能会出现饥饿的情况，即一些事件因为条件不满足而得不到处理，影响程序的响应性能。
>
> 边缘触发是指只有当事件状态发生变化时，才会触发一次事件处理。例如，使用边缘触发的 I/O 处理，**在读取缓冲区数据时，只有当缓冲区由空变成非空，或者由非空变成空时**，才会触发一次事件处理。边缘触发的优点是不会出现饥饿的情况，保证所有事件都得到及时处理；缺点是处理复杂，需要对事件状态进行判断，实现难度较大。
>
> 因此，条件触发和边缘触发各有优缺点，根据具体的场景和要求进行选择。一般来说，对于一些需要及时响应的事件，比如**网络通信和多线程同步等场景，推荐使用边缘触发方式**；对于一些对及时性要求不高的事件，例如文件读写等场景，可以考虑使用条件触发方式。

边缘触发方式可以做到这点：

> 可以分离接收数据和处理数据的时间点！

下面是边缘触发的图

![img](TCPIP网络编程.assets/68747470733a2f2f692e6c6f6c692e6e65742f323031392f30322f30312f356335343231653362336632622e706e67.png)

运行流程如下：

- 服务器端分别从 A B C 接收数据
- 服务器端按照 A B C 的顺序重新组合接收到的数据
- 组合的数据将发送给任意主机。

为了完成这个过程，如果可以按照如下流程运行，服务端的实现并不难：

- 客户端按照 A B C 的顺序连接服务器，并且按照次序向服务器发送数据
- 需要接收数据的客户端应在客户端 A B C 之前连接到服务器端并等待

但是实际情况中可能是下面这样：

- 客户端 C 和 B 正在向服务器发送数据，但是 A 并没有连接到服务器
- 客户端 A B C 乱序发送数据
- 服务端已经接收到数据，但是要接收数据的目标客户端并没有连接到服务器端。

因此，即使输入缓冲收到数据，服务器端也能决定读取和处理这些数据的时间点，这样就给服务器端的实现带来很大灵活性。



### 17.3 习题

1. 利用 select 函数实现服务器端时，代码层面存在的两个缺点是？

   答：①调用 select 函数后常见的针对所有文件描述符的循环语句

   ​	   ②每次调用 select 函数时都要传递监视对象信息。

   

2. 无论是 select 方式还是 epoll 方式，都需要将监视对象文件描述符信息通过函数调用传递给操作系统。请解释传递该信息的原因。

   答：文件描述符是由操作系统管理的，所以必须要借助操作系统才能完成。

   

3. select 方式和 epoll 方式的最大差异在于监视对象文件描述符传递给操作系统的方式。请说明具体差异，并解释为何存在这种差异。

   答：**select 函数每次调用都要传递所有的监视对象信息，而 epoll 函数仅向操作系统传递 1 次监视对象，监视范围或内容发生变化时只通知发生变化的事项。select 采用这种方法是为了保持兼容性。**

   

4. 虽然 epoll 是 select 的改进方案，但 select 也有自己的优点。在何种情况下使用 select 更加合理。

   答：①服务器端接入者少

   ​	   ②程序应具有兼容性。

   > 在使用 epoll 时，可以选择条件触发（Level-Triggered，简称 LT）或边缘触发（Edge-Triggered，简称 ET）方式来工作。
   >
   > - 条件触发方式（LT）：当内核缓冲区中有数据可读或可写时，就会不断通知程序，直到应用程序读取或写入完所有数据。如果应用程序没有读取或写入所有数据，下次触发时会再次通知程序。这种方式**不会漏掉任何数据**，但是会频繁通知程序，可能会造成一定的开销。
   > - 边缘触发方式（ET）：仅在**输入缓冲区状态发生变化时通知程序**，即当数据从“无数据”状态变为“有数据”状态时才会通知程序。这种方式可以减少通知次数，降低了开销，但是如果应用程序没有读取或写入所有数据，会导致数据丢失。
   >
   > **从输入缓冲的角度来看，条件触发方式通知事件的时间点是在有新数据到达时就会通知程序，无论之前是否已经通知过。而边缘触发方式只在输入缓冲区状态发生变化时通知程序，只通知一次，直到应用程序读取或写入完所有数据，再有新的数据到达时才会通知程序。因此，在使用边缘触发方式时，应用程序需要及时读取或写入所有数据，避免数据丢失。**

   

5. epoll 是以条件触发和边缘触发方式工作。二者有何差别？从输入缓冲的角度说明这两种方式通知事件的时间点差异。

   答：在条件触发中，只要输入缓冲有数据，就会一直通知该事件。

   ​	   边缘触发中输入缓冲收到数据时仅注册 1 次该事件，即使输入缓冲中还留有数据，也不会再进行注册。

   

6. 采用边缘触发时可以分离数据的接收和处理时间点。请说明其优点和原因。

   答：分离接收数据和处理数据的时间点，给服务端的实现带来很大灵活性。

   > 边缘触发（Edge-triggered）是一种 I/O 多路复用技术，在应用程序中可以使用 epoll 等系统调用实现。与条件触发（Level-triggered）相比，边缘触发具有以下优点：
   >
   > 1. **可以避免饥饿现象**
   >
   > 当多个事件同时到来时，条件触发模式下，事件处理函数会被调用多次，而边缘触发模式下，只有当输入缓冲中有新数据到来时，事件处理函数才会被调用。因此，边缘触发模式可以避免事件处理函数被反复调用，避免饥饿现象。
   >
   > 2. **提高事件处理效率**
   >
   > 在条件触发模式下，事件处理函数必须一直等待直到某个事件发生，然后才能进行处理。而在边缘触发模式下，事件处理函数只在有新数据到来时才会被调用，可以及时处理事件，提高处理效率。
   >
   > 3. **分离数据的接收和处理时间点**
   >
   > 在边缘触发模式下，输入缓冲中的数据只有在有新数据到来时才被通知，因此可以分离数据的接收和处理时间点。当新数据到来时，事件处理函数被调用处理新数据，可以将新数据与旧数据分离，避免出现数据混淆的情况。
   >
   > 
   >
   > 总之，边缘触发模式可以避免饥饿现象、提高事件处理效率，并且分离数据的接收和处理时间点，是一种高效的 I/O 多路复用技术。







## 第18章 多线程服务端的实现

### 18.1 理解线程的概念

**引入线程背景**

第 10 章介绍了多进程服务端的实现方法。多进程模型与 select 和 epoll 相比的确有自身的优点，但同时也有问题。如前所述，创建（复制）进程的工作本身会给操作系统带来相当沉重的负担。而且，每个进程都具有独立的内存空间，所以进程间通信的实现难度也会随之提高。换言之，**多进程的缺点可概括为**：

- 创建进程的过程会带来一定的开销，每个进程都需要独立的资源，如独立的内存空间、文件描述符等，这会增加系统的负担。 
- 为了完成进程间数据交换，需要特殊的 IPC 技术，如管道、消息队列、共享内存等，这些机制使用起来相对复杂。

但是更大的缺点是下面的：

- 每秒少则 10 次，多则千次的**「上下文切换」**是创建进程的最大开销

只有一个 CPU 的系统是将时间分成多个微小的块后分配给了多个进程。为了分时使用 CPU ，需要「上下文切换」的过程。「**上下文切换」是指运行程序前需要将相应进程信息读入内存**，如果运行进程 A 后紧接着需要运行进程 B ，就应该将进程 A 相关信息移出内存，并读入进程 B 相关信息。这就是上下文切换。但是此时进程 A 的数据将被移动到硬盘，所以上下文切换要很长时间，即使通过优化加快速度，也会存在一定的局限。

为了保持多进程的优点，同时在一定程度上克服其缺点，人们引入的线程（Thread）的概念。这是为了将进程的各种劣势降至最低程度（不是直接消除）而设立的一种「轻量级进程」。线程比进程具有如下优点：

- **线程的创建和上下文切换比进程的创建和上下文切换更快**
- **线程间交换数据无需特殊技术**

> 1. **资源消耗更少：**线程在进程内部运行，共享进程的资源，如内存、文件描述符等，因此线程的创建和**上下文切换**的开销比进程要小很多。
> 2. **执行效率更高：**由于线程共享进程的内存空间，因此线程之间的数据共享和通信相对容易实现，这比进程之间的通信要快速、简单。
> 3. **编程更简单：**线程之间的通信和同步相对简单，因为线程共享相同的地址空间，因此数据共享的方式更加简单。
> 4. **更好的可扩展性：**由于线程比进程消耗更少的资源，因此可以创建更多的线程，从而提高程序的并发性和处理能力。
>
> 综上所述，线程比进程具有更好的资源利用效率、执行效率、编程简单性和可扩展性等优点。因此，在多线程和多进程之间进行选择时，需要根据具体的应用场景和需求进行权衡。



**线程和进程的差异**

> 线程和进程是操作系统中最基本的概念，它们之间的区别主要有以下几个方面：
>
> 1. **资源占用：进程是资源分配的基本单位，一个进程拥有独立的地址空间、文件描述符、信号处理器等资源。而线程是进程的执行实体，它和同一进程内的其他线程共享进程的所有资源。**
> 2. **调度和切换：进程是系统资源的拥有者，它需要操作系统进行调度和切换**，进程的切换需要保存和恢复进程的所有状态信息，包括进程的PC值、寄存器状态、内存映像等。**而线程是在进程内部进行调度和切换**，线程的切换相对于进程的切换来说更加快速。
> 3. **通信和同步：**由于线程共享进程的地址空间，因此**线程之间通信和同步相对简单，如可以使用共享内存、信号量、互斥量等机制来实现。而进程之间的通信和同步则需要使用操作系统提供的IPC机制**。
> 4. **安全性：**由于线程共享进程的地址空间，因此线程之间的安全问题更加复杂。**当一个线程写入数据时，需要考虑其他线程是否正在读取或写入同一数据，从而避免数据的竞争和冲突。而进程之间由于地址空间是独立的，因此安全性相对较高**。
> 5. **创建和销毁：创建和销毁线程的开销比进程小很多，因为线程的创建和销毁只需要操作系统分配和释放栈空间即可，而进程的创建和销毁则需要进行更多的初始化和清理工作。**
>
> **综上所述，线程和进程在资源占用、调度和切换、通信和同步、安全性、创建和销毁等方面都存在较大的差异。在选择线程或进程时，需要根据具体的应用场景和需求进行权衡。**

线程是为了解决：为了得到多条代码执行流而复制整个内存区域的负担太重。

每个进程的内存空间都由保存全局变量的**「数据区」**、向 malloc 等函数动态分配提供空间的**堆**（Heap）、函数运行时间使用的**栈**（Stack）构成。每个进程都有独立的这种空间，多个进程的内存结构如图所示：

![img](TCPIP网络编程.assets/68747470733a2f2f692e6c6f6c692e6e65742f323031392f30322f30322f356335356161353764623363372e706e67.png)

但如果以获得多个代码执行流为目的，则不应该像上图那样完全分离内存结构，而只需分离栈区域。通过这种方式可以获得如下优势：

- **上下文切换时不需要切换数据区和堆**
- **可以利用数据区和堆交换数据**

实际上这就是线程。线程为了保持多条代码执行流而隔开了栈区域，因此具有如下图所示的内存结构：

![img](TCPIP网络编程.assets/68747470733a2f2f692e6c6f6c692e6e65742f323031392f30322f30322f356335356162343535653339392e706e67.png)

如图所示，多个线程共享数据区和堆。为了保持这种结构，线程将在进程内创建并运行。也就是说，进程和线程可以定义为如下形式：

- **进程：在操作系统构成单独执行流的单位**
- **线程：在进程构成单独执行流的单位**

如果说进程在操作系统内部生成多个执行流，那么线程就在同一进程内部创建多条执行流。因此，操作系统、进程、线程之间的关系可以表示为下图：

![img](TCPIP网络编程.assets/68747470733a2f2f692e6c6f6c692e6e65742f323031392f30322f30322f356335356163323061613737362e706e67.png)





### 18.2 线程创建及运行

可移植操作系统接口（英语：Portable Operating System Interface，缩写为POSIX）是IEEE为要在各种UNIX操作系统上运行软件，而定义API的一系列互相关联的标准的总称，其正式称呼为IEEE Std 1003，而国际标准名称为ISO/IEC 9945。此标准源于一个大约开始于1985年的项目。POSIX这个名称是由理查德·斯托曼（RMS）应IEEE的要求而提议的一个易于记忆的名称。它基本上是Portable Operating System Interface（可移植操作系统接口）的缩写，而X则表明其对Unix API的传承。

Linux基本上逐步实现了POSIX兼容，但并没有参加正式的POSIX认证。

微软的Windows NT声称部分实现了POSIX标准。

当前的POSIX主要分为四个部分：Base Definitions、System Interfaces、Shell and Utilities和Rationale。



**线程的创建和执行流程**

线程具有单独的执行流，因此需要单独定义线程的 main 函数，还需要请求操作系统在单独的执行流中执行该函数，完成函数功能的函数如下：

```c++
#include <pthread.h>

int pthread_create(pthread_t *restrict thread,			//保存新创建的线程ID
                   const pthread_attr_t *restrict attr,  //线程的属性
                   void * (*start_routine) (void *),	 //线程的main函数
                   void * restrict arg);				//传递main的参数信息
/*
成功时返回 0 ，失败时返回其他值
restrict关键字，用于向编译器表明指针所指向的内存区域是唯一的，即没有别的指针指向同一内存区域
thread : 保存新创建线程 ID 的变量地址值。线程与进程相同，也需要用于区分不同线程的 ID
attr : 用于传递线程属性的参数，传递 NULL 时，创建默认属性的线程
start_routine : 相当于线程 main 函数的、在单独执行流中执行的函数地址值（函数指针）
arg : 通过第三个参数传递的调用函数时包含传递参数信息的变量地址值
*/
```

下面通过简单示例了解该函数功能：

[thread1.cpp]

```c++
#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

void* thread_main(void *arg){
    int cnt = *((int *)arg);    //首先使用(int*)强制转换为地址，在使用*进行解引用
    for (int i = 0; i < cnt; i++){
        sleep(1);
        cout << "running thread" << endl;
    }
    return NULL;
}

int main(int argc, char* argv[]){
    pthread_t t_id;
    int thread_param = 5;

    //请求创建一个线程，从 thread_main 调用开始，在单独的执行流中运行。同时传递参数
    if (pthread_create(&t_id, NULL, thread_main, &thread_param) != 0){
        cout << "pthread_create error" << endl;
        return -1;
    }

    sleep(10);
    cout << "end of main" << endl;
    return 0;
}
```

输出：

```c++
running thread
running thread
running thread
running thread
running thread
end of main
```

上述程序的执行如图所示：

![img](TCPIP网络编程.assets/68747470733a2f2f692e6c6f6c692e6e65742f323031392f30322f30322f356335356236393433323535622e706e67.png)

可以看出，程序在主进程没有结束时，生成的线程每隔一秒输出一次 `running thread` ，但是如果主进程没有等待十秒，而是直接结束，这样也会强制结束线程，不论线程有没有运行完毕。

将main函数中的sleep(10)改为sleep(2)，编译并运行

```c++
running thread
end of main
running thread
```

并不会像之前的代码输出5次running thread，因为在main函数返回后整个进程都将被销毁。



那是否意味着主进程必须每次都 sleep 来等待线程执行完毕？并不需要，可以通过以下函数解决。

```c++
#include <pthread.h>

int pthread_join(pthread_t thread, void **status);
/*
成功时返回 0 ，失败时返回其他值
thread : 该参数值 ID 的线程终止后才会从该函数返回
status : 保存线程的 main 函数返回值的指针的变量地址值
*/
```

**作用就是调用该函数的进程（或线程）将进入阻塞状态，直到第一个参数为 ID 的线程终止为止并回收它的资源。而且可以得到线程的 main 函数的返回值。**

下面是该函数的用法代码：

```c++
#include <iostream>
#include <pthread.h>
#include <cstring>
#include <unistd.h>
using namespace std;

void* thread_main(void *arg){
    int cnt = *((int *)arg);    //首先使用(int*)强制转换为地址，在使用*进行解引用
    char *msg = new char[50];
    strcpy(msg, "Hello, I'm a thread\n");
    for (int i = 0; i < cnt; i++){
        sleep(1);
        cout << "running thread" << endl;
    }
    return (void*)msg;
}

int main(int argc, char* argv[]){
    pthread_t t_id;
    int thread_param = 5;
    void * thr_ret;

    //请求创建一个线程，从 thread_main 调用开始，在单独的执行流中运行。同时传递参数
    if (pthread_create(&t_id, NULL, thread_main, &thread_param) != 0){
        cout << "pthread_create error" << endl;
        return -1;
    }

    //使用thread_join函数来控制线程的执行流, main函数将等待 ID 保存在 t_id 变量中的线程终止
    if (pthread_join(t_id, &thr_ret) != 0){
        cout << "pthread_join error" << endl;
        return -1;
    }

    cout << "Thread return message : " << (char *) thr_ret << endl;
    free(thr_ret);
    return 0;
}
```

输出

```c++
running thread
running thread
running thread
running thread
running thread
Thread return message : Hello, I'm a thread 
```

可以看出，线程输出了5次字符串，并且把返回值给了主进程

下面是该函数的执行流程图：

![img](TCPIP网络编程.assets/68747470733a2f2f692e6c6f6c692e6e65742f323031392f30322f30322f356335356264643362623363382e706e67.png)



**可在临界区内调用的函数**

> **在多线程编程中，临界区是指一段同时只能被一个线程执行的代码段**。在临界区中，如果有多个线程同时执行，就会出现竞态条件（race condition），从而导致程序出现不可预期的结果。
>
> 通常情况下，临界区是由共享资源所保护的，例如一个全局变量、一个文件、一个共享内存区域等。当多个线程同时访问这个共享资源时，就需要使用一些同步机制，如**互斥锁、条件变量、信号量**等，来保证线程的安全访问。在这些同步机制中，互斥锁是最常用的一种。
>
> 临界区的实现需要保证以下两个条件：
>
> 1. **互斥性：**在任何时刻，只能有一个线程进入临界区执行代码。
> 2. **有限等待：**如果有多个线程等待进入临界区，则只有一个线程能够进入，其他线程需要等待，而等待的时间应该是有限的，即不能无限制地等待下去。
>
> 通常情况下，临界区的长度应该尽量短，以避免多个线程长时间等待，从而降低程序的性能。因此，开发人员需要根据具体情况来设计临界区的大小和位置，以保证线程的安全访问和程序的高效性能。

**在同步的程序设计中，临界区块（Critical section）指的是一个访问共享资源（例如：共享设备或是共享存储器）的程序片段，而这些共享资源有无法同时被多个线程访问的特性。**

根据临界区是否引起问题，函数可以分为以下 2 类：

- 线程安全函数（Thread-safe function）
- 非线程安全函数（Thread-unsafe function）

线程安全函数被多个线程同时调用也不会发生问题。反之，非线程安全函数被同时调用时会引发问题。但这并非有关于临界区的讨论，线程安全的函数中同样可能存在临界区。只是在线程安全的函数中，同时被多个线程调用时可通过一些措施避免问题。

幸运的是，大多数标准函数都是线程安全函数。操作系统在定义非线程安全函数的同时，提供了具有相同功能的线程安全的函数。比如，第 8 章的：

```c++
struct hostent *gethostbyname(const char *hostname);
```

同时，也提供了同一功能的安全函数：

```c++
struct hostent *gethostbyname_r(const char *name,
                                struct hostent *result,
                                char *buffer,
                                int intbuflen,
                                int *h_errnop);
```

线程安全函数结尾通常是 `_r` 。但是使用线程安全函数会给程序员带来额外的负担，可以通过以下方法自动将 `gethostbyname` 函数调用改为 `gethostbyname_r` 函数调用。

> 声明头文件前定义 `_REENTRANT` 宏。

无需特意更改源代码加，可以在编译的时候指定编译参数定义宏。

```c++
gcc -D_REENTRANT mythread.c -o mthread -lpthread
```



**工作（Worker）线程模型**

下面的示例是计算从 1 到 10 的和，但并不是通过 main 函数进行运算，而是创建两个线程，其中一个线程计算 1 到 5 的和，另一个线程计算 6 到 10 的和，main 函数只负责输出运算结果。这种方式的线程模型称为「工作线程」。显示该程序的执行流程图：

![img](TCPIP网络编程.assets/68747470733a2f2f692e6c6f6c692e6e65742f323031392f30322f30332f356335356333333065386235622e706e67.png)

下面是代码：

```c++
#include <iostream>
#include <pthread.h>
#include <cstring>
#include <unistd.h>
using namespace std;

int sum = 0;

void* thread_summation(void *arg){
    int start = ((int *)arg)[0];
    int end = ((int*)arg)[1];

    while (start <= end){
        sum += start;
        start++;
    }
    return NULL;
}

int main(int argc, char* argv[]){
    pthread_t id_t1, id_t2;
    int range1[] = {1, 5}, range2[] = {6, 10};

    if (pthread_create(&id_t1, NULL, thread_summation, &range1) != 0){
        cout << "pthread_create error" << endl;
        return -1;
    }

    if (pthread_create(&id_t2, NULL, thread_summation, &range2) != 0){
        cout << "pthread_create error" << endl;
    }

    //线程等待终止
    if (pthread_join(id_t1, NULL) != 0){
        cout << "pthread_join error" << endl;
    }
      
    //线程等待终止
    if (pthread_join(id_t2, NULL) != 0){
        cout << "pthread_join error" << endl;
    }

    cout << sum << endl;

    return 0;
}
```

输出：

```c++
55
```

可以看出计算结果正确，两个线程都用了全局变量 sum ,证明了 2 个线程共享保存全局变量的数据区。

但是本例子本身存在问题。存在临界区相关问题，可以从下面的代码看出，下面的代码和上面的代码相似，只是增加了发生临界区错误的可能性，即使在高配置系统环境下也容易产生的错误：

```c++
#include <iostream>
#include <pthread.h>
#include <cstring>
#include <unistd.h>
using namespace std;

#define NUM_THREAD 100

long long num = 0;

void* thread_inc(void *arg){	//利用thread_inc函数对num++
    for (int i = 0; i < 500000000; i++)
        num++;
    return NULL;
}

void* thread_des(void *arg){	//利用thread_inc函数对num--
    for (int i = 0; i < 500000000; i++)
        num--;
    return NULL;
}

int main(int argc, char* argv[]){
    pthread_t pthread_id[NUM_THREAD];

    cout << "sizeof long long : " << sizeof(long long) << endl;

    for (int i = 0; i < NUM_THREAD; i++){
        if (i%2)	
            pthread_create(&pthread_id[i], NULL, thread_inc, NULL);
        else
            pthread_create(&pthread_id[i], NULL, thread_des, NULL);
    }

    for (int i = 0; i < NUM_THREAD; i++)
        pthread_join(pthread_id[i], NULL);

    cout << "result : " << num << endl;

    return 0;
}
```

上述示例中共创建了100线程，其中一半执行 `thread_inc` 函数中的代码，另一半执行 `thread_des` 函数中的代码，全部变量经过增减过程后应该结果为0，但是实际的结果为：

```c++
sizeof long long : 8
result : -23731416	//可能每次运行完之后的结果都不相同
```



### 18.3 线程存在的问题和临界区

下面分析 [thread4.cpp] 中产生问题的原因，并给出解决方案。

**多个线程访问同一变量是问题**

> 多个线程访问同一变量可能会导致以下问题：
>
> 1. **竞争条件**：当多个线程同时读取、写入同一变量时，可能会发生竞争条件，导致程序的行为出现不可预期的错误。例如，多个线程同时读取某个计数器变量的值，进行加一操作后再写回该变量，如果不加同步措施，就可能会导致计数器值的错误累加。
> 2. **互斥问题**：当多个线程需要对同一资源进行修改时，需要保证在某一时刻只有一个线程可以访问该资源，否则就可能会发生互斥问题。例如，多个线程需要向同一**文件**中写入数据，如果不加同步措施，就可能会导致数据被覆盖或者混乱。
> 3. **死锁问题**：当多个线程需要互相等待对方释放资源时，就可能会发生死锁问题，导致程序无法继续执行。例如，线程A需要获取资源1和资源2，线程B需要获取资源2和资源1，如果不加同步措施，就可能会导致A获取资源1后等待B释放资源2，B获取资源2后等待A释放资源1，从而导致死锁。
>
> 综上所述，多个线程访问同一变量可能会导致一系列问题，需要通过使用同步措施来避免这些问题的发生。常用的同步措施包括互斥锁、条件变量、信号量等，可以有效地避免多线程访问同一变量导致的问题。

[thread4.cpp]的问题如下：

> 2 个线程正在同时访问全局变量 num

任何内存空间，只要被同时访问，都有可能发生问题。

因此，线程访问变量 num 时应该阻止其他线程访问，直到线程 1 运算完成。这就是同步（Synchronization）



**临界区位置**

**临界区是指一段同时只能被一个线程执行的代码段。**

那么在刚才代码中的临界区位置是：

> 函数内同时运行多个线程时引发问题的多条语句构成的代码块

全局变量 num 不能视为临界区，因为他不是引起问题的语句，只是一个内存区域的声明。下面是刚才代码的两个 main 函数

```c++
void *thread_inc(void *arg)
{
    for (int i = 0; i < 50000000; i++)
        num += 1;		//临界区
    return NULL;
}

void *thread_des(void *arg)
{
    for (int i = 0; i < 50000000; i++)
        num -= 1;		//临界区
    return NULL;
}
```

由上述代码可知，临界区并非 num 本身，而是访问 num 的两条语句，这两条语句可能由多个线程同时运行，也是引起这个问题的直接原因。

**产生问题的原因可以分为以下三种情况：**

- 2 个线程同时执行 `thread_inc` 函数
- 2 个线程同时执行 `thread_des` 函数
- 2 个线程分别执行 `thread_inc` 和 `thread_des` 函数

比如发生以下情况：

> 线程 1 执行 `thread_inc` 的 num+=1 语句的同时，线程 2 执行 `thread_des` 函数的 num-=1 语句

也就是说，两条不同的语句由不同的线程执行时，也有可能构成临界区。前提是这 2 条语句访问同一内存空间。





### 18.4 线程同步

前面讨论了线程中存在的问题，下面就是解决方法，线程同步。



**同步的两面性**

线程同步用于解决线程访问顺序引发的问题。需要同步的情况可以从如下两方面考虑。

- **同时访问同一内存空间时发生的情况**
- **需要指定访问同一内存空间的线程顺序的情况**

情况一之前已经解释过，下面讨论情况二。这是「控制线程执行的顺序」的相关内容。假设有 A B 两个线程，线程 A 负责向指定的内存空间内写入数据，线程 B 负责取走该数据。所以这是有顺序的，不按照顺序就可能发生问题。所以这种也需要进行同步。



**互斥量**

> **互斥量（mutex）是一种用于实现多线程同步的机制，主要用于保护共享资源，防止多个线程同时访问和修改同一共享资源，从而避免产生数据竞争等问题。**

互斥锁（英语：英语：Mutual exclusion，缩写 Mutex）是一种用于多线程编程中，防止两条线程同时对同一公共资源（比如全域变量）进行读写的机制。该目的通过将代码切片成一个一个的临界区域（critical section）达成。临界区域指的是一块对公共资源进行访问的代码，并非一种机制或是算法。一个程序、进程、线程可以拥有多个临界区域，但是并不一定会应用互斥锁。

**通俗的说就互斥量就是一把优秀的锁，当临界区被占据的时候就上锁，等占用完毕然后再放开。**

**下面是互斥量的创建及销毁函数。**

```c++
#include <pthread.h>

int pthread_mutex_init(pthread_mutex_t *mutex,
                       const pthread_mutexattr_t *attr);	//创建互斥量
                       
int pthread_mutex_destroy(pthread_mutex_t *mutex);		    //销毁互斥量
/*
成功时返回 0，失败时返回其他值
mutex : 创建互斥量时传递保存互斥量的变量地址值，销毁时传递需要销毁的互斥量地址
attr : 传递即将创建的互斥量属性，没有特别需要指定的属性时传递 NULL
*/
```

从上述函数声明中可以看出，为了创建相当于锁系统的互斥量，需要声明如下 `pthread_mutex_t` 型变量：

```c++
pthread_mutex_t mutex
```

该变量的地址值传递给 `pthread_mutex_init` 函数，用来保存操作系统创建的互斥量（锁系统）。调用 `pthread_mutex_destroy` 函数时同样需要该信息。如果不需要配置特殊的互斥量属性，则向第二个参数传递 NULL 时，可以利用 PTHREAD_MUTEX_INITIALIZER 进行如下声明：

```c++
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
```

推荐**尽可能的使用 `pthread_mutex_init` 函数进行初始化**，因为通过宏进行初始化时很难发现发生的错误。

下面是利用互斥量锁住或释放临界区时使用的函数。

```c++
#include <pthread.h>

int pthread_mutex_lock(pthread_mutex_t *mutex);		//互斥量加锁

int pthread_mutex_unlock(pthread_mutex_t *mutex);	//互斥量解锁

//成功时返回 0 ，失败时返回其他值
```

函数本身含有 lock unlock 等词汇，很容易理解其含义。**进入临界区前调用的函数就是 `pthread_mutex_lock` 。调用该函数时，发现有其他线程已经进入临界区，则 `pthread_mutex_lock` 函数不会返回，直到里面的线程调用 `pthread_mutex_unlock` 函数退出临界区位置。也就是说，其他线程让出临界区之前，当前线程一直处于阻塞状态。**

接下来利用互斥量来解决示例[thread4.cpp]中遇到的问题：

```c++
#include <iostream>
#include <pthread.h>
#include <cstring>
#include <unistd.h>
using namespace std;

#define NUM_THREAD 100

long long num = 0;
pthread_mutex_t mutex;  //互斥量

void* thread_inc(void *arg){
    pthread_mutex_lock(&mutex);  	//加锁
    for (int i = 0; i < 500000000; i++)
        num++;  		//临界区
    pthread_mutex_unlock(&mutex);	//解锁
    return NULL;
}

void* thread_des(void *arg){
    for (int i = 0; i < 500000000; i++){
        pthread_mutex_lock(&mutex);
        num--;          //临界区
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(int argc, char* argv[]){
    pthread_t pthread_id[NUM_THREAD];

    pthread_mutex_init(&mutex, NULL);    //互斥量的创建

    cout << "sizeof long long : " << sizeof(long long) << endl;

    for (int i = 0; i < NUM_THREAD; i++){
        if (i%2)
            pthread_create(&pthread_id[i], NULL, thread_inc, NULL);
        else
            pthread_create(&pthread_id[i], NULL, thread_des, NULL);
    }

    for (int i = 0; i < NUM_THREAD; i++)
        pthread_join(pthread_id[i], NULL);

    cout << "result : " << num << endl;

    pthread_mutex_destroy(&mutex);   	//互斥量的销毁

    return 0;
}
```

输出：

```c++
sizeof long long : 8
result : 0
```

从运行结果可以看出，通过互斥量机制得出了正确的运行结果。

在代码中：

```c++
void *thread_inc(void *arg)
{
    int i;
    pthread_mutex_lock(&mutex); //上锁
    for (i = 0; i < 50000000; i++)
        num += 1;
    pthread_mutex_unlock(&mutex); //解锁
    return NULL;
}
```

以上代码的临界区划分范围较大，但这是考虑如下优点所做的决定:

> **最大限度减少互斥量 lock unlock 函数的调用次数**



**信号量**

> **Linux中的信号量是一种线程同步机制，它可以协调多个线程对共享资源的访问。**
>
> Linux中的信号量分为两种类型**：二进制信号量和计数信号量。**
>
> 二进制信号量是一种二元信号量，只有两个值：0和1。它用于解决对共享资源的独占访问问题。当一个线程对二进制信号量**加锁**时，如果该信号量的值为**1**，则该线程可以继续执行；如果该信号量的值为0，则该线程会被阻塞，直到其他线程释放该信号量。
>
> 计数信号量是一种计数型信号量，它可以有多个值，用于控制多个线程对共享资源的访问。当一个线程对计数信号量加锁时，如果该信号量的值大于0，则该线程可以继续执行；如果该信号量的值等于0，则该线程会被阻塞，直到其他线程释放该信号量。
>
> Linux中的信号量使用系统调用 `sem_init`、`sem_wait`、`sem_post`和`sem_destroy`进行创建、加锁、解锁和销毁操作。其中，`sem_init` 用于初始化信号量，`sem_wait` 用于加锁操作，`sem_post` 用于解锁操作，`sem_destroy` 用于销毁信号量。

信号量（英语：Semaphore）又称为信号标，是一个同步对象，用于保持在0至指定最大值之间的一个计数值。当线程完成一次对该semaphore对象的等待（wait）时，该计数值减一；当线程完成一次对semaphore对象的释放（release、post）时，计数值加一。当计数值为0，则线程等待该semaphore对象不再能成功直至该semaphore对象变成signaled状态。semaphore对象的计数值大于0，为signaled状态；计数值等于0，为 `nonsignaled` 状态.

semaphore对象适用于控制一个仅支持有限个用户的共享资源，是一种不需要使用忙碌等待（busy waiting）的方法。

信号量的概念是由荷兰计算机科学家艾兹赫尔·戴克斯特拉（Edsger W. Dijkstra）发明的，广泛的应用于不同的操作系统中。在系统中，给予每一个进程一个信号量，代表每个进程当前的状态，未得到控制权的进程会在特定地方被强迫停下来，等待可以继续进行的信号到来。如果信号量是一个任意的整数，通常被称为计数信号量（Counting semaphore），或一般信号量（general semaphore）；如果信号量只有二进制的0或1，称为二进制信号量（binary semaphore）。

**在Linux系统中，二进制信号量（binary semaphore）又称互斥锁（Mutex）。**

下面介绍信号量，在互斥量的基础上，很容易理解信号量。此处只涉及利用「二进制信号量」（只用 0 和 1）完成**「控制线程顺序」**为中心的同步方法。下面是信号量的创建及销毁方法：

```c++
#include <semaphore.h>

int sem_init(sem_t *sem, int pshared, unsigned int value);	//信号量的创建
int sem_destroy(sem_t *sem);						      //信号量的销毁
/*
成功时返回 0 ，失败时返回其他值
sem : 创建信号量时保存信号量的变量地址值，销毁时传递需要销毁的信号量变量地址值
pshared : 传递其他值时，创建可由多个继承共享的信号量；传递 0 时，创建只允许 1 个进程内部使用的信号量。需要完成同一进程的线程同步，故为0. 如果pshared参数为非零，则信号量可以在不同进程之间共享。
value : 指定创建信号量的初始值
*/
```

上述的 shared 参数超出了我们的关注范围，故默认向其传递为 0 。下面是信号量中相当于互斥量 lock unlock 的函数。

```c++
#include <semaphore.h>

int sem_wait(sem_t *sem);	//sem_wait函数用于获取一个信号量，信号量-1
int sem_post(sem_t *sem);	//sem_post函数用于释放一个信号量，信号量+1
/*
成功时返回 0 ，失败时返回其他值
sem : 传递保存信号量读取值的变量地址值，传递给 sem_post 的信号量增1，传递给 sem_wait 时信号量减一
*/
```

调用 `sem_init` 函数时，操作系统将创建信号量对象，此对象中记录这「信号量值」（Semaphore Value）整数。该值在调用 `sem_post` 函数时增加 1 ，调用 wait_wait 函数时减一。但信号量的值不能小于 0 ，因此，在信号量为 0 的情况下调用 `sem_wait` 函数时，调用的线程将进入阻塞状态（因为函数未返回）。当然，此时如果有其他线程调用 `sem_post` 函数，信号量的值将变为 1 ，而原本阻塞的线程可以将该信号重新减为 0 并跳出阻塞状态。实际上就是通过这种特性完成临界区的同步操作，可以通过如下形式同步临界区（**假设信号量的初始值为 1**）

```c++
sem_wait(&sem);		//信号量变为0...
/* 临界区的开始
...
临界区的结束*/
sem_post(&sem);		//信号量变为1...
```

上述代码结构中，调用 `sem_wait` 函数进入临界区的线程在调用 `sem_post` 函数前不允许其他线程进入临界区。信号量的值在 0 和 1 之间跳转，因此，具有这种特性的机制称为「**二进制信号量**」。接下来的代码是信号量机制的代码。下面代码并非是同时访问的同步，而是关于控制访问顺序的同步，该场景为：

> 线程 A 从用户输入得到值后存入全局变量 num ，此时线程 B 将取走该值并累加。该过程一共进行 5 次，完成后输出总和并退出程序。

[semaphore.cpp]代码：

```c++
#include <iostream>
#include <thread>
#include <semaphore.h>
using namespace std;

static int num;
static sem_t sem_one, sem_two;  //使用两个信号量

void* read(void *arg){
    for (int i = 0; i < 5; i++){
        cout << "Input num : ";
        sem_wait(&sem_two);     //对sem_two信号量加锁
        cin >> num;
        sem_post(&sem_one);     //对sem_one进行释放
    }
    return NULL;
}

void* accu(void *arg){
    int sum = 0;
    for (int i = 0; i < 5; i++){
        sem_wait(&sem_one);		//对sem_one进行加锁
        sum += num;
        sem_post(&sem_two);		//对sem_two进行解锁
    }
    cout << "result : " << sum << endl;
    return NULL;
}

int main(int argc, char *argv[]){
    sem_init(&sem_one, 0, 0);  //创建sem_one信号量只允许一个进程内部使用的信号量，初始值为0
    sem_init(&sem_two, 0, 1);

    pthread_t id_t1, id_t2;
    pthread_create(&id_t1, NULL, read, NULL);
    pthread_create(&id_t2, NULL, accu, NULL);

    pthread_join(id_t1, NULL);
    pthread_join(id_t2, NULL);

    sem_destroy(&sem_one);
    sem_destroy(&sem_two);
    return 0;
}
```

输出：

```c++
Input num : 1
Input num : 2
Input num : 3
Input num : 4
Input num : 5
result : 15
```

如果将上述代码进行修改

```c++
sem_init(&sem_one, 0, 0);  //两个信号量的初值都为0
sem_init(&sem_two, 0, 0);
         
//accu函数         
sem_post(&sem_two);   	  //对sem_two信号量加锁 0 -> 1
sum += num; //临界区
sem_wait(&sem_one);       //对sem_one进行释放   1 -> 0        
```

> 如果将`sem_init(&sem_one, 0, 0);`和`sem_init(&sem_two, 0, 0);`中的信号量初始值都设置为0，那么这两个信号量在初始化时没有可用的资源，也就是说它们都被锁住了。在这种情况下，代码将会发生死锁。
>
> 具体来说，当读取线程首先执行时，它会对`sem_two`进行加锁操作，由于`sem_two`的初始值为0，所以该线程会被阻塞，一直等待`sem_two`变为可用。然而，由于计算线程还没有开始执行，它也无法对`sem_one`进行解锁操作，因此读取线程会一直等待，最终导致程序无法继续执行下去。
>
> 因此，如果将`sem_init(&sem_one, 0, 0);`和`sem_init(&sem_two, 0, 0);`中的信号量初始值都设置为0，应该在程序中进行必要的修改以避免死锁的发生。例如，可以将其中一个信号量的初始值设置为1，以确保程序一开始就有可用的资源。

会导致得不到正确的结果

```c++
Input num : 1
Input num : 2
Input num : 3
Input num : 4
Input num : 5
result : 10
```

结果为10不是我们想要的





### 18.5 线程的销毁和多线程并发服务器端的实现

先介绍线程的销毁，然后再介绍多线程服务端



**销毁线程的 3 种方法**

Linux 的线程并不是在首次调用的线程 **main** 函数返回时自动销毁，所以利用如下方法之一加以明确。否则由线程创建的内存空间将一直存在。

- 调用 **`pthread_join`** 函数
- 调用 **`pthread_detach`** 函数

之前调用过 `pthread_join` 函数。调用该函数时，不仅会等待线程终止，还会引导线程销毁。但该函数的问题是，线程终止前，调用该函数的线程将进入**阻塞**状态。因此，通过如下函数调用引导线程销毁。

```c++
#include <pthread.h>

int pthread_detach(pthread_t th);
/*
成功时返回 0 ，失败时返回其他值
thread : 终止的同时需要销毁的线程 ID
*/
```

调用上述函数不会引起线程终止或进入阻塞状态，可以通过该函数引导销毁线程创建的内存空间。调用该函数后不能再针对相应线程调用 `pthread_join` 函数。



**多线程并发服务器端的实现**

多个客户端交换信息的简单聊天程序

[chat_server.cpp]

```c++
#include <iostream>
#include <thread>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
using namespace std;

#define BUF_SIZE 100
#define MAX_CLNT 256

//全局变量  临界区
int clnt_cnt, clnt_socks[MAX_CLNT];
pthread_mutex_t mutex;

void send_msg(char *msg, int len){  //向所有的客户端发送信息
    pthread_mutex_lock(&mutex);

    for (int i = 0; i < clnt_cnt; i++){
        write(clnt_socks[i], msg, len);
    }

    pthread_mutex_unlock(&mutex);
}

void* handle_clnt(void *arg){   //利用handle_clnt向所有连接的客户端发送消息
    int clnt_sock = *((int *)arg);
    int str_len = 0;
    char msg[BUF_SIZE];

    while ((str_len = read(clnt_sock, msg, sizeof(msg))) != 0)
        send_msg(msg, str_len);
        
    pthread_mutex_lock(&mutex);  //在互斥量上加锁

    //临界区
    for (int i = 0; i < clnt_cnt; i++){
        if (clnt_socks[i] == clnt_sock){    //移除clnt_sock客户端
            while (i+1 < clnt_cnt){
                clnt_socks[i] = clnt_socks[i+1];
                i++;
            }
            break;
        }
    }
    clnt_cnt--;

    pthread_mutex_unlock(&mutex);

    close(clnt_sock);
    return NULL;
}

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

    if (listen(serv_sock, 5) == -1){
        cout << "server listen socket error" << endl;
        return -1;
    }

    pthread_t t_id;

    while (1){
        clnt_size = sizeof(clnt_addr);

        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_size);
        if (clnt_sock == -1){
            cout << "server accept socket error" << endl;
            return -1;
        }

        pthread_mutex_lock(&mutex);     //利用互斥量来进行加锁

        clnt_socks[clnt_cnt++]  = clnt_sock;

        pthread_mutex_unlock(&mutex);

        //创建线程
        pthread_create(&t_id, NULL, handle_clnt, (void*)&clnt_sock);
        pthread_detach(t_id);

        cout << "connected client ip : " << inet_ntoa(clnt_addr.sin_addr) << endl;  //以点分十进制的形式输出IP地址
    }
}
```

[chat_client.cpp]

```c++
#include <iostream>
#include <thread>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
using namespace std;

#define BUF_SIZE 100
#define NAME_SIZE 20

char name[NAME_SIZE] = "[DEFAULT]";
char msg[BUF_SIZE];

void* send_msg(void *arg){  //利用线程将客户端的输入输出进行分离
    int sock = *((int *)arg);
    char name_msg[NAME_SIZE + BUF_SIZE];
    while (1){
        cin.getline(msg, BUF_SIZE);
        if (strcmp(msg, "Q") == 0 || strcmp(msg, "q") == 0){
            close(sock);
            exit(0);
        }
        sprintf(name_msg, "%s %s", name, msg);
        write(sock, name_msg, strlen(name_msg));    //向sock写入name_msg
    }
    return NULL;
}

void* recv_msg(void *arg){
    int sock = *((int *)arg);
    char name_msg[NAME_SIZE + BUF_SIZE];
    while (1){
        int str_len = read(sock, name_msg, NAME_SIZE + BUF_SIZE - 1);
        if (str_len == -1)
            return (void*) -1;
        name_msg[str_len] = 0;
        cout << name_msg << endl;                   //读取来自sock的消息
    }
    return NULL;
}

int main(int argc, char *argv[]){
    if (argc != 4){
        cout << "Usage : <IP> <port> <name>" << endl;
        return -1;
    }

    int clnt_sock;
    struct sockaddr_in serv_addr;

    sprintf(name, "[%s]", argv[3]);     //user name

    clnt_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (clnt_sock == -1){
        cout << "client create socket error" << endl;
        return -1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));
    
    if (connect(clnt_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        cout << "client connect to server error" << endl;
    }

    pthread_t send_thread, recv_thread;

    pthread_create(&send_thread, NULL, send_msg, (void*)&clnt_sock);
    pthread_create(&recv_thread, NULL, recv_msg, (void*)&clnt_sock);

    /*
    pthread_detach(send_thread);
    pthread_detach(recv_thread);
    将代码修改，那么客户端会立即结束
    */ 

    pthread_join(send_thread, NULL);
    pthread_join(recv_thread, NULL);

    close(clnt_sock);
    return 0;
}
```

客户端运行并输出；

```c++
connected client ip : 127.0.0.1
connected client ip : 127.0.0.1
connected client ip : 127.0.0.1
```

服务端1：

```c++
Hi everyone
[Yoon] Hi everyone
[Choi] Hi Yoon
[Hong] Hi~ friends
```

服务端2：

```c++
[Yoon] Hi everyone
Hi Yoon
[Choi] Hi Yoon
[Hong] Hi~ friends
```

服务端3：

```c++
[Yoon] Hi everyone
[Choi] Hi Yoon
Hi~ friends
[Hong] Hi~ friends
```

注意，如果将上述代码中的 `pthread_join` 换成 `pthread_detach`会导致客户端运行之后立刻结束

> `pthread_join()`函数用于等待指定线程结束并回收其资源。在客户端中，使用`pthread_join()`函数可以让**主线程等待子线程结束后再继续执行**。而`pthread_detach()`函数则是将指定线程与当前线程分离，使得指定线程成为了“自洁”线程，结束时会自动回收资源，**不需要等待主线程处理**。如果客户端使用`pthread_detach()`，则可能导致客户端线程立即结束而没有机会正确地执行。



### 18.6 习题

1. **单 CPU 系统中如何同时执行多个进程？请解释该过程中发生的上下文切换**。

   > 在单 CPU 系统中，通过操作系统的调度算法，可以实现在同一时间同时运行多个进程。当多个进程同时运行时，CPU 会通过上下文切换来切换不同的进程，以保证它们都能得到处理器的时间片。
   >
   > **上下文切换**是指在一个进程执行到一半的时候，操作系统会将当前进程的执行环境（如寄存器、程序计数器等）保存起来，然后切换到另一个进程的执行环境，让它继续执行。当这个进程的时间片用完或者等待某些事件完成后，操作系统会再次进行上下文切换，将保存的执行环境还原回来，让进程继续执行。这个过程是通过操作系统内核进行的，因此需要在操作系统内核的支持下才能实现。
   >
   > 当多个进程同时运行时，操作系统会根据不同的调度算法来决定当前应该运行哪个进程。常见的调度算法包括先来先服务（FCFS）、时间片轮转（RR）、优先级调度等。根据不同的算法，操作系统会维护一个进程队列，用来存储所有需要执行的进程，并根据队列的顺序来决定下一个应该执行的进程。
   >
   > 在一个进程被切换出去的时候，操作系统会保存当前进程的执行环境，并将其从运行队列中移除。然后它会从队列中选择下一个要执行的进程，并将其执行环境恢复回来，开始运行这个进程。这个过程就是上下文切换。在上下文切换的过程中，操作系统需要保存和还原大量的执行环境，因此会带来一定的性能开销，特别是当进程数量增加时，上下文切换的频率也会增加，导致性能下降。因此，在设计多进程系统时，需要根据实际情况选择合适的调度算法，以提高系统的运行效率。

   答：系统将 CPU 时间分成多个微小的时间块后分配给了多个进程。为了分时使用 CPU ，需要「上下文切换」过程。运行程序前需要将相应进程信息读入内存，如果运行进程 A 后需要紧接着运行进程 B ，就应该将进程 A 相关信息移出内存，并读入进程 B 的信息。这就是上下文切换

   

2. **为何线程的上下文切换速度相对更快？线程间数据交换为何不需要类似 IPC 特别技术**。

   > 线程的上下文切换速度相对更快是因为线程是轻量级的，其创建和销毁所需的时间都比进程少得多。**线程是在同一进程中创建的，它们共享进程的地址空间和其他资源，因此线程之间的数据交换可以直接进行，不需要像进程之间的 IPC 通信那样需要使用特别的技术。**
   >
   > 线程之间数据的交换可以通过共享内存、全局变量等方式进行，由于线程间共享进程地址空间，这些数据对于线程都是可见的。而进程之间要通过共享文件、管道、消息队列、共享内存等方式进行数据交换，这些通信方式都需要在进程间复制数据，所以速度比线程间数据交换慢。此外，由于进程间数据交换需要通过内核空间进行，因此开销更大，切换速度更慢。

   答：线程上下文切换过程不需要切换数据区和堆。可以利用数据区和堆交换数据。

   

3. **请从执行流角度说明进程和线程的区别**。

   > 从执行流的角度来看，进程和线程的主要区别在于它们的执行方式。
   >
   > **一个进程通常包括一个或多个线程，它们共享进程的内存空间和资源，但拥有独立的执行流**。每个进程都有自己的地址空间、全局变量和文件描述符等，进程之间的通信需要使用特殊的IPC机制，如管道、消息队列、共享内存等。
   >
   > 线程是轻量级的执行流，它们共享进程的内存空间和资源，但拥有独立的执行堆栈和局部变量。线程之间的通信可以直接访问共享的内存空间和全局变量，不需要使用IPC机制。由于线程共享了进程的地址空间和资源，因此线程之间的上下文切换相对进程更加快速。

   答：进程：在操作系统构成单独执行流的单位。线程：在进程内部构成单独执行流的单位。线程为了保持多条代码执行流而隔开了栈区域。

   

4. **下面关于临界区的说法错误的是**？

   答：下面加粗的选项为说法正确。（全错）

   1. 临界区是多个线程同时访问时发生问题的区域
   2. 线程安全的函数中不存在临界区，即便多个线程同时调用也不会发生问题
   3. 1 个临界区只能由 1 个代码块，而非多个代码块构成。换言之，线程 A 执行的代码块 A 和线程 B 执行的代码块 B 之间绝对不会构成临界区。
   4. 临界区由访问全局变量的代码构成。其他变量中不会发生问题。

   

5. **下列关于线程同步的说法错误的是**？

   答：下面加粗的选项为说法正确。

   1. 线程同步就是限制访问临界区

   2. **线程同步也具有控制线程执行顺序的含义**

   3. **互斥量和信号量是典型的同步技术**

   4. 线程同步是代替进程 IPC 的技术。

      

6. **请说明完全销毁 Linux 线程的 2 种办法**

   答：①调用 pthread_join 函数

   ​	   ②调用 pthread_detach 函数。

   第一个会阻塞调用的线程，而第二个不阻塞。都可以引导线程销毁。





## 第 19 章 Windows 平台下线程的使用



## 第 20 章 Windows 中的线程同步

暂略



## 第 21 章 异步通知 I/O 模型

暂略



## 第 22 章 重叠 I/O 模型

暂略



## 第 23 章 IOCP

暂略



## 第 24 章 制作 HTTP 服务器端

### 24.1 HTTP 概要

本章将编写 HTTP（HyperText Transfer Protocol，超文本传输协议）服务器端，即 Web 服务器端。



**理解 Web 服务器端**

web服务器端就是要基于 HTTP 协议，将网页对应文件传输给客户端的服务器端。



**HTTP**

无状态的 Stateless 协议

![img](TCPIP网络编程.assets/68747470733a2f2f692e6c6f6c692e6e65742f323031392f30322f30372f356335626336393733613464302e706e67.png)

从上图可以看出，服务器端相应客户端请求后立即断开连接。换言之，服务器端不会维持客户端状态。即使同一客户端再次发送请求，服务器端也无法辨认出是原先那个，而会以相同方式处理新请求。因此，HTTP 又称「无状态的 Stateless 协议」

**Cookie & Session**

> 为了弥补HTTP无法保持连接的缺点,Web编程中通常会使用Cookie和Session技术。相信各位都接触过购物网站的购物车功能,即使关闭浏览器也不会丢失购物车内的信息(甚至不用登录)。这种保持状态的功能都是通过Cookie和 Session技术实现的。



**请求消息（Request Message）的结构**

下面是客户端向服务端发起请求消息的结构：

![img](TCPIP网络编程.assets/68747470733a2f2f692e6c6f6c692e6e65742f323031392f30322f30372f356335626362623735323032662e706e67.png)

从图中可以看出，请求消息可以分为**请求头、消息头、消息体** 3 个部分。其中，请求行含有请求方式（请求目的）信息。典型的请求方式有 GET 和 POST ，GET 主要用于请求数据，POST 主要用于传输数据。为了降低复杂度，我们实现只能响应 GET 请求的 Web 服务器端，下面解释图中的请求行信息。其中「GET/index.html HTTP/1.1」 具有如下含义：

> **请求（GET）index.html 文件，通常以 1.1 版本的 HTTP 协议进行通信。**

请求行只能通过 1 行（line）发送，因此，服务器端很容易从 HTTP 请求中提取第一行，并分别分析请求行中的信息。

请求行下面的消息头中包含发送请求的浏览器信息、用户认证信息等关于 HTTP 消息的附加信息。最后的消息体中装有客户端向服务端传输的数据，为了装入数据，需要以 POST 方式发送请求。但是我们的目标是实现 GET 方式的服务器端，所以可以忽略这部分内容。另外，消息体和消息头与之间以空行隔开，因此不会发生边界问题



 **响应消息（Response Message）的结构**

下面是 Web 服务器端向客户端传递的响应信息的结构。从图中可以看出，该响应消息由状态行、头信息、消息体等 3 个部分组成。状态行中有关于请求的状态信息，这是与请求消息相比最为显著地区别。

![img](TCPIP网络编程.assets/68747470733a2f2f692e6c6f6c692e6e65742f323031392f30322f30372f356335626639616431623566392e706e67.png)

第一个字符串状态行中含有关于客户端请求的处理结果。例如，客户端请求 index.html 文件时，表示 index.html 文件是否存在、服务端是否发生问题而无法响应等不同情况的信息写入状态行。图中的「HTTP/1.1 200 OK」具有如下含义：

- **200 OK : 成功处理了请求!**
- **404 Not Found : 请求的文件不存在!**
- **400 Bad Request : 请求方式错误，请检查！**

消息头中含有传输的数据类型和长度等信息。图中的消息头含有如下信息：

> 服务端名为 SimpleWebServer ，传输的数据类型为 text/html。数据长度不超过 2048 个字节。

最后插入一个空行后，通过消息体发送客户端请求的文件数据。以上就是实现 Web 服务端过程中必要的 HTTP 协议。



### 24.2 实现简单的 Web 服务器端

**实现基于 Windows 的多线程 Web 服务器端**

暂略



**实现基于 Linux 的多线程 Web 服务器端**

服务端[webServ.cpp]

```c++
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
    send_data(clnt_write, ct, file_name);   
    return NULL;
}

void send_data(FILE *fp, char *ct, char *file_name){
    char protocol[] = "HTTP/1.0 200 OK \r\n";
    char server[] = "Server : Linux Web Server\n";
    char cnt_len[] = "Content-length: 2048 \r\n";
    char cnt_type[SMALL_BUF], buf[BUF_SIZE];

    sprintf(cnt_type, "Content-type:%s\r\n\r\n", ct);

    FILE *send_file = fopen(file_name, "r");
    if (send_file == NULL){
        send_error(fp);
        return ;
    }

    //传输头信息
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
    strcpy(file_name, file);	//例如文件名index.html,得到的扩展名就是html

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
```

编译并运行；

```c++
g++ webServ.cpp -o webServ -lpthread	//会产生warming，但不影响
./webServ 9190
```

在终端中利用lynx来访问

```shell
root@tang:/home/tang# lynx http://localhost:9190/index.html
```

<img src="TCPIP网络编程.assets/image-20230417124216340.png" alt="image-20230417124216340" style="zoom:80%;" />

服务端的输出；

```shell
Connection request : 127.0.0.1:52860
```

在Windows下的浏览器打开可能会导致页面无法显示



### 24.3 习题 

1. **下列关于 Web 服务器端和 Web 浏览器端的说法错误的是**？

   答：以下加粗选项代表正确。

   1. **Web 浏览器并不是通过自身创建的套接字连接服务端的客户端**
   2. Web 服务器端通过 TCP 套接字提供服务，因为它将保持较长的客户端连接并交换数据
   3. 超文本与普通文本的最大区别是其具有可跳转的特性
   4. Web 浏览器可视为向浏览器提供请求文件的文件传输服务器端
   5. 除 Web 浏览器外，其他客户端都无法访问 Web 服务器端。

   > **Web 浏览器使用的是应用层协议 HTTP 来进行客户端与服务端之间的通信，而不是直接使用套接字连接。**
   >
   > 当用户在浏览器的地址栏中输入一个 URL 地址时，浏览器会根据 URL 中的主机名和端口号向 DNS 服务器发起查询获取对应的 IP 地址。然后浏览器会创建一个连接到该 IP 地址上的端口号 80（如果 URL 中没有指定端口号）的套接字。这个套接字是由操作系统的网络协议栈创建的，而不是浏览器自身创建的。
   >
   > 然后，浏览器会构造 HTTP 请求报文并通过套接字发送给服务端。服务端接收到请求报文后进行处理，再将响应报文通过套接字返回给客户端。浏览器接收到响应报文后对其进行解析，显示对应的 HTML 内容。这个过程中，浏览器只需要使用操作系统提供的网络 API，而无需直接管理套接字连接。

   

2. **下列关于 HTTP 协议的描述错误的是**？

   答：以下加粗选项代表正确。

   1. HTTP 协议是无状态的 Stateless 协议，不仅可以通过 TCP 实现，还可以通过 UDP 来实现

   2. **HTTP 协议是无状态的 Stateless 协议，因为其在 1 次请求和响应过程完成后立即断开连接。因此，如果同一服务器端和客户端需要 3 次请求及响应，则意味着需要经过 3 次套接字的创建过程**。

      > 在HTTP/1.0中，默认使用非持久连接，即每次请求和响应之后都会关闭连接。而在HTTP/1.1中，默认使用持久连接，即在一定时间内保持连接，可以通过使用Connection头来控制连接的行为。

   3. **服务端向客户端传递的状态码中含有请求处理结果的信息**。

   4. **HTTP 协议是基于因特网的协议，因此，为了同时向大量客户端提供服务，HTTP 协议被设计为 Stateless 协议**。
