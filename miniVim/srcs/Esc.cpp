#include "../includes/Esc.h"
#include "../includes/mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>


Esc::Esc(MainWindow &win, Ui::MainWindow &ui, const char *file):ui(ui),win(win)
{
  this->esc_mode = false;
  this->ins_mode = true;
  this->cmd_mode = false;
  this->vis_mode = true;
  this->file = file;
  ui.iTextEdit->installEventFilter(this);
  ui.eTextEdit->installEventFilter(this);
  ui.iTextEdit->setFocus();
  connect(this,&Esc::escModeToggled, &Esc::toggleEscMode);
  connect(this,&Esc::cmdModeToggled, &Esc::toggleCmdMode);
  connect(this,&Esc::insModeToggled, &Esc::toggleInsMode);
  connect(this,&Esc::visModeToggled, &Esc::toggleVisMode);
  this->sel_struct = new t_sel();

}

Esc::~Esc()
{
}

bool Esc::getEscMode()
{
  return this->esc_mode;
}
