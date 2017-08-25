#ifndef _WIN_KEY_H_
#define _WIN_KEY_H_
#include "../send_key_event.h"

void win_register_hot_key(void (*func)(HotKey));
void win_send_key();
#endif