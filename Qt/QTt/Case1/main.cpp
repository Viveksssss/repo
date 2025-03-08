#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include "datamanager.h"
int main(int argc, char *argv[])
{
    DataManager::instance();

    QApplication a(argc, argv);
    QFile styleFile(":/style/style.qss");
    if(styleFile.open(QFile::ReadOnly)){
        QString styleSheet = QString(styleFile.readAll());
        a.setStyleSheet(styleSheet );
        styleFile.close();
    }
    MainWindow w;

    w.show();
    return a.exec();
}
