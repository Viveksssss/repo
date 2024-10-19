#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QStringList>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    // ui->radioButton->setChecked(true);
    // //output based on status
    // connect(ui->checkBox,&QCheckBox::stateChanged,[=](int state){
    //     qDebug()<<state;
    // });

    // QListWidgetItem *item = new QListWidgetItem("皇后皇后皇后");
    // ui->listWidget->addItem(item);
    // item->setTextAlignment(Qt::AlignCenter);

    // QStringList qsl ;
    // qsl<<"hhh"<<"aaa"<<"lll"<<"sss";
    // ui->listWidget->addItems(qsl);
    ui->treeWidget->setHeaderLabels(QStringList()<<"英雄"<<"英雄简介");
    QTreeWidgetItem*liitem = new QTreeWidgetItem(QStringList()<<"力量");
    QTreeWidgetItem*minitem = new QTreeWidgetItem(QStringList()<<"敏捷");
    QTreeWidgetItem*aaa = new QTreeWidgetItem(QStringList()<<"aaa");
    QTreeWidgetItem*bbb = new QTreeWidgetItem(QStringList()<<"bbb");
    liitem->addChild(aaa);
    minitem->addChild(bbb);
    ui->treeWidget->addTopLevelItem(liitem);
    ui->treeWidget->addTopLevelItem(minitem);
}

Widget::~Widget()
{
    delete ui;
}
