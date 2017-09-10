#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <X11/Xlib.h>

#include "register_hot_key.h"
#include "utils.h"
void (*callback)(HotKey);

static void down(xhkEvent e, void *r1, void *r2, void *r3) {
 	if (callback == null) {
 		return;
 	}

 	callback(KEY_Down);
}

static void left(xhkEvent e, void *r1, void *r2, void *r3) {
	
 	if (callback == null) {
 		return;
 	}

 	callback(KEY_Left);
}

static void right(xhkEvent e, void *r1, void *r2, void *r3) {
 	if (callback == null) {
 		return;
 	}
 	callback(KEY_Right);
}

static void up(xhkEvent e, void *r1, void *r2, void *r3) {

 	if (callback == null) {
 		return;
 	}
 	callback(KEY_Up);
}

void register_hot_key(void (*func)(HotKey)) {
    xhkConfig *hkconfig;
	hkconfig = xhkInit(NULL);
	callback = func;
	
    xhkBindKey(hkconfig, 0, /*XK_Shift_L*/XK_Up, 0, xhkKeyPress, &up, 0, 0, 0);

    xhkBindKey(hkconfig, 0, XK_Left, 0, xhkKeyPress, &left, 0, 0, 0);

    xhkBindKey(hkconfig, 0, XK_Right, 0, xhkKeyPress, &right, 0, 0, 0);

    xhkBindKey(hkconfig, 0, XK_Down, 0, xhkKeyPress, &down, 0, 0, 0);

    while (1) {
        xhkPollKeys(hkconfig, 1);
    }

    xhkClose(hkconfig);
}
