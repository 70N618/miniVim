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

bool Mode::triggerEsc(QEvent *event)
{

  // Trigger ESC Mode

  QKeyEvent *keyEvent;
  keyEvent = static_cast<QKeyEvent *>(event);

  if (event->type() == QEvent::KeyPress)
  {
    if (keyEvent->key() == Qt::Key_Escape)
    {
      qDebug() << "Key Esc pressed";
      this->ui.label->setText("NRM");
      emit sigNormMode(event);
      return true;
    }
  }
  return false;
}

// Trigger Ins mode

bool Mode::triggerIns(QEvent *event)
{
  QKeyEvent *keyEvent;
  keyEvent = static_cast<QKeyEvent *>(event);
  if (event->type() == QEvent::KeyPress && esc_mode == true && cmd_mode == false)
  {
    if (keyEvent->text() == "i")
    {
      qDebug() << "Insert mode\n";
      this->ui.label->setText("INS");
      emit sigInsMode();
      return true;
    }
  }
  return false;
}
