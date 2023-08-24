#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

int num;
pthread_rwlock_t rwlock;

void* readNum(void *arg){
    while (1){
        pthread_rwlock_rdlock(&rwlock);
        cout << "read number, pid : " << pthread_self() << " : num " << num << endl;
        pthread_rwlock_unlock(&rwlock);
        usleep(100); 
    }

    return NULL;
}

void* writeNum(void *arg){
    while (1){
        pthread_rwlock_wrlock(&rwlock);
        num++;
        cout << "write number, pid : " << pthread_self() << " : num " << num << endl;
        pthread_rwlock_unlock(&rwlock);
        usleep(100); 
    }

    return NULL;
}

int main(){
    //对读写锁的初始化
    pthread_rwlock_init(&rwlock, NULL);

    //模拟多个进程来进行读写
    pthread_t wrtids[3], rdtids[5];

    for (int i = 0; i < 3; i++){
        pthread_create(&wrtids[i], NULL, writeNum, NULL);
    }

    for (int i = 0; i < 5; i++){
        pthread_create(&rdtids[i], NULL, readNum, NULL);
    }

    //线程分离
    for (int i = 0; i < 3; i++){
        pthread_detach(wrtids[i]);
    }

    for (int i = 0; i < 5; i++){
        pthread_detach(rdtids[i]);
    }


    //即使主线程结束之后子进程也能继续执行
    pthread_exit(NULL);

    pthread_rwlock_destroy(&rwlock);

    return 0;
}