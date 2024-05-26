#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}

void Form::on_pigBtn_clicked()
{
    Form1 *new_window1 = new Form1;
    new_window1->show();
}

void Form::on_snakeBtn_clicked()
{
    Form2 *new_window = new Form2;
    new_window->show();
}

void Form::on_pigeunBtn_clicked()
{
    Form3 *new_window = new Form3;
    new_window->show();
}
