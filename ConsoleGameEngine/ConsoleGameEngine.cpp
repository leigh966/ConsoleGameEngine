// ConsoleGameEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cmath>
#include <Windows.h>
#include <string.h>
#include <chrono>
#include <thread>
#include <cmath>

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
    float x, y;
};

Vector2D pos = { 5.0f,5.0f };
Vector2D facing = { 0.0f, -1.0f};

int roundToInt(float f)
{
    return round(f);
}


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
    map[roundToInt(pos.y) * MAP_WIDTH + roundToInt(pos.x)] = 'p';

    // draw player facing vector
    int facingMarkerX = roundToInt(pos.x) + roundToInt(facing.x);
    int facingMarkerY = roundToInt(pos.y) + roundToInt(facing.y);
    map[facingMarkerY * MAP_WIDTH + facingMarkerX] = '+';

    char buffer[MAP_WIDTH*2 * MAP_HEIGHT + MAP_HEIGHT];
    int bufferIndex = 0;
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            buffer[bufferIndex++] = map[y * MAP_WIDTH + x];
            buffer[bufferIndex++] = ' ';
        }
        buffer[bufferIndex++] = '\n';
    }
    cout << "\033[2J\033[1;1H" << buffer; // clear screen and draw from buffer
}

bool keyDown(char keyCode)
{
    return GetKeyState(keyCode) & 0x8000;
}

void rotateVector(Vector2D* vect, float deg)
{
    float newX = vect->x * cos(deg) - vect->y * sin(deg);
    float newY = vect->x * sin(deg) + vect->y * cos(deg);
    vect->x = newX;
    vect -> y = newY;
}

bool handleControls()
{
    const float speed = 0.1f;
    if (keyDown('Q'))
    {
        return false;
    }
    if (keyDown('W'))
    {
        pos.x += facing.x * speed;
        pos.y += facing.y * speed;
    }
    if (keyDown('S'))
    {
        pos.x -= facing.x * speed;
        pos.y -= facing.y * speed;
    }
    if (keyDown('A'))
    {
        pos.x -= facing.y * speed;
        pos.y -= facing.x * speed;
    }
    if (keyDown('D'))
    {
        pos.x += facing.y * speed;
        pos.y += facing.x * speed;
    }

    const float turnSpeed = 0.1f;
    if (keyDown('P'))
    {
        rotateVector(&facing, turnSpeed);
    }
    if (keyDown('O'))
    {
        rotateVector(&facing, -turnSpeed);
    }
    return true;
}

int main()
{
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds
    
    bool keepGoing = true;
    drawMap();
    while (keepGoing)
    {
        drawMap();
        keepGoing = handleControls();
        cout << "\nfacing.x=" << facing.x << endl;
        cout << "facing.y=" << facing.y << endl;
        sleep_for(nanoseconds(1000));
    }
}
