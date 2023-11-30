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

void drawMap(Vector2D pos, Vector2D facing, Line lines[])
{
    //initialise map
    char map[MAP_WIDTH * MAP_HEIGHT];
    initializeCharArray(map, MAP_WIDTH * MAP_HEIGHT, ' ');

    drawLinesToMap(map, lines, 4);

    // draw player
    map[roundToInt(pos.y) * MAP_WIDTH + roundToInt(pos.x)] = 'p';

    // draw player facing vector
    int facingMarkerX = roundToInt(pos.x) + roundToInt(facing.x);
    int facingMarkerY = roundToInt(pos.y) + roundToInt(facing.y);
    map[facingMarkerY * MAP_WIDTH + facingMarkerX] = '+';

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
}

