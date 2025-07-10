#include "../includes/mainwindow.h"
#include "ui_mainwindow.h"
#include <qdebug.h>
#include <qevent.h>
#include <qlogging.h>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  sh = new SyntaxHighlight(ui->iTextEdit->document());
  this->setAttribute(Qt::WA_DeleteOnClose);
}

MainWindow::~MainWindow()
{
  delete sh;
  delete ui;
  qDebug() << "Called\n";
}

Ui::MainWindow *MainWindow::getUi()
{
  return this->ui;
}

SyntaxHighlight *MainWindow::getSh()
{
  return this->sh;
}
