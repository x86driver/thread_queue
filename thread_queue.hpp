#ifndef THREAD_QUEUE_HPP
#define THREAD_QUEUE_HPP

#include <queue>
#include <utils/threads.h>

using std::queue;
using android::Mutex;
using android::AutoMutex;

template <typename T>
class Queue {
public:
    Queue();
    void push(const T &);
    void pop();
    bool empty() const;
    typename queue<T>::size_type size() const;
    typename queue<T>::reference front();
private:
    mutable Mutex mLock;
    queue<T> q;
};

#endif
