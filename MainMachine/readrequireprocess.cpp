#include "readrequireprocess.h"

ReadRequireProcess::ReadRequireProcess()
{

}

ReadRequireProcess::~ReadRequireProcess()
{

}


ReadRequireProcess::ReadRequireProcess(MasterControl *mc): stopped(true){
    this->mc = mc;
}

//线程的开始
void ReadRequireProcess::started(){
    if (stopped == true){
        stopped = false;
        this->start();
    }
}

//线程的暂停函数
void ReadRequireProcess::stopping(){
    stopped = true;
}

void ReadRequireProcess::run(){
      while(true) {
          mc->analyzeRequire(mc->readRequire());
      }
}

ReadRequireProcess::~ReadRequireProcess(){

}

