#include "../includes/Mode.h"
#include "../includes/mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <qcoreevent.h>
#include <qevent.h>
#include <qglobal.h>
#include <qnamespace.h>

/* slot.
 * @brief: handle ":" when esc is pressed. */

void Mode::toggleCmdMode()
{
  if (this->esc_mode == true)
  {
    ui.eTextEdit->setFocus();
  }
}

/* slot.
 * @brief: Start selection when v is pressed. */

void Mode::toggleVisMode()
{
  if (this->vis_mode == true)
  {
    qDebug() << "Selection started\n";
    this->sel_struct->sel_start = sel_struct->tcurs.anchor();
    qDebug() << "Start:" << sel_struct->sel_start;
  }
}

/* slot.
 * @brief: Handles each situation in which ESC is pressed.
 * If ESC is pressed in insert mode with enter NRM MODE.
 * If ESC is pressed in cmd mode we exit cmd_mode and enter NRM mode.
 * If ESC is pressed in visual mode we exit vis_mode and enter NRM_MODE
 * It also handles widgets focus.
 * */

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

/* slot.
 * @brief: Slot function to enable INS mode.
 * */

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
