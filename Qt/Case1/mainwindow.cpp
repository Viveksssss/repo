#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPushButton *btn = new QPushButton;
    btn ->setParent(this);
    btn ->setText("button");
    btn ->move(20,20);
    btn ->resize(30,30);
    setWindowTitle("window");
    resize(600,400);
}

MainWindow::~MainWindow()
{
    delete ui;
}
