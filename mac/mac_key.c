#include <stdio.h>
#include "include/HotkeyRegisterMac.h"

#include "../register_hot_key.h"
#include "../utils.h"
#include "mac_key.h"

void (*callback)(HotKey);
 
void macKeyCode(int keyCode) {
	if (callback == NULL) {
		return;
	}

	switch (keyCode) {
		case 0:
			callback(KEY_Up);
			break;
		case 1:
			callback(KEY_Down);
			break;
		case 2:
			callback(KEY_Left);
			break;
		case 3:
			callback(KEY_Right);
			break;
	}
}

void mac_register_hot_key(void (*func)(HotKey))  
{  
    callback = func;
    registerHotKey(&macKeyCode);
}

void win_send_key()
{  
} 