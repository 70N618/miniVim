#include "../includes/Mode.h"
#include "../includes/mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <qdebug.h>

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    MainWindow w;
    Ui::MainWindow ui = *w.getUi();
    Mode mode(w,ui,NULL);
    if (argc == 2)
    {
      mode.setFile(argv[1]);
      mode.createFile();
    }
    w.show();
    return a.exec();
}
