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

/* @brief: Function that handles visual Mode.
 * @Paramas: QEvent
 * @return: True or False depending if the event has handled */

bool Mode::visMode(QEvent *event)
{
  QKeyEvent *keyEvent;
  keyEvent = static_cast<QKeyEvent *>(event);

  // If event is not a keypress event we're not interested.

  if (event->type() != QEvent::KeyPress)
    return false;

  if (keyEvent->text() == "v" && cmd_mode == false)
  {
    // If v is pressed and visual mode is enabled
    // we disable it and go back to nrm mode.

    if (vis_mode == true)
    {
      qDebug() << "Visual mode disabled\n";
      this->vis_mode = false;
      this->ui.label->setText("NRM");
      return true;
    }

    // Else we enable it and emit sigVisMode signal.

    qDebug() << "Visual mode\n";
    this->ui.label->setText("Vis");
    this->vis_mode = true;
    emit sigVisMode();

    return true;
  }

  /* Handle when y is pressed while in vis_mode
   * Start of selection is set inside toggleVisMode().
   * When we press y we end selection
   * selected text is saved inside struct var "to_paste" */

  if (keyEvent->text() == "y" && vis_mode == true)
  {
    ui.iTextEdit->setTextCursor(sel_struct->tcurs);

    // We start selection from start and end on sel_end.
    // cursor will select text it goes over thanks to KeepAnchor

    sel_struct->sel_end = sel_struct->tcurs.position();
    sel_struct->tcurs.setPosition(this->sel_struct->sel_start);
    sel_struct->tcurs.setPosition(sel_struct->sel_end, QTextCursor::KeepAnchor);

    // tcurs.selectedText() will provide us with the text to copy.

    qDebug() << "End:" << sel_struct->sel_end;
    sel_struct->to_paste = sel_struct->tcurs.selectedText();

    this->vis_mode = false;
    this->ui.label->setText("NRM");
    return true;
  }
  return false;
}
