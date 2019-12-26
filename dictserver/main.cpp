#include "tcpserver.h"
#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TcpServer tcpServer;
    tcpServer.listen(QHostAddress::Any, 9999);


    QPushButton pushButton("quit");
    QObject::connect(&pushButton, SIGNAL(clicked()), &a, SLOT(quit()));
    pushButton.show();

    return a.exec();
}
