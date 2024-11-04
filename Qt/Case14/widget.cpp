#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QPicture>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    // QPixmap pix(300,300);
    // pix.fill(Qt::white);

    // QPainter painter(&pix);
    // painter.setRenderHint(QPainter::Antialiasing);
    // painter.setPen(QPen(Qt::red));
    // painter.drawEllipse(QPoint(150,150),100,100);

    // pix.save("/home/vivek/pix.png");

    // QImage img(300,300,QImage::Format_RGB32);
    // img.fill(Qt::white);
    // QPainter painter(&img);
    // painter.setRenderHint(QPainter::Antialiasing);
    // painter.drawEllipse(QPoint(150,150),100,100);
    // img.save("/home/vivek/img.png");


    // QPicture
    QPicture pic;
    QPainter painter;
    painter.begin(&pic);

    painter.drawEllipse(QPoint(100,100),150,150);


    painter.end();

    pic.save("/home/vivek/pic.zt");
}

Widget::~Widget()
{
    delete ui;
}


void Widget::paintEvent(QPaintEvent*){
    QImage img;
    img.load(":/aaa.png");

    QPainter painter(this);

    // //修改像素
    // for(int i = 100;i<150;i++){
    //     for(int j = 100;j<150;j++){
    //         QRgb value = qRgb(255,0,0);
    //         img.setPixel(i,j,value);
    //     }
    // }

    // painter.drawImage(0,0,img);

    QPicture pic;
    pic.load("/home/vivek/pic.zt");
    painter.drawPicture(0,0,pic);



}
