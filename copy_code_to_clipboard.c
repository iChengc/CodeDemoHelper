#include <string.h>
#include <stdlib.h>
#include "copy_code_to_clipboard.h"
#include "utils.h"

#ifdef _WIN32
#include<windows.h>
#endif // _WIN32

void copyCode2clipboard(char *code) {

	if (code == NULL) {
		return;
	}

#ifdef __APPLE__
	char *cacheFile = "./.cache";
	char *cpShell = "pbcopy ./.cache ";
#elif _WIN32
	char *cacheFile = ".\\.cache";
	char *cpShell = "clip < .\\.cache ";
#else
	char *cacheFile = "./.cache";
	char *cpShell = "xclip -selection clipboard ./.cache ";
#endif

    // use a cache file to cache the code snippet, this is a workround approch
	FILE *fp = null;
#ifdef _WIN32
	fopen_s(&fp, cacheFile, "w+");
#else
	fp = fopen(cacheFile, "w");
#endif // _WIN32
	if (fp == NULL) {
		return;
	}

	fwrite(code, sizeof(char), strlen(code), fp);
	fclose(fp);
#ifdef _WIN32
	//system(cpShell);
	//system("DEL -F .\\.cache ");
	ShellExecute(null, "open", cpShell, null, null, SW_HIDE);
	ShellExecute(null, "open", "DEL -F .\\.cache ", null, null, SW_HIDE);
#else
	// use xclip tool to copy the code snippet to the system clipboard
	system(cpShell);
	// remove the cache file.
	system("rm ./.cache ");
#endif // _WIN32
}
