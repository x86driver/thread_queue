#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include "thread_queue.hpp"

pthread_mutex_t mutex;

template <typename T>
Queue<T>::Queue()
    : mLock(), q()
{
    
}

template <typename T>
void Queue<T>::push(const T &value)
{
    AutoMutex _l(mLock);

    q.push(value);
}

template <typename T>
void Queue<T>::pop()
{
    AutoMutex _l(mLock);

    q.pop();
}

template <typename T>
bool Queue<T>::empty() const
{
    AutoMutex _l(mLock);

    return q.empty();
}

template <typename T>
typename queue<T>::size_type Queue<T>::size() const
{
    AutoMutex _l(mLock);

    return q.size();
}

template <typename T>
typename queue<T>::reference Queue<T>::front()
{
    AutoMutex _l(mLock);

    return q.front();
}

void *thread1(void *data)
{
    Queue<int> *queue = static_cast<Queue<int> *>(data);

    for (int i = 0; i < 1000; ++i) {
        queue->push(rand() % 100);
    }
    return NULL;
}

void *thread2(void *data)
{
    Queue<int> *queue = static_cast<Queue<int> *>(data);

    for (int i = 0; i < 1000; ++i) {
        queue->push(rand() % 100);
    }
    return NULL;
}

int main()
{
    Queue<int> queue;
    pthread_t tid1, tid2;

    srand(time(0));

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&tid1, NULL, thread1, &queue);
    pthread_create(&tid2, NULL, thread2, &queue);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("size: %u\n", queue.size());

    return 0;
}
