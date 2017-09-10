#ifndef _CODE_DEMO_HELPER_
#define _CODE_DEMO_HELPER_
#include "code_snippet.h"
#ifdef __cplusplus
extern "C" {
#endif
	typedef struct _HotKeyCallBack {
		CodeSnippet *(*showCode)();
		void(*next)();
		void(*previous)();
		void(*pasteCode)();
	} HotKeyCallBack;

	HotKeyCallBack * demo_start(char *filePath, int(*onRegisterHotKey)(),
		void(*onSendPasteHotKey)(), void(*onError)(char *));

#ifdef __cplusplus
}
#endif

#endif // _CODE_DEMO_HELPER_

