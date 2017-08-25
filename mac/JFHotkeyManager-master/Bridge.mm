//
//  MacHotKeyRegister.c
//  JFHotkeyManager
//
//  Created by Developer on 2017/8/25.
//
//

#include "Bridge.h"
#include "JFHotkeyManager.h"

@implementation Bridge {
    CALLBACK callback;
}

void registerHotKey(void (*func)(int)) {
    callback = func;
    JFHotkeyManager *hkm = [[JFHotkeyManager alloc] init];
#ifdef MAC_OS_X_VERSION_10_3
    int id = 0;
#else
    int id = 49;
#endif
    
    // Bind using key code and modifiers
    [hkm bindKeyRef:id withModifiers: kVK_LeftArrow target:self action:@selector(leftkeyClicked)];
    
    // Bind using key code and modifiers
    [hkm bindKeyRef:id withModifiers:kVK_RightArrow target:self action:@selector(rightkeyClicked)];
    // Bind using key code and modifiers
    [hkm bindKeyRef:id withModifiers:kVK_UpArrow target:self action:@selector(upkeyClicked)];
    // Bind using key code and modifiers
    [hkm bindKeyRef:id withModifiers:kVK_DownArrow target:self action:@selector(downkeyClicked)];
    
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
@end
