#include "tcpserver.h"
#include "tcpsocket.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QtWidgets>
#include <QStringList>

TcpServer::TcpServer(QObject *parent) :QTcpServer(parent)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("onlineDict.db");
    db.open();
    dataImport();

}

TcpServer::~TcpServer()
{
    //数据库中表的删除，方便下次启动时更新数据，但由于导入太慢，将其注释掉。
    /*QString str = QString("drop table dict");
    QSqlQuery sqlQuery;
    sqlQuery.exec(str);*/

}
void TcpServer::incomingConnection(qintptr socketDescriptor)
{
    TcpSocket *tcpSocket=new TcpSocket(this);
    tcpSocket->setSocketDescriptor(socketDescriptor);
}

void TcpServer::dataImport()
{
    QString str = QString("create table dict(word text,expalin text)");
    QSqlQuery sqlQuery;
    if(!sqlQuery.exec(str))
    {
        return ; //表存在则直接返回
    }

    QFile file("dict.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "cannot find dict.txt";
    }
    QTextStream in(&file);
    QString line;
    QStringList list;
    QString word;
    QString explain;
    int i = 0;
    while(!in.atEnd())
    {
        line=in.readLine();
        list = line.split("  ", QString::SkipEmptyParts);
        word = list[0];
        line=line.mid(word.length());
        explain=line.trimmed();
        QString str1 = QString("insert into dict values('%1', '%2')").arg(word).arg(explain);
        QSqlQuery sqlQuery;
        sqlQuery.exec(str1);
        qDebug() << i;
        i++;
    }
}
