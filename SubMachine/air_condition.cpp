#include "air_condition.h"


Air_condition::Air_condition()
{

}

void Air_condition::setState(AC_STATE state_in)
{
    state = state_in;
}

AC_STATE Air_condition::getState()
{
    return state;
}

void Air_condition::setWind(SPEED_WIND speed_in)
{
    speed = speed_in;
}
SPEED_WIND Air_condition::getWind()
{
    return speed;
}

void Air_condition::setGoal_Temp(float goal_in)
{
    goal_Temp = goal_in;
}

float Air_condition::getGoal_Temp()
{
    return goal_Temp;
}

void Air_condition::setModel(AC_MODEL model_in)
{
    model = model_in;
}

AC_MODEL Air_condition::getModel()
{
    return model;
}

void Air_condition::setTemp_Change(float temp_Change_in)
{
    temp_Change = temp_Change_in;
}

float Air_condition::getTemp_Change()
{
    return temp_Change;
}

