
#include <stdio.h>
#ifdef __APPLE__
#include <sys/malloc.h>
#else
#include <malloc.h>
#endif
#include <string.h>

#include "code.h"
#include "utils.h"

char* expandMemory(int originLen, int *remainingLen, char* newCode) {
	if (newCode != null && strlen(newCode) > *remainingLen) {
		*remainingLen = originLen + strlen(newCode) + 1024 - *remainingLen;
	}
	char * ret = malloc((*remainingLen) * sizeof(char));
	memset(ret, 0, (*remainingLen) * sizeof(char));
	return ret;
}

Code* createCode(char *code) {
	Code *c;
	int codeLen = 1024;
	c = malloc(sizeof(Code));
	c->code = expandMemory(0, &codeLen, code);
	c->totalLen = codeLen;
	c->len = code == null ? 0 : strlen(code);
	return c;
}

void appendCode(Code *code, char *newCode) {
	int remainingLen;
	char *t;
	int legthOfCode = strlen(newCode);
	if (code == null) {
		return;
	}

	remainingLen = code->totalLen - code->len;
	
	if (legthOfCode < remainingLen) {
#ifdef _WIN32
		strcat_s(code->code, code->totalLen, newCode);
#else
		strcat(code->code, newCode);
#endif // _WIN32
	} else {
		t = expandMemory(code->totalLen, &remainingLen, newCode);
		memcpy(t, code->code, code->len);
#ifdef _WIN32
		strcat_s(t, remainingLen, newCode);
#else
		strcat(t, newCode);
#endif // _WIN32
		freeCode(code);
		code->code = t;
		code->totalLen = remainingLen;
	}
	code->len = strlen(code->code);
}

void freeCode(Code *code) {
	if (code == null) {
		return;
	}

	free(code->code);
}