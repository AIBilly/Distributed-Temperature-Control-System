#include "socket_client.h"

Socket_client::Socket_client(QWidget *parent,QString adds,QString por) :
    QWidget(parent),close(true),port(por),address(adds),byteSize(0),buffer("")
{
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket,SIGNAL(connected()),this,SLOT(build_socket()));
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(ReadMessage()));
    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError()));

    timer = new QTimer();
    timer->setInterval(1000);
    connect(timer,SIGNAL(timeout()),this,SLOT(Trylink()));
    timer->start();
}


void Socket_client::build_socket(){

    emit linkChanged("connected");
    close = false;
}

void Socket_client::ReadMessage(){
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_4_6);

    if(byteSize == 0){
        if(tcpSocket->bytesAvailable() < (int)sizeof(quint16) )return;

        in >> byteSize;
    }

    if(tcpSocket->bytesAvailable() < byteSize) return;
    QString temp;
    in >> temp;

    recivelock.lock();
    buffer.append(temp);
    recivelock.unlock();
    byteSize = 0;
    emit mesArrival();
}

void Socket_client::displayError(){
    close = true;
    emit linkChanged("disconnected");
    qDebug() << tcpSocket->errorString();
    tcpSocket->disconnectFromHost();
}


bool Socket_client::send(QString mes){
    if(tcpSocket == NULL || close || tcpSocket->state() != 3) return false;

    sendlock.lock();
    QByteArray block;

    QDataStream out(&block,QIODevice::WriteOnly);

    out.setVersion(QDataStream::Qt_4_6);

    out << (quint16) 0;
    out << mes;
    out.device()->seek(0);
    out << (qint16)(block.size() - sizeof(quint16));

    tcpSocket->write(block);

    sendlock.unlock();
        qDebug() <<"send :" <<  mes;
    return true;
}

void Socket_client::Trylink(){
    if(tcpSocket->state() != 3)
        connect_to_host();
}

QString Socket_client::recive(){
    QStringList item = buffer.split("$$");
    if (item.length() == 0) return "";

    recivelock.lock();

    QString temp = item[0];
    item.removeAt(0);

    buffer.clear();
    buffer.append( item.join("$$"));
    recivelock.unlock();

    return temp;
}

void Socket_client::close_connect(){
    close = true;
    emit linkChanged("disconnected");
    tcpSocket->close();
}

void Socket_client::connect_to_host(){
    if(tcpSocket->state() != 3)
        tcpSocket->connectToHost(address,port.toInt());
}
