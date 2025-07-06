#include "../includes/Esc.h"
#include "../includes/mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Ui::MainWindow ui = *w.getUi();
    if (argc == 2)
    {
      Esc  mode(w, ui, argv[1]);
      mode.createFile();
    }
    else
      Esc  mode(w, ui, NULL);
    w.show();
    return a.exec();
}
