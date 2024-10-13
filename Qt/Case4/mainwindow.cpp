#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //添加图标
    ui->actionaa->setIcon(QIcon(":/Image/aaa.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
