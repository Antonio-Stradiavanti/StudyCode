#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Главное окно");

    //statusBar()->showMessage("Сообщение");
    //menuBar()->addMenu("File");

    // Пользовательская команда
    QAction* copyAction = new QAction("Copy");
    copyAction->setIcon(QIcon(":/images/copy.png"));
    // Аргумент описывает сочетание клавиш
    copyAction->setShortcut(QKeySequence::Copy);

    QAction* pasteAction = new QAction("Paste");
    copyAction->setIcon(QIcon(":/images/paste.png"));
    // Аргумент описывает сочетание клавиш

    // Перечисление.
    copyAction->setShortcut(QKeySequence::Paste);

    QMenu* fileMenu = menuBar()->addMenu("File");
    fileMenu->addAction(copyAction);
    fileMenu->addAction(pasteAction);


}

MainWindow::~MainWindow() {

}
