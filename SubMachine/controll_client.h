#ifndef CONTROLL_CLIENT_H
#define CONTROLL_CLIENT_H
#include<QTimer>
#include <QWidget>
#include <Qfile>
#include <QString>
#include <QTextStream>
#include "socket_client.h"
#include "hotel_controll.h"
class Controll_client : public QWidget
{
    Q_OBJECT
public:
    explicit Controll_client(QWidget *parent=0);

    void send(QString str);

    void connected();

    void close_connect();

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

signals:
    int mesArrive();

    int linkChanged(QString state);
private:
    Socket_client *client;

    Hotel *room;

    QTimer *timer;

    int count;

    void setfrequence(int fre);

    void client_para_change_1(QStringList mes);

    void client_para_change_0(QStringList mes);

    void initialize(void);


private slots:
    
    void getMes();

   
    void mesSend();

   
    void SendMes();

    void linkChange(QString state);
};

#endif // CONTROLL_CLIENT_H
