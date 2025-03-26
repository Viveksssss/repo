#ifndef TESTSIGNAL_H
#define TESTSIGNAL_H

#include <QObject>

class testSignal : public QObject
{
    Q_OBJECT
public:
    explicit testSignal(QObject *parent = nullptr);

    Q_INVOKABLE int getPro1() const; // 添加Q_INVOKABL就可以是的qml在其中访问
    Q_INVOKABLE void setPro1(int newPro1);

    Q_INVOKABLE int getPro2() const;
    Q_INVOKABLE void setPro2(int newPro2);

signals:
    void pro1Changed();

    void pro2Changed();

public slots:
    void prints();

private:
    int pro1 = 20;
    int pro2 = 30;



    Q_PROPERTY(int pro1 READ getPro1 WRITE setPro1 NOTIFY pro1Changed FINAL)
    Q_PROPERTY(int pro2 READ getPro2 WRITE setPro2 NOTIFY pro2Changed FINAL)
};

#endif // TESTSIGNAL_H
