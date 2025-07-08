#include "../includes/Mode.h"
#include "../includes/mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <qcoreevent.h>
#include <qevent.h>
#include <qglobal.h>
#include <qnamespace.h>

// Handle ":" when esc is pressed

void Mode::toggleCmdMode()
{
  if (this->esc_mode == true)
  {
    ui.eTextEdit->setFocus();
  }
}

void Mode::toggleVisMode()
{
  if (this->vis_mode == true)
  {
    qDebug() << "Selection started\n";
    sel_struct->tcurs = this->ui.iTextEdit->textCursor();
    this->sel_struct->sel_start = sel_struct->tcurs.anchor();
    sel_struct->tcurs.setPosition(this->sel_struct->sel_start);
    qDebug() << "Start:" << sel_struct->sel_start;
  }
}

// SLOT Handle esc mode

void Mode::toggleEscMode()
{
  if (this->esc_mode == false)
  {
    this->esc_mode = true;
    qDebug() << "[ESC MODE ENABLED]\n";
  }
  else if (this->esc_mode == true && this->cmd_mode == true)
  {
    this->cmd_mode = false;
    qDebug() << "[CMD MODE DISABLED]\n";
    ui.eTextEdit->clear();
    ui.iTextEdit->setFocus();
  }
  else if (this->esc_mode == true && this->vis_mode == true)
  {
    this->vis_mode = false;
    qDebug() << "[VIS MODE DISABLED]\n";
    ui.iTextEdit->setFocus();
  }
  qDebug() << "Set esc mode to: " << this->esc_mode;
}

// SLOT Handle ins mode

void Mode::toggleInsMode()
{
  if (this->esc_mode == true)
  {
    esc_mode = false;
    ins_mode = true;
    qDebug() << "[INSERT MODE ENABLED]\n";
    ui.iTextEdit->setFocus();
  }
}
