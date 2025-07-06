#include "../includes/mainwindow.h"
#include "ui_mainwindow.h"
#include <qdebug.h>
#include <qevent.h>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

Ui::MainWindow *MainWindow::getUi()
{
  return this->ui;
}
