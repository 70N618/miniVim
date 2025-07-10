#include "../includes/Mode.h"
#include <qevent.h>
#include <qglobal.h>
#include <QDebug>

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
  if (event->type() != QEvent::KeyPress)
        return false;

  // After this check we're safe to static_cast to a QKeyEvent

  QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

  if (!keyEvent)
  {
      qWarning() << "Warning: Event marked as KeyPress is not a QKeyEvent!";
      return false;
  }

  if (cmdHandler(keyEvent) == true)
    return true;
  if (triggerIns(keyEvent) == true)
    return true;
  if (triggerEsc(keyEvent) == true)
    return true;
  if (visMode(keyEvent) == true)
    return true;
  if (keyBinds(keyEvent) == true)
    return true;

  return false;
}
