#include <iostream>
#include <pthread.h>
#include <cstring>
#include <unistd.h>
using namespace std;

#define NUM_THREAD 100

long long num = 0;

void* thread_inc(void *arg){
    for (int i = 0; i < 500000000; i++)
        num++;
    return NULL;
}

void* thread_des(void *arg){
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