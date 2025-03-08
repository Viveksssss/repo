#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QButtonGroup>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QButtonGroup*btnGrp = new QButtonGroup(this);
    btnGrp->addButton(ui->btnFinance,2);
    btnGrp->addButton(ui->btnHonor,3);
    btnGrp->addButton(ui->btnSchedule,1);
    btnGrp->addButton(ui->btnSettings,4);
    btnGrp->addButton(ui->btnStudentInfo,0);

    connect(btnGrp,&QButtonGroup::idClicked,ui->stackedWidget,&QStackedWidget::setCurrentIndex);

    btnGrp->button(0)->setChecked(true);
    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

