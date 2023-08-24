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