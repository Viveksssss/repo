#include "widget.h"
#include<QPushButton>

widget::widget(QWidget *parent)
    : QWidget{parent}
{
    this->tc = new Teacher(this);
    this->st = new Student(this);

    //connect signal to slots
    // connect(tc,&Teacher::hungry,st,&Student::treat);


    // typedef void(Teacher:: *teacher)(QString);
    // teacher t = Teacher::hungry;
    // typedef void(Student::*student)(QString);
    // student s= Student::treat;
    void(Teacher::*t)(QString) = &Teacher::hungry;
    void(Student::*s)(QString) = &Student::treat;
    resize(600,400);

    QPushButton *btn = new QPushButton;
    connect(tc,t,st,s);
    btn->setParent(this);
    btn->setText("下课");
    connect(btn,&QPushButton::clicked,tc,[=](){
        tc->hungry("asd");
    });
    connect(btn,&QPushButton::clicked,this,&widget::classover);




    // void(Teacher::*t)() = &Teacher::hungry;
    // void(Student::*s)() = &Student::treat;


    // connect(tc,t ,st,s);
    // classover();



    //1.0signal can connect to signal
    // connect(btn,&QPushButton::clicked,this,classover);

    //2.0signal can disconnect to the signal and slot
    // disconnect(btn,&QPushButton::clicked,tc,t);

    //3.0 one signal can respond to multiple slot
    //4.0 several signals can link to the same slot
    //5.0 the parameter type of signal and slot should be the same,except for number
    //meanwhile,they should correspond one by one.

    //Writing style of Q4 version
    //disadvantage:Do not perform matching detection on parameter types
    //nature:SiGNAL("Teacher::hungry(QString)"),SLOT("Student::treat(QString)");
}

void widget::classover(){
    //触发
    //the keyword emit can tigger the signal
    emit this->tc->hungry();
    emit this->tc->hungry("好吃的");
}
