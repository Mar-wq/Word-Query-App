#include "logindialog.h"
#include "dictdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    loginDialog w;
    w.show();

    if(w.exec() == QDialog::Rejected)
        return 0;

    DictDialog x;
    x.show();

    return a.exec();
}
