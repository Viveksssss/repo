#include "testsignal.h"
#include "qdebug.h"
testSignal::testSignal(QObject *parent)
    : QObject{parent}
{
}
void testSignal::prints(){
    qDebug()<<"hello world!";
}

int testSignal::getPro2() const
{
    return pro2;
}

void testSignal::setPro2(int newPro2)
{
    if (pro2 == newPro2)
        return;
    pro2 = newPro2;
    emit pro2Changed();
}

int testSignal::getPro1() const
{
    return pro1;
}

void testSignal::setPro1(int newPro1)
{
    if (pro1 == newPro1)
        return;
    pro1 = newPro1;
    emit pro1Changed();
}
