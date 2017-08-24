#include <stdlib.h>
#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#include <X11/extensions/XTest.h>
#include <unistd.h>

#include "xhklib.h"
#include "code_snippet.h"
#include "utils.h"

CodeSnippet *codeSnippets;

/*static void sendPastKey() {
 	Display *dis = XOpenDisplay(NULL);
    KeyCode ctlCode = 0, vCode; //init value
    ctlCode = XKeysymToKeycode(dis, XK_Control_L);
    XTestFakeKeyEvent(dis, ctlCode, True, 0);
    XFlush(dis);
    //sleep(1);
    vCode = XKeysymToKeycode(dis, XK_V);
    XTestFakeKeyEvent(dis, vCode, True, 0);
    usleep(500000);
    XFlush(dis);
    XTestFakeKeyEvent(dis, vCode, False, 0);
    XTestFakeKeyEvent(dis, ctlCode, False, 0);
    XFlush(dis);
}*/

static void sendKey (KeySym keysym, KeySym modsym) {
	Display * disp = XOpenDisplay(NULL); 
 	KeyCode keycode = 0, modcode = 0;
 	keycode = XKeysymToKeycode (disp, keysym);
 	if (keycode == 0) return; //init value

 	/* Generate modkey press */
 	if (modsym != 0) {
  		modcode = XKeysymToKeycode(disp, modsym);
  		XTestFakeKeyEvent (disp, modcode, True, 0);
 		XFlush(disp);
 	}
 	/* Generate regular key press and release */
 	XTestFakeKeyEvent (disp, keycode, True, 0);
 	usleep(500000);
    XFlush(disp);
	XTestFakeKeyEvent (disp, keycode, False, 0); 
 
 	/* Generate modkey release */
 	if (modsym != 0) {
 	 	XTestFakeKeyEvent (disp, modcode, False, 0);
 	}
 	XFlush(disp);
 	XCloseDisplay(disp);
}

static void copyCode2clipboard(char *code) {
	if (code == null) {
		return;
	}

	char *cacheFile = "./.cache";
	char *cpShell = "./cp.sh ./.cache ";

    // use a cache file to cache the code snippet, this is a workround approch
	FILE *fp = fopen(cacheFile, "w");
	if (fp == null) {
		return;
	}

	fwrite(code, sizeof(char), strlen(code), fp);
	fclose(fp);

    // use xclip tool to copy the code snippet to the system clipboard
	system(cpShell);
    // remove the cache file.
    system("rm ./.cache ");
}

// Call this when "H" is pressed.
void printCode(xhkEvent e, void *r1, void *r2, void *r3)
{
 	if (codeSnippets == null) {
 		return;
 	}

 	copyCode2clipboard(codeSnippets->code->code);
 	sendKey(XK_V, XK_Control_L);
 	if (codeSnippets->next == null) {
 		// back to head.
 		while(codeSnippets->pre != null) {
 			codeSnippets = codeSnippets->pre;
 		}
 	} else {
 		codeSnippets = codeSnippets->next;
 	}
}

void jump2PreSnippet(xhkEvent e, void *r1, void *r2, void *r3) {
	if (codeSnippets != null && codeSnippets->pre != null) {
		codeSnippets = (*codeSnippets).pre;
	}
}

void jump2NextSnippet(xhkEvent e, void *r1, void *r2, void *r3) {
	if (codeSnippets != null && codeSnippets->next != null) {
		codeSnippets = codeSnippets->next;
	}
}

void showCode(xhkEvent e, void *r1, void *r2, void *r3) {
	CodeSnippet *p = codeSnippets;
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
	}
}

int main()
{
    xhkConfig *hkconfig;
    char fileName[100];
    char *divider="--------";

    printf("Please input the resource file name:");
    scanf("%s", fileName);
    codeSnippets = parseFromFile(fileName, divider);
    if (codeSnippets == null) {
    	return 0;
    }
    hkconfig = xhkInit(NULL);
    xhkBindKey(hkconfig, 0, /*XK_Shift_L*/XK_Up, 0, xhkKeyPress, &printCode, 0, 0, 0);

    xhkBindKey(hkconfig, 0, XK_Left, 0, xhkKeyPress, &jump2PreSnippet, 0, 0, 0);

    xhkBindKey(hkconfig, 0, XK_Right, 0, xhkKeyPress, &jump2NextSnippet, 0, 0, 0);

    xhkBindKey(hkconfig, 0, XK_S, 0, xhkKeyPress, &showCode, 0, 0, 0);

    while (1) {
        xhkPollKeys(hkconfig, 1);
    }

    xhkClose(hkconfig);

    return 0;
}