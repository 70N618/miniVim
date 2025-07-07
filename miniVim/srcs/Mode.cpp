#include "../includes/Mode.h"
#include "../includes/mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <qdebug.h>
#include <qglobal.h>


Mode::Mode(MainWindow &win, Ui::MainWindow &ui, const char *file):ui(ui),win(win)
{
  this->esc_mode = false;
  this->ins_mode = true;
  this->cmd_mode = false;
  this->vis_mode = true;
  this->file = file;
  ui.iTextEdit->installEventFilter(this);
  ui.eTextEdit->installEventFilter(this);
  ui.iTextEdit->setFocus();
  connect(this,&Mode::escModeToggled, &Mode::toggleEscMode);
  connect(this,&Mode::cmdModeToggled, &Mode::toggleCmdMode);
  connect(this,&Mode::insModeToggled, &Mode::toggleInsMode);
  connect(this,&Mode::visModeToggled, &Mode::toggleVisMode);
  qDebug() << this->file;
  this->sel_struct = new t_sel();
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
