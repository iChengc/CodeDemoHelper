#ifndef _CODE_H_
#define _CODE_H_
#ifdef __cplusplus
extern "C" {
#endif
	typedef struct Code
	{
		char *code;
		int len;
		int totalLen;
	} Code;

	Code* createCode(char *c);

	void appendCode(Code *code, char *c);

	void freeCode(Code* code);

#ifdef __cplusplus
}
#endif

#endif