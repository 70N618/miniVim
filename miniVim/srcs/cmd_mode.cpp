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

/* @brief: Function that handles cmd Mode.
 * @Paramas: QEvent
 * @return: True or False depending if the event has handled */

bool Mode::cmdHandler(QKeyEvent *keyEvent)
{

  if (esc_mode == true)
  {
    if (keyEvent->text() == ":")
    {
      qDebug() << "Cmd mode\n";
      this->ui.label->setText("CMD");
      this->cmd_mode = true;
      emit sigCmdMode();
      return true;
    }
  }

  if (esc_mode == true && cmd_mode == true)
  {
    if (keyEvent->key() == Qt::Key_Return)
    {
      QString cmd = ui.eTextEdit->toPlainText();
      qDebug() << cmd;

      if (cmd == "q")
      {
        delete this->dTimer;
        delete this->yTimer;
        out.close();
        QApplication::quit();
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
  return false;
}
