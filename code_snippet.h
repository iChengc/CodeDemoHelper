#ifndef _CODE_SNIPPET_H_
#define _CODE_SNIPPET_H_
#include "code.h"

typedef struct CS {
	int order;
	Code *code;
	struct CS *next;
	struct CS *pre;
} CodeSnippet;

/**
 * Parse the code snippet from a specify file.
 *
 * @param fileName the name of the file.
 * @divider the divider of the code snippet
 */
CodeSnippet* parseFromFile(char *fileName);

#endif