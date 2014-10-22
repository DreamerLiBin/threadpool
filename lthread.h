#ifndef LTHREAD_H
#define LTHREAD_H

#include <pthread.h>
using namespace std;

class LBaseJob;
class LThreadPool;

class LThread {
public:
    LThread();
    ~LThread();
    void run();
    bool init(LThreadPool* thpool);
    bool get_status() { return status_; }
    unsigned long get_tid() { return tid_; }
    void set_status(bool status)  { status_ = status; }
    void set_tid(int tid) { tid_ = tid; }
    void set_job(LBaseJob* job) { job_ = job; }
    void set_thread_pool(LThreadPool* thpool) { threadpool_ = thpool; }
private:
    LBaseJob* job_;
    LThreadPool* threadpool_;
    pthread_t* lpthread_;
    unsigned long tid_;
    /* status is true(busy) or false(idle) */
    bool status_;
};

#endif
