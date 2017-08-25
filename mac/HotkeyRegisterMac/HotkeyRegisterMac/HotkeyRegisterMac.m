//
//  HotkeyRegisterMac.m
//  HotkeyRegisterMac
//
//  Created by Developer on 2017/8/25.
//  Copyright © 2017年 Developer. All rights reserved.
//

#include "Bridge.h"
#include "HotkeyRegisterMac.h"

void registerHotKey(void (* func)(int)) {
    registerHotKey_bridge(func);
}
