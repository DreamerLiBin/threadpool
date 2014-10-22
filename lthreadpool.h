#ifndef LTHPOOL_H
#define LTHPOOL_H

#include <pthread.h>
#include <list>
using namespace std;

class LThread;
class LBaseJob;

class LThreadMutex {
public:
    LThreadMutex() { pthread_mutex_init(&lock_, NULL); }
    ~LThreadMutex() { pthread_mutex_destroy(&lock_); }
    void lock() { pthread_mutex_lock(&lock_); }
    void unlock() { pthread_mutex_unlock(&lock_); }
private:
    pthread_mutex_t lock_;
};

class LThreadPool {
public:
    LThreadPool();
    LThreadPool(int init_thread_num);
    virtual ~LThreadPool();
    LThreadMutex mutex_busy;
    LThreadMutex mutex_idle;
    list<LThread*> busylist;
    list<LThread*> idlelist;

    void set_init_thread(int init_thread_num) { init_thread_num_ = init_thread_num; }
    void set_max_thread(int max_thread_num) { max_thread_num = max_thread_num_; }
    int get_init_thread() { return init_thread_num_; }
    int get_max_thread() { return max_thread_num_; }
    int get_busy_size() { return busylist.size(); }
    int get_idle_size() { return idlelist.size(); }
    int get_all_size() { return busylist.size() + idlelist.size(); }
    LThread* get_idle_thread();
    void move_to_busy(LThread*);
    void move_to_idle(LThread*);
    void destroy();
    void run(LBaseJob* job);

private:
    bool alive_;
    int  init_thread_num_;
    int  max_thread_num_;
};

#endif
