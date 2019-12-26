#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QtWidgets>
#include <QDebug>
#include <QTcpSocket>

namespace Ui {
class loginDialog;
}

class loginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit loginDialog(QWidget *parent = 0);
    ~loginDialog();


private slots:
    void on_pushButton_clicked();
    void sendRequest();
    void recvResponse();

private:
    Ui::loginDialog *ui;
    QTcpSocket *tcpSocket;
    quint32 nextBlockSize;
};

#endif // LOGINDIALOG_H
