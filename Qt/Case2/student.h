#ifndef STUDENT_H
#define STUDENT_H

#include <QObject>

class Student : public QObject
{
    Q_OBJECT
public:
    explicit Student(QObject *parent = nullptr);

signals:

public slots:
    //type of return is void
    //we need to achieve it
    void treat();
    void treat(QString foodname);
};

#endif // STUDENT_H
