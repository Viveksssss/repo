#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MyWidget;
}

QT_END_NAMESPACE


class MyWidget : public QMainWindow
{
    Q_OBJECT    //宏支持信号和槽

public:
    MyWidget(QWidget *parent = nullptr);
    ~MyWidget();

private:
    Ui::MyWidget *ui;
};

#endif // MYWIDGET_H
