#include "Shared.h"

#pragma once
//hook keyboard
LRESULT CALLBACK KeyboardHooker(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* kbStruct = (KBDLLHOOKSTRUCT*)lParam;

        // Check if a key was pressed
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            keysPressed.push_back(kbStruct->vkCode);
        }

        // check if relece
        if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) {
            keysPressed.erase(std::remove(keysPressed.begin(), keysPressed.end(), kbStruct->vkCode), keysPressed.end());
        }
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}
