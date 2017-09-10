#include <stdlib.h>
#include <stdio.h>

#include "code_snippet.h"
#include "utils.h"
#include "register_hot_key.h"
#include "xhklib.h"
#include "copy_code_to_clipboard.h"
#include "send_key_event.h"

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

// Call this when "Up key" is pressed.
void pc()
{
 	if (codeSnippets == null) {
 		return;
 	}

 	copyCode2clipboard(codeSnippets->code->code);
 	sendPasteKeyEvent();
 	if (codeSnippets->next == null) {
 		// back to head.
 		while(codeSnippets->pre != null) {
 			codeSnippets = codeSnippets->pre;
 		}
 	} else {
 		codeSnippets = codeSnippets->next;
 	}
}

void pre() {
	if (codeSnippets != null && codeSnippets->pre != null) {
		codeSnippets = (*codeSnippets).pre;
	}
}

void nxt() {
	if (codeSnippets != null && codeSnippets->next != null) {
		codeSnippets = codeSnippets->next;
	}
}

void sc() {
	CodeSnippet *p = codeSnippets;
	if (codeSnippets == null) {
		return;
	}

	// Seek to the head of code snippet list
	while (p->pre != null) {
		p = p->pre;
	}

	while (p != null) {
		printf("%d.\n%s\n\n", (*p).order, (*p).code->code);
		p = (*p).next;
	}
}

void registerHotKeyCallback(HotKey key) {
	switch (key) {
		case KEY_Down:
			sc();
			break;
		case KEY_Up:
			pc();
			break;
		case KEY_Left:
			pre();
			break;
		case KEY_Right:
			nxt();
			break;
	}
}

int main()
{
    char fileName[100];

    printf("Please input the resource file name:");
    scanf("%s", fileName);
    codeSnippets = parseFromFile(fileName);
    if (codeSnippets == null) {
    	return 0;
    }
    
    register_hot_key(&registerHotKeyCallback);
    return 0;
}
