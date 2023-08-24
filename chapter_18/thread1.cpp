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

    if (pthread_create(&t_id, NULL, thread_main, &thread_param) != 0){
        cout << "pthread_create error" << endl;
        return -1;
    }

    sleep(10);
    cout << "end of main" << endl;
    return 0;
}