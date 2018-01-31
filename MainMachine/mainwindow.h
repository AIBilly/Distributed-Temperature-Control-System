#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QCloseEvent>

static const int EXIT_CODE_REBOOT = -2;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent* e);
    void closeEvent (QCloseEvent* event);

private:
    Ui::MainWindow *ui;

private:
        QLabel *msgLabel;
        QLabel *ztgLabel;
        QLabel *zsgLabel;

private slots:
    void timerUpDate();
    void on_logout_triggered();
    void on_staff_manage_triggered();
    void on_options_triggered();
};

#endif // MAINWINDOW_H
