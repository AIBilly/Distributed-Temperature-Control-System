#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "staff_manage.h"
#include "options.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QTextCodec>
#include <QMessageBox>
#include <QDateTime>
#include <QTimer>
#include <QProgressBar>

extern int systemstate;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //居中设置
    QDesktopWidget* desktop = QApplication::desktop();
    int width = desktop->width();
    int height = desktop->height();
    move((width - this->width())/2, (height - this->height())/2);

    QTimer *timer = new QTimer(this);
    //新建定时器
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpDate()));
    //关联定时器计满信号和相应的槽函数
    timer->start(1000);

    //状态栏初始化

    msgLabel=new QLabel();
    this->ui->statusBar->addPermanentWidget(msgLabel);
    ztgLabel=new QLabel();
    this->ui->statusBar->addWidget(ztgLabel);
    QProgressBar *progressBar = new QProgressBar();
    progressBar->setTextVisible( false );
    progressBar->setRange(0,0);
    this->ui->statusBar->addWidget(progressBar,1);

    //工具栏初始化

    //从控机表初始化
    this->ui->SubMachines->setColumnCount(8);
    QStringList header;
    header<<"Number"<<"Current temperature"<<"Objective temperature"<<"Wind speed"<<"Mode"<<"Schedule state"<<"Power"<<"Connected";
    this->ui->SubMachines->setHorizontalHeaderLabels(header);
    this->ui->SubMachines->resizeColumnsToContents();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::closeEvent(QCloseEvent* event )
{
    switch(QMessageBox::information(this,tr("exit"),tr("Do you really want to exit?"),tr("Yes"),tr("No"),0,1))
    {
    case 0:
       event->accept();
       break;
    case 1:
    default:
       event->ignore();
       break;
    }
}

void MainWindow::timerUpDate()
{
    QDateTime time = QDateTime::currentDateTime();
    //获取系统现在的时间
    QString str = time.toString("yyyy-MM-dd hh:mm:ss ddd"); //设置显示格式
    ztgLabel->setText(tr("state:%1").arg(qrand()%10));
    msgLabel->setText(str);
}

void MainWindow::on_logout_triggered()
{
    systemstate = -1;
    qApp->exit( EXIT_CODE_REBOOT );//调用exit()，退出应用程序。
}

void MainWindow::on_staff_manage_triggered()
{
    Staff_manage sm;
    sm.exec();
}

void MainWindow::on_options_triggered()
{
    Options op;
    op.exec();
}
