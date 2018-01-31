#include "normalcommunicationprocess.h"



NormalCommunicationProcess::NormalCommunicationProcess(MasterControl *mc): stopped(true){
    this->mc = mc;
}

//线程的开始
void NormalCommunicationProcess::started(){
    if (stopped == true){
        stopped = false;
        this->start();
    }
}

//线程的暂停函数
void NormalCommunicationProcess::stopping(){
    stopped = true;
}

void NormalCommunicationProcess::run(){
       while(true) {
           mc->normalCommunicate();
           Sleep(normal_time);
       }

}

NormalCommunicationProcess::~NormalCommunicationProcess(){

}
