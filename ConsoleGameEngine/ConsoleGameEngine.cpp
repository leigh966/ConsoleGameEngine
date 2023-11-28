// ConsoleGameEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cmath>
#include <Windows.h>
#include <string.h>

using namespace std;

const int WIDTH = 119, HEIGHT = 119;
const int MAP_WIDTH = 10, MAP_HEIGHT = 10;
const int FOV = 90;
char screen[WIDTH*HEIGHT];

struct Line
{
    int x1, y1, x2, y2;
};

const int LEFT = 0, RIGHT = MAP_WIDTH - 1, TOP = 0, BOTTOM = MAP_HEIGHT-1;

Line lines[4] = { {LEFT, BOTTOM, RIGHT, BOTTOM},{LEFT, TOP, RIGHT, TOP},
    {LEFT, TOP, LEFT, BOTTOM},{RIGHT, TOP, RIGHT, BOTTOM} };

struct Vector2D
{
    int x, y;
};

Vector2D pos = { 5,5 };
Vector2D facing = { 1, 0};

void drawMap()
{
    //initialise map
    char map[MAP_WIDTH * MAP_HEIGHT];
    for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++)
    {
        map[i] = ' ';
    }

    // draw lines
    for (int i = 0; i < 4; i++)
    {
        for (int x = lines[i].x1; x<=lines[i].x2 ;x++)
        {
            for (int y = lines[i].y1; y <=lines[i].y2; y++)
            {
                map[y * MAP_WIDTH + x] = '~';
            }
        }
    }

    // draw player
    map[pos.y * MAP_WIDTH + pos.x] = 'p';

    // draw player facing vector
    map[(pos.y + facing.y) * MAP_WIDTH + (pos.x + facing.x)] = '+';
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            cout << map[y * MAP_WIDTH + x];
            cout << ' ';
        }
        cout << "\n";
    }
}

int main()
{
    drawMap();
}
