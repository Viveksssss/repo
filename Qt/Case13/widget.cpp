#include "widget.h"
#include "ui_widget.h"
#include <QPainter>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    pox = 0;
    QTimer *qt = new QTimer();
    qt->start(1000);
    connect(qt,&QTimer::timeout,this,[=](){
        pox+=10;
        update();
    });
    // connect(ui->pushButton,&QPushButton::clicked,[=](){
    //     pox+=10;
    //     update();
    // });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *e) {
    QPainter painter(this);

    //基础设置
    // QPen pen((QColor(Qt::red)));
    // QBrush brush(Qt::cyan);
    // brush.setStyle(Qt::Dense4Pattern);
    // painter.setBrush(brush);
    // pen.setWidth(5);
    // pen.setStyle(Qt::DashDotDotLine);
    // painter.setPen(pen);
    // painter.drawLine(QPoint(0,0), QPoint(100,100));
    // painter.drawEllipse(QPoint(100,100), 50, 50);
    // painter.drawRect(QRect(20,30,50,60));
    // painter.drawText(QRect(20,20,100,100),"好好学习，天天向上");

    // //高级设置
    // painter.drawEllipse(QPoint(100,100),50,50);



    // //抗锯齿
    // painter.setRenderHint(QPainter::Antialiasing);
    // painter.save();//保存状态
    // painter.translate(500,500);//原坐标点移动
    // painter.restore();//取出状态
    // painter.drawEllipse(QPoint(300,100),50,50);

    //画资源图片
    // painter.drawPixmap(pox,0,QBitmap(":/aaa.png"));
    painter.drawPixmap(pox,0,QPixmap(":/aaa.png"));

}


