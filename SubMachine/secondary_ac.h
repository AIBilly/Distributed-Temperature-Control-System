#ifndef SECONDARY_AC_H

#include"air_condition.h"
#define SECONDARY_AC_H


class Secondary_ac : public Air_condition
{
private:
    float cost;
    float energy_Cost;

public:
    Secondary_ac(AC_MODEL m,AC_STATE s,float gTem,SPEED_WIND w);

    Secondary_ac();

    void setCost(float cost_in);

    void setEcost(float ecost_in);

    float getCost();

    float getEcost();


};

#endif // SECONDARY_AC_H
