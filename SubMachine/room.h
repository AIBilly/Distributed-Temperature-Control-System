#ifndef ROOM_H
#define ROOM_H

#include<stdio.h>

class Room
{
private:
    float temperature_Outside;
    float temperature_Room;
    int room_Num;

public:

    Room(float temO,float temR,int num);

    Room();

    void setRoomN(int num);

    void setOutT(float out_in);

    void setRoomT(float room_in);

    int getRoomN();

    float getOutT();

    float getRoomT();

protected:
    void TempNatureDerease();
};

#endif // ROOM_H
