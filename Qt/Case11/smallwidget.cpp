#include "smallwidget.h"
#include "ui_smallwidget.h"




//右键项目->添加新文件->Qt->设计师->Widget 可以构建自定义框架
SmallWidget::SmallWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SmallWidget)
{
    ui->setupUi(this);
    void (QSpinBox::*spinbox)(int) = &QSpinBox::valueChanged;
    connect(ui->spinBox,spinbox,[=](int value){
        ui->horizontalSlider->setValue(value);
    });

    connect(ui->horizontalSlider,&QSlider::valueChanged,[=](int value){
        ui->spinBox->setValue(value);
    });

    connect(ui->pushButton,&QPushButton::clicked,this,&SmallWidget::setData);

}

void SmallWidget::setData(int val){
    val = 50;
    ui->horizontalSlider->setValue(val);
}


SmallWidget::~SmallWidget()
{
    delete ui;
}
