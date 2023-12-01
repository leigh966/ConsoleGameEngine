#pragma once
#include <iostream>
#include "ImageGrid.h"
#include "Vector2D.h"
#include "ConsoleEngineMath.h"
#include "Line.h"
using namespace std;

const int MAP_WIDTH = 10, MAP_HEIGHT = 10;

void drawLinesToMap(char map[], Line lines[], int numberOfLines)
{
    // draw lines
    for (int i = 0; i < numberOfLines; i++)
    {
        for (int x = lines[i].x1; x <= lines[i].x2; x++)
        {
            for (int y = lines[i].y1; y <= lines[i].y2; y++)
            {
                map[y * MAP_WIDTH + x] = '~';
            }
        }
    }
}

bool posOnMap(int x, int y)
{
    return x > 0 && y > 0 && x < MAP_WIDTH && y < MAP_HEIGHT;
}

const int mapArraySize = MAP_WIDTH * MAP_HEIGHT;
char* getMap(Vector2D pos, Vector2D facing, Line lines[])
{
    //initialise map
    char map[mapArraySize];

    initializeCharArray(map, mapArraySize, ' ');

    drawLinesToMap(map, lines, 4);

    // draw player
    if (posOnMap(pos.x, pos.y))
    {
        int playerIndex = roundToInt(pos.y) * MAP_WIDTH + roundToInt(pos.x);
        map[playerIndex] = 'p';
    }

    // draw player facing vector
    int facingMarkerX = roundToInt(pos.x) + roundToInt(facing.x);
    int facingMarkerY = roundToInt(pos.y) + roundToInt(facing.y);
    if (posOnMap(facingMarkerX, facingMarkerY))
    {
        int facingMarkerIndex = facingMarkerY * MAP_WIDTH + facingMarkerX;
        map[facingMarkerIndex] = '+';
    }
    return map;
}

void drawMap(Vector2D pos, Vector2D facing, Line lines[])
{
    char* map = getMap(pos, facing, lines);
    char buffer[MAP_WIDTH * 2 * MAP_HEIGHT + MAP_HEIGHT];
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
    delete map;
}

