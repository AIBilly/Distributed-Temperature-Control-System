#include "staff_controler.h"

staff_controler::staff_controler()
{

}

staff_controler::~staff_controler()
{

}

int staff_controler::initialize_staff()
{
    int i = 0;
    if (!staff_f->open(QIODevice::ReadOnly))
    {
        return -1;
    }
    else
    {
        QDataStream fin(staff_f);
        while (!fin.atEnd())
        {
            Clerk temp;
            fin >> temp.username >> temp.password >> temp.usertype;
            staff.append(temp);
            i++;
        }
        staff_f->close();
        staffs = i;
        return i - 1;
    }
}

int staff_controler::login(QString username,QString password,int system_state)
{
    if (system_state == -1)
    {
        int flag = 0;
        int temp;
        for (int e = 0; e < staffs; e++)
        {
            if (staff[e].username == username)
            {
                flag = 1;
                temp = e;
            }
        }
        if (flag == 0)
        {
            qDebug() << "1";
            return -1;
        }
        else
        {
            if(staff[temp].password == password)
            {
                return 1;
            }
            else
            {
                qDebug() << "2";
                return -1;
            }
        }
    }
    else
    {
        qDebug() << "3";
        return -1;
    }
}

int staff_controler::add_staff(QString username,QString password)
{
    if(staffs < MAXSTAFF)
    {
        int flag = 0;
        for(int i = 0;i < staffs;i++)
        {
            if(username == staff[i].username)
                flag = 1;
        }
        if(flag == 1)
        {
            return -2;
        }
        else
        {
            Clerk temp;
            temp.username = username;
            temp.password = password;
            temp.usertype = 1;
            staff.append(temp);
            staffs++;
            return 0;
        }
    }
    else
        return -1;
}

int staff_controler::delete_staff(QString username)
{
    int flag = 0;
    int target = -1;
    for(int i = 0;i < staffs;i++)
    {
        if(username == staff[i].username)
        {
            flag = 1;
            target = i;
        }
    }
    if(flag == 0)
    {
        return -1;
    }
    else
    {
        staff.erase(staff.begin()+target);
        staffs--;
        return 0;
    }
}

void staff_controler::save_staff(void)
{
    if (!staff_f->open(QIODevice::WriteOnly))
    {
        return;
    }
    else
    {
        QDataStream fout(staff_f);
        for(int i = 0;i < staffs;i++)
        {
            fout << staff[i].username << staff[i].password << staff[i].usertype;
        }
        staff_f->close();
    }
}
