#ifndef DICTDIALOG_H
#define DICTDIALOG_H

#include <QDialog>
#include <QTcpSocket>

namespace Ui {
class DictDialog;
}

class DictDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DictDialog(QWidget *parent = 0);
    ~DictDialog();

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void sendRequest();

    void recvResponse();

private:
    Ui::DictDialog *ui;
    QTcpSocket *tcpSocket;
    quint32 nextBlockSize;
};

#endif // DICTDIALOG_H
