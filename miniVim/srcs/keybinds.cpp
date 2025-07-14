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
#include <qtmetamacros.h>

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
    return indent(keyEvent);
  }

  if (this->esc_mode == true && this->cmd_mode == false)
  {
    int key = keyEvent->key();
    QTextCursor tcurs = ui.iTextEdit->textCursor();
    qDebug() << key;

    switch (key)
    {
      case(Qt::Key_H):
        sel_struct->tcurs.movePosition(QTextCursor::Left);
        ui.iTextEdit->moveCursor(QTextCursor::Left);
        break;
      case(Qt::Key_J):
        sel_struct->tcurs.movePosition(QTextCursor::Down);
        ui.iTextEdit->moveCursor(QTextCursor::Down);
        break;
      case(Qt::Key_K):
        sel_struct->tcurs.movePosition(QTextCursor::Up);
        ui.iTextEdit->moveCursor(QTextCursor::Up);
        break;
      case(Qt::Key_L):
        sel_struct->tcurs.movePosition(QTextCursor::Right);
        ui.iTextEdit->moveCursor(QTextCursor::Right);
        break;
      case(Qt::Key_Dollar):
        sel_struct->tcurs.movePosition(QTextCursor::EndOfLine);
        ui.iTextEdit->moveCursor(QTextCursor::EndOfLine);
        break;
      case(Qt::Key_0):
        sel_struct->tcurs.movePosition(QTextCursor::StartOfLine);
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
        {
          QTextCursor cs = ui.iTextEdit->textCursor();
          QString curr = cs.block().text();
          QString trimmed = cs.block().text().trimmed();
          QString indent;

          for (QChar ch: curr)
          {
            if (ch == '\t') indent += ch;
            else if (ch == ' ') indent += ' ';
            else break;
          }

          cs.movePosition(QTextCursor::EndOfLine);
          cs.insertText("\n");

          if (trimmed.endsWith('{'))
            indent+='\t';

          cs.insertText(indent);

          ui.iTextEdit->setTextCursor(cs);
          this->ins_mode = true;
          this->esc_mode = false;
          ui.label->setText("INS");
          break;
        }
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

