#ifndef _REGISTER_HOT_KEY_
#define _REGISTER_HOT_KEY_
#include "xhklib.h"
typedef enum HotKey {
	KEY_Up,KEY_Down,KEY_Left, KEY_Right
} HotKey;

void register_hot_key(void (*func)(HotKey));
#endif
