#include "win_key.h"
#include <windows.h>  
#include <stdio.h>  
#include "win_key_core.h"
void (*callback)(HotKey);
 
void winKeyCode(int keyCode) {
	if (cal == NULL) {
		return;
	}
	
	switch (keyCode) {
		case 0:
			func(Key_Up);
			break;
		case 1:
			func(Key_Down);
			break;
		case 2:
			func(Key_Left);
			break;
		case 3:
			func(Key_Right);
			break;
	}
}

void win_register_hot_key(void (*func)(HotKey))  
{  
    HINSTANCE hDll;  
    typedef void (*Fun)(void (*f)(int));  
    Fun fp;
	callback = func;
    hDll = LoadLibrary("winKeyCore.dll");  
	
    if(NULL == hDll)  
    {  
        fprintf(stderr, "load dll 'winKeyCore.dll' fail.");  
        return;  
    }  
  
    fp = (Fun)GetProcAddress(hDll, "register_hot_key");  
    if(NULL == fp)  
    {  
        fprintf(stderr, "call function 'register_hot_key' fail.");  
        FreeLibrary(hDll);  
        return;  
    }  
  
	fp(f);
    FreeLibrary(hDll);  
}

void win_send_key()
{  
    HINSTANCE hDll;  
    typedef void (*Fun)();  
    Fun fp;
    hDll = LoadLibrary("winKeyCore.dll");  
	
    if(NULL == hDll)  
    {  
        fprintf(stderr, "load dll 'winKeyCore.dll' fail.");  
        return;  
    }  
  
    fp = (Fun)GetProcAddress(hDll, "send_key");  
    if(NULL == fp)  
    {  
        fprintf(stderr, "call function 'send_key' fail.");  
        FreeLibrary(hDll);  
        return;  
    }  
  
	fp();
    FreeLibrary(hDll);  
} 