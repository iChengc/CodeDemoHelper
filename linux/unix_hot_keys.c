#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <X11/Xlib.h>

#include "xhklib.h"
#include "unix_hot_keys.h"
#include "utils.h"
xhkConfig *hkconfig;
HotKeyCallBack *callback;

void onShowCode(CodeSnippet *p) {
	while (p != null) {
		printf("%d.\n%s\n\n", (*p).order, (*p).code->code);
		p = (*p).next;
	}
}

static void onPressUpKey(xhkEvent e, void *r1, void *r2, void *r3) {
    if (callback == null) {
	return;
    }
    callback->pasteCode();
}

static void onPressDownKey(xhkEvent e, void *r1, void *r2, void *r3) {
    if (callback == null) {
	return;
    }
    onShowCode(callback->showCode());
}

static void onPressLeftKey(xhkEvent e, void *r1, void *r2, void *r3) {
    if (callback == null) {
	return;
    }
    callback->previous();
}

static void onPressRightKey(xhkEvent e, void *r1, void *r2, void *r3) {
    if (callback == null) {
	return;
    }
    callback->next();
}


int registerUnixHotKeys(HotKeyCallBack *cb)
{
    hkconfig = xhkInit(NULL);
    callback = cb;
    xhkBindKey(hkconfig, 0, /*XK_Shift_L*/XK_Up, 0, xhkKeyPress, &onPressUpKey, 0, 0, 0);

    xhkBindKey(hkconfig, 0, XK_Left, 0, xhkKeyPress, &onPressLeftKey, 0, 0, 0);

    xhkBindKey(hkconfig, 0, XK_Right, 0, xhkKeyPress, &onPressRightKey, 0, 0, 0);

    xhkBindKey(hkconfig, 0, XK_Down, 0, xhkKeyPress, &onPressDownKey, 0, 0, 0);
    return 1;
}

void pollUnixHotKeys() {
    while (1) {
        xhkPollKeys(hkconfig, 1);
    }

    xhkClose(hkconfig);
}

static void sendKey (KeySym keysym, KeySym modsym) {
	Display * disp = XOpenDisplay(NULL); 
 	KeyCode keycode = 0, modcode = 0;
 	keycode = XKeysymToKeycode (disp, keysym);
 	if (keycode == 0) return; //init value

 	/* Generate modkey press */
 	if (modsym != 0) {
  		modcode = XKeysymToKeycode(disp, modsym);
  		XTestFakeKeyEvent (disp, modcode, True, 0);
 		XFlush(disp);
 	}
 	/* Generate regular key press and release */
 	XTestFakeKeyEvent (disp, keycode, True, 0);
 	usleep(150000);
    	XFlush(disp);
	XTestFakeKeyEvent (disp, keycode, False, 0); 
 
 	/* Generate modkey release */
 	if (modsym != 0) {
 	 	XTestFakeKeyEvent (disp, modcode, False, 0);
 	}
 	XFlush(disp);
 	XCloseDisplay(disp);
}

void sendPasteKeyEvent() {
	sendKey(XK_V, XK_Control_L);
}
