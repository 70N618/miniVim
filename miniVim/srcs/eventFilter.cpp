#include "../includes/Mode.h"
#include "ui_mainwindow.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <qaction.h>
#include <qcoreevent.h>
#include <qevent.h>
#include <qglobal.h>
#include <QDebug>
#include <qaction.h>
#include <QAction>
#include <qnamespace.h>
#include <qregion.h>
#include <qtimer.h>

bool Mode::eventFilter(QObject *obj, QEvent *event)
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

    if (esc_mode == true && cmd_mode == true)
    {
      if (keyEvent->key() == Qt::Key_Return)
      {
        QString cmd = ui.eTextEdit->toPlainText();
        qDebug() << cmd;

        if (cmd == "q")
        {
          out.close();
          exit(0);
        }


        if (cmd == "wq" || cmd == "w")
        {
          out.setFileName(this->file);
          out.open(QIODevice::Truncate | QIODevice::Append | QIODevice::Text);
          QString to_copy = ui.iTextEdit->toPlainText();
          QTextStream outstream(&out);
          outstream << to_copy;
          if (cmd == "wq")
          {
            out.close();
            exit(0);
          }
          else
          {
            ui.eTextEdit->clear();
            ui.iTextEdit->setFocus();
          }
        }
        return true;
      }
    }

  // Handle visual mode

    if (keyEvent->text() == "v" && cmd_mode == false)
    {
      if (vis_mode == true)
      {
        qDebug() << "Visual mode disabled\n";
        this->vis_mode = false;
        this->ui.label->setText("NRM");
        return true;
      }
      qDebug() << "Visual mode\n";
      this->ui.label->setText("Vis");
      this->vis_mode = true;
      emit visModeToggled();
      return true;
    }

    // Handle copy
    if (keyEvent->text() == "y" && vis_mode == true)
    {
      ui.iTextEdit->setTextCursor(sel_struct->tcurs);

      sel_struct->sel_end = sel_struct->tcurs.position();
      sel_struct->tcurs.setPosition(this->sel_struct->sel_start);
      sel_struct->tcurs.setPosition(sel_struct->sel_end, QTextCursor::KeepAnchor);
      qDebug() << "End:" << sel_struct->sel_end;
      sel_struct->to_paste = sel_struct->tcurs.selectedText();

      this->vis_mode = false;
      this->ui.label->setText("NRM");
      return true;
    }
  }


  if (event->type() == QEvent::KeyPress && this->ins_mode == true)
  {
    qDebug() << event;
    // Se viene premuta una parentesi graffa e poi return --> indent
  }

  // Handle Esc shortcuts

  if (event->type() == QEvent::KeyPress && this->esc_mode == true && this->cmd_mode == false)
  {
    int key = keyEvent->key();
    QTextCursor tcurs = ui.iTextEdit->textCursor();
    qDebug() << key;

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
        ui.iTextEdit->insertPlainText(sel_struct->to_paste);
        break;
      case(Qt::Key_B):
        ui.iTextEdit->moveCursor(QTextCursor::PreviousWord);
        sel_struct->tcurs.movePosition(QTextCursor::PreviousWord);
        break;
      case(Qt::Key_W):
        ui.iTextEdit->moveCursor(QTextCursor::WordRight);
        sel_struct->tcurs.movePosition(QTextCursor::WordRight);
        break;
      case(Qt::Key_U):
        ui.iTextEdit->undo();
        ui.iTextEdit->moveCursor(QTextCursor::PreviousBlock);
        sel_struct->tcurs.movePosition(QTextCursor::PreviousBlock);
        break;
      case(Qt::Key_D):
        if (dCount == 0 || dCount %2 != 0)
        {
          if (dTimer->isValid() == false)
            dTimer->start();
          dCount++;
        }
        if (dCount %2 == 0)
        {
          deleteLine();
          dCount^=dCount;
          dTimer->invalidate();
        }
      case(Qt::Key_Y):
        if (yCount == 0 || yCount %2 != 0)
        {
          if (yTimer->isValid() == false)
            yTimer->start();
          yCount++;
        }
        if (yCount %2 == 0)
        {
          copyLine();
          yCount^=yCount;
          yTimer->invalidate();
        }
        return true;
    }
    return true;
  }

  return false;
}
