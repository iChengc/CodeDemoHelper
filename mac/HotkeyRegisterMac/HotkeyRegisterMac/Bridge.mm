//
//  MacHotKeyRegister.c
//  JFHotkeyManager
//
//  Created by Developer on 2017/8/25.
//
//

#include "Bridge.h"
#include "JFHotkeyManager.h"


void (*callback)(int);

@implementation Bridge
    -(void) registerkey {
        JFHotkeyManager *hkm = [[JFHotkeyManager alloc] init];
    #ifdef MAC_OS_X_VERSION_10_3
        int ref = 0;
    #else
        int ref = 49;
    #endif
                
        // Bind using key code and modifiers
        [hkm bindKeyRef:ref withModifiers: kVK_LeftArrow target:self action:@selector(leftkeyClicked1)];
                
        // Bind using key code and modifiers
        [hkm bindKeyRef:ref withModifiers:kVK_RightArrow target:self action:@selector(rightkeyClicked)];
        // Bind using key code and modifiers
        [hkm bindKeyRef:ref withModifiers:kVK_UpArrow target:self action:@selector(upkeyClicked)];
        // Bind using key code and modifiers
        [hkm bindKeyRef:ref withModifiers:kVK_DownArrow target:self action:@selector(downkeyClicked)];
    }
                     

@end

void leftkeyClicked1 () {
    if (nil != callback) {
        callback(2);
    }
    
}
void registerHotKey_bridge(void (*func)(int)) {
    callback = func;
    Bridge *bridge = [[Bridge alloc] init];
    [bridge registerkey];
}


void upkeyClicked() {
    if (nil != callback) {
        callback(0);
    }
}
void downkeyClicked() {
    if (nil != callback) {
        callback(1);
    }
    
}
void leftkeyClicked() {
    if (nil != callback) {
        callback(2);
    }
    
}
void rightkeyClicked() {
    if (nil != callback) {
        callback(3);
    }
    
}
