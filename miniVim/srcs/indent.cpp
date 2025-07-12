#include "../includes/Mode.h"
#include "ui_mainwindow.h"
#include <qevent.h>
#include <qlogging.h>
#include <qtextcursor.h>

bool Mode::indent(QKeyEvent *ke)
{
  // Move cursor up one line and get last char.

  QTextCursor cs = sel_struct->tcurs;
  int cbind = 0;

  QString prev = cs.block().text().trimmed();
  qDebug() << "Prev: " << prev;
  qDebug() << "Ends with: " << prev.endsWith('{');

  if (prev.endsWith('{'))
    this->ind_flag++;

  else if (prev.endsWith('}'))
    this->ind_flag--;

  if (this->ind_flag < 0)
    this->ind_flag = 0;

  cs.insertText("\n");
  for (int i = 0; i < this->ind_flag; ++i)
  {
    cs.insertText("\t");
  }

  return true;
}

