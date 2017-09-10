#pragma once
#include <stdio.h>
#include <Windows.h>
#include <windowsx.h>

BOOL registerWinHotKeys(HWND hWnd);

BOOL unregisterWinHotKeys(HWND hWnd);

void sendPasteKey(BOOL bState);