#ifndef FORM2_H
#define FORM2_H


#include <QWidget>
#include<QTimer>
#include<QPaintEvent>
#include<QVector>
#include<QStack>
#include<QPoint>

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

private slots:
    void moveObject_2();

private:
    Ui::Form2 *ui;
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
};

#endif // FORM2_H

