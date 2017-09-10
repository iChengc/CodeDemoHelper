#include <stdlib.h>
#include <stdio.h>

#include "code_snippet.h"
#include "utils.h"
#include "code_demo_helper.h"
#include "unix_hot_keys.h"

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
HotKeyCallBack * callback;
void onShowCode(CodeSnippet *p) {
	while (p != null) {
		printf("%d.\n%s\n\n", (*p).order, (*p).code->code);
		p = (*p).next;
	}
}


void onHotKey(xhkEvent e, void *r1, void *r2, void *r3) {
    if (callback == null) {
        return;
    }

    switch(e.keycode) {
        case XK_Up:
	    callback->pasteCode();
	    break;
        case XK_Left:
	    callback->previous();
	    break;
        case XK_Right:
	    callback->next();
	    break;
        case XK_Down:
	    onShowCode(callback->showCode());
	    break;
    }
}

int onRegisterHotKeys() {
    return registerUnixHotKeys(&onHotKey);
}

void onError(char *msg) {
    printf("Error occured:%s", msg);
}

int main()
{
    char fileName[100];

    printf("Please input the resource file name:");
    scanf("%s", fileName);
    callback = demo_start(fileName, &onRegisterHotKeys, &sendPasteKeyEvent, &onError);
    pollUnixHotKeys();
    return 0;
}
