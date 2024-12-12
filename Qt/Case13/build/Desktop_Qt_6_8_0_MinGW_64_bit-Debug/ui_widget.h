/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QWidget *widget;
    QTextEdit *textEdit_2;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QTextEdit *textEdit;
    QPushButton *pushButton;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(800, 600);
        widget = new QWidget(Widget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(190, 50, 364, 412));
        textEdit_2 = new QTextEdit(widget);
        textEdit_2->setObjectName("textEdit_2");
        textEdit_2->setGeometry(QRect(0, 30, 351, 381));
        widget_2 = new QWidget(widget);
        widget_2->setObjectName("widget_2");
        widget_2->setGeometry(QRect(0, 0, 352, 41));
        widget_2->setContextMenuPolicy(Qt::ContextMenuPolicy::DefaultContextMenu);
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setObjectName("horizontalLayout");
        textEdit = new QTextEdit(widget_2);
        textEdit->setObjectName("textEdit");

        horizontalLayout->addWidget(textEdit);

        pushButton = new QPushButton(widget_2);
        pushButton->setObjectName("pushButton");

        horizontalLayout->addWidget(pushButton);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        pushButton->setText(QCoreApplication::translate("Widget", "\351\200\211\346\213\251\346\226\207\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
