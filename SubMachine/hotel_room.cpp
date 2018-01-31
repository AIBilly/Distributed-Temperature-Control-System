#include "hotel_room.h"
#include <QTextStream>
#include <QDebug>

QString Hotel_room::getModelName()
{//根据模式的值，返回其名称
    if(air_Condition.getModel()==cold)
    {
        return "cold";
    }
    else if(air_Condition.getModel()==hot)
    {
        return "hot";
    }
    else
    {
        return "";
    }
}

QString Hotel_room::getSpeedName()
{//根据风速的值，返回其名称
    if(air_Condition.getWind()==low)
    {
        return "low";
    }
    else if(air_Condition.getWind()==middle)
    {
        return "middle";
    }
    else if(air_Condition.getWind()==high)
    {
        return "high";
    }
    else
    {
        return "";
    }
}

QString Hotel_room::getStateName()
{//根据状态的值，返回其名称
    if(air_Condition.getState()==on)
    {
        return "run";
    }
    else if(air_Condition.getState()==off)
    {
        return "off";
    }
    else if(air_Condition.getState()==stay)
    {
        return "stay";
    }
    else
    {
        return "";
    }
}


Hotel_room::Hotel_room(float temO,float temR,int num)
{//构造函数
    Room(temO,temR,num);
}

Hotel_room::Hotel_room()
{
    Room();
}

Secondary_ac Hotel_room::getSec()
{//获取air_Condition类
    return air_Condition;
}

void Hotel_room::SetGoalTemp(float goal_in)
{//设置目标温度
    air_Condition.setGoal_Temp(goal_in);
}

float Hotel_room::getGoalTemp()
{//获得目标温度
    return air_Condition.getGoal_Temp();
}

void Hotel_room::SetWind(SPEED_WIND speed_in)
{//设置风速
    air_Condition.setWind(speed_in);
}

SPEED_WIND Hotel_room::getWind()
{//获得风速
    return air_Condition.getWind();
}

void Hotel_room::SetState(AC_STATE state_in)
{//设置从控机状态
    air_Condition.setState(state_in);
}

AC_STATE Hotel_room::getState()
{//获取从控机状态
    return air_Condition.getState();
}

void Hotel_room::SetModel(AC_MODEL model_in)
{//设置模式
    air_Condition.setModel(model_in);
}

AC_MODEL Hotel_room::getModel()
{//获取模式
    return air_Condition.getModel();
}

void Hotel_room::SetTemp_Change(float temp_Change_in)
{
    air_Condition.setTemp_Change(temp_Change_in);
}

float Hotel_room::getTEmp_Change()
{
    return air_Condition.getTemp_Change();
}

void Hotel_room::setCost(float cost)
{//设置费用
    air_Condition.setCost(cost);
}

float Hotel_room::getCost()
{//获取费用
    return air_Condition.getCost();
}

void Hotel_room::setEcost(float ecost)
{//设置能耗
    air_Condition.setEcost(ecost);
}

float Hotel_room::getEcost()
{//获取能耗
    return air_Condition.getEcost();
}

QString Hotel_room::ShowMes()
{//显示从控机的信息

    QString num = QString("%1").arg(this->getRoomN());
    QString Temp=QString::number(this->getRoomT(),10,2);
    QString Temp1=QString::number(air_Condition.getGoal_Temp(),10,2);
    QString Ecost=QString::number(air_Condition.getEcost(),10,1);
    QString cost=QString::number(air_Condition.getCost(),10,1);
 //   QString QString::number(double n, char format = 'g', int precision = 6);





    return "Informations of room "+num+": RoomTemp:"+Temp+" GoalTemp:"+Temp1+" Energy:"+Ecost+" Cost:"+cost+" Mode:"+getModelName()+" Speed:"+getSpeedName()+" State:"+getStateName();
    }

int Hotel_room::calFinTem()
{//计算在室外温度和空调的影响下的室温,返回值代表通信类型（034）
    //室温－目标
    float c=Room::getRoomT()-air_Condition.getGoal_Temp();



    if((air_Condition.getState() == on) && ((c >= 0 && getModel() == cold)||(c <= 0 && getModel() == hot)))
    {//空调正常运行
        if(getModel()==cold && c > 0)
        {
            if(getWind()==low)
                Room::setRoomT(Room::getRoomT()-0.15);
            else if(getWind()==middle)
                Room::setRoomT(Room::getRoomT()-0.2);
            else if(getWind()==high)
                Room::setRoomT(Room::getRoomT()-0.25);
        }
        else if(getModel()==hot && c < 0)
        {
            if(getWind()==low)
                Room::setRoomT(Room::getRoomT()+0.15);
            else if(getWind()==middle)
                Room::setRoomT(Room::getRoomT()+0.2);
            else if(getWind()==high)
                Room::setRoomT(Room::getRoomT()+0.25);
        }

        Room::TempNatureDerease();

        return 0;
    }
    else if((c >= 0 && getModel()==hot) || (c<=0 && getModel() == cold))
    {

        Room::TempNatureDerease();


        //达到温度时通知主机
        if(air_Condition.getState() == on){
          air_Condition.setState(stay);
          return 3;
        }
        else
          return 0;
    }
    else
    {
        Room::TempNatureDerease();
        if(( ( c >= 1 && getModel() == cold)||(c <= -1 && getModel() == hot)) &&(air_Condition.getState() == stay))
        {

            return 4;//从机要求改变目标温度或者目标风速
        }

        return 0;
    }

}



