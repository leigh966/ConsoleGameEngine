// ConsoleGameEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cmath>
#include <Windows.h>
#include <string.h>
#include <chrono>
#include <thread>
#include <cmath>
#include "Collision2D.h"

using namespace std;

const int SCREEN_WIDTH = 100, SCREEN_HEIGHT = 50;
const int MAP_WIDTH = 10, MAP_HEIGHT = 10;
const int FOV = 90;


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


void drawLineToScreen(int height, int x)
{

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
    vect->y = vect->x * sin(deg) + vect->y * cos(deg);
    vect->x = newX;
}

void drawLineToScreen(char screen[], int x, int lineSize)
{
    int gap = (SCREEN_HEIGHT - lineSize) / 2;
    for (int y = gap; y < SCREEN_HEIGHT - gap; y++)
    {
        screen[y * SCREEN_WIDTH + x] = '+' ;
    }
}

void drawScreen()
{
    char screen[SCREEN_WIDTH * SCREEN_HEIGHT];
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
    {
        screen[i] = ' ';
    }
    const float radiansFactor = 0.01745329f;
    float thetaPerStep = (float)FOV / (float)SCREEN_WIDTH * radiansFactor;
    float viewDistance = 10.0f;

    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
        Vector2D rayVector = { facing.x * viewDistance, facing.y * viewDistance };
        float theta = -(FOV / 2) + x * thetaPerStep;
        rotateVector(&rayVector, theta);
        for (int i = 0; i < 4; i++)
        {
            Collision2D col = Collision2D::LineLine(pos.x, pos.y, pos.x + rayVector.x, pos.y + rayVector.y, lines[i].x1, lines[i].y1, lines[i].x2, lines[i].y2);
            if (!col.getCollisionOccurred()) continue;
            // get the distance
            float* intersectionPointer = col.getIntersection();
            float intersectionX = *intersectionPointer;
            float intersectionY = *(intersectionPointer + 1);
            float dx = intersectionX - pos.x;
            float dy = intersectionY - pos.y;
            float distance = sqrt(dx * dx + dy * dy);

            // calc line height from distance
            int size = round((float)(SCREEN_HEIGHT) / distance);

            drawLineToScreen(screen, x, size);
        }
    }
    char buffer[SCREEN_WIDTH * 2 * SCREEN_HEIGHT + SCREEN_HEIGHT];
    int bufferIndex = 0;
    for (int y = 0; y < SCREEN_HEIGHT; y++)
    {
        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            buffer[bufferIndex++] = screen[y * SCREEN_WIDTH + x];
            buffer[bufferIndex++] = ' ';
        }
        buffer[bufferIndex++] = '\n';
    }
    cout << "\033[2J\033[1;1H" << buffer; // clear screen and draw from buffer
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
    while (keepGoing)
    {
        drawScreen();
        //drawMap();
        keepGoing = handleControls();
        //cout << "\nfacing.x=" << facing.x << endl;
        //cout << "facing.y=" << facing.y << endl;
        sleep_for(nanoseconds(1000));
    }
}
