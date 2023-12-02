#include "widget.h"
// Конструктор
Widget::Widget(QWidget *parent)
    // Вызываем конструктор базового класса
    : QWidget(parent) {
    setWindowIcon(QIcon(":/images/qt.png"));
}

Widget::~Widget() {}
