#include "widget.h"
#include <QApplication>
#include "QString"
#include "QTextEdit"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    QTextEdit textEdit;

    textEdit.setAutoFillBackground(true);
    textEdit.setStyleSheet("background-color: rgba(0, 0, 0, 0);");
    return a.exec();

}
