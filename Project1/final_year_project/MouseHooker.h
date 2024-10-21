#include "Shared.h"

#pragma once

//hook mouse
LRESULT CALLBACK MouseHooker(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        MSLLHOOKSTRUCT* mouseStruct = (MSLLHOOKSTRUCT*)lParam;

        if (wParam == WM_LBUTTONDOWN) {
            // capture point start
            draged = true;
            startPoint = mouseStruct->pt;
        }

        if (wParam == WM_LBUTTONUP && draged) {
            // capture point end
            endPoint = mouseStruct->pt;
            draged = false;
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}
