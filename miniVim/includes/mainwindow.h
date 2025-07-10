#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "SyntaxHighlight.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
  class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT
  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    SyntaxHighlight *getSh();
    Ui::MainWindow *getUi();

  private:
    Ui::MainWindow *ui;
    SyntaxHighlight *sh;
};

#endif // MAINWINDOW_H
