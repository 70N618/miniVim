#include "../includes/mainwindow.h"
#include "ui_mainwindow.h"
#include <qdebug.h>
#include <qevent.h>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  QFont font;
  font.setFamily("Courier");
  font.setFixedPitch(true);
  font.setPointSize(80);
  ui->iTextEdit->setFont(font);

  sh = new SyntaxHighlight(ui->iTextEdit->document());
}

MainWindow::~MainWindow()
{
    delete ui;
}

Ui::MainWindow *MainWindow::getUi()
{
  return this->ui;
}
