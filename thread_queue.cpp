#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include "thread_queue.hpp"

template <typename T>
Queue<T>::Queue()
  : mLock(), condition(), q()
{
}

template <typename T>
void Queue<T>::push(const T &value)
{
    AutoMutex _l(mLock);

    q.push(value);
    condition.signal();
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

    if (q.empty()) {
        condition.wait(mLock);
    }

    return q.front();
}

void *thread1(void *data)
{
    Queue<uint8_t> *queue = static_cast<Queue<uint8_t> *>(data);

    for (int i = 0; i < 100000; ++i) {
        queue->push(rand() % 256);
    }
    printf("thread1 done\n");
    return NULL;
}

void *thread2(void *data)
{
    Queue<uint8_t> *queue = static_cast<Queue<uint8_t> *>(data);

    for (int i = 0; i < 100000; ++i) {
        queue->push(rand() % 256);
    }
    printf("thread2 done\n");
    return NULL;
}

int main()
{
    Queue<uint8_t> queue;
    pthread_t tid1, tid2;

    srand(time(0));

    pthread_create(&tid1, NULL, thread1, &queue);
    pthread_create(&tid2, NULL, thread2, &queue);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("size: %u\n", queue.size());
    return 0;
}
