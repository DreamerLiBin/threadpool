#include <stdio.h>
#include <unistd.h>
#include <cassert>

#include "lthread.h"
#include "ljob.h"
#include "lthreadpool.h"
using namespace std;

LThreadPool::LThreadPool()
{
    init_thread_num_ = 5;
    max_thread_num_ = 15;
    busylist.clear();
    idlelist.clear();
    int i;
    for (i = 0; i < init_thread_num_; ++i) {
        LThread* thread = new LThread();
        thread->init(this);
        idlelist.push_back(thread);
    }
    alive_ = true;
}

LThreadPool::LThreadPool(int init_thread_num)
{
    init_thread_num_ = init_thread_num;
    max_thread_num_ = 15;
    int i;
    for (i = 0; i < init_thread_num; ++i) {
        LThread* thread = new LThread();
        thread->init(this);
        idlelist.push_back(thread);
    }
    alive_ = true;
}

LThreadPool::~LThreadPool()
{
    destroy();
}

void LThreadPool::move_to_busy(LThread* thread)
{
    mutex_busy.lock();
    busylist.push_back(thread);
    mutex_busy.unlock();
}

void LThreadPool::move_to_idle(LThread* thread)
{
    mutex_idle.lock();
    idlelist.push_back(thread);
    mutex_idle.unlock();
}

LThread* LThreadPool::get_idle_thread()
{
    while (get_idle_size() <= 0) {
        usleep(10);
    }
    LThread* thread = NULL;
    mutex_idle.lock();
    if (get_idle_size() > 0) {
        thread = idlelist.front();
        idlelist.pop_front();
    }
    mutex_idle.unlock();
    return thread;
}

void LThreadPool::destroy()
{
    if (!alive_) {
        printf("The threadpool is not alive\n");
        return;
    }
    list<LThread*>::iterator iter;
    mutex_idle.lock();
    /* clear() will do delete and free the memory */
    idlelist.clear();
    mutex_idle.unlock();
    mutex_busy.lock();
    busylist.clear();
    mutex_busy.unlock();
}

void LThreadPool::run(LBaseJob* job)
{
    assert(job != NULL);
    LThread* thread = get_idle_thread();
    if (thread != NULL) {
        move_to_busy(thread);
        thread->set_thread_pool(this);
        thread->set_job(job);
    }
}
