#include "form2.h"
#include "ui_form2.h"

#include <QPainter>
#include <QTimer>
#include <QStack>

Form2::Form2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form2),
    player1Speed(100),
    player2Speed(100),
    player1Position(1,0),
    player2Position(15,15)
{
    ui->setupUi(this);
    QFont font;
    font.setPixelSize(cellSize);

    player1Timer = new QTimer(this);
    connect(player1Timer,&QTimer::timeout, this, &Form2::movePlayer1);
    player2Timer = new QTimer(this);
    connect(player2Timer,&QTimer::timeout, this, &Form2::movePlayer2);
}

Form2::~Form2()
{
    delete ui;
}

void Form2::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制迷宫和对象
    drawMaze(painter);
    drawPlayer1(painter);
    drawPlayer2(painter);
    int mazeData[15][15];
}


void Form2::drawMaze(QPainter &painter)
{
    // 绘制迷宫
    // 迷宫数据，0表示墙，1表示通
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
    painter.drawText(360,400,"外卖");
}

void Form2::drawObject(QPainter &painter)
{
    // 绘制对象
    if (currentPosition >= route.size()) return;
    painter.setPen(Qt::blue);
    QPoint pos = route[currentPosition];
    QRect rect(pos.x() * cellSize, pos.y() * cellSize, cellSize, cellSize);
    painter.drawEllipse(rect);  // 使用 drawEllipse 方法绘制对象
    currentPosition++;
}


void Form2::moveObject_2()
{
    //++currentPosition; // 更新当前位置
    if (currentPosition >= route.size()) {
        moveTimer->stop(); // 路线走完，停止定时器
    }
    update();
}
