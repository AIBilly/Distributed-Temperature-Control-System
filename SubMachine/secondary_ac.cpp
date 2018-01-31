#include "secondary_ac.h"

    Secondary_ac::Secondary_ac(AC_MODEL m,AC_STATE s,float gTem,SPEED_WIND w)
    {//从控机信息初始化
        cost=0;
        energy_Cost=0;
        this->Air_condition::setWind(w);
        this->Air_condition::setModel(m);
        this->Air_condition::setGoal_Temp(gTem);
        this->Air_condition::setState(s);
    }

    Secondary_ac::Secondary_ac()
    {
        Air_condition();
        cost=0;
        energy_Cost=0;
    }

    void Secondary_ac::setCost(float cost_in)
    {//设置费用
        cost = cost_in;
    }

    void Secondary_ac::setEcost(float ecost_in)
    {//设置能耗
        energy_Cost=ecost_in;
    }

    float Secondary_ac::getCost()
    {//获取费用
        return cost;
    }

    float Secondary_ac::getEcost()
    {//获取能耗
        return energy_Cost;
    }

