#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    initUi();
}

Widget::~Widget()
{
    delete ui;
}
//void Widget::paintEvent(QPaintEvent *)
//{
//    QPainter painter(this);
//    QPen pen_1;
//    pen_1.setColor(Qt::red);
//    pen_1.setWidth(3);
//    painter.setPen(pen_1);
//    //添加资源文件
//    painter.drawPixmap(0,0,QPixmap(":/ybp/111.png"));
//    int point_left,point_right;
//    int du = 240;
//    point_left = 80*sin(du*M_PI/180);
//    point_right = 80*cos(du*M_PI/180);
//    painter.drawLine(QPoint(150,150),QPoint(150+point_left,150-point_right));
//    //添加水深
//    QPainter painter_2(this);
//    QPen pen_2;
//    pen_2.setColor(QColor(0,30,50));
//    pen_2.setWidth(3);
//    painter_2.setPen(pen_2);
//    painter_2.drawRect(300,0,100,300);
//    int a = 100;
//    painter_2.fillRect(300,300-a,100,a,Qt::green);
//}
void Widget::initUi()
{
    QTimer* m_pTimer = new QTimer(this);
//    m_pTimer->setInterval(10);
    connect(m_pTimer, &QTimer::timeout, this, &Widget::onTimeout);
    m_pTimer->start(100);
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
//    painter.setBrush(QColor("#87CEFA"));
//    painter.setBrush(Qt::white);
    QPen pen;
    pen.setColor(QColor("#d4fdd8"));
    painter.setPen(pen);
    painter.drawRect(300,0,100,200);
//    painter.drawPixmap(QRect(0, 0, this->width(), 768), m_bg);
//    painter.drawPixmap(QRect(width()/2 - 111, 270, 222, 164), m_logoBg);
//    painter.drawPixmap(QRect(width()/2 - 119, 447, 237, 81), m_nameBg);

    //起始点坐标和结束点坐标
    int startX = 300;
    int startY = 200;
    int endX = 400;
    int endY = 200;
    /*200,是往下渲染的高度*/
    //第一条波浪路径集合
    QPainterPath waterPath1;
    //第二条波浪路径集合
    QPainterPath waterPath2;
    //第三条波浪路径集合
    QPainterPath waterPath3;
    QPainterPath waterPath4;


    //移动到左上角起始点
    waterPath1.moveTo(startX, startY);
    waterPath2.moveTo(startX, endY);
    waterPath3.moveTo(startX, endY);
    waterPath4.moveTo(startX, endY);

    //正弦曲线公式 y = A * qSin(ωx + φ) + k
    //A表示振幅,可以理解为水波的高度
    //k表示y轴偏移,控制在垂直方向显示的位置
    //φ控制x轴偏移，通过定时器控制实现动画效果
    //w表示周期,可以理解为水波的密度,值越大密度越大(浪越密集 ^_^),取值 密度*M_PI/宽度
    int Density = 10;
    double w = Density*M_PI/300;
    int offset;
    offset += 6000;
    for(int i = 300; i <= 400; i++){
        /*50是幅值*/
        double y1 = (double)(6 * sin(-w * i + offset)) + 50;
        double y2 = (double)(6 * sin(-w * i + offset + 20*w))+45;
        double y3 = (double)(6 * sin(-w/2*i + offset + 40*w));
        double y4 = (double)(6 * sin(-w * i + offset - 30*w));
        waterPath1.lineTo(i, y1);
        waterPath2.lineTo(i, y2);
        waterPath3.lineTo(i, y3);
        waterPath4.lineTo(i, y4);
    }

    //形成闭合路径
    waterPath1.lineTo(endX, endY);
    waterPath2.lineTo(endX, endY);
    waterPath3.lineTo(endX, endY);
    waterPath4.lineTo(endX, endY);

    //颜色及透明度设置
    QColor waterColor1 = QColor("#1c8584");
    waterColor1.setAlpha(205);
    QColor waterColor2 = QColor("#7cc4c9");
    waterColor2.setAlpha(105);
//    QColor waterColor3 = QColor("#1c8584");
//    waterColor3.setAlpha(150);
//    QColor waterColor4 = QColor("#d4fdd8");
//    waterColor4.setAlpha(70);

    //绘制path
    painter.setBrush(waterColor2);
    painter.drawPath(waterPath2);

//    painter.setBrush(waterColor3);
//    painter.drawPath(waterPath3);

//    painter.setBrush(waterColor4);
//    painter.drawPath(waterPath4);

    painter.setBrush(waterColor1);
    painter.drawPath(waterPath1);

    QWidget::paintEvent(event);
}

void Widget::onTimeout()
{
    update();
}
