#include "../includes/Esc.h"
#include "../includes/mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <qevent.h>

void Esc::createFile()
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
}
