#ifndef NORMALCOMMUNICATIONPROCESS_H
#define NORMALCOMMUNICATIONPROCESS_H

#include "MasterControl.h"
#include <Qthread>
#include <QMutex>
#include <iostream>
#include <Windows.h>
using namespace std;


//执行部件，线程模板

class NormalCommunicationProcess : public QThread{
private:
    bool stopped;
    MasterControl *mc;

protected:
    void run();

public:
    NormalCommunicationProcess(MasterControl *mc);
    ~NormalCommunicationProcess();

    //启动进程的执行
    void started();

    //停止进程的执行
    void stopping();



};

#endif // NORMALCOMMUNICATIONPROCESS_H
