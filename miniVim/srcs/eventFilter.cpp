#include "../includes/Esc.h"
#include "ui_mainwindow.h"
#include <cstdio>
#include <qcoreevent.h>
#include <qevent.h>
#include <qglobal.h>
#include <QDebug>
#include <QAction>
#include <qnamespace.h>

bool Esc::eventFilter(QObject *obj, QEvent *event)
{
  QKeyEvent *keyEvent;
  keyEvent = static_cast<QKeyEvent *>(event);

  // Trigger ESC Mode

  if (event->type() == QEvent::KeyPress)
  {
    if (keyEvent->key() == Qt::Key_Escape)
    {
      qDebug() << "Key Esc pressed";
      this->ui.label->setText("NRM");
      emit escModeToggled(event);
    }
  }

  // Trigger Ins mode

  if (event->type() == QEvent::KeyPress && esc_mode == true && cmd_mode == false)
  {
    if (keyEvent->text() == "i")
    {
      qDebug() << "Insert mode\n";
      this->ui.label->setText("INS");
      emit insModeToggled();
    }
  }

  // Handle double dots while in ESC mode

  if (event->type() == QEvent::KeyPress && esc_mode == true)
  {
    if (keyEvent->text() == ":")
    {
      qDebug() << "Cmd mode\n";
      this->ui.label->setText("CMD");
      this->cmd_mode = true;
      emit cmdModeToggled();
      return true;
    }
    if (keyEvent->text() == "v" && cmd_mode == false)
    {
      qDebug() << "Visual mode\n";
      this->ui.label->setText("Vis");
      this->vis_mode = true;
      emit visModeToggled();
      return true;
    }
    if (keyEvent->text() == "y" && vis_mode == true)
    {
      sel_struct->sel_end = sel_struct->tcurs.position();
      sel_struct->tcurs.setPosition(this->sel_struct->sel_start);
      sel_struct->tcurs.setPosition(sel_struct->sel_end, QTextCursor::KeepAnchor);
      qDebug() << "End:" << sel_struct->sel_end;
      this->ui.label->setText("NRM");
      qDebug() << sel_struct->tcurs.selectedText();
      this->ui.iTextEdit->copy();
      this->vis_mode = false;
      return true;
    }
  }

  // Handle Esc shortcuts
  if (event->type() == QEvent::KeyPress && this->esc_mode == true && this->cmd_mode == false)
  {
    int key = keyEvent->key();
    QTextCursor tcurs = ui.iTextEdit->textCursor();

    switch (key)
    {
      case(Qt::Key_H):
        ui.iTextEdit->moveCursor(QTextCursor::Left);
        sel_struct->tcurs.movePosition(QTextCursor::Left);
        break;
      case(Qt::Key_J):
        ui.iTextEdit->moveCursor(QTextCursor::Down);
        sel_struct->tcurs.movePosition(QTextCursor::Down);
        break;
      case(Qt::Key_K):
        ui.iTextEdit->moveCursor(QTextCursor::Up);
        sel_struct->tcurs.movePosition(QTextCursor::Up);
        break;
      case(Qt::Key_L):
        ui.iTextEdit->moveCursor(QTextCursor::Right);
        sel_struct->tcurs.movePosition(QTextCursor::Right);
        break;
      case(Qt::Key_Dollar):
        ui.iTextEdit->moveCursor(QTextCursor::EndOfLine);
        sel_struct->tcurs.movePosition(QTextCursor::EndOfLine);
        break;
      case(Qt::Key_0):
        ui.iTextEdit->moveCursor(QTextCursor::StartOfLine);
        sel_struct->tcurs.movePosition(QTextCursor::StartOfLine);
        break;
      case(Qt::Key_P):
        ui.iTextEdit->paste();
        break;
    }
    return true;
  }
  return false;
}
