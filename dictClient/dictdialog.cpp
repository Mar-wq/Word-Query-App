#include "dictdialog.h"
#include "ui_dictdialog.h"

DictDialog::DictDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DictDialog)
{
    ui->setupUi(this);
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(sendRequest()));
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(recvResponse()));
}

DictDialog::~DictDialog()
{
    delete ui;
}

void DictDialog::on_pushButton_clicked()
{

    nextBlockSize = 0;
    tcpSocket->connectToHost("127.0.0.1", 9999);
}

void DictDialog::on_lineEdit_textChanged(const QString &arg1)
{
    if(!arg1.isEmpty())
        ui->pushButton->setEnabled(true);
    else
        ui->pushButton->setEnabled(false);
}

void DictDialog::sendRequest()
{
    QByteArray buf;
    QDataStream out(&buf, QIODevice::WriteOnly);
    out << quint32(0);
    out << quint8('Q');
    out << ui->lineEdit->text();
    out.device()->seek(0);
    out << quint32(buf.size() - sizeof(quint32));
    tcpSocket->write(buf);
}

void DictDialog::recvResponse()
{
    ui->textBrowser->clear();
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

    ui->textBrowser->setText(str);
}
