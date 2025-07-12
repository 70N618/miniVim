#include "../includes/Mode.h"
#include "../includes/Mode.h"
#include "../includes/mainwindow.h"
#include "ui_mainwindow.h"
#include <qaction.h>
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
  // Initialize variables

  this->esc_mode = false;
  this->ins_mode = true;
  this->cmd_mode = false;
  this->vis_mode = false;
  this->file = file;
  this->dCount = 0;
  this->yCount = 0;
  this->nl = false;
  this->ind_flag = 0;
  this->sel_struct = new t_sel();
  this->dTimer = new QElapsedTimer();
  this->yTimer = new QElapsedTimer();
  this->sel_struct->tcurs = this->ui.iTextEdit->textCursor();

  // Install EventFilter on both insert and edit QTextEdit

  ui.iTextEdit->installEventFilter(this);
  ui.eTextEdit->installEventFilter(this);
  ui.iTextEdit->setFocus();


  // Connect signals with slots

  connect(this,&Mode::sigNormMode, &Mode::toggleEscMode);
  connect(this,&Mode::sigCmdMode, &Mode::toggleCmdMode);
  connect(this,&Mode::sigInsMode, &Mode::toggleInsMode);
  connect(this,&Mode::sigVisMode, &Mode::toggleVisMode);
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
