#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

pthread_mutex_t mutex1, mutex2;

void* workA(void *arg){
    pthread_mutex_lock(&mutex1);
    sleep(1);
    pthread_mutex_lock(&mutex2);

    cout << "workA runing" << endl;
    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);

    return NULL;
}

void* workB(void *arg){
    //如果先对1加锁在对2加锁，那么当workA执行完毕之后会再来执行workB
    //workA对1加锁，同时workdB对2加锁，他们之间相互竞争资源而导致产生的死锁
    pthread_mutex_lock(&mutex2);
    pthread_mutex_lock(&mutex1);

    cout << "workB runing" << endl;
    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);

    return NULL;
}

int main(){
    pthread_mutex_init(&mutex1, NULL);
    pthread_mutex_init(&mutex2, NULL);

    //创建两个相互竞争资源的线程来演示死锁
    pthread_t tid1, tid2;

    pthread_create(&tid1, NULL, workA, NULL);
    pthread_create(&tid2, NULL, workB, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&mutex2);

    return 0;
}