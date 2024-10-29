#include <iostream>
#include <string> 
#include <vector>
#include <windows.h>
#include <fstream> 
#include <gdiplus.h>
#include <gdiplusinit.h>

#pragma once
// somthing like a class to shere the data
#ifndef SHARED_H
#define SHARED_H
//pointers
POINT startPoint, endPoint;
bool draged = false;
std::vector<int> keysPressed;
//the comindation of the keys pressed for the action keys are reccorded in ascii
std::vector<int> keyCombo = {160,162,164,191 };
//make a file for the cords to be read from the other code
std::ofstream file("selectedCordsOfTheUser.txt");
//the juals
std::string memTarhet;

#endif 
