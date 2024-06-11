#ifndef FORM2_H
#define FORM2_H

#include <QWidget>
#include<QTimer>
#include<QPaintEvent>
#include<QVector>
#include<QStack>
#include<QPoint>
#include<QKeyEvent>

namespace Ui {
class Form2;
}

class Form2 : public QWidget
{
    Q_OBJECT

public:
    explicit Form2(QWidget *parent = 0);
    ~Form2();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    int mazeData[15][15] = {
        {0,1,0,0,0,1,1,1,0,0,1,1,1,0,0},
        {0,1,1,0,0,1,0,1,0,0,1,0,1,0,0},
        {0,0,1,0,0,1,0,1,1,0,1,0,1,0,0},
        {0,1,1,0,0,1,0,0,1,0,1,0,1,1,0},
        {1,1,0,0,0,1,0,1,1,0,1,0,0,1,0},
        {1,0,0,0,1,1,0,1,0,1,1,0,1,1,0},
        {1,1,1,0,1,0,0,1,0,1,0,0,1,0,0},
        {0,0,1,0,1,1,0,1,0,1,1,0,1,0,0},
        {0,0,1,0,0,1,0,1,0,0,1,0,1,1,1},
        {0,1,1,0,1,1,0,1,0,1,1,0,0,0,1},
        {0,1,0,0,1,0,1,1,0,1,0,0,0,1,1},
        {0,1,1,0,1,0,1,0,0,1,0,0,1,1,0},
        {0,0,1,0,1,0,1,1,0,1,0,0,1,0,0},
        {0,0,1,0,1,0,0,1,0,1,0,0,1,1,0},
        {0,0,1,1,1,0,0,1,1,1,0,0,0,1,0}
    };

private:
    Ui::Form2 *ui;
    QTimer *player1Timer;
    QTimer *player2Timer;
    //迷宫相关
    static const int N = 15; // 迷宫大小
    int cellSize = 20;
    void drawMaze(QPainter &painter);
    QPoint centerPosition = QPoint(7,7);
    //玩家相关
    int player1Speed;
    int player2Speed;
    void movePlayer1();
    void movePlayer2();
    void drawPlayer1(QPainter &painter);
    void drawPlayer2(QPainter &painter);
    bool isValid(const QPoint &pos);
    int moveDx1,moveDy1;
    int moveDx2,moveDy2;
    QPoint player1Position,player2Position;
    QPoint currentDirection1,currentDirection2;

    void checkWinOrLose();
};

#endif // FORM2_H

