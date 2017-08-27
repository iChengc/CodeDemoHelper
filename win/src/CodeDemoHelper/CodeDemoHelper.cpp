/****************************** Module Header ******************************\
Module Name:  CppRegisterHotkey.cpp
Project:      CppRegisterHotkey
Copyright (c) Microsoft Corporation.

The sample demonstrates how to register and unregister a hotkey for the
current application.

This source is subject to the Microsoft Public License.
See http://www.microsoft.com/opensource/licenses.mspx#Ms-PL.
All other rights reserved.

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
\***************************************************************************/
#include "stdafx.h"
#pragma region Includes and Manifest Dependencies
#include <stdio.h>
#include <Windows.h>
#include <windowsx.h>
#include <strsafe.h>
#include "resource.h"

#include <CommCtrl.h>
#pragma comment(lib, "Comctl32.lib")

// Enable Visual Style
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#pragma endregion
#include "registerHotkey.h"

//
//   FUNCTION: ReportError(LPWSTR, DWORD)
//
//   PURPOSE: Display an error dialog for the failure of a certain function.
//
//   PARAMETERS:
//   * pszFunction - the name of the function that failed.
//   * dwError - the Win32 error code. 
//
void ReportError(LPCWSTR pszFunction, DWORD dwError = NO_ERROR)
{
	wchar_t szMessage[200];
	if (dwError == NO_ERROR)
	{
		StringCchPrintf(szMessage, ARRAYSIZE(szMessage),
			L"%s failed", pszFunction);
	}
	else if (dwError == ERROR_HOTKEY_ALREADY_REGISTERED)
	{
		StringCchPrintf(szMessage, ARRAYSIZE(szMessage),
			L"The hotkey is in use");
	}
	else
	{
		StringCchPrintf(szMessage, ARRAYSIZE(szMessage),
			L"%s failed w/err 0x%08lx", pszFunction, dwError);
	}

	MessageBox(NULL, szMessage, L"Error", MB_ICONERROR);
}

BOOL g_fHotkeyRegistered = FALSE;

// 
//   FUNCTION: OnInitDialog(HWND, HWND, LPARAM)
//
//   PURPOSE: Process the WM_INITDIALOG message. 
//
BOOL OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam)
{

	Button_Enable(GetDlgItem(GetParent(hWnd), IDC_BUTTON_REGISTER), FALSE);
	Button_Enable(GetDlgItem(GetParent(hWnd), IDC_BUTTON_UNREGISTER), TRUE);
	return TRUE;
}


//
//   FUNCTION: OnCommand(HWND, int, HWND, UINT)
//
//   PURPOSE: Process the WM_COMMAND message
//
void OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case IDC_BUTTON_REGISTER:
		registerDemoHotKey(hWnd);
		g_fHotkeyRegistered = TRUE;
		Button_Enable(GetDlgItem(GetParent(hWnd), IDC_BUTTON_REGISTER), FALSE);
		Button_Enable(GetDlgItem(GetParent(hWnd), IDC_BUTTON_UNREGISTER), TRUE);

		break;

	case IDC_BUTTON_UNREGISTER:
		unregisterDemoHotKey(hWnd);
		g_fHotkeyRegistered = FALSE;
		Button_Enable(GetDlgItem(GetParent(hWnd), IDC_BUTTON_REGISTER), TRUE);
		Button_Enable(GetDlgItem(GetParent(hWnd), IDC_BUTTON_UNREGISTER), FALSE);
		break;
	}
}


//
//   FUNCTION: OnHotKey(HWND, int, UINT, UINT)
//
//   PURPOSE: Process the WM_HOTKEY message. The WM_HOTKEY message is posted 
//   when the user presses a hot key registered by the RegisterHotKey 
//   function. The message is placed at the top of the message queue 
//   associated with the thread that registered the hot key. 
//
void OnHotKey(HWND hWnd, int idHotKey, UINT fuModifiers, UINT vk)
{
	OnHotKeyPressed(hWnd, idHotKey, fuModifiers, vk);
}


//
//   FUNCTION: OnClose(HWND)
//
//   PURPOSE: Process the WM_CLOSE message
//
void OnClose(HWND hWnd)
{
	EndDialog(hWnd, 0);
}


//
//   FUNCTION: OnNCDestroy(HWND)
//
//   PURPOSE: Process the WM_NCDESTROY message
//
void OnNCDestroy(HWND hWnd)
{
	if (g_fHotkeyRegistered)
	{
		// Unregister the hotkey.
		unregisterDemoHotKey(hWnd);
	}
}


//
//  FUNCTION: DialogProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main dialog.
//
INT_PTR CALLBACK DialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		// Handle the WM_INITDIALOG message in OnInitDialog
		HANDLE_MSG(hWnd, WM_INITDIALOG, OnInitDialog);

		// Handle the WM_COMMAND message in OnCommand
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);

		// Handle the WM_HOTKEY message in OnHotKey
		HANDLE_MSG(hWnd, WM_HOTKEY, OnHotKey);

		// Handle the WM_CLOSE message in OnClose
		HANDLE_MSG(hWnd, WM_CLOSE, OnClose);

		// Handle the WM_NCDESTROY message in OnNCDestroy
		HANDLE_MSG(hWnd, WM_NCDESTROY, OnNCDestroy);

	default:
		return FALSE;
	}
	return 0;
}


//
//  FUNCTION: wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
//
//  PURPOSE:  The entry point of the application.
//
int APIENTRY wWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR    lpCmdLine,
	int       nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAINDIALOG), NULL, DialogProc);
}