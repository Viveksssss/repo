#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMenuBar>
#include<QToolBar>
#include<QLabel>
#include<QStatusBar>
#include<QDockWidget>
#include<QTextEdit>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(600,400);
    QMenuBar *bar = new QMenuBar;
    setMenuBar(bar);


    //Menu
    QMenu * filemenu = bar->addMenu("file");
    QMenu * editmenu = bar->addMenu("edit");
    QMenu * viewmenu = bar->addMenu("view");
    QMenu * constuctmenu = bar->addMenu("constuct");

    filemenu->addSeparator();
    QAction * newadd = filemenu->addAction("new add");
    QAction * open = filemenu->addAction("open");


    QAction * asd = editmenu->addAction("asd");
    QAction * bda = editmenu->addAction("bda");

    //Tool
    QToolBar *qtb = new  QToolBar(this);
    addToolBar(Qt::LeftToolBarArea,qtb);
    qtb->move(100,200);
    qtb->setFloatable(false);
    //使用位或来表示或
    qtb->addSeparator();
    qtb->setAllowedAreas(Qt::LeftToolBarArea | Qt::TopToolBarArea);

    qtb->setMovable(false);

    qtb->addAction(newadd);

    //Status
    QStatusBar *qsb = new QStatusBar;
    setStatusBar(qsb);
    QLabel *qlb1  = new QLabel("提示信息",this);
    qsb->addWidget(qlb1);

    QLabel *qlb2  = new QLabel("提示信息",this);
    qsb->addPermanentWidget(qlb2);
    // qsb->setFixedSize(20,30);

    //Float Window
    QDockWidget *dw = new QDockWidget("hhh",this);
    addDockWidget(Qt::TopDockWidgetArea,dw);

    dw->setAllowedAreas(Qt::TopDockWidgetArea |  Qt::BottomDockWidgetArea);

    //Core component
    QTextEdit *qtext = new QTextEdit(this);
    setCentralWidget(qtext);
}

MainWindow::~MainWindow()
{
    delete ui;
}
