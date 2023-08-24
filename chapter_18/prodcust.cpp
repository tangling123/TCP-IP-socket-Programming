#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

struct ListNode{
    int val;
    ListNode* next;
    ListNode() : val(-1), next(nullptr){}
    ListNode(int v) : val(v), next(nullptr){}
    ListNode(int v, ListNode* ne) : val(v), next(ne){}
};


ListNode* head = new ListNode();
pthread_mutex_t mutex;
//对于临界区的数据需要进行加锁

void* addNode(void* arg){
    //生产者的main函数
    while (1){
        //使用头插法的方式向链表中插入节点
        pthread_mutex_lock(&mutex);
        ListNode* newNode = new ListNode(rand() % 1000, head);    //结点值为0-1000的随机数
        head = newNode;
        cout << "add node tid : " << pthread_self() << " val : " << newNode->val << endl;
        pthread_mutex_unlock(&mutex);
    }
}

void* removeNode(void* arg){
    //消费者的mian函数
    while (1){
        pthread_mutex_lock(&mutex);
        ListNode* t = head;
        head = head->next;
        cout << "remove node tid : " << pthread_self() << " val : " << t->val << endl;
        delete t;
        pthread_mutex_unlock(&mutex);
    }
}

/*
*   对于生产者消费者模型，可能在生产者生产之前消费者就已经开始消费
*   但此时容器中并没有数据，应通知生产者去生产
*   通过条件变量和互斥锁来处理生产者-消费者模型
*/

int main(){
    pthread_mutex_init(&mutex, NULL);
    pthread_t prod[5], cust[5];

    for (int i = 0; i < 5; i++){
        pthread_create(&prod[i], NULL, addNode, NULL);
        pthread_create(&cust[i], NULL, removeNode, NULL);
    }

    for (int i = 0; i < 5; i++){
        pthread_detach(prod[i]);
        pthread_detach(cust[i]);
    }

    pthread_mutex_destroy(&mutex);
    while (1){
        usleep(100);
    }

    pthread_exit(NULL);
    return 0;
}