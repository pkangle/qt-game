#ifndef FORM1_H
#define FORM1_H

#include <QWidget>
#include<QTimer>
#include<QPaintEvent>
#include<QVector>
#include<QStack>
#include<QPoint>
#include<QKeyEvent>

namespace Ui {
class Form1;
}

class Form1 : public QWidget
{
    Q_OBJECT

public:
    explicit Form1(QWidget *parent = 0);
    ~Form1();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    int mazeData[15][15] = {
        {0,1,0,0,1,1,1,1,0,0,1,1,1,1,0},
        {0,1,1,0,1,0,0,1,0,0,1,0,0,1,0},
        {0,0,1,0,1,1,0,1,1,0,1,0,0,1,1},
        {0,0,1,0,0,1,0,0,1,0,1,1,0,0,1},
        {1,1,1,0,1,1,0,0,1,1,0,1,0,1,1},
        {1,0,0,0,1,0,0,0,0,1,0,1,0,1,0},
        {1,1,1,0,1,0,0,1,1,1,0,1,0,1,0},
        {0,0,1,0,1,1,0,1,0,0,0,1,0,1,1},
        {0,0,1,0,0,1,0,1,1,0,0,1,0,0,1},
        {0,0,1,0,0,1,0,0,1,0,1,1,0,0,1},
        {0,1,1,0,1,1,0,1,1,0,1,0,0,1,1},
        {0,1,0,0,1,0,1,1,0,0,1,0,0,1,0},
        {0,1,1,0,1,0,1,0,0,0,1,1,0,1,0},
        {0,0,1,0,1,0,1,1,0,0,0,1,0,1,0},
        {0,0,1,1,1,0,0,1,1,1,1,1,0,1,0},
    };


private slots:
    void moveObject();

private:
    Ui::Form1 *ui;
    QTimer *moveTimer;
    QTimer *StudentTimer;

    static const int N = 15; // 迷宫大小
    int cellSize = 20;
    QVector<QPoint> route; // 对象路线
    int currentPosition; // 当前位置索引
    int moveSpeed; // 移动速度，单位为毫秒
    int StudentSpeed;
    void getObjectRoute();
    void dfs(int x, int y, QStack<QPoint> &path);
    void setupRoute(const QVector<QPoint> &solutionRoute);
    void drawObject(QPainter &painter);
    void drawMaze(QPainter &painter);
    QVector<QVector<bool>> visited;
    QPoint studentPosition; // 对象位置
    QPoint currentDirection;
    void moveStudent();
    void drawStudent(QPainter &painter);
    bool isValidPosition(const QPoint &pos);
    int moveDx;
    int moveDy;

    void checkWinOrLose();
};

#endif // FORM1_H
