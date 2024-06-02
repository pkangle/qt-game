#include "form1.h"
#include "ui_form1.h"
#include <QPainter>
#include <QTimer>
#include <QStack>

Form1::Form1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form1),
    currentPosition(0),
    moveSpeed(500) // 设置移动速度，单位为毫秒
{
    ui->setupUi(this);

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
}

void Form1::getObjectRoute()
{
    QStack<QPoint> path;
    dfs(20, 0, path); // 从起点开始深度优先搜索
}

void Form1::dfs(int x, int y, QStack<QPoint> &path)
{
    if (x < 0 || x >= N || y < 0 || y >= N || mazeData[x][y] == 0) return; // 越界或者遇到墙
    mazeData[x][y] = 0; // 标记已访问
    path.push({x, y}); // 将当前位置加入路径
    if (x == N - 1 && y == N - 1) { // 到达终点
        while (!path.empty()) {
            route.push_back(path.top());
            path.pop();
        }
        return;
    }
    // 四个方向搜索
    dfs(x - 1, y, path); // 上
    dfs(x + 1, y, path); // 下
    dfs(x, y - 1, path); // 左
    dfs(x, y + 1, path); // 右
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
    for (int y = 0; y < N; ++y) {
        for (int x = 0; x < N; ++x) {
            QRect rect(x * cellSize, y * cellSize, cellSize, cellSize);
            if (mazeData[y][x] == 0) {
                painter.fillRect(rect, Qt::black);
            } else {
                painter.fillRect(rect, Qt::white);
            }
        }
    }
    painter.setPen(Qt::green);
    painter.drawText(20,10,"起点");
    painter.setPen(Qt::red);
    painter.drawText(360,400,"摆烂");
}

void Form1::drawObject(QPainter &painter)
{
    // 绘制对象
    if (currentPosition >= route.size()) return;
    while(currentPosition < route.size()){
    painter.setPen(Qt::blue);
    QPoint pos = route[currentPosition];
    QRect rect(pos.x() * cellSize, pos.y() * cellSize, cellSize, cellSize);
    painter.fillRect(rect, Qt::red);
    currentPosition++;
    }
}

void Form1::moveObject()
{
    ++currentPosition; // 更新当前位置
    if (currentPosition >= route.size()) {
        moveTimer->stop(); // 路线走完，停止定时器
    }
    update();
}
