#include "mybutton.h"

MyButton::MyButton(QPushButton *parent)
    : QPushButton{parent}
{

}

MyButton::~MyButton(){
    qDebug() << "~MyButton";
}
