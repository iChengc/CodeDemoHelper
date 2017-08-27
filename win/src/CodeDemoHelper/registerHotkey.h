#pragma once

#include "stdafx.h"

void registerDemoHotKey(HWND hWnd);

void unregisterDemoHotKey(HWND hWnd);

void OnHotKeyPressed(HWND hWnd, int idHotKey, UINT fuModifiers, UINT vk);