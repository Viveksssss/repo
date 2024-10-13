#ifndef WIDGET_H
#define WIDGET_H
#include "student.h"
#include "teacher.h"
#include <QWidget>

class widget : public QWidget
{
    Q_OBJECT
public:
    explicit widget(QWidget *parent = nullptr);

    Teacher*tc;
    Student*st;

    void classover();
signals:
};

#endif // WIDGET_H
