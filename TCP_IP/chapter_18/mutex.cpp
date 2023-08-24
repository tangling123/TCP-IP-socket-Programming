#include <iostream>
#include <pthread.h>
#include <cstring>
#include <unistd.h>
using namespace std;

#define NUM_THREAD 100

long long num = 0;
pthread_mutex_t mutex;  //互斥量

void* thread_inc(void *arg){
    pthread_mutex_lock(&mutex);  //加锁
    for (int i = 0; i < 500000000; i++)
        num++;  //临界区
    pthread_mutex_unlock(&mutex);//解锁
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

    pthread_mutex_destroy(&mutex);   //互斥量的销毁

    return 0;
}