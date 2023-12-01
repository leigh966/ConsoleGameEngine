// ConsoleGameEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "main.h"
using namespace std;

const int LEFT = 0, RIGHT = MAP_WIDTH - 1, TOP = 0, BOTTOM = MAP_HEIGHT-1;

Line lines[4] = { {LEFT, BOTTOM, RIGHT, BOTTOM},{LEFT, TOP, RIGHT, TOP},
    {LEFT, TOP, LEFT, BOTTOM},{RIGHT, TOP, RIGHT, BOTTOM} };

Vector2D pos = { 5.0f,5.0f };
Vector2D facing = { 0.0f, -1.0f};

void setFont()
{
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;                   // Width of each character in the font
    cfi.dwFontSize.Y = 10;                  // Height
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, L"Consolas"); // Choose your font
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

    std::cout << "Font: Consolas, Size: 24\n";
}

int main()
{
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds
    setFont();
    bool keepGoing = true;
    while (keepGoing)
    {
        drawScreenWithMap(pos, facing, lines);
        //drawMap(pos, facing, lines);
        keepGoing = handleControls(&pos,&facing);
        //cout << "\nfacing.x=" << facing.x << endl;
        //cout << "facing.y=" << facing.y << endl;
        sleep_for(nanoseconds(1000));
    }
}
