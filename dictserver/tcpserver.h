#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>

class TcpServer : public QTcpServer
{
    Q_OBJECT

public:
    TcpServer(QObject *parent=0);
    ~TcpServer();

protected:
    void incomingConnection(qintptr socketDescriptor);
private:
    void dataImport();
};

#endif // TCPSERVER_H
