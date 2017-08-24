#include <stdio.h>
#if TARGET_OS_MAC
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
	return malloc((*remainingLen) * sizeof(char));
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
	if (code == null) {
		return;
	}

	remainingLen = code->totalLen - code->len;
	if (strlen(newCode) < remainingLen) {
		strcat(code->code, newCode);
	} else {
		t = expandMemory(code->totalLen, &remainingLen, newCode);
		memcpy(t, code->code, code->len);
		strcat(t, newCode);
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