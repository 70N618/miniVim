#include "../includes/Esc.h"
#include "../includes/mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Ui::MainWindow ui = *w.getUi();
    Esc  mode(w, ui);
    w.show();
    return a.exec();
}
