#include "form2.h"
#include "ui_form2.h"

#include <QPainter>
#include <QTimer>
#include <QStack>
#include <QMessageBox>

Form2::Form2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form2),
    player1Speed(100),
    player2Speed(100),
    player1Position(1,0),
    player2Position(13,14)
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

    painter.setPen(Qt::red);
    painter.setFont(QFont("Arial", 10, QFont::Bold));
    painter.drawText(centerPosition.x() * cellSize, centerPosition.y() * cellSize, cellSize, cellSize, Qt::AlignCenter, "外卖");
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

}

void Form2::keyPressEvent(QKeyEvent *event)
{
    int step = 1;
    switch (event->key()) {
    case Qt::Key_W:
        currentDirection1 = QPoint(0, -step);
        player1Timer->start();
        break;
    case Qt::Key_S:
        currentDirection1 = QPoint(0, step);
        player1Timer->start();
        break;
    case Qt::Key_A:
        currentDirection1 = QPoint(-step, 0);
        player1Timer->start();
        break;
    case Qt::Key_D:
        currentDirection1 = QPoint(step, 0);
        player1Timer->start();
        break;
    case Qt::Key_Up:
        currentDirection2 = QPoint(0, -step);
        player2Timer->start();
        break;
    case Qt::Key_Down:
        currentDirection2 = QPoint(0, step);
        player2Timer->start();
        break;
    case Qt::Key_Left:
        currentDirection2 = QPoint(-step, 0);
        player2Timer->start();
        break;
    case Qt::Key_Right:
        currentDirection2 = QPoint(step, 0);
        player2Timer->start();
        break;
    default:
        QWidget::keyPressEvent(event);
    }

}


void Form2::movePlayer1()
{
    QPoint newPos = player1Position + currentDirection1;

    if (isValid(newPos)) {
        player1Position = newPos;
        checkWinOrLose();
        update();
    } else {
        player1Timer->stop(); // 碰到墙，停止计时器
    }
}

void Form2::movePlayer2()
{
    QPoint newPos = player2Position + currentDirection2;

    if (isValid(newPos)) {
        player2Position = newPos;
        checkWinOrLose();
        update();
    } else {
        player2Timer->stop(); // 碰到墙，停止计时器
    }
}

void Form2::drawPlayer1(QPainter &painter)
{
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 8));
    painter.drawText(player1Position.x() * cellSize, player1Position.y() * cellSize, cellSize, cellSize, Qt::AlignCenter, "大学生");
}

void Form2::drawPlayer2(QPainter &painter)
{
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 8));
    painter.drawText(player2Position.x() * cellSize, player2Position.y() * cellSize, cellSize, cellSize, Qt::AlignCenter, "外卖贼");
}

bool Form2::isValid(const QPoint &pos)
{
    if (mazeData[pos.y()][pos.x()] == 0 || pos.y() > 14 || pos.y() < 0 || pos.x() > 14 || pos.x() < 0) {
        return false;
    }
    return true;
}

void Form2::checkWinOrLose()
{
    if (player1Position == centerPosition) {
        QMessageBox::information(this, "游戏结果", "你守住了你的外卖");
        player1Timer->stop();
        player2Timer->stop();
        player1Position = QPoint(1,0);
        player2Position = QPoint(13,14);
    }

    else if (player2Position == centerPosition) {
        QMessageBox::information(this, "游戏结果", "外卖贼偷走了你的外卖！");
        player1Timer->stop();
        player2Timer->stop();
        player1Position = QPoint(1,0);
        player2Position = QPoint(13,14);
    }
}
