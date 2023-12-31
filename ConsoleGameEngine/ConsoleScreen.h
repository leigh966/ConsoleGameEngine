#pragma once
#include "ImageGrid.h"
#include "Vector2D.h"
#include "Collision2D.h"
#include "Line.h"
#include <iostream>
#include "Vector2D.h"
#include "ConsoleMap.h"
using namespace std;

const int SCREEN_WIDTH = 150, SCREEN_HEIGHT = 50;
const int screenArraySize = SCREEN_WIDTH * SCREEN_HEIGHT;

const int FOV = 90;

void drawLineToScreen(char screen[], int x, int lineSize)
{
    int gap = (SCREEN_HEIGHT - lineSize) / 2;
    for (int y = gap; y < SCREEN_HEIGHT - gap; y++)
    {
        screen[y * SCREEN_WIDTH + x] = '+';
    }
}

void raycastToScreen(Vector2D pos, Vector2D facing, Line lines[], char* screen)
{
    const float radiansFactor = 0.01745329f;
    float thetaPerStep = (float)FOV / (float)SCREEN_WIDTH * radiansFactor;
    float viewDistance = 10.0f;
    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
        Vector2D rayVector = { facing.x * viewDistance, facing.y * viewDistance };
        float theta = -(FOV / 2) + x * thetaPerStep;
        Vector2D::rotateVector(&rayVector, theta);
        for (int i = 0; i < 4; i++)
        {
            Collision2D col = Collision2D::LineLine(pos.x, pos.y, pos.x + rayVector.x, pos.y + rayVector.y, lines[i].x1, lines[i].y1, lines[i].x2, lines[i].y2);
            if (!col.getCollisionOccurred()) continue;
            // get the distance
            float* intersectionPointer = col.getIntersection();
            float intersectionX = *intersectionPointer;
            float intersectionY = *(intersectionPointer + 1);
            float distance = getDistance(pos.x, pos.y, intersectionX, intersectionY);

            // calc line height from distance
            int size = round((float)(SCREEN_HEIGHT) / distance);
            if (size >= SCREEN_HEIGHT) size = SCREEN_HEIGHT - 1;
            if (size>0) drawLineToScreen(screen, x, size);
        }
    }
}

void outputScreen(char* screen)
{
    char buffer[SCREEN_WIDTH * 2 * SCREEN_HEIGHT + SCREEN_HEIGHT];
    drawToBuffer(screen, buffer, SCREEN_WIDTH, SCREEN_HEIGHT);
    cout << "\033[2J\033[1;1H" << buffer; // clear screen and draw from buffer
    //cout << "\r" << buffer << flush; // possible alternative for high resolutions but causes almost CRT style wobble
}

void drawScreen(Vector2D pos, Vector2D facing, Line lines[])
{
    char screen[screenArraySize];
    initializeCharArray(screen, screenArraySize, ' ');

    raycastToScreen(pos, facing, lines, screen);

    outputScreen(screen);
}


void drawScreenWithMap(Vector2D pos, Vector2D facing, Line lines[])
{
    char screen[screenArraySize];
    initializeCharArray(screen, screenArraySize, ' ');

    raycastToScreen(pos, facing, lines, screen);

    // draw map to screen
    char* map = getMap(pos, facing, lines);
    drawImageOntoArray(screen, SCREEN_WIDTH, SCREEN_HEIGHT, map, MAP_WIDTH, MAP_HEIGHT, 0, 0);

    outputScreen(screen);

}