#ifndef READREQUIREPROCESS_H
#define READREQUIREPROCESS_H
#include "MasterControl.h"
#include <Qthread>
#include <QMutex>
#include <iostream>
#include <Windows.h>
using namespace std;

class ReadRequireProcess : public QThread{
private:
    bool stopped;
    MasterControl *mc;

protected:
    void run();

public:
    ReadRequireProcess(MasterControl *mc);
    ~ReadRequireProcess();

    //启动进程的执行
    void started();

    //停止进程的执行
    void stopping();



};

#endif // READREQUIREPROCESS_H
