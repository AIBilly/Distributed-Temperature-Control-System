#include "controll_client.h"

Controll_client::Controll_client(QWidget *parent) :count(0)
{
    initialize();
}
void Controll_client::mesSend(){
    QString temp = room->getMes();
    client->send(temp);
    qDebug() << "send: " + temp;
}

//定时通信
void Controll_client::SendMes(){
    client->send("0 "+ QString::number(room->getRoomNum()) + " " + QString("%1").arg(room->getTemRoom())
                 + " " + QString::number(room->getGoalTemp())+ " " + QString::number(room->getWindSpeed()+1));
}

//得到返回的信息，并进行指定的操作，需补充这里
void Controll_client::getMes(){
    QString temp = client->recive();
    QStringList paralist = temp.split(" ");
    qDebug() << "client: " <<temp;
    if(paralist.length() != 8)
        return;

    switch(paralist[0].toInt()){
        case 0:
            client_para_change_0(paralist);
            break;
        case 1:
            client_para_change_1(paralist);
            break;
        default:
            return;
    }
    emit mesArrive();
}

//有需求时使用
void Controll_client::send(QString str){
    client->send(str);
}

void Controll_client::connected(){
    client->connect_to_host();
}

void Controll_client::close_connect(){
    client->close_connect();
}

void Controll_client::setfrequence(int fre){
    timer->stop();
    timer->setInterval(fre * 1000);
    timer->start();
}

void Controll_client::client_para_change_0(QStringList mes){
    if(mes.length() != 8)
        return;
   // qDebug()<<"mes:"<<mes<<endl;
    //是否送风


    if(room->getState() != off)
    {
        if(mes[1] == "1")
            room->setState(on);
        else
            room->setState(stay);


        //模式
        if(mes[2] == "1")
            room->setModel(cold);
        else
            room->setModel(hot);


        //目标温度
        room->setGoalTemp(mes[3].toFloat());


        //风速
        if(mes[4] == "1")
            room->setWindSpeed(low);
        if(mes[4] == "2")
            room->setWindSpeed(middle);
        if(mes[4] == "3")
            room->setWindSpeed(high);

        if(mes[7].toInt() > 0)
            this->setfrequence(mes[7].toInt());
    }


}
void Controll_client::client_para_change_1(QStringList mes){
    if(mes.length() != 8)
        return;

    room->setECost(mes[5].toFloat());

    room->setCost(mes[6].toFloat());
}
void Controll_client::initialize(void){
    QFile* ini;
    ini = new QFile("initialize.txt");
    if(!ini->open(QIODevice::ReadOnly))
    {
        qDebug()<<"failed!";
    }
    else
    {
        AC_MODEL mode;
        SPEED_WIND wind_speed;
        QStringList result;
        QTextStream fin(ini);
        QString line;
        while (!fin.atEnd())
        {
            line = fin.readLine();
            QStringList myline = line.split(":");
            if(myline.size()==2)
            {
                result.push_back(myline[1]);
            }
        }
        if(result[6]=="hot")
            mode=hot;
        else
            mode=cold;

        if(result[7]=="low")
            wind_speed=low;
        else if(result[7]=="middle")
            wind_speed=middle;
        else
            wind_speed=high;

        client = new Socket_client(this,result[0],result[1]);
        connect(client,SIGNAL(mesArrival()),this,SLOT(getMes()));
        client->connect_to_host();

        room = new Hotel(result[3].toFloat(),result[4].toFloat(),result[2].toInt(),mode,result[5].toFloat(),wind_speed);
        connect(room,SIGNAL(MesArrival()),this,SLOT(mesSend()));
        room->started();

        timer = new QTimer();
        timer->setInterval(1000);
        connect(timer,SIGNAL(timeout()),this,SLOT(SendMes()));
        timer->start();
        connect(client,SIGNAL(linkChanged(QString)),this,SLOT(linkChange(QString)));

    }
    ini->close();
}

void Controll_client::linkChange(QString state){
    emit linkChanged(state);
}


void Controll_client::setTemOut(float o)
{
    room->setTemOut(o);
}

float Controll_client::getTemOut()
{
    return room->getTemOut();
}

void Controll_client::setTemRoom(float r)
{
    room->setTemRoom(r);
}

float Controll_client::getTemRoom()
{
    return room->getTemRoom();
}

void Controll_client::setRoomNum(int n)
{
    room->setRoomNum(n);
}

int Controll_client::getRoomNum()
{
    return room->getRoomNum();
}

void Controll_client::setGoalTemp(float r)
{
    room->setGoalTemp(r);
}

float Controll_client::getGoalTemp()
{
    return room->getGoalTemp();
}

void Controll_client::setWindSpeed(SPEED_WIND w)
{
    room->setWindSpeed(w);
}

SPEED_WIND Controll_client::getWindSpeed()
{
    return room->getWindSpeed();
}

void Controll_client::setCost(float c)
{
    room->setCost(c);
}

float Controll_client::getCost()
{
    return room->getCost();
}

void Controll_client::setECost(float e)
{
    room->setECost(e);
}

float Controll_client::getECost()
{
    return room->getECost();
}

void Controll_client::setModel(AC_MODEL ac)
{
      room->setModel(ac);
}

AC_MODEL Controll_client::getModel()
{
    return room->getModel();
}

void Controll_client::setState(AC_STATE s)
{
    room->setState(s);
}

AC_STATE Controll_client::getState()
{
    return room->getState();
}
