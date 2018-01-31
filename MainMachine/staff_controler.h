#ifndef STAFF_CONTROLER_H
#define STAFF_CONTROLER_H

#define MAXSTAFF 30

#include <QString>
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QVector>

struct Clerk
{
    QString username;//登陆用户名
    QString password;
    qint32 usertype;//0代表administrator,1代表普通员工
};

class staff_controler
{
public:
    staff_controler();
    ~staff_controler();
    int initialize_staff();
    int login(QString username,QString password,int system_state);
    int add_staff(QString username, QString password);
    int delete_staff(QString username);
    void save_staff(void);

private:
    QFile* staff_f;
    QVector<Clerk> staff;
    int staffs;
};

#endif // STAFF_CONTROLER_H
