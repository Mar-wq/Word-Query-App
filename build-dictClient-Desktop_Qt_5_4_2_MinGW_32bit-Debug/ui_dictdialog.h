/********************************************************************************
** Form generated from reading UI file 'dictdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DICTDIALOG_H
#define UI_DICTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DictDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QTextBrowser *textBrowser;

    void setupUi(QDialog *DictDialog)
    {
        if (DictDialog->objectName().isEmpty())
            DictDialog->setObjectName(QStringLiteral("DictDialog"));
        DictDialog->setEnabled(true);
        DictDialog->resize(295, 251);
        verticalLayout = new QVBoxLayout(DictDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lineEdit = new QLineEdit(DictDialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setEnabled(true);

        horizontalLayout->addWidget(lineEdit);

        pushButton = new QPushButton(DictDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setEnabled(false);

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);

        textBrowser = new QTextBrowser(DictDialog);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        verticalLayout->addWidget(textBrowser);


        retranslateUi(DictDialog);

        QMetaObject::connectSlotsByName(DictDialog);
    } // setupUi

    void retranslateUi(QDialog *DictDialog)
    {
        DictDialog->setWindowTitle(QApplication::translate("DictDialog", "Dialog", 0));
        pushButton->setText(QApplication::translate("DictDialog", "\346\237\245\346\211\276", 0));
    } // retranslateUi

};

namespace Ui {
    class DictDialog: public Ui_DictDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DICTDIALOG_H
