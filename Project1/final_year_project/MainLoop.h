#include "AdjustPixelsOnTheScreen.h"
#include "Shared.h"
#include "MouseHooker.h"

#pragma once

int MainLoop() {
    //the loop for the actions
    while (true) {
        if (keysPressed == keyCombo) {
            while (true) {
                //hooks for the mouse
                HHOOK mouseHooker = SetWindowsHookEx(WH_MOUSE_LL, MouseHooker, NULL, 0);
                //check if its hooked the mouse
                if (!mouseHooker) {
                    std::cout << "Failed to hook mouse" << std::endl;
                    return 1;
                }
                RECT selectedArea = { min(startPoint.x, endPoint.x), min(startPoint.y, endPoint.y),
                              max(startPoint.x, endPoint.x), max(startPoint.y, endPoint.y) };
                AdjustPixels(GetDC(NULL), selectedArea);
                //check if cords are sellected
                if (startPoint.x != NULL && startPoint.y != NULL && endPoint.x != NULL && endPoint.y != NULL) {
                    if (file.is_open()) {
                        file << "cords start x: " + startPoint.x;
                        file << "cords start y: " + startPoint.y;
                        file << "cords end x: " + endPoint.x;
                        file << "cords end y: " + endPoint.y;
                    }
                }
                //unhook the mouse we dont need it any more
                UnhookWindowsHookEx(mouseHooker);
                break;
            }
            //add some code here cuz its kind of empty

            break;
        }
    }
}
