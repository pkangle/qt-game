#include "form1.h"
#include "ui_form1.h"
#include <QPainter>
#include <QTimer>
#include <QStack>

Form1::Form1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form1),
    currentPosition(0),
    moveSpeed(100) // 设置移动速度，单位为毫秒
{
    ui->setupUi(this);
    QFont font;
    font.setPixelSize(cellSize);
    // 创建定时器，控制对象移动速度
    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &Form1::moveObject);
    moveTimer->start(moveSpeed);

    // 获取对象路线
    getObjectRoute();
}

Form1::~Form1()
{
    delete ui;
}

void Form1::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制迷宫和对象
    drawMaze(painter);
    drawObject(painter);
    int mazeData[20][20];
}

void Form1::getObjectRoute()
{
    route = {{1,0}, {1,1},{1,2},{1,3},{1,4},{1,5},{1,6},{1,7},{1,8},{2,8},{3,8},{3,9},{3,10},{2,10},{1,10},{1,11},{1,12},{1,13},{1,14},
            {1,15},{2,15},{2,16},{2,17},{2,18},{2,19},{3,19},
            {4,19},{4,18},{4,17},{4,16},{5,16},{6,16},{6,15},{6,14},{5,14},{4,14},{4,13},{4,12},{5,12},{5,11},{5,10},{5,9},{5,8},{5,7},
            {5,6},{4,6},{3,6},{3,5},{3,3},{3,2},{3,1},{3,0},{4,0},{5,0},
            {5,1},{5,2},{5,3},{5,4},{6,4},{7,4},{7,5},{7,6},{7,7},{8,7},{9,7},{9,8},{9,9},{8,9},{7,9}};
}

void Form1::drawMaze(QPainter &painter)
{
    // 绘制迷宫
    // 迷宫数据，0表示墙，1表示通路
    int mazeData[20][20] = {
        {0,1,0,1,1,1,0,0,0,1,1,1,1,0,0,0,1,1,1,0},
        {0,1,0,1,0,1,0,1,1,0,1,0,1,0,0,0,1,0,1,0},
        {0,1,0,1,0,1,0,1,0,1,1,0,1,0,0,0,1,0,1,0},
        {0,1,0,1,0,1,0,1,0,1,1,0,1,0,0,1,1,0,1,0},
        {0,1,0,1,0,1,1,1,0,1,0,0,1,1,0,1,0,0,1,1},
        {0,1,0,1,0,0,0,1,0,1,1,1,0,1,0,1,0,0,0,1},
        {0,1,0,1,1,1,0,1,0,0,0,1,0,1,0,1,1,0,1,1},
        {0,1,0,0,0,1,0,1,1,1,0,1,0,1,0,0,1,1,0,1},
        {0,1,1,1,0,1,0,0,0,1,0,1,0,1,1,0,0,1,0,1},
        {0,0,0,1,0,1,0,1,1,1,0,1,0,0,1,0,1,1,0,1},
        {0,1,1,1,0,1,0,1,0,0,0,1,0,1,1,0,1,0,0,1},
        {0,1,0,0,0,1,0,1,0,0,1,1,0,1,0,1,1,0,1,1},
        {0,1,0,0,1,1,0,1,1,0,1,0,0,1,0,1,0,0,1,0},
        {0,1,0,0,1,0,0,0,1,0,1,0,1,1,0,1,0,1,1,0},
        {0,1,0,0,1,1,1,0,1,0,1,0,1,0,0,1,0,1,0,0},
        {0,1,1,0,0,0,1,0,1,0,1,0,1,1,0,1,0,1,1,0},
        {0,0,1,0,1,1,1,0,1,0,1,0,0,1,0,1,0,0,1,0},
        {0,0,1,0,1,0,0,0,1,0,1,0,1,1,0,1,0,0,1,0},
        {0,0,1,0,1,0,0,0,1,0,1,0,1,0,0,1,0,0,1,0},
        {0,0,1,1,1,0,0,0,1,1,1,0,1,1,1,1,0,0,1,0}
    };

    QFont font1;
    font1.setPixelSize(cellSize);
    font1.setBold(true);
    painter.setFont(font1);

    for (int y = 0; y < N; ++y) {
        for (int x = 0; x < N; ++x) {
            QRect rect(x * cellSize, y * cellSize, cellSize, cellSize);
            if (mazeData[y][x] == 0) {
                painter.drawText(x * cellSize, y * cellSize, cellSize, cellSize, Qt::AlignCenter, "墙");painter.drawText(rect,"墙");

            } else {
                painter.fillRect(rect, Qt::white);
            }
        }
    }

    QFont font2;
    font2.setPixelSize(15);
    painter.setFont(font2);

    painter.setPen(Qt::red);
    painter.drawText(360,400,"摆烂");
}

void Form1::drawObject(QPainter &painter)
{
    // 绘制对象
    if (currentPosition >= route.size()) return;
    painter.setPen(Qt::blue);
    QPoint pos = route[currentPosition];
    QRect rect(pos.x() * cellSize, pos.y() * cellSize, cellSize, cellSize);
    painter.drawEllipse(rect);  // 使用 drawEllipse 方法绘制对象
    currentPosition++;
}


void Form1::moveObject()
{
    //++currentPosition; // 更新当前位置
    if (currentPosition >= route.size()) {
        moveTimer->stop(); // 路线走完，停止定时器
    }
    update();
}
