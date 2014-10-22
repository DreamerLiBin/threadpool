#include <stdio.h>
#include <unistd.h>
#include <cassert>

#include "ljob.h"
#include "lthread.h"
#include "lthreadpool.h"
using namespace std;

LThread::LThread():tid_(-1), status_(false), threadpool_(NULL)
{
    lpthread_ = new pthread_t;
}

LThread::~LThread()
{
    if (lpthread_ != NULL) {
	delete lpthread_;
	lpthread_ = NULL;
    }
    if (job_ != NULL) {
        delete job_;
        job_ = NULL;
    }
    threadpool_ = NULL;
}

void LThread::run()
{
    for (; true; usleep(10)) {
        while (job_ == NULL) {
            usleep(20);
        }
        status_ = true;
        job_->run();
        job_ = NULL;
        status_ = false;
        threadpool_->move_to_idle(this);
    }
}

static void* thread_routine(void* arg)
{
    LThread* th = (LThread*)arg;
    th->run();
}

bool LThread::init(LThreadPool* thpool)
{
    threadpool_ = thpool;
    int ret = pthread_create(lpthread_, NULL, thread_routine, (void*)this);
    assert(ret == 0);
    tid_ = *lpthread_;
    return true;
}
