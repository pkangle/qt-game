#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->gamename->setStyleSheet("background-color: rgba(0, 0, 0, 0);");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_startBtn_clicked()
{
    Form *new_window = new Form;
    new_window->show();
}
