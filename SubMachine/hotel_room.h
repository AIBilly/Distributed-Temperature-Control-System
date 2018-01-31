#ifndef HOTEL_ROOM_H
#define HOTEL_ROOM_H
#include"room.h"
#include"secondary_ac.h"



class Hotel_room : public Room
{
private:
    Secondary_ac air_Condition;

public:



    QString getModelName();

    QString getSpeedName();

    QString getStateName();


    Hotel_room(float temO,float temR,int num);

    Hotel_room();

    Secondary_ac getSec();

    void SetGoalTemp(float goal_in);

    float getGoalTemp();

    void SetWind(SPEED_WIND speed_in);

    SPEED_WIND getWind();

    void SetState(AC_STATE state_in);

    AC_STATE getState();

    void SetModel(AC_MODEL model_in);

    AC_MODEL getModel();

    void SetTemp_Change(float temp_Change_in);

    float getTEmp_Change();

    void setCost(float cost);

    float getCost();

    void setEcost(float ecost);

    float getEcost();


    QString ShowMes();


    int calFinTem();
};

#endif // HOTEL_ROOM_H
