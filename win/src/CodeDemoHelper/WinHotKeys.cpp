#include <string.h>
#include "WinHotKeys.h"
#include "hot_keys.h"
#include "utils.h"

BOOL registerWinHotKeys(HWND hWnd) {
	if (RegisterHotKey(hWnd, KEY_Left, 0, VK_LEFT)
		&& RegisterHotKey(hWnd, KEY_Up, 0, VK_UP)
		&& RegisterHotKey(hWnd, KEY_Right, 0, VK_RIGHT)
		&& RegisterHotKey(hWnd, KEY_Down, 0, VK_DOWN)) {
		return true;
	}
	
	return false;
}

BOOL unregisterWinHotKeys(HWND hWnd) {
	UnregisterHotKey(hWnd, KEY_Left);
	UnregisterHotKey(hWnd, KEY_Up);
	UnregisterHotKey(hWnd, KEY_Right);
	UnregisterHotKey(hWnd, KEY_Down);
	return true;
}

void sendPasteKey(BOOL bState)
{
	BYTE keyState[256];

	GetKeyboardState((LPBYTE)&keyState);
	if ((bState && !(keyState[VK_NUMLOCK] & 1)) ||
		(!bState && (keyState[VK_NUMLOCK] & 1)))
	{
		// Simulate a key press
		keybd_event(VK_CONTROL,
			0x45,
			KEYEVENTF_EXTENDEDKEY | 0,
			0);
		// Simulate a key press
		keybd_event('V',
			0x45,
			KEYEVENTF_EXTENDEDKEY | 0,
			0);

		// Simulate a key release
		keybd_event('V',
			0x45,
			KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,
			0);
		keybd_event(VK_CONTROL,
			0x45,
			KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,
			0);
	}
}