#include "mywidget.h"
#include "ui_mywidget.h"
#include "MyButton.h"
#include <QPushButton>

MyWidget::MyWidget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    QPushButton *btn = new QPushButton;

    //if you want to display button in this screen,you need to specify dependencies
    btn->setParent(this);

    //setText enables you to set text
    btn->setText("大苏打");

    connect(btn,&QPushButton::clicked,this,&QWidget::hide);

    QPushButton *btn2 = new QPushButton;
    btn2->setParent(this);
    btn2->setText("sadasdsa");

    //move btn to somewhere
    btn2->move(100,100);
    btn->resize(20,20);

    //reset the size of widget
    resize(600,400);

    //specify window title
    setWindowTitle("my first window");

    //fix the size of window
    setFixedSize(600,400);

    //create MyButton
    MyButton * mbtn = new MyButton;
    mbtn->setParent(this);
    mbtn->setText("My Button");
    mbtn->move(20,20);
    connect(mbtn,&MyButton::clicked,this,&QWidget::close);
}

MyWidget::~MyWidget()
{
    qDebug()<<"~MyWidget";
    delete ui;
}
