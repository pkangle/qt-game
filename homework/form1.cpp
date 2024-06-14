#include "form1.h"
#include "ui_form1.h"
#include <QPainter>
#include <QTimer>
#include <QStack>
#include <QDebug>
#include <QVector>
#include <QMessageBox>

Form1::Form1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form1),
    currentPosition(0),
    moveSpeed(5000),
    StudentSpeed(200),
    studentPosition(1,0),
    gameEnded1(false),
    gameEnded2(false)
{
    ui->setupUi(this);
    QFont font;
    font.setPixelSize(cellSize);
    // 创建定时器，控制对象移动速度
    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &Form1::moveObject);
    moveTimer->start(moveSpeed);

    //操作对象计时器
    StudentTimer = new QTimer(this);
    connect(StudentTimer,&QTimer::timeout, this, &Form1::moveStudent);

    // 获取对象路线
    getObjectRoute();
    setFocusPolicy(Qt::StrongFocus);

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
    int mazeData[15][15];
    //绘制操控对象
    drawStudent(painter);

}

void Form1::getObjectRoute()
{
    route = {
        {2,14},{3,14},{4,14},{4,13},{4,12},{4,11},{4,10},{5,10},{5,9},{5,8},{5,7},{4,7},{4,6},{4,5},{4,4},{5,4},{5,3},{5,2},{4,2},{4,1},
        {4,0},{5,0},{6,0},{7,0},{7,1},{7,2},{8,2},{8,3},{8,4},{9,4},{9,5},{9,6},{8,6},{7,6},{7,7},{7,8},{8,8},{8,9},{8,10},
        {7,10},{7,11},{6,11},{6,12},{6,13},{7,13},{7,14},{8,14},{9,14},{10,14},{11,14},
        {11,13},{11,12},{10,12},{10,11},{10,10},{10,9},{11,9},{11,8},{11,7},{11,6},{11,5},{11,4},{11,3},{10,3},{10,1},{10,0},
        {11,0},{12,0},{13,0},
        {13,1},{13,2},{14,2},{14,3},{14,4},{13,4},{13,5},{13,6},{13,7},{14,7},{14,8},{14,9},{14,10},{13,10},{13,11},{13,12},{13,13},{13,14}
    };
}


void Form1::drawMaze(QPainter &painter)
{
    // 绘制迷宫
    // 迷宫数据，0表示墙，1表示通路


    QFont font1;
    font1.setPixelSize(cellSize);
    font1.setBold(true);
    painter.setFont(font1);

    for (int y = 0; y < N; ++y) {
        for (int x = 0; x < N; ++x) {
            QRect rect(x * cellSize, y * cellSize, cellSize, cellSize);
            if (mazeData[y][x] == 0) {
                painter.drawText(x * cellSize, y * cellSize, cellSize, cellSize, Qt::AlignCenter, "墙");

            } else {
                painter.fillRect(rect, Qt::white);
            }
        }
    }

    QFont font2;
    font2.setPixelSize(10);
    painter.setFont(font2);

    painter.setPen(Qt::red);
    painter.drawText(260,290,"摆烂");
}

void Form1::drawObject(QPainter &painter)
{
    // 绘制对象
    if (currentPosition >= route.size()) return;
    painter.setPen(Qt::blue);
    QPoint pos = route[currentPosition];
    QFont font3;
    font3.setPixelSize(10);
    painter.setFont(font3);
    painter.drawText(pos.x() *cellSize, pos.y() *cellSize, cellSize, cellSize, Qt::AlignCenter, "组员");


    if (pos == studentPosition) {
        gameEnded1 = true;
        moveTimer->stop();
        StudentTimer->stop();
    }

    if (pos == QPoint(13,14)){
        gameEnded2 = true;
        moveTimer->stop();
        StudentTimer->stop();
    }
    currentPosition++;
}


void Form1::moveObject()
{
    if (currentPosition >= route.size()) {
        moveTimer->stop(); // 路线走完，停止定时器
    }

    checkWinOrLose();
    update();
}

void Form1::keyPressEvent(QKeyEvent *event)
{
    int step = 1;
    switch (event->key()) {
    case Qt::Key_Up:
        currentDirection = QPoint(0, -step);
        StudentTimer->start();
        break;
    case Qt::Key_Down:
        currentDirection = QPoint(0, step);
        StudentTimer->start();
        break;
    case Qt::Key_Left:
        currentDirection = QPoint(-step, 0);
        StudentTimer->start();
        break;
    case Qt::Key_Right:
        currentDirection = QPoint(step, 0);
        StudentTimer->start();
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}

void Form1::keyReleaseEvent(QKeyEvent *event)
{
    Q_UNUSED(event);
    //StudentTimer->stop(); // 停止键盘计时器
}


void Form1::moveStudent()
{
    QPoint newPos = studentPosition + currentDirection;

    if (!(isValidPosition(newPos))) {
        StudentTimer->stop();
    } else {
        studentPosition = newPos;
        update();
    }
    checkWinOrLose();
}

bool Form1::isValidPosition(const QPoint &pos)
{

    if (mazeData[pos.y()][pos.x()] == 0 || pos.y() > 14 || pos.y() < 0 || pos.x() > 14 || pos.x() < 0) {
        return false;
    }
    return true;

}

void Form1::drawStudent(QPainter &painter)
{
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 10));
    painter.drawText(studentPosition.x() * cellSize, studentPosition.y() * cellSize, cellSize, cellSize, Qt::AlignCenter, "分工");

    if (studentPosition == route[currentPosition -1 ]) {
        gameEnded1 = true;
        moveTimer->stop();
        StudentTimer->stop();
    }
}

void Form1::checkWinOrLose()
{
    if(gameEnded1){
        QMessageBox::information(this, "游戏结束", "成功让组员摆烂前分工");
    }
    if(gameEnded2){
        QMessageBox::information(this, "游戏结束", "组员开始摆烂");
    }
}
