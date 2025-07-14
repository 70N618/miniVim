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
#include <qlogging.h>
#include <qnamespace.h>
#include <qregion.h>
#include <qtextcursor.h>
#include <qtimer.h>

/* @brief: Handles Keybinds when in NRM mode.
 * Once a keybind is handled it must return true.
 * This way the event filter will know the event was handled.
 *
 * @params: takes a QEvent which must be of type KeyPress.
 *
 * @return: true if even has handled else false. */

bool Mode::keyBinds(QKeyEvent *keyEvent)
{
  if (this->ins_mode == true  && esc_mode == false)
  {
      QTextCursor cs = ui.iTextEdit->textCursor();

      int base_indent = ind_flag;

      // If key is return and ind_flag is already higher than 0

      if (keyEvent->key() == Qt::Key_Return)
      {
        QString curr = cs.block().text().trimmed();
        if (curr == '{')
        {
          ind_flag++;

          cs.insertText("\n");
          for (int i = 0; i < ind_flag; i++)
            cs.insertText("\t");

          return true;
        }
        else
        {
          cs.insertText("\r");
          for (int i = 0; i < ind_flag; i++)
            cs.insertText("\t");
          return true;
        }
      }
      if (keyEvent->text() == '}')
      {
        ind_flag--;
        cs.insertText("\n");
        for (int i = 0; i < ind_flag; i++)
          cs.insertText("\t");
      }
  }

  if (this->esc_mode == true && this->cmd_mode == false)
  {
    int key = keyEvent->key();
    QTextCursor tcurs = ui.iTextEdit->textCursor();
    qDebug() << key;

    switch (key)
    {
      case(Qt::Key_H):
        ui.iTextEdit->moveCursor(QTextCursor::Left);
        break;
      case(Qt::Key_J):
        ui.iTextEdit->moveCursor(QTextCursor::Down);
        break;
      case(Qt::Key_K):
        ui.iTextEdit->moveCursor(QTextCursor::Up);
        break;
      case(Qt::Key_L):
        ui.iTextEdit->moveCursor(QTextCursor::Right);
        break;
      case(Qt::Key_Dollar):
        ui.iTextEdit->moveCursor(QTextCursor::EndOfLine);
        break;
      case(Qt::Key_0):
        ui.iTextEdit->moveCursor(QTextCursor::StartOfLine);
        break;
      case(Qt::Key_P):
        if (nl)
        {
          sel_struct->tcurs.movePosition(QTextCursor::StartOfLine);
          ui.iTextEdit->setTextCursor(sel_struct->tcurs);
          nl = false;
        }
        ui.iTextEdit->insertPlainText(sel_struct->to_paste);
        break;
      case(Qt::Key_B):
        ui.iTextEdit->moveCursor(QTextCursor::PreviousWord);
        break;
      case(Qt::Key_W):
        ui.iTextEdit->moveCursor(QTextCursor::WordRight);
        break;
      case(Qt::Key_U):
        ui.iTextEdit->undo();
        ui.iTextEdit->setTextCursor(sel_struct->tcurs);
        break;
      case(Qt::Key_O):
        ui.iTextEdit->moveCursor(QTextCursor::EndOfLine);
        ui.iTextEdit->insertPlainText("\n");
        for (int i = 0; i < this->ind_flag; ++i)
        {
          sel_struct->tcurs.insertText("\t");
        }
        this->esc_mode = false;
        this->ins_mode = true;
        this->ui.label->setText("INS");
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
        break;
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
        break;
    }
    return true;
  }
  return false;
}

