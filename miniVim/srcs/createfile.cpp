#include "../includes/Mode.h"
#include "../includes/mainwindow.h"
#include "ui_mainwindow.h"
#include <qevent.h>

void Mode::createFile()
{
  QFile file(this->file);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
  while (!file.atEnd())
  {
        QByteArray line = file.readLine();
        QString qstr = QString::fromStdString(line.toStdString());
        ui.iTextEdit->insertPlainText(qstr);
  }
  file.close();
}
