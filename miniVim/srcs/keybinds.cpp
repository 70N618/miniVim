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

// Handle Esc shortcuts

bool Mode::keyBinds(QEvent *event)
{
  QKeyEvent *keyEvent;
  keyEvent = static_cast<QKeyEvent *>(event);

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
        sel_struct->tcurs.movePosition(QTextCursor::PreviousWord);
        break;
      case(Qt::Key_W):
        ui.iTextEdit->moveCursor(QTextCursor::WordRight);
        sel_struct->tcurs.movePosition(QTextCursor::WordRight);
        break;
      case(Qt::Key_U):
        ui.iTextEdit->undo();
        ui.iTextEdit->setTextCursor(sel_struct->tcurs);
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
