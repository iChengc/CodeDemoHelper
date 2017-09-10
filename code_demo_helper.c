#ifdef __APPLE__
#include <sys/malloc.h>
#else
#include <malloc.h>
#endif
#include <stdio.h>
#include <string.h>

#include "code_snippet.h"
#include "utils.h"
#include "copy_code_to_clipboard.h"
#include "code_demo_helper.h"

/**
The Predefined Macros site has a very complete list of checks. Here are a few of them, with links to where they're found:

Windows

_WIN32   Both 32 bit and 64 bit
_WIN64   64 bit only

Unix (Linux, *BSD, Mac OS X)

See this related question on some of the pitfalls of using this check.

unix
__unix
__unix__

Mac OS X

__APPLE__
__MACH__

Both are defined; checking for either should work.

Linux

__linux__
linux
__linux

FreeBSD

__FreeBSD__
*/
CodeSnippet *codeSnippets;

/**
 * The callback method to be invoked when need to send fake paste hot keys(ctrl+V). 
 */
void(*sendPasteHotKey)();

// paste the code snippet, Called when "Up key" is pressed.
void pasteCode()
{
	if (codeSnippets == null) {
		return;
	}

	copyCode2clipboard(codeSnippets->code->code);
	if (sendPasteHotKey != null) {
		sendPasteHotKey();
	}
	if (codeSnippets->next == null) {
		// back to head.
		while (codeSnippets->pre != null) {
			codeSnippets = codeSnippets->pre;
		}
	}
	else {
		codeSnippets = codeSnippets->next;
	}
}

/**
 * switch to previous code snippet. Called when "left key" was pressed
 */
void jump2PreSnippet() {
	if (codeSnippets != null && codeSnippets->pre != null) {
		codeSnippets = (*codeSnippets).pre;
	}
}

/**
 * switch to next code snippet. Called when "right key" was pressed
 */
void jump2NextSnippet() {
	if (codeSnippets != null && codeSnippets->next != null) {
		codeSnippets = codeSnippets->next;
	}
}

/**
 * Showing all of the code snippets, called when "down key" was pressed
 */
CodeSnippet * showCode() {
	CodeSnippet *p = codeSnippets;
	if (codeSnippets == null) {
		return null;
	}

	// Seek to the head of code snippet list
	while (p->pre != null) {
		p = p->pre;
	}

	return p;
}

HotKeyCallBack * demo_start(char *filePath, int(*onRegisterHotKey)(),
	void (*onSendPasteHotKey)(), void (*onError)(char *))
{
	if (filePath == null || strlen(filePath) == 0) {
		if (onError != null) {
			onError("You must specify the file that save the code snippets!");
			return null;
		}
	}

	codeSnippets = parseFromFile(filePath);
	if (codeSnippets == null) {
		if (onError != null) {
			onError("No code was found!");
		}
		return null;
	}
	sendPasteHotKey = onSendPasteHotKey;
	if (onRegisterHotKey != null) {
		if (!onRegisterHotKey()) {
			onError("Can not register hot keys");
			return null;
		}
	}

	HotKeyCallBack *ret = malloc(sizeof(HotKeyCallBack));
	if (ret == null) {
		onError("Out of memory!");
		return null;
	}
	ret->next = &jump2NextSnippet;
	ret->pasteCode = &pasteCode;
	ret->previous = &jump2PreSnippet;
	ret->showCode = &showCode;
	return ret;
}
