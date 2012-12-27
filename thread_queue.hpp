#ifndef THREAD_QUEUE_HPP
#define THREAD_QUEUE_HPP

#include <queue>
#include <utils/threads.h>

using std::queue;
using android::Mutex;
using android::AutoMutex;
using android::Condition;

template <typename T>
class Queue {
public:
    Queue();
    void push(const T &);
    void push_back(const T &);
    void pop();
    bool empty() const;
    typename queue<T>::size_type size() const;
    typename queue<T>::reference front();
    typedef typename queue<T>::value_type value_type;
private:
    mutable Mutex mLock;
    Condition condition;
    queue<T> q;
};

#endif
