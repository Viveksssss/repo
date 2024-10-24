#ifndef MYLABEL_H
#define MYLABEL_H

#include <QWidget>
#include <QLabel>

class MyLabel :public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = nullptr);

    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);

    void mouseMoveEvent(QMouseEvent*ev);
    void mousePressEvent(QMouseEvent*ev);
    void mouseReleaseEvent(QMouseEvent*ev);
signals:
};

#endif // MYLABEL_H
