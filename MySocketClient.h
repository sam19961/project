#ifndef FORTUNETHREAD_H
#define FORTUNETHREAD_H

#include <iostream>
using namespace std;

#include <QThread>
#include <QTcpSocket>
#include <QFile>
#include <QDir>

//#include "Objects.h"

class MySocketClient : public QThread
{
    Q_OBJECT

public:
    MySocketClient(int socketDescriptor, QObject *parent);

    void run();

signals:
    void error(QTcpSocket::SocketError socketError);

private:
    int socketDescriptor;
    QString text;
};

#endif
