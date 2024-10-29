#include "AdjustPixelsOnTheScreen.h"
#include "Shared.h"
#include "MouseHooker.h"
#include <tuple>

#pragma once

void CordsReturnTXT() {
    if (file.is_open()) {
        file << "cords start x: " + std::to_string(startPoint.x) << std::endl;
        file << "cords start y: " + std::to_string(startPoint.y) << std::endl;
        file << "cords end x: " + std::to_string(endPoint.x) << std::endl;
        file << "cords end y: " + std::to_string(endPoint.y) << std::endl;
    }
}

std::tuple<HHOOK, int> MouseH() {
    HHOOK mouseHooker = SetWindowsHookEx(WH_MOUSE_LL, MouseHooker, NULL, 0);
    if (!mouseHooker) {
        std::cout << "Failed to hook mouse" << std::endl;
        exit(0);  // Program exits, no need for return after this
    }
    return std::make_tuple(mouseHooker, 0);
}

int MainLoop() {
    while (true) {
        if (keysPressed == keyCombo) {
            while (true) {
                auto val = MouseH();
                HHOOK mouseHooker = std::get<0>(val);
                RECT selectedArea = { 
                    min(startPoint.x, endPoint.x), 
                    min(startPoint.y, endPoint.y),
                    max(startPoint.x, endPoint.x), 
                    max(startPoint.y, endPoint.y) 
                };
                AdjustPixels(GetDC(NULL), selectedArea);

                if (startPoint.x != NULL && startPoint.y != NULL && endPoint.x != NULL && endPoint.y != NULL) {
                    CordsReturnTXT();
                }

                UnhookWindowsHookEx(mouseHooker);
                break;
            }

            // Additional logic can be added here

            break;
        }
    }
    return 0;  // Add a return value for MainLoop
}
