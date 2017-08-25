#ifdefine __APPLE__
// Mac implementation
#elif _WIN32
// Windows implementation
include "win/win_key.h"
#else
#include <X11/Intrinsic.h>
#include <X11/extensions/XTest.h>
#endif

#include "send_key_event.h"

#ifdefine __APPLE__
// Mac implementation
#elif _WIN32
// Windows implementation
#else
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
 	usleep(500000);
    XFlush(disp);
	XTestFakeKeyEvent (disp, keycode, False, 0); 
 
 	/* Generate modkey release */
 	if (modsym != 0) {
 	 	XTestFakeKeyEvent (disp, modcode, False, 0);
 	}
 	XFlush(disp);
 	XCloseDisplay(disp);
}
#endif

void sendPasteKeyEvent() {
#ifdefine __APPLE__
// Mac implementation
#elif _WIN32
// Windows implementation
	win_send_key();
#else
	sendKey(XK_V, XK_Control_L);
#endif
}