#ifndef STUDENTINFOWIDGET_H
#define STUDENTINFOWIDGET_H

#include <QWidget>
#include <QByteArray>
#include <QTableWidgetItem>
namespace Ui {
class StudentInfoWidget;
}
class QGroupBox;
class StudentInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StudentInfoWidget(QWidget *parent = nullptr);
    ~StudentInfoWidget();

private slots:
    void on_buttonAdd_clicked();

    void on_buttonDelItem_clicked();

    void on_buttonDelRow_clicked();

    void handleItemChanged(QTableWidgetItem*item);
private:
    QGroupBox*createFormGroup();
    QGroupBox*createPhotoGroup();
    void handleDialogAccepted(QGroupBox*formGroup,QGroupBox*photoGroup);
    void refreshTable();
    QByteArray photoData;
    Ui::StudentInfoWidget *ui;
};

#endif // STUDENTINFOWIDGET_H
