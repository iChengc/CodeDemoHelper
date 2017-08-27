#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <X11/Xlib.h>

#include "xhklib.h"
#include "register_hot_key.h"
void (*callback)(HotKey);

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
}