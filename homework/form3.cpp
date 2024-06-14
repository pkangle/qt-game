#include "form3.h"
#include "ui_form3.h"

#include <QPainter>
#include <QTimer>
#include <QStack>

Form3::Form3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form3),
    moveSpeed(100),
    currentPosition(0),
    StudentSpeed(100),
    studentPosition(1,0)
{
    ui->setupUi(this);
    QFont font;
    font.setPixelSize(cellSize);
    // 创建定时器，控制对象移动速度
    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &Form3::moveObject);
    moveTimer->start(moveSpeed);

    //操作对象计时器
    StudentTimer = new QTimer(this);
    connect(StudentTimer,&QTimer::timeout, this, &Form3::moveStudent);

    // 获取对象路线
    getObjectRoute();
    setFocusPolicy(Qt::StrongFocus);
}

Form3::~Form3()
{
    delete ui;
}

void Form3::paintEvent(QPaintEvent *event)
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

void Form3::getObjectRoute()
{
    route = {
        {2,14},{3,14},{4,14},{4,13},{4,12},{4,11},{5,11},{5,10},{5,9},{4,9},{4,8},{4,7},{3,7},{3,6},{3,5},
        {4,5},{4,4},{5,4},{6,4},{6,3},{6,2},{5,2},{5,1},{5,0},{6,0},{7,0},{8,0},{8,1},
        {8,2},{8,3},{9,3},{9,4},{9,5},{9,6},{8,6},{7,6},{7,7},{7,8},{8,8},{8,9},{8,10},{8,11},{7,11},{7,12},
        {7,13},{7,14},{8,14},{9,14},{10,14},{10,13},{10,12},{10,11},{11,11},{11,10},
        {11,9},{10,9},{10,8},{10,7},{11,7},{11,6},{11,5},{11,4},{11,3},{11,2},{10,2},{10,1},{10,0},{11,0},{12,0},
        {13,0},{13,1},{13,2},{13,3},{14,3},{14,4},{14,5},{13,5},{13,6},{13,7},{13,8},{13,9},{14,9},{14,10},{14,11},
        {14,12},{13,12},{13,13},{13,14}
    };
}

void Form3::drawMaze(QPainter &painter)
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
    font2.setPixelSize(15);
    painter.setFont(font2);

    painter.setPen(Qt::red);
    painter.drawText(360,400,"完成");
}

void Form3::drawObject(QPainter &painter)
{
    // 绘制对象
    if (currentPosition >= route.size()) return;
    painter.setPen(Qt::blue);
    QPoint pos = route[currentPosition];
    QFont font3;
    font3.setPixelSize(10);
    painter.setFont(font3);
    painter.drawText(pos.x() *cellSize, pos.y() *cellSize, cellSize, cellSize, Qt::AlignCenter, "ddl");
    currentPosition++;
}


void Form3::moveObject()
{
    if (currentPosition >= route.size()) {
        moveTimer->stop(); // 路线走完，停止定时器
    }
    update();
}

void Form3::keyPressEvent(QKeyEvent *event)
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

void Form3::moveStudent()
{
    QPoint newPos = studentPosition + currentDirection;

    if (isValidPosition(newPos)) {
        studentPosition = newPos;
        update();
    } else {
        StudentTimer->stop(); // 碰到墙，停止计时器
    }
}

bool Form3::isValidPosition(const QPoint &pos)
{

    if (mazeData[pos.y()][pos.x()] == 0 || pos.y() > 14 || pos.y() < 0 || pos.x() > 14 || pos.x() < 0) {
        return false;
    }
    return true;

}

void Form3::drawStudent(QPainter &painter)
{
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 10));
    painter.drawText(studentPosition.x() * cellSize, studentPosition.y() * cellSize, cellSize, cellSize, Qt::AlignCenter, "ddl");
}


