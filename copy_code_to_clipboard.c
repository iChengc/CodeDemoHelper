#include <string.h>
#include "copy_code_to_clipboard.h"

void copyCode2clipboard(char *code) {
	if (code == NULL) {
		return;
	}

	char *cacheFile = "./.cache";
#ifdef __APPLE__
	char *cpShell = "pbcopy ./.cache ";
#elif _WIN32
	char *cpShell = "clip < ./.cache ";
#else
	char *cpShell = "xclip -selection clipboard ./.cache ";
#endif

    // use a cache file to cache the code snippet, this is a workround approch
	FILE *fp = fopen(cacheFile, "w");
	if (fp == NULL) {
		return;
	}

	fwrite(code, sizeof(char), strlen(code), fp);
	fclose(fp);

    // use xclip tool to copy the code snippet to the system clipboard
	system(cpShell);
    // remove the cache file.
    system("rm ./.cache ");
}