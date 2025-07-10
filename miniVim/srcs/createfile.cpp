#include "../includes/Mode.h"
#include "../includes/mainwindow.h"
#include "ui_mainwindow.h"
#include <qevent.h>

/*@brief: iterates over given file and copy its content.
 * Content is copied inside iTextEdit.
 * This is needed to edit the file passed as parameter to main. */

void Mode::createFile()
{
  QFile file(this->file);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
  ui.iTextEdit->insertPlainText(QString::fromUtf8(file.readAll()));
  sel_struct->tcurs.setPosition(QTextCursor::Start);
  ui.iTextEdit->setTextCursor(sel_struct->tcurs);
  file.close();
}
