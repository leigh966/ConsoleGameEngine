#pragma once
#include <cmath>
class Vector2D
{
public:
    float x, y;
    static void rotateVector(Vector2D* vect, float deg);
    void normalize();
    void transform(float x, float y);
};
