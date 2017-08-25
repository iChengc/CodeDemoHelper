#include <stdlib.h>
#include <stdio.h>

#include "code_snippet.h"
#include "utils.h"
#include "register_hot_key.h"

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

// Call this when "Up key" is pressed.
void printCode()
{
 	if (codeSnippets == null) {
 		return;
 	}

 	copyCode2clipboard(codeSnippets->code->code);
 	
 	if (codeSnippets->next == null) {
 		// back to head.
 		while(codeSnippets->pre != null) {
 			codeSnippets = codeSnippets->pre;
 		}
 	} else {
 		codeSnippets = codeSnippets->next;
 	}
}

void jump2PreSnippet() {
	if (codeSnippets != null && codeSnippets->pre != null) {
		codeSnippets = (*codeSnippets).pre;
	}
}

void jump2NextSnippet() {
	if (codeSnippets != null && codeSnippets->next != null) {
		codeSnippets = codeSnippets->next;
	}
}

void showCode() {
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

void registerHotKeyCallback(HotKey key) {
	switch (key) {
		case KEY_S:
			showCode();
			break;
		case KEY_Up:
			printCode();
			break;
		case KEY_Left:
			jump2PreSnippet();
			break;
		case KEY_Right:
			jump2NextSnippet();
			break;
	}
}

int main()
{
    char fileName[100];
    char *divider="--------";

    printf("Please input the resource file name:");
    scanf("%s", fileName);
    codeSnippets = parseFromFile(fileName, divider);
    if (codeSnippets == null) {
    	return 0;
    }
    
	register_hot_key(&registerHotKeyCallback);
    return 0;
}