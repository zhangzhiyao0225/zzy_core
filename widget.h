#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <qmath.h>
#include <QPainter>
#include <QPoint>
#include <QPixmap>
#include <QTimer>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    //void paintEvent(QPaintEvent *);
//    void update();
    void initUi();
    void paintEvent(QPaintEvent *event);
    void onTimeout();
private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
