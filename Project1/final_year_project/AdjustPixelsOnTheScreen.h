#include "Shared.h"

#pragma once
void AdjustPixels(HDC hdc, RECT selectedArea) {
    //screen Width and Hight
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    //screen capture
    HDC hdcScreen = GetDC(NULL);
    HDC hdcMem = CreateCompatibleDC(hdcScreen);
    HBITMAP hBitmap = CreateCompatibleBitmap(hdcScreen, screenWidth, screenHeight);
    SelectObject(hdcMem, hBitmap);

    //set to the mem 
    BitBlt(hdcMem, 0, 0, screenWidth, screenHeight, hdcScreen, 0, 0, SRCCOPY);

    //pixel data
    BITMAPINFO bmi = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = screenWidth;
    bmi.bmiHeader.biHeight = -screenHeight;  //negative to keep right side up
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    std::vector<COLORREF> pixels(screenWidth * screenHeight);
    GetDIBits(hdcMem, hBitmap, 0, screenHeight, &pixels[0], &bmi, DIB_RGB_COLORS);

    //do it for all pixel
    for (int y = 0; y < screenHeight; ++y) {
        for (int x = 0; x < screenWidth; ++x) {
            int index = y * screenWidth + x;
            COLORREF pixel = pixels[index];

            //RGB values
            int red = GetRValue(pixel);
            int green = GetGValue(pixel);
            int blue = GetBValue(pixel);

            //lighten the pixel
            if (x >= selectedArea.left && x <= selectedArea.right &&
                y >= selectedArea.top && y <= selectedArea.bottom) {
                red = min(255, red + 20);
                green = min(255, green + 20);
                blue = min(255, blue + 20);
            }
            //darken the pixel
            else {
                red = max(0, red - 50);
                green = max(0, green - 50);
                blue = max(0, blue - 50);
            }

            //set the new pixel value
            pixels[index] = RGB(red, green, blue);
        }
    }
    //aplay the hdc
    SetDIBits(hdcMem, hBitmap, 0, screenHeight, &pixels[0], &bmi, DIB_RGB_COLORS);

    //draw it on the scr
    BitBlt(hdcScreen, 0, 0, screenWidth, screenHeight, hdcMem, 0, 0, SRCCOPY);

    //clean the mem cuz mem its not inf
    DeleteObject(hBitmap);
    DeleteDC(hdcMem);
    ReleaseDC(NULL, hdcScreen);
}
