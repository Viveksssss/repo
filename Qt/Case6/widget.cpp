#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("das");
    this->setMinimumHeight(336);
    this->setMaximumHeight(336);
    this->setMinimumWidth(245);
    this->setMaximumWidth(246);
}

Widget::~Widget()
{
    delete ui;
}
