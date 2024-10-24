#include "widget.h"
#include "ui_widget.h"
#include <QMovie>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{

    ui->setupUi(this);
    ui->label->setPixmap(QPixmap(":/new/prefix1/Image/aaa.png"));
    ui->stackedWidget->setCurrentIndex(2);
    connect(ui->b1,&QPushButton::clicked,ui->scrollArea,[=](){
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(ui->b2,&QPushButton::clicked,ui->scrollArea,[=](){
        ui->stackedWidget->setCurrentIndex(1);
    });
    connect(ui->b3,&QPushButton::clicked,ui->scrollArea,[=](){
        ui->stackedWidget->setCurrentIndex(2);
    });

    ui->comboBox->addItem("奔驰");
    ui->comboBox->addItem("宝马");

    connect(ui->pushButton_11,&QPushButton::clicked,[=](){
        ui->comboBox->setCurrentIndex(9);
    });

    QMovie *move = new QMovie("");
    ui->label->setMovie(move);
    move->start();
}

Widget::~Widget()
{
    delete ui;
}
