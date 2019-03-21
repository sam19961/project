#ifndef FORTUNESERVER_H
#define FORTUNESERVER_H

#include <QStringList>
#include <QTcpServer>
//#include "MyFileCache.h"

class MySocketServer : public QTcpServer
{
Q_OBJECT

public:
        MySocketServer(QObject *parent = nullptr);

protected:
    void incomingConnection(qintptr socketDescriptor);

};

#endif
