#include <iostream>
#include <thread>
#include <semaphore.h>
using namespace std;

static int num;
static sem_t sem_one, sem_two;  //使用两个信号量

void* read(void *arg){
    for (int i = 0; i < 5; i++){
        cout << "Input num : ";
        sem_wait(&sem_two);     //对sem_two信号量加锁 1 -> 0
        cin >> num;
        sem_post(&sem_one);     //对sem_one进行释放   0 -> 1
    }
    return NULL;
}

void* accu(void *arg){
    int sum = 0;
    for (int i = 0; i < 5; i++){
        sem_wait(&sem_one);     //对sem_one进行释放   1 -> 0
        sum += num; //临界区
        sem_post(&sem_two);     //对sem_two信号量加锁 0 -> 1
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