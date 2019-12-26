#include "logindialog.h"
#include "ui_logindialog.h"

loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(sendRequest()));
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(recvResponse()));
}

loginDialog::~loginDialog()
{
    delete ui;
}

void loginDialog::on_pushButton_clicked()
{
    if(ui->lineEdit->text().isEmpty() || ui->lineEdit_2->text().isEmpty())
    {
        QMessageBox::warning(this, "错误", "无用户名或密码");
        return ;
    }
    nextBlockSize = 0;
    tcpSocket->connectToHost("127.0.0.1", 9999);
}

void loginDialog::sendRequest()
{
    QByteArray buf;
    QDataStream out(&buf, QIODevice::WriteOnly);
    out << quint32(0);
    if(ui->radioButton->isChecked())
        out << quint8('L');
    else
        out << quint8('R');
    out << ui->lineEdit->text() << ui->lineEdit_2->text();
    out.device()->seek(0);
    out << quint32(buf.size() - sizeof(quint32));
    tcpSocket->write(buf);
}

void loginDialog::recvResponse()
{
    QDataStream in(tcpSocket);
    if(nextBlockSize == 0)
    {
        if(tcpSocket->bytesAvailable() < sizeof(quint32))
            return ;
        in >> nextBlockSize;
    }
    if(tcpSocket->bytesAvailable() < nextBlockSize)
        return ;

    quint8 byte1,status ;
    QString str;

    in >> byte1 >> status >> str;
    tcpSocket->close();

    switch (byte1) {
    case 'L':
        if(status == 'T')
        {
            QMessageBox::information(this, "login", str);
            accept();
        }
        else
        {
            QMessageBox::information(this, "login", str);
            return ;
        }
        break;
    case 'R':
        if(status == 'T')
        {
            QMessageBox::information(this, "register", str);
            ui->lineEdit->clear();
            ui->lineEdit_2->clear();
            return ;
        }
        else
        {
          QMessageBox::information(this, "register", str);
          ui->lineEdit->clear();
          ui->lineEdit_2->clear();
          return ;
        }
        break;
    }

}
