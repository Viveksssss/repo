#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <QDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QFontDialog>
#include <QInputDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // modal dialog box do not allow to click other
    connect(ui->actionopen,&QAction::triggered,this,[=](){
        QDialog dig(this);
        dig.resize(120,30);
        dig.exec();//阻塞
    });
    //non-modal dialog box the opppsite
    connect(ui->actionnew,&QAction::triggered,this,[=](){
        // QDialog *dig2 = new QDialog(this);
        // dig2->resize(120,30);
        // dig2->setAttribute(Qt::WidgetAttribute::WA_DeleteOnClose);//purpose is to delete after closing the window
        // dig2->show();
        QColorDialog *dig = new QColorDialog(this);
        dig->exec();
    });
    //standard message box
    connect(ui->actionreset,&QAction::triggered,this,[=](){
        //error message
        // QMessageBox::critical(this,"wrong!","wrong!");
        //information
        // QMessageBox::information(this,"info","info");
        //question
        // QMessageBox::question(this,"ques","Ques");
        // if(QMessageBox::Save == QMessageBox::question(this,"ques","Ques",QMessageBox::Save|QMessageBox::Cancel,QMessageBox::Save))
        //     qDebug()<<"good";
        // else qDebug()<<"No!";
        //warning
        // QMessageBox::warning(this,"warning","warning");
        // QMessageBox *dig = new QMessageBox(this);
        // dig ->setIcon(QMessageBox::Warning);
        // dig ->setIcon(QMessageBox::Critical);
        // dig->exec();

        QColor color = QColorDialog::getColor(Qt::red);
        qDebug()<<color.red()<<" "<<color.green()<<" "<<color.blue();
        qDebug()<<color.name().toUtf8().data();

        // QString filename = QFileDialog::getOpenFileName(this,"打开文件","/","(*)");
        // qDebug()<<filename;

        // int a = QInputDialog::getInt(this,"hh","hhh",200);
        // bool flag;
        // QFont font = QFontDialog::getFont(&flag,QFont("微软雅黑",24));
        // qDebug() << font.family().toUtf8().data() << " "<<font.pointSize()<<" " \
        //          <<font.bold()<<" "<<font.italic();

    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
