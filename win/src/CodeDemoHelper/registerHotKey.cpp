#include "registerHotkey.h"
#include "stdafx.h"
#include "sendKeyEvent.h"

const int upId = 100;
const int downId = 101;
const int leftId = 102;
const int rightId = 103;

#pragma hotkey process
// CodeSnippet *codeSnippets;

// Call this when "Up key" is pressed.
void printCode()
{
	/*if (codeSnippets == null) {
		return;
	}

	copyCode2clipboard(codeSnippets->code->code);

	if (codeSnippets->next == null) {
		// back to head.
		while (codeSnippets->pre != null) {
			codeSnippets = codeSnippets->pre;
		}
	}
	else {
		codeSnippets = codeSnippets->next;
	}*/
	sendPasteKey(true);
}

void jump2PreSnippet() {
	/*if (codeSnippets != null && codeSnippets->pre != null) {
		codeSnippets = (*codeSnippets).pre;
	}*/
}

void jump2NextSnippet() {
	/*if (codeSnippets != null && codeSnippets->next != null) {
		codeSnippets = codeSnippets->next;
	}*/
}

void showCode() {
	/*CodeSnippet *p = codeSnippets;
	if (codeSnippets == null) {
		return;
	}

	// Seek to the head of code snippet list
	while (codeSnippets->pre != null) {
		p = codeSnippets->pre;
	}

	while (p != null) {
		printf("%d.\n%s\n\n", (*p).order, (*p).code->code);
		p = (*p).next;
	}*/
	sendPasteKey(true);
}

void registerDemoHotKey(HWND hWnd) {
	RegisterHotKey(hWnd, downId, 0, VK_UP);
	RegisterHotKey(hWnd, leftId, 0, VK_LEFT);
	RegisterHotKey(hWnd, upId, 0, VK_UP);
	RegisterHotKey(hWnd, rightId, 0, VK_RIGHT);
}

//
//   FUNCTION: OnHotKey(HWND, int, UINT, UINT)
//
//   PURPOSE: Process the WM_HOTKEY message. The WM_HOTKEY message is posted 
//   when the user presses a hot key registered by the RegisterHotKey 
//   function. The message is placed at the top of the message queue 
//   associated with the thread that registered the hot key. 
//
void OnHotKeyPressed(HWND hWnd, int idHotKey, UINT fuModifiers, UINT vk)
{
	switch (idHotKey)
	{
	case downId:
		showCode();
		break;
	case leftId:
		jump2PreSnippet();
		break;
	case rightId:
		jump2NextSnippet();
		break;
	case upId:
	default:
		printCode();
		break;
	}
}
void unregisterDemoHotKey(HWND hWnd) {
	UnregisterHotKey(hWnd, downId);
	UnregisterHotKey(hWnd, leftId);
	UnregisterHotKey(hWnd, rightId);
	UnregisterHotKey(hWnd, upId);
}