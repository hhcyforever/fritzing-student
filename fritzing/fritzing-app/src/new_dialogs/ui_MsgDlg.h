#ifndef UI_MsgDlg_H
#define UI_MsgDlg_H
 
#include <QtCore/QVariant> 
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QLabel>
	
QT_BEGIN_NAMESPACE 
 
class Ui_MsgDlg
{
public: 
    QLabel *MsgLabel;
    QLabel *MsgLabelText;
	void setupUi(QDialog *Dialog) 
	{
		if (Dialog->objectName().isEmpty()) 
			Dialog->setObjectName(QString::fromUtf8("Dialog")); 
		Dialog->resize(600, 400); 
        MsgLabel = new QLabel(Dialog);
        MsgLabel->setObjectName(QString::fromUtf8("picture"));
        MsgLabel->setGeometry(QRect(30, 10, 256, 192));
        MsgLabelText = new QLabel(Dialog);
        MsgLabelText->setObjectName(QString::fromUtf8("text"));
        MsgLabelText->setGeometry(QRect(30, 100, 300, 50));
		QMetaObject::connectSlotsByName(Dialog);
	} // setupUi	    
}; 
 
namespace Ui { 
    class MsgDlg: public Ui_MsgDlg {};
} // namespace Ui 
 
QT_END_NAMESPACE 
 
#endif // UI_MsgDlg_H
