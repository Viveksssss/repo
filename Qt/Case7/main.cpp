#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}



// #include<QApplication>
// #include<QWidget>
// #include<QLabel>
// #include<QLineEdit>
// #include<QHBoxLayout>
// #include<QVBoxLayout>
// #include<QPushButton>
// int main(int argc,char*argv[]){
//     QApplication app(argc,argv);
//     QLabel *inforLabel = new QLabel;//
//     QLabel *openLabel = new QLabel;//
//     QLineEdit*cmdLineEdit = new QLineEdit;
//     QPushButton*commitButton = new QPushButton;//
//     QPushButton*cancelButton = new QPushButton;//
//     QPushButton*browseButton = new QPushButton;//

//     inforLabel->setText("input cmd:");
//     openLabel->setText("open");

//     commitButton->setText("commit");
//     cancelButton->setText("cancel");
//     browseButton->setText("browse");
//     //cmdlayout
//     QHBoxLayout *cmdlayout = new QHBoxLayout;
//     cmdlayout->addWidget(openLabel);
//     cmdlayout->addWidget(cmdLineEdit);
//     //buttonlayout
//     QHBoxLayout* buttonlayout = new QHBoxLayout;
//     buttonlayout->addWidget(commitButton);
//     buttonlayout->addWidget(cancelButton);
//     buttonlayout->addWidget(browseButton);

//     QVBoxLayout*mainlayout = new QVBoxLayout;
//     mainlayout->addWidget(inforLabel);
//     mainlayout->addLayout(cmdlayout);
//     mainlayout->addLayout(buttonlayout);

//     QWidget w;
//     w.setLayout(mainlayout);
//     w.show();
//     return app.exec();
// }
