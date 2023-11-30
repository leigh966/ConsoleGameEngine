#pragma once
#include<cmath>
float getDistance(float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}

int roundToInt(float f)
{
    return round(f);
}