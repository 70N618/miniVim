#include "../includes/Mode.h"
#include "../includes/mainwindow.h"
#include "ui_mainwindow.h"
#include <qaction.h>
#include <QAction>
#include <QTimer>
#include <qdebug.h>
#include <qelapsedtimer.h>
#include <qglobal.h>
#include <qnamespace.h>
#include <qobjectdefs.h>


// Triggered when "dd" is pressed in NRM mode

void Mode::deleteLine()
{
  qDebug() << dTimer->elapsed();

  if (dTimer->elapsed() <= 1500)
  {
    QTextCursor c = sel_struct->tcurs;

    // Set cursor to delete current line

    c.movePosition(QTextCursor::StartOfLine);
    c.movePosition(QTextCursor::EndOfLine,QTextCursor::KeepAnchor);

    if (c.hasSelection())
    {
      qDebug() << c.selectedText();
      c.removeSelectedText();
    }

    // Remove new line

    c.deletePreviousChar();

    ui.iTextEdit->setTextCursor(c);

    qDebug() << "line deleted\n";
  }
}

void Mode::copyLine()
{
  qDebug() << yTimer->elapsed();

  if (yTimer->elapsed() <= 1500)
  {
    QTextCursor c = sel_struct->tcurs;

    // Set cursor to delete current line

    c.movePosition(QTextCursor::StartOfLine);
    c.movePosition(QTextCursor::EndOfLine,QTextCursor::KeepAnchor);

    if (c.hasSelection())
    {
      sel_struct->to_paste = c.selectedText() + '\n';
      qDebug() << "Line yanked: " << sel_struct->to_paste;
    }

    ui.iTextEdit->setTextCursor(c);

  }
}
