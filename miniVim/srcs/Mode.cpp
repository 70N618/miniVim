#include "../includes/Mode.h"
#include "../includes/mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <qaction.h>
#include <QAction>
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

  QAction *action = new QAction("delete line");
  action->setShortcut({QKeySequence(Qt::Key_D, Qt::Key_D)});
  ui.iTextEdit->addAction(action);
  connect(action, &QAction::triggered, this, &Mode::deleteLine);

  qDebug() << this->file;
  this->sel_struct = new t_sel();
}

void Mode::deleteLine()
{
  qDebug() << "Line deleted\n";
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
