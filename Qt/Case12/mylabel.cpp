#include "mylabel.h"
#include <QLabel>
#include <QMouseEvent>

MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{
    setMouseTracking(true);

}



void MyLabel::enterEvent(QEvent*){
    qDebug()<<"yes";
}
void MyLabel::leaveEvent(QEvent*){
    qDebug()<<"no";
}


void MyLabel::mouseMoveEvent(QMouseEvent*ev){
    //Qt中可以直接对字符串中的变量命为%1.%2。。。
    //然后.arg(参数)来格式化

    //因为按下和释放都是瞬间的状态，而移动是一个持续的过程，所以我们用buttons
    //又因为，过程中可能是组合按键，所以我们用&，只要有左键即可


    //下列代码可以在按下左键移动的同时打出输出
    // if(ev->buttons () & Qt::LeftButton){
        // QString str = QString("当前坐标是 x = %1,y = %2").arg(ev->x()).arg(ev->y());
        // qDebug()<<str;
    // }

    //但是我们想要的是在不按下的情况下移动，也能输出
    //我们可以设置鼠标追踪状态，参上第6行
    QString str = QString("当前坐标是 x = %1,y = %2").arg(ev->x()).arg(ev->y());

    qDebug()<<str;
}
void MyLabel::mousePressEvent(QMouseEvent*ev){
    if(ev->button() == Qt::LeftButton){
        qDebug()<<"press";
    }
}
void MyLabel::mouseReleaseEvent(QMouseEvent*ev){
    qDebug()<<"release";
}
