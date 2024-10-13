#include "student.h"
#include <QDebug>
Student::Student(QObject *parent)
    : QObject{parent}
{}


void Student::treat(){
     qDebug()<<"吃饭！";
}

void Student::treat(QString foodname){
    qDebug()<<"吃"<<foodname.toUtf8().data();
}
