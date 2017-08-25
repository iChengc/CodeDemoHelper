//
//  MacHotKeyRegister.h
//  JFHotkeyManager
//
//  Created by Developer on 2017/8/25.
//
//

#ifndef BRIDGE_h
#define BRIDGE_h
#import <Cocoa/Cocoa.h>
#include <stdio.h>

@interface Bridge : NSObject  {
}

@end

void registerHotKey_bridge(void (* func)(int));
#endif /* MacHotKeyRegister_h */
