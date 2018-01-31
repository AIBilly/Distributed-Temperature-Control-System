#include "room.h"


    Room::Room(float temO,float temR,int num)
        {//初始化
            temperature_Outside=temO;
            temperature_Room=temR;
            room_Num=num;

        }

    Room::Room()
    {
        temperature_Outside=25;
        temperature_Room=25;
        room_Num=105;
    }
    void Room::setRoomN(int num)
    {//设置房间号
            room_Num = num;
    }
        void Room::setOutT(float out_in)
        {//设置室外温度
            temperature_Outside = out_in;
        }

        void Room::setRoomT(float room_in)
        {//设置室内温度
            temperature_Room = room_in;
        }

        int Room::getRoomN()
        {//获取房间号
            return room_Num;
        }

        float Room::getOutT()
        {//获取外温
            return temperature_Outside;
        }

        float Room::getRoomT()
        {//获取室温
            return temperature_Room;
        }

        void Room::TempNatureDerease()
        {//自然条件下，室温每秒向自然温度靠近0.1度
            if((temperature_Outside - temperature_Room>=0.01)||(temperature_Outside - temperature_Room<=-0.01))
            {
                float tem = temperature_Outside - temperature_Room;
                if(tem>0)
                    temperature_Room=temperature_Room+0.1;
                else if(tem<0)
                    temperature_Room=temperature_Room-0.1;
            }
        }

