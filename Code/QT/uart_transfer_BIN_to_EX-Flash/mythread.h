#ifndef MYTHREAD_H
#define MYTHREAD_H
#include "main.h"

class myThread: public QThread
{
public:
    myThread();
    void run();
    void stop();
    void goOn();
private:
    volatile bool stoped;

};

#endif // MYTHREAD_H

