#include <stdio.h>
#include "utils.h"
#include <string.h>
#ifdef TARGET_OS_MAC
#include <sys/malloc.h>
#else
#include <malloc.h>
#endif

#include "code_snippet.h"
#include "code.h"

static void codeSnippetWasFound(CodeSnippet** p, Code* code) {
	CodeSnippet *t = *p, *cs = malloc(sizeof(CodeSnippet));
	cs->code = code;
	if (t == null) {
		cs->order = 1;
		cs->pre = null;
		*p = cs;
	} else {
		while(t->next != null) {
			t = t->next;
		}
		cs->pre = t;
		cs->order = t->order + 1;
		t->next = cs;
	}
}

CodeSnippet* parseFromFile(char *fileName, char *divider) {
	// FILE * fopen(const char * path, const char * mode);
	char line[1024];
	CodeSnippet* ret = null;
	Code *code = createCode(NULL);

	if (divider == null) {
		printf("You must specify divider.\n");
		return null;
	}
	
	FILE *fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("Can not open file:%s.\n", fileName);
		return null;
	}

	// size_t fread ( void *buffer, size_t size, size_t count, FILE *stream) ;
	while (!feof(fp)) 
    {
        fgets(line, 1024, fp);  //读取一行
        // printf("%s\n", line);

        // Remove the last \n character
        if (line[strlen(line) - 1] == '\n') {
        	line[strlen(line) - 1] = '\0';
        }

        if (strcmp(divider, line) == 0) {
        	codeSnippetWasFound(&ret, code);
        	code = createCode(NULL);
        	line[0] = '\0';
        } else {
    		line[strlen(line)] = '\n';
        	appendCode(code, line);
        }
    }

    if (strlen(line) > 0) {
    	line[strlen(line)] = '\n';
        codeSnippetWasFound(&ret, code);
    }

	fclose(fp);
	return ret;
}