#ifndef _CODE_H_
#define _CODE_H_

typedef struct Code
{
	char *code;
	int len;
	int totalLen;
} Code;

Code* createCode(char *c);

void appendCode(Code *code, char *c);

void freeCode(Code* code);

#endif