#include "../includes/Mode.h"
#include <qglobal.h>

/* @brief: overrided function of QPlainTextEdit
 * This is the core of event handling.
 *
 * @Params:
 *  obj -> obj where we installed the eventFilter
 *  event-> the event itself.
 *
 * @Return:
 *  True or false depending on if the event was
 *  handled or not. */


bool Mode::eventFilter(QObject *obj, QEvent *event)
{
  if (triggerIns(event) == true)
    return true;
  if (triggerEsc(event) == true)
    return true;
  if (visMode(event) == true)
    return true;
  if (keyBinds(event) == true)
    return true;
  if (cmdHandler(event) == true)
    return true;
  return false;
}
