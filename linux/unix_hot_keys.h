#ifndef _WIN_KEY_H_
#define _WIN_KEY_H_

#include <X11/Xlib.h>

#include "xhklib.h"

int registerUnixHotKeys(void (*callback)(xhkEvent, void *, void *, void *));
void sendPasteKeyEvent();
#endif
