#include "hotel_controll.h"
#include <Qthread>
#include <QMutex>
#include <iostream>
#include <Windows.h>
#include<QTextStream>

//线程的开始
void Hotel::started()
{
    if (stopped == true)
    {
        stopped = false;
        this->start();
    }
}

//线程的暂停函数
void Hotel::stopping()
{
    stopped = true;
}

void Hotel::appendstr(QString str)
{
    lock.lock();
    temp.append(str+ "$$");
    emit MesArrival();
    lock.unlock();
}

Hotel::Hotel():stopped(true)
{
    room.setCost(100);
    room.setEcost(500);
    room.SetGoalTemp(25);
    room.setRoomT(25);
    room.SetModel(hot);
    room.setRoomN(105);
    room.setOutT(25);
    room.SetState(on);
    room.SetWind(low);
}

Hotel::Hotel(float temO, float temR, int num, AC_MODEL m, float gTem, SPEED_WIND w):stopped(true)
{
    //room = Hotel_room(temO,temR,num);
    room.SetGoalTemp(gTem);
    room.SetWind(w);
    room.setCost(0);
    room.setEcost(0);
    room.SetModel(m);
    room.SetState(off);

}

void Hotel::setTemOut(float o)
{
    room.setOutT(o);
}

float Hotel::getTemOut()
{
    return room.getOutT();
}

void Hotel::setTemRoom(float r)
{
    room.setRoomT(r);
}

float Hotel::getTemRoom()
{
    return room.getRoomT();
}

void Hotel::setRoomNum(int n)
{
    room.setRoomN(n);
}

int Hotel::getRoomNum()
{
    return room.getRoomN();
}

void Hotel::setGoalTemp(float r)
{
    room.SetGoalTemp(r);
}

float Hotel::getGoalTemp()
{
    return room.getGoalTemp();
}

void Hotel::setWindSpeed(SPEED_WIND w)
{
    room.SetWind(w);
}

SPEED_WIND Hotel::getWindSpeed()
{
    return room.getWind();
}

void Hotel::setCost(float c)
{
    room.setCost(c);
}

float Hotel::getCost()
{
    return room.getCost();
}

void Hotel::setECost(float e)
{
    room.setEcost(e);
}

float Hotel::getECost()
{
    return room.getEcost();
}

void Hotel::setModel(AC_MODEL ac)
{
      room.SetModel(ac);
}

AC_MODEL Hotel::getModel()
{
    return room.getModel();
}

void Hotel::setState(AC_STATE s)
{
    room.SetState(s);
}

AC_STATE Hotel::getState()
{
    return room.getState();
}

void Hotel::run()
{
    while(!stopped)
    {

    sleep(1);
    int flag=room.calFinTem();

    if(flag==3 || flag==4)
    {
        QString str=QString("%1").arg(flag)+" "+QString("%1").arg(this->getRoomNum())+" "+QString("%1").arg(this->getTemRoom())+" "+QString("%1").arg(this->getGoalTemp())+" "+QString("%1").arg(this->getWindSpeed());
        this->appendstr(str);
    }


    QString s=room.ShowMes();
    qDebug() << s <<endl;

    }

}

QString Hotel::getMes(){
    QStringList item = temp.split("$$");
    if (item.length() == 0) return "";

    lock.lock();

    QString str = item[0];
    item.removeAt(0);

    temp.clear();
    temp.append(item.join("$$"));
    lock.unlock();

    return str;
}

Hotel::~Hotel()
{
    //delete(kernel);
}

