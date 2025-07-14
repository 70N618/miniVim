#include "../includes/Mode.h"
#include "ui_mainwindow.h"
#include <qevent.h>
#include <qlogging.h>
#include <QDebug>
#include <qtextcursor.h>


/*
 * @Brief: indenting function.
 * It counts the number of tabs on the current line
 * and checks for { or }
 *
 * @Args: KeyEvent --> the key being pressed.
 *
 * @Return: true if event has handled else false */

bool Mode::indent(QKeyEvent *keyEvent)
{
  // First check if enter is pressed.
  // In this case we look for { or words and calculate indent.

  if (keyEvent->key() == Qt::Key_Return)
  {
    // We get current text block with and without spaces.
    // We also decleare indent as a string.
    // This is gonna get filled with tabs and spaces.

    QTextCursor cs = ui.iTextEdit->textCursor();
    QString curr = cs.block().text();
    QString trimmed = cs.block().text().trimmed();
    QString indent;

    // Iterate over current string, looking for tabs/spaces.

    for (QChar ch: curr)
    {
      if (ch == '\t') indent += ch;
      else if (ch == ' ') indent += ' ';
      else break;
    }

    // Indent is now applied.

    cs.insertText("\n");
    if (trimmed.endsWith('{'))
      indent+='\t';
    cs.insertText(indent);

    // Update text cursor.

    ui.iTextEdit->setTextCursor(cs);

    return true;
  }

  // Here we handle }.
  // In this case we don't need to press enter and
  // indent will happen automatically.

  if (keyEvent->text() == '}')
  {

    // Retrieve cursor and current string.

    QTextCursor cs = ui.iTextEdit->textCursor();
    QString curr = cs.block().text();
    QString indent;

    // Iterate over the string

    for (QChar ch: curr)
    {
      if (ch == '\t') indent += ch;
      else if (ch == ' ') indent += ' ';
      else break;
    }

    // Since we've to indent back,
    // we check for a tab at the end.
    // If it's present we chop the string.

    if (indent.endsWith('\t'))
      indent.chop(1);

    // Finally we insert the right indent.

    cs.insertText("\n" + indent + '}');

    // Set updated cursor.
    ui.iTextEdit->setTextCursor(cs);

    return true;
  }
  return false;
}

