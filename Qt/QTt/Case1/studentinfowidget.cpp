#include "studentinfowidget.h"
#include "ui_studentinfowidget.h"
#include <QSqlQuery>
#include <QDialog>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QObject>
#include <QFormLayout>
#include <QLineEdit>
#include <QDateEdit>
#include <QComboBox>
#include <QLabel>
#include <QFileDialog>
#include <QStandardPaths>
#include <QBuffer>
#include <QMessageBox>
#include <QDebug>
#include <QErrorMessage>
#include <QSqlError>
#include "tabledelegates.h"

StudentInfoWidget::StudentInfoWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StudentInfoWidget)
{
    ui->setupUi(this);


    ui->tableWidget->verticalHeader()->setDefaultSectionSize(80);
    ui->tableWidget->resizeColumnToContents(160);

    //性别代理
    ComboBoxDelegate*genderDelegate = new ComboBoxDelegate(this);
    genderDelegate->setItem(QStringList() << "男" << "女");
    ui->tableWidget->setItemDelegateForColumn(2,genderDelegate);

    //进度列代理
    ComboBoxDelegate*progressDelegate = new ComboBoxDelegate(this);
    progressDelegate->setItem(QStringList() <<"0%"<<"20%"<<"40%" <<"60%" <<"80%" << "100%" );
    ui->tableWidget->setItemDelegateForColumn(6,progressDelegate);

    ui->tableWidget->setItemDelegateForColumn(3,new DateEditDelegate(this));
    ui->tableWidget->setItemDelegateForColumn(4,new DateEditDelegate(this));

    ui->tableWidget->setItemDelegateForColumn(7,new ImageDelegate(this));

    connect(ui->tableWidget,&QTableWidget::itemChanged,this,&StudentInfoWidget::handleItemChanged);
    refreshTable();
}

StudentInfoWidget::~StudentInfoWidget()
{
    delete ui;
}

void StudentInfoWidget::refreshTable()
{
    ui->tableWidget->blockSignals(true);
    ui->tableWidget->setRowCount(0);

    QSqlQuery query("select * from studentInfo");
    while(query.next()){
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        for(int i = 0;i<ui->tableWidget->columnCount();i++){
            QTableWidgetItem*item = new QTableWidgetItem();
            item->setTextAlignment(Qt::AlignCenter);
            if(i == ui->tableWidget->columnCount()-1){
                photoData = query.value(i).toByteArray();
                if(!photoData.isEmpty()){
                    QPixmap photo;
                    photo.loadFromData(photoData);
                    item->setData(Qt::DecorationRole,photo.scaled(100,100,Qt::KeepAspectRatio));
                    item->setData(Qt::UserRole,photoData);
                }
            }
            else{
                item->setText(query.value(i).toString());
            }
            ui->tableWidget->setItem(row,i,item);

        }
    }
    ui->tableWidget->blockSignals(false);
}

void StudentInfoWidget::on_buttonAdd_clicked()
{
    QDialog *dlg = new QDialog(this);
    dlg->setWindowTitle("添加学生信息");
    dlg->setMinimumSize(600,400);

    QVBoxLayout*mainLayout = new QVBoxLayout(dlg);
    QHBoxLayout*contentLayout = new QHBoxLayout();

    mainLayout->addLayout(contentLayout);

    QGroupBox* formGroup = createFormGroup();
    QGroupBox* photoGroup = createPhotoGroup();

    contentLayout->addWidget(formGroup,1);
    contentLayout->addWidget(photoGroup,1);

    QHBoxLayout*btnLayout = new QHBoxLayout();
    QPushButton*btnConfirm = new QPushButton("确定");
    QPushButton*btnCancel = new QPushButton("取消");

    btnConfirm->setFixedWidth(150);
    btnCancel->setFixedWidth(150);


    btnLayout->addStretch(); //弹簧
    btnLayout->addWidget(btnConfirm);
    btnLayout->addWidget(btnCancel);
    btnLayout->addStretch();  //弹簧


    connect(btnConfirm,&QPushButton::clicked,dlg,&QDialog::accept);
    connect(btnCancel,&QPushButton::clicked,dlg,&QDialog::reject);

    mainLayout->addLayout(btnLayout);

    if(dlg->exec() == QDialog::Accepted){
        handleDialogAccepted(formGroup,photoGroup);
    }

}

QGroupBox *StudentInfoWidget::createFormGroup()
{
    QGroupBox*formGroup = new QGroupBox("基本信息");
    QFormLayout*formLayout = new QFormLayout(formGroup);

    //初始化控件
    QLineEdit*idEdit = new QLineEdit();
    idEdit->setObjectName("idEdit");
    QLineEdit*nameEdit = new QLineEdit();
    nameEdit->setObjectName("nameEdit");
    QComboBox*genderCombo = new QComboBox();
    genderCombo->setObjectName("genderCombo");
    QDateEdit*birthdayEdit = new QDateEdit(QDate::currentDate());
    birthdayEdit->setObjectName("birthdayEdit");
    QDateEdit*joinDateEdit = new QDateEdit(QDate::currentDate());
    joinDateEdit->setObjectName("joinDateEdit");
    QLineEdit*goalEdit = new QLineEdit();
    goalEdit->setObjectName("goalEdit");
    QComboBox*progressCombo = new QComboBox();
    progressCombo->setObjectName("progressCombo");

    //配置控件
    genderCombo->addItems({tr("男"),tr("女")});
    progressCombo->addItems({
        ("0%"),("20%"),("40%"),("60%"),("80%"),("100%")
    });

    birthdayEdit->setDisplayFormat("yyyy-MM-dd");
    joinDateEdit->setDisplayFormat("yyyy-MM-dd");

    birthdayEdit->setCalendarPopup(true);
    joinDateEdit->setCalendarPopup(true);

    formLayout->addRow(tr("编号:"),idEdit);
    formLayout->addRow(tr("姓名:"),nameEdit);
    formLayout->addRow(tr("性别:"),genderCombo);
    formLayout->addRow(tr("出生日期:"),birthdayEdit);
    formLayout->addRow(tr("入学日期:"),joinDateEdit);
    formLayout->addRow(tr("学习目标:"),goalEdit);
    formLayout->addRow(tr("当前进度:"),progressCombo);

    return formGroup;
}

QGroupBox *StudentInfoWidget::createPhotoGroup()
{
    QGroupBox*photoGroup = new QGroupBox("照片上传");
    QVBoxLayout*photoLayout = new QVBoxLayout(photoGroup);

    QLabel*labelPhotoPreview = new QLabel();
    QPushButton*btnSelectPhoto = new QPushButton("选择照片");

    labelPhotoPreview->setAlignment(Qt::AlignCenter);
    labelPhotoPreview->setMinimumSize(200,200);
    btnSelectPhoto->setFixedSize(100,40);

    photoLayout->addWidget(labelPhotoPreview);
    photoLayout->addWidget(btnSelectPhoto,0,Qt::AlignHCenter);

    connect(btnSelectPhoto,&QPushButton::clicked,[this,labelPhotoPreview](){
        QString fileName = QFileDialog::getOpenFileName(
            this,tr("选择学生照片"),
            QStandardPaths::writableLocation(QStandardPaths::PicturesLocation),
            tr("图片文件(*.png *.jpg *.jpeg)")
        );


        if(!fileName.isEmpty()){
            QPixmap pixmap(fileName);
            if(!pixmap.isNull()){
                pixmap = pixmap.scaled(
                    labelPhotoPreview->width()-30,
                    labelPhotoPreview->height()-30,
                    Qt::KeepAspectRatio
                );
                labelPhotoPreview->setPixmap(pixmap);
                QBuffer buffer(&this->photoData);
                buffer.open(QIODevice::WriteOnly);
                pixmap.save(&buffer,"PNG");
            }
            else QMessageBox::warning(this,"错误","无法加载图片");
        }
    });

    return photoGroup;
}

void StudentInfoWidget::handleDialogAccepted(QGroupBox *formGroup, QGroupBox *photoGroup)
{
    // 获取表单控件（修正joinDateEdit的查找）
    QLineEdit*idEdit = formGroup->findChild<QLineEdit*>("idEdit");
    QLineEdit*nameEdit = formGroup->findChild<QLineEdit*>("nameEdit");
    QComboBox*genderCombo = formGroup->findChild<QComboBox*>("genderCombo");
    QDateEdit*birthdayEdit = formGroup->findChild<QDateEdit*>("birthdayEdit");
    QDateEdit*joinDateEdit = formGroup->findChild<QDateEdit*>("joinDateEdit"); // 修正此处
    QLineEdit*goalEdit = formGroup->findChild<QLineEdit*>("goalEdit");
    QComboBox*progressCombo = formGroup->findChild<QComboBox*>("progressCombo");

    // 非空检查
    if(idEdit->text().isEmpty() || nameEdit->text().isEmpty()){
        QMessageBox::warning(this,"错误","学号和姓名不能为空");
        return ;
    }

    // 检查学号是否已存在
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT id FROM studentInfo WHERE id = ?");
    checkQuery.addBindValue(idEdit->text());
    if(checkQuery.exec() && checkQuery.next()){
        QMessageBox::warning(this,"错误",tr("学号 %1 已存在!").arg(idEdit->text()));
        return;
    }

    // 准备插入语句（修正字段名和占位符）
    QSqlDatabase::database().transaction();
    QSqlQuery insertQuery;
    insertQuery.prepare(
        "INSERT INTO studentInfo "
        "(id, name, gender, birthday, join_data, study_goal, progress, photo) "
        "VALUES (?, ?, ?, ?, ?, ?, ?, ?)"
        );

    // 绑定参数（顺序对应字段）
    insertQuery.addBindValue(idEdit->text());
    insertQuery.addBindValue(nameEdit->text());
    insertQuery.addBindValue(genderCombo->currentText());
    insertQuery.addBindValue(birthdayEdit->date().toString("yyyy-MM-dd"));
    insertQuery.addBindValue(joinDateEdit->date().toString("yyyy-MM-dd")); // join_date
    insertQuery.addBindValue(goalEdit->text()); // study_goal
    insertQuery.addBindValue(progressCombo->currentText()); // progress
    insertQuery.addBindValue(photoData.isEmpty() ? QVariant() : photoData);

    if(!insertQuery.exec()){
        QSqlDatabase::database().rollback();
        QMessageBox::critical(this,"错误", "添加失败: " + insertQuery.lastError().text());
    } else {
        QSqlDatabase::database().commit();
        refreshTable();
        QMessageBox::information(this,"成功",tr("已成功添加学生: %1").arg(nameEdit->text()));
    }
}


void StudentInfoWidget::on_buttonDelItem_clicked()
{
    auto selected = ui ->tableWidget->selectedItems();
    if(selected.isEmpty()){
        QMessageBox::warning(this,"warning","mismatched!");
        return ;
    }

    QSqlDatabase::database().transaction();
    for(const QTableWidgetItem*item:selected){
        int row = item->row();
        int col = item->column();
        QString id = ui->tableWidget->item(row,0)->text();
        const QStringList columns = {"id","name","gender","birthday","join_data","study_goal","progress","photo"};
        QSqlQuery query;
        query.prepare(QString("update studentInfo set %1 = ? where id = ?").arg(columns[col]));
        query.addBindValue("");
        query.addBindValue(id);

        if(!query.exec()){
            QSqlDatabase::database().rollback();
            QMessageBox::critical(this,"错误","更新失败"+query.lastError().text());
            return ;
        }
        QSqlDatabase::database().commit();
        refreshTable();
    }
}


void StudentInfoWidget::on_buttonDelRow_clicked()
{
    auto selected = ui->tableWidget->selectionModel()->selectedRows();
    if(selected.isEmpty()){
        QMessageBox::warning(this,"warning","mismatched!");
        return;
    }
    QSqlDatabase::database().transaction();
    for(const QModelIndex&index:selected){
        QString id = ui->tableWidget->item(index.row(),0)->text();
        QSqlQuery query;
        query.prepare("delete from studentInfo where id = ?");
        query.addBindValue(id);
        if(!query.exec()){
            QSqlDatabase::database().rollback();
            QMessageBox::critical(this,"错误","删除s失败:"+query.lastError().text());
            return;
        }
    }
    QSqlDatabase::database().commit();
    refreshTable();
}


void StudentInfoWidget::handleItemChanged(QTableWidgetItem*item){
    const int row = item->row();
    const int col = item->column();
    if(col == 0){
        QMessageBox::warning(this,"警告","学号不可修改");
        refreshTable();
        return ;
    }

    const QString originalId = ui->tableWidget->item(row,0)->text();
    const QString columnName = QStringList{"id","name","gender","birthday","join_data","study_goal","progress","photo"}[col] ;

    QSqlDatabase::database().transaction();
    try{
        QSqlQuery updateQuery;
        updateQuery.prepare(QString("update studentInfo set %1 = ? where id = ?").arg(columnName));
        if(columnName == "photo"){
            updateQuery.addBindValue(item->data(Qt::UserRole).toByteArray());
        }else{
            updateQuery.addBindValue(item->text().trimmed());
        }

        updateQuery.addBindValue(originalId);

        if(!updateQuery.exec()){
            throw std::runtime_error("更新失败"+updateQuery.lastError().text().toStdString());
        }
        QSqlDatabase::database().commit();
    }catch(const std::exception&e){
        QSqlDatabase::database().rollback();
        refreshTable();
        QMessageBox::critical(this,"操作失败",QString::fromUtf8(e.what()));
    }
}






