#ifndef TEACHER_H
#define TEACHER_H

#include <QObject>

class Teacher : public QObject
{
    Q_OBJECT
public:
    explicit Teacher(QObject *parent = nullptr);

//customize signals shouled be writed after "signals"
//the type of return value is void
//just need to statement,don't need to achieve
//we can reload it
signals:
    void hungry();

    void hungry(QString foodname);
};

#endif // TEACHER_H
