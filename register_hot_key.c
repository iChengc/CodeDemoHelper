#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#ifdefine __APPLE__

#elif _WIN32
#include "win/win_key.h"
#else
#include <X11/Xlib.h>
#endif

#include "xhklib.h"
#include "register_hot_key"
void (*callback)(HotKey);

// Call this when "Up key" is pressed.
void printCode(xhkEvent e, void *r1, void *r2, void *r3)
{
 	if (callback == null) {
 		return;
 	}

 	callback(KEY_Up);
}

void jump2PreSnippet(xhkEvent e, void *r1, void *r2, void *r3) {
	
 	if (callback == null) {
 		return;
 	}

 	callback(KEY_Left);
}

void jump2NextSnippet(xhkEvent e, void *r1, void *r2, void *r3) {
 	if (callback == null) {
 		return;
 	}

 	callback(KEY_Right);
}

void showCode(xhkEvent e, void *r1, void *r2, void *r3) {
 	if (callback == null) {
 		return;
 	}

 	callback(KEY_Down);
}

void register_hot_key(void (*func)(HotKey)) {
#ifdefine __APPLE__
	// mac implementation
	
#elif _WIN32
	// windows implementation
	win_register_hot_key(func);
#else
    xhkConfig *hkconfig;
	hkconfig = xhkInit(NULL);
	callback = func;
	
    xhkBindKey(hkconfig, 0, /*XK_Shift_L*/XK_Up, 0, xhkKeyPress, &printCode, 0, 0, 0);

    xhkBindKey(hkconfig, 0, XK_Left, 0, xhkKeyPress, &jump2PreSnippet, 0, 0, 0);

    xhkBindKey(hkconfig, 0, XK_Right, 0, xhkKeyPress, &jump2NextSnippet, 0, 0, 0);

    xhkBindKey(hkconfig, 0, XK_S, 0, xhkKeyPress, &showCode, 0, 0, 0);

    while (1) {
        xhkPollKeys(hkconfig, 1);
    }

    xhkClose(hkconfig);
#endif
}