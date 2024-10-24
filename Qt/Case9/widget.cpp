#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    //tableWidget
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setRowCount(5);

    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"姓名"<<"性别"<<"年龄");

    QList<QString>namelist;
    QList<QString>listlist;
    namelist<<"hh"<<"aa"<<"yes"<<"sss"<<"ddd";
    listlist<<"AAA"<<"BBB"<<"CCC"<<"DDD"<<"EEE";
    for(int i = 0;i<5;i++){
        int col = 0;
        ui->tableWidget->setItem(i,col++,new QTableWidgetItem(namelist[i]));
        ui->tableWidget->setItem(i,col++,new QTableWidgetItem(listlist[i]));
        ui->tableWidget->setItem(i,col++,new QTableWidgetItem(QString::number(i+18)));

    }
}

Widget::~Widget()
{
    delete ui;
}
