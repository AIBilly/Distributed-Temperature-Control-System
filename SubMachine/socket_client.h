#ifndef SOCKET_CLIENT_H
#define SOCKET_CLIENT_H
#include <QtNetwork>
#include <QString>
#include <QWidget>
#include <QMutex>

class Socket_client : public QWidget
{
    Q_OBJECT
public:
    explicit Socket_client(QWidget *parent,QString adds,QString por);

    bool send(QString mes);

    QString recive();

    void close_connect();

    void connect_to_host();

private:
    bool close;

    QMutex recivelock;

    QMutex sendlock;

    QTcpSocket *tcpSocket;

    QString port;

    QString address;

    quint16 byteSize;

    QString buffer;

    QTimer *timer;

signals:
    int mesArrival();

    int linkChanged(QString state);

private slots:

    void ReadMessage();

    void displayError();

    void build_socket();

    void Trylink();
};

#endif // SOCKET_CLIENT_H
