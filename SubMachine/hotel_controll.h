#ifndef PCONTROL_H
#define PCONTROL_H

#include <Qthread>
#include <QMutex>
#include <iostream>
#include <Windows.h>
#include <QDebug>
#include"hotel_room.h"
#include <QMutex>
using namespace std;

class Hotel: public QThread
{
    Q_OBJECT
private:
    bool stopped;
    QString temp;
    Hotel_room room;
    QMutex lock;
    void appendstr(QString str);
protected:
    void run();

signals:
    int MesArrival();

public:

    Hotel(float temO, float temR, int num, AC_MODEL m, float gTem, SPEED_WIND w);

    Hotel();

    ~Hotel();

    QString getMes();

    void started();

    void stopping();



    void setTemOut(float o);

    float getTemOut();

    void setTemRoom(float r);

    float getTemRoom();

    void setRoomNum(int n);

    int getRoomNum();

    void setGoalTemp(float r);

    float getGoalTemp();

    void setWindSpeed(SPEED_WIND w);

    SPEED_WIND getWindSpeed();

    void setCost(float c);

    float getCost();

    void setECost(float e);

    float getECost();

    void setModel(AC_MODEL ac);

    AC_MODEL getModel();

    void setState(AC_STATE s);

    AC_STATE getState();


};
#endif

