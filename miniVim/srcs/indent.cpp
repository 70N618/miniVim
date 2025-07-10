#include "../includes/Mode.h"
#include "ui_mainwindow.h"
#include <qevent.h>
#include <qlogging.h>

bool Mode::indent(QKeyEvent *ke, char c)
{
  if (c == '{')
    this->ind_flag++;
  else if (c == '}')
    this->ind_flag--;
  if (this->ind_flag < 1)
    ind_flag = 1;
  QTextBlockFormat fmt = QTextBlockFormat();
  fmt.setTextIndent(this->ind_flag * 40);
  sel_struct->tcurs.mergeBlockFormat(fmt);
  return true;
}

