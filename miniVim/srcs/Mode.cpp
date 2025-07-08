#include "../includes/Mode.h"
#include "../includes/mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <qaction.h>
#include <QAction>
#include <QTimer>
#include <qdebug.h>
#include <qelapsedtimer.h>
#include <qglobal.h>
#include <qnamespace.h>
#include <qobjectdefs.h>


Mode::Mode(MainWindow &win, Ui::MainWindow &ui, const char *file):ui(ui),win(win)
{
  this->esc_mode = false;
  this->ins_mode = true;
  this->cmd_mode = false;
  this->vis_mode = true;
  this->file = file;
  this->count = 0;
  ui.iTextEdit->installEventFilter(this);
  ui.eTextEdit->installEventFilter(this);
  ui.iTextEdit->setFocus();
  connect(this,&Mode::escModeToggled, &Mode::toggleEscMode);
  connect(this,&Mode::cmdModeToggled, &Mode::toggleCmdMode);
  connect(this,&Mode::insModeToggled, &Mode::toggleInsMode);
  connect(this,&Mode::visModeToggled, &Mode::toggleVisMode);
  qDebug() << this->file;
  this->sel_struct = new t_sel();
  this->timer = new QElapsedTimer();
}

void Mode::deleteLine()
{
  qDebug() << timer->elapsed();
  if (timer->elapsed() <= 1500)
  {
    qDebug() << "line deleted\n";
  }
}

Mode::~Mode()
{
}

bool Mode::getModeMode()
{
  return this->esc_mode;
}

void Mode::setFile(const char *file)
{
  this->file = file;
}
