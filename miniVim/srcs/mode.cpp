#include "../includes/Esc.h"
#include "../includes/mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <qcoreevent.h>
#include <qevent.h>
#include <qglobal.h>
#include <qnamespace.h>

// Handle ":" when esc is pressed

void Esc::toggleCmdMode()
{
  if (this->esc_mode == true)
  {
    ui.eTextEdit->setFocus();
  }
}

void Esc::toggleVisMode()
{
  if (this->vis_mode == true)
  {
    qDebug() << "Selection started\n";
    this->sel_struct->tcurs = this->ui.iTextEdit->textCursor();
    this->sel_struct->sel_start = sel_struct->tcurs.selectionStart();
    qDebug() << "Start:" << sel_struct->sel_start;
  }
}

// SLOT Handle esc mode

void Esc::toggleEscMode()
{
  if (this->esc_mode == false)
  {
    this->esc_mode = true;
    this->ui.iTextEdit->setCursor(Qt::PointingHandCursor);
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

void Esc::toggleInsMode()
{
  if (this->esc_mode == true)
  {
    esc_mode = false;
    ins_mode = true;
    qDebug() << "[INSERT MODE ENABLED]\n";
    ui.iTextEdit->setFocus();
  }
}
