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
private slots:
    void moveObject();

private:
    Ui::Form1 *ui;
    QTimer *moveTimer;

    static const int N = 20; // 迷宫大小
    int mazeData[N][N];
    int cellSize = 20;
    QVector<QPoint> route; // 对象路线
    int currentPosition; // 当前位置索引
    int moveSpeed; // 移动速度，单位为毫秒
    void getObjectRoute();
    void dfs(int x, int y, QStack<QPoint> &path);
    void setupRoute(const QVector<QPoint> &solutionRoute);
    void drawObject(QPainter &painter);
    void drawMaze(QPainter &painter);

    QPoint studentPosition; // 对象位置

    void moveStudent(int dx, int dy);
    bool isValidPosition(const QPoint &pos);
};

#endif // FORM1_H
