#ifndef AIR_CONDITION_H
#include<QString.h>
enum AC_MODEL{cold=1,hot=2};
enum AC_STATE{on=1,off=2,stay=3};
enum SPEED_WIND{low=1,middle=2,high=3};

#define AIR_CONDITION_H


class Air_condition
{
private:
    AC_STATE state;//运行，待机，关闭
    SPEED_WIND speed;
    float goal_Temp;
    float temp_Change;
    AC_MODEL model;


protected:
    float CalCulTempChange(QString in_str);

public:
    void setState(AC_STATE state_in);

    AC_STATE getState();

    void setWind(SPEED_WIND speed_in);
    SPEED_WIND getWind();

    void setGoal_Temp(float goal_in);

    float getGoal_Temp();

    void setModel(AC_MODEL model_in);

    AC_MODEL getModel();

    void setTemp_Change(float temp_Change_in);

    float getTemp_Change();

public:
    Air_condition();
};

#endif // AIR_CONDITION_H
