#include "mythread.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

void myThread::run()
{
    while(!stoped){

    }
    stoped = true;
}

myThread::myThread()
{

    stoped = false;
}

void myThread::stop()
{
    stoped = true;
}
void myThread::goOn()
{
    stoped = false;
}
