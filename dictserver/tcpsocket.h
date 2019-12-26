#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QTcpSocket>

namespace Ui {
class TcpSocket;
}

class TcpSocket : public QTcpSocket
{
    Q_OBJECT

public:
    explicit TcpSocket(QObject *parent = 0);
private slots:
    void readClient();
private:
    void userLogin(QDataStream &);
    void userRegister(QDataStream &);
    void wordQuery(QDataStream &);
    quint32 nextBlockSize;
};

#endif // TCPSOCKET_H
