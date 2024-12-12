#include "widget.h"
#include "ui_widget.h"
#include <QTimer>
#include <QDebug>
#include <QMouseEvent>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //以下是两种定时器，一种是Widget里面的事件
    //另一种是Timer类
    //有两个定时器，但是要想在timerEvent里面区分，就要用到timerid
    //timerid和定时器id1/id2相当，则走对应的定时器
    id1 = startTimer(500);
    id2 = startTimer(100);

    QTimer *q1 = new QTimer(this);
    q1->start(5);
    //每隔5毫秒抛出信号
    connect(q1,&QTimer::timeout,this,[=](){
        static int num = 1;
        ui->label_4->setText(QString::number(num+=1));
    });


    connect(ui->pushButton,&QPushButton::clicked,[=](){
        static int mm = 1;
        if(mm%2==1){
            mm++;
            q1->stop();
        }
        else{
            mm++;
            q1->start();
        }
    });

    ui->label->installEventFilter(this);

}

bool Widget::eventFilter(QObject*obj,QEvent*e){
    if(obj == ui->label){
        if(e->type() == QEvent::MouseButtonPress){

            QMouseEvent*ev = static_cast<QMouseEvent*>(e);

            QString str = QString("in event 当前坐标是 x = %1,y = %2").arg(ev->x()).arg(ev->y());

            qDebug()<<str;

            return true;
        }
    }
    return QWidget::eventFilter(obj,e);
}

void Widget::timerEvent(QTimerEvent*e){
    static int num1 = 1;
    if(id1==e->timerId())
    ui->label_2->setText(QString::number(num1++));

    static int num2 = 1;
    if(id2==e->timerId())
    ui->label_3->setText(QString::number(num2++));


}


Widget::~Widget()
{
    delete ui;
}
