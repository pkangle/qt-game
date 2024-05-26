#ifndef FORM3_H
#define FORM3_H

#include <QWidget>

namespace Ui {
class Form3;
}

class Form3 : public QWidget
{
    Q_OBJECT

public:
    explicit Form3(QWidget *parent = 0);
    ~Form3();

private:
    Ui::Form3 *ui;
};

#endif // FORM3_H
