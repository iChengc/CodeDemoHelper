#ifndef _WIN_KEY_H_
#define _WIN_KEY_H_

#include <X11/Xlib.h>

#include "xhklib.h"
#include "code_demo_helper.h"

int registerUnixHotKeys(HotKeyCallBack *);
void sendPasteKeyEvent();
#endif
