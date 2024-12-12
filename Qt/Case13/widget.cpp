#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::clicked,[=]{
        QString s =  QFileDialog::getOpenFileName(this,"打开文件","c:","*.cpp");
        if(s.isEmpty()){
            QMessageBox::warning(this,"警告","文件路径异常");
            return ;
        }
        QFile file(s);
        file.open(QIODevice::ReadOnly);
        ui->textEdit->setText(s);
        file.open(QIODevice::ReadOnly);
        //默认支持utf-8

        QFileInfo info(file);

        // ui->textEdit_2->setText(info.suffix());//后缀
        ui->textEdit_2->setText(info.canonicalFilePath());
    });
}

Widget::~Widget()
{

    delete ui;
}
