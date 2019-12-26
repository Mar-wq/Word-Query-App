#include "tcpsocket.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QtWidgets>

TcpSocket::TcpSocket(QObject *parent) :QTcpSocket(parent)
{
    /*QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("onlineDict.db");
    if(db.open())
        qDebug() << "success";
    else
        qDebug() << "failed";*/
    nextBlockSize = 0;
    connect(this,SIGNAL(disconnected()),this,SLOT(deleteLater()));
    connect(this,SIGNAL(readyRead()),this,SLOT(readClient()));
}

void TcpSocket::readClient()
{
    QDataStream in(this);
    if(nextBlockSize==0)
    {
        if(bytesAvailable() < sizeof(quint32))
            return;
        in >> nextBlockSize;
    }
    if(bytesAvailable() < nextBlockSize)
        return;
    quint8 type;
    in >> type;

    switch (type) {
    case 'L':
        userLogin(in);
        break;
    case 'R':
        userRegister(in);
        break;
    case 'Q':
        wordQuery(in);
        break;
    }

    /*进行登录,注册,查单词
    QByteArray buf;
    QDataStream out(&buf,QIODevice::WriteOnly);
    out << quint32(0);
    out << type << QString("success");
    out.device()->seek(0);
    out << quint32(buf.size()-sizeof(quint32));
    write(buf);
    close();*/
}

void TcpSocket::userRegister(QDataStream &in)
{
    QString username,password;
    in >> username >> password;

    QByteArray buf;
    QDataStream out(&buf,QIODevice::WriteOnly);

    QString str = QString("select * from users where name='%1'").arg(username);
    QSqlQuery sqlQuery;
    sqlQuery.exec(str);
    if(!sqlQuery.next())
    {
         QString str1 = QString("insert into users values('%1', '%2')").arg(username).arg(password);
         QSqlQuery sqlQuery;
         if(!sqlQuery.exec(str1))
         {
             out << quint32(0);
             out << quint8('R') << quint8('F') << QString("Register faild,server exception");
             out.device()->seek(0);
             out << quint32(buf.size()-sizeof(quint32));
             write(buf);
             close();
         }
         else
         {
             out << quint32(0);
             out << quint8('R')<< quint8('T') << QString("Register succeed");
             out.device()->seek(0);
             out << quint32(buf.size()-sizeof(quint32));
             write(buf);
             close();
         }
    }
    else
    {
        out << quint32(0);
        out << quint8('R') << quint8('F') << QString("Register faild,username already exists!");
        out.device()->seek(0);
        out << quint32(buf.size()-sizeof(quint32));
        write(buf);
        close();
    }

}

void TcpSocket::wordQuery(QDataStream &in)
{
    QString word;
    in >> word;


    QByteArray buf;
    QDataStream out(&buf,QIODevice::WriteOnly);

    QString str = QString("select * from dict where word='%1'").arg(word);
    QSqlQuery sqlQuery;
    if(sqlQuery.exec(str))
    {   if(sqlQuery.next())
        {
            QString explain=sqlQuery.value(1).toString();
            out << quint32(0);
            out << quint8('Q') << quint8('T') << explain;
            out.device()->seek(0);
            out << quint32(buf.size()-sizeof(quint32));
            write(buf);
            close();
        }
        else
        {
            out << quint32(0);
            out << quint8('Q') << quint8('F') << QString("not find");
            out.device()->seek(0);
            out << quint32(buf.size()-sizeof(quint32));
            write(buf);
            close();
        }
    }
    else
    {
        out << quint32(0);
        out << quint8('Q') << quint8('F') << QString("Query faild,server exception");
        out.device()->seek(0);
        out << quint32(buf.size()-sizeof(quint32));
        write(buf);
        close();
    }

}

void TcpSocket::userLogin(QDataStream &in)
{
    QString username,password;
    in >> username >> password;

    QByteArray buf;
    QDataStream out(&buf,QIODevice::WriteOnly);

    QString str = QString("select * from users where name='%1'").arg(username);
    qDebug() << str;
    QSqlQuery sqlQuery;
    sqlQuery.exec(str);
    if(!sqlQuery.next())
    {
        out << quint32(0);
        out << quint8('L') << quint8('F') <<QString("username error");
        out.device()->seek(0);
        out << quint32(buf.size()-sizeof(quint32));
        write(buf);
        close();
    }
    else
    {
        QString str = QString("select * from users where name='%1' and password='%2'").arg(username).arg(password);
        qDebug() << str;
        QSqlQuery sqlQuery;
        sqlQuery.exec(str);
        if(!sqlQuery.next())
        {
            out << quint32(0);
            out << quint8('L') << quint8('F') <<QString("password error");
            out.device()->seek(0);
            out << quint32(buf.size()-sizeof(quint32));
            write(buf);
            close();
        }
        else
        {
            out << quint32(0);
            out << quint8('L') << quint8('T') <<QString("login succeed");
            out.device()->seek(0);
            out << quint32(buf.size()-sizeof(quint32));
            write(buf);
            close();
        }
    }
}

