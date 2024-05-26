#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include "form1.h"
#include "form2.h"
#include "form3.h"

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();

private slots:
    void on_pigBtn_clicked();

    void on_snakeBtn_clicked();

    void on_pigeunBtn_clicked();

private:
    Ui::Form *ui;
};

#endif // FORM_H
