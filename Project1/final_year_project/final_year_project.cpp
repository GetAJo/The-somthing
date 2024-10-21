#include "AdjustPixelsOnTheScreen.h"
#include "Shared.h"
#include "MouseHooker.h"
#include "MainLoop.h"
#include "KeyBoardHooker.h"

#pragma comment (lib, "gdiplus.lib")



int main() {
    //open the Gdiplus for some fun
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    //hook for the keyboard
    HHOOK keyboardHooker = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHooker, NULL, 0);


    //check if its hooked the keyboard
    if (!keyboardHooker) {
        std::cout << "Failed to hook keyboard" << std::endl;
        return 2;
    }

    int doesItReurnError = MainLoop();

    //close the Gdiplus cuz its no longer fun
    Gdiplus::GdiplusShutdown(gdiplusToken);
    //unhook and close the loop keyboard and mouse
    UnhookWindowsHookEx(keyboardHooker);
    if (doesItReurnError != 0) {
        //if there is a error there will shall not return 0 so every difrent number is a difrent error to the code at the bottom is a decription there what every return means
        return doesItReurnError;
    }
    return 0; //returns 0
}
/*
if its a 0 its all good
if its a 1 its a mouse hookup gone wrong
if its a 2 its a keyboard hookup gone wrong
*/
