//
//  MacHotKeyRegister.h
//  JFHotkeyManager
//
//  Created by Developer on 2017/8/25.
//
//

#ifndef MacHotKeyRegister_h
#define MacHotKeyRegister_h

#include <stdio.h>
typedef void (*CALLBACK)(int);

@interface Bridge : NSObject {
}

void registerHotKey(void (* func)(int));

@end

#endif /* MacHotKeyRegister_h */
