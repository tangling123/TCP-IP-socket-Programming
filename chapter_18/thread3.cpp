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

    if (pthread_join(id_t1, NULL) != 0){
        cout << "pthread_join error" << endl;
    }
        
    if (pthread_join(id_t2, NULL) != 0){
        cout << "pthread_join error" << endl;
    }

    cout << sum << endl;

    return 0;
}