﻿#ifndef SIGN_UP_H
#define SIGN_UP_H

#include <QDialog>
#include <QtGui>
#include <QMessageBox>
#include <QFile>

namespace Ui {
class sign_up;
}

class sign_up : public QDialog
{
    Q_OBJECT

public:
    explicit sign_up(QWidget *parent = 0);
    ~sign_up();

private slots:
    void on_ok_clicked();

private:
    Ui::sign_up *ui;
};

#endif // SIGN_UP_H
