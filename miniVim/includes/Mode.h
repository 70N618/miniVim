#ifndef ESC_H
#define ESC_H

#include "SyntaxHighlight.h"
#include "mainwindow.h"
#include <qcoreevent.h>
#include <qelapsedtimer.h>
#include <qevent.h>
#include <qmainwindow.h>
#include <qplaintextedit.h>
#include <qtextcursor.h>
#include <QElapsedTimer>
#include <QFile>

struct t_sel
{
    QTextCursor tcurs;
    int sel_start;
    int sel_end;
    QString to_paste;
};

class Mode: public QPlainTextEdit
{
  Q_OBJECT

  public:
    Mode(MainWindow &win, Ui::MainWindow &ui, const char *file);
    ~Mode();
    bool getModeMode();
    void setFile(const char *file);

    void createFile();
    void deleteLine();
    void copyLine();
    void startOfFile();

  public slots:
    void toggleEscMode();
    void toggleInsMode();
    void toggleCmdMode();
    void toggleVisMode();

  protected:
    bool eventFilter(QObject *obj, QEvent *ev) override;
    bool triggerEsc(QKeyEvent *keyEvent);
    bool triggerIns(QKeyEvent *keyEvent);
    bool cmdHandler(QKeyEvent *keyEvent);
    bool visMode(QKeyEvent *keyEvent);
    bool keyBinds(QKeyEvent *keyEvent);
    bool indent(QKeyEvent *keyEvent);

  signals:
    void sigNormMode();
    void sigCmdMode();
    void sigInsMode();
    void sigVisMode();


  private:
    bool esc_mode;
    bool ins_mode;
    bool cmd_mode;
    bool vis_mode;

    Ui::MainWindow &ui;
    MainWindow &win;
    t_sel *sel_struct;
    const char *file;
    QFile out;
    int dCount;
    int yCount;
    int gCount;
    QElapsedTimer *dTimer;
    QElapsedTimer *yTimer;
    QElapsedTimer *gTimer;
    bool nl;
    char last_char;
    int ind_flag;

};


#endif
