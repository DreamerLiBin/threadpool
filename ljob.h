#ifndef LJOB_H
#define LJOB_H

class LBaseJob {
public:
    virtual void run() { routine(arg); }
    void* (*routine)(void*);
    void* arg;
};

#endif
