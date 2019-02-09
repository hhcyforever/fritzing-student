#ifndef UI_shadowdlg_H
#define UI_shadowdlg_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QLabel>
#include <QWidget>
#include <QPushButton>

QT_BEGIN_NAMESPACE

class Ui_shadowdlg
{
public:
    QLabel *s1;
    QLabel *s2;
    QLabel *s3;
    QLabel *s4;
    QLabel *s5;
    QLabel *s6;
    QLabel *s7;
    QLabel *s8;
    QLabel *message;
    QPushButton *button;
    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("shadowDialog"));
        s1 = new QLabel(Dialog);
        s1->setStyleSheet(QString("background-color: rgba(0, 0, 0, 40%);"));
        s2 = new QLabel(Dialog);
        s2->setStyleSheet(QString("background-color: rgba(0, 0, 0, 40%);"));
        s3 = new QLabel(Dialog);
        s3->setStyleSheet(QString("background-color: rgba(0, 0, 0, 40%);"));
        s4 = new QLabel(Dialog);
        s4->setStyleSheet(QString("background-color: rgba(0, 0, 0, 40%);"));
        s5 = new QLabel(Dialog);
        s5->setStyleSheet(QString("background-color: rgba(0, 0, 0, 40%);"));
        s6 = new QLabel(Dialog);
        s6->setStyleSheet(QString("background-color: rgba(0, 0, 0, 40%);"));
        s7 = new QLabel(Dialog);
        s7->setStyleSheet(QString("background-color: rgba(0, 0, 0, 40%);"));
        s8 = new QLabel(Dialog);
        s8->setStyleSheet(QString("background-color: rgba(0, 0, 0, 40%);"));
        message = new QLabel(Dialog);
        message->setStyleSheet(QString("background-color: rgba(0, 0, 0, 40%);"));
        message->setText("Please focus on this part");
        message->setFont(QFont("Timers" , 18 ,  QFont::Bold));
        button = new QPushButton(Dialog);
        button->setText("OK");
        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi
};

namespace Ui {
    class shadowdlg: public Ui_shadowdlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_shadowdlg_H
