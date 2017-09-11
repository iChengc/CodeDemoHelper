#ifndef _MAC_KEY_H_
#define _MAC_KEY_H_
#include "../send_key_event.h"

void mac_register_hot_key(void (*func)(HotKey));
#endif