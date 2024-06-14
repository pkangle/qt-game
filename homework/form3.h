#ifndef FORM3_H
#define FORM3_H

#include <QWidget>
#include<QTimer>
#include<QPaintEvent>
#include<QVector>
#include<QStack>
#include<QPoint>
#include<QKeyEvent>

namespace Ui {
class Form3;
}

class Form3 : public QWidget
{
    Q_OBJECT

public:
    explicit Form3(QWidget *parent = 0);
    ~Form3();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    int mazeData[15][15] = {
        {0,1,0,0,1,1,1,1,1,0,1,1,1,1,0},
        {0,1,0,0,0,1,0,0,1,0,1,0,0,1,0},
        {0,1,1,0,0,1,1,0,1,0,1,1,0,1,0},
        {0,0,1,0,0,0,1,0,1,1,0,1,0,1,1},
        {0,1,1,0,1,1,1,0,0,1,0,1,0,0,1},
        {0,1,0,1,1,0,0,0,0,1,0,1,0,1,1},
        {1,1,0,1,0,0,0,1,1,1,0,1,0,1,0},
        {1,0,0,1,1,0,0,1,0,0,1,1,0,1,0},
        {1,1,0,0,1,0,0,1,1,0,1,0,0,1,0},
        {0,1,1,0,1,1,0,0,1,0,1,1,0,1,1},
        {0,0,1,0,0,1,0,0,1,0,0,1,0,0,1},
        {1,1,1,0,1,1,0,1,1,0,1,1,0,0,1},
        {1,0,0,0,1,0,0,1,0,0,1,0,0,1,1},
        {1,1,1,0,1,0,0,1,0,0,1,0,0,1,0},
        {0,0,1,1,1,0,0,1,1,1,1,0,0,1,0},

    };

private slots:
    void moveObject();

private:
    QTimer *moveTimer;
    QTimer *StudentTimer;
    //地图相关
    static const int N = 15; // 迷宫大小
    int cellSize = 20;
    void drawMaze(QPainter &painter);
    //玩家相关
    int StudentSpeed;
    void moveStudent();
    void drawStudent(QPainter &painter);
    bool isValidPosition(const QPoint &pos);
    int moveDx,moveDy;
    QPoint studentPosition;
    QPoint currentDirection;
    //追击相关
    int moveSpeed;
    void drawObject(QPainter &painter);
    int currentPosition;
    QVector<QPoint> route;
    void getObjectRoute();

    void checkWinOrLose();

    Ui::Form3 *ui;
};

#endif // FORM3_H
