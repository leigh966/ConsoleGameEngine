#include "Vector2D.h"
void rotateVector(Vector2D* vect, float deg)
{
    float newX = vect->x * cos(deg) - vect->y * sin(deg);
    vect->y = vect->x * sin(deg) + vect->y * cos(deg);
    vect->x = newX;
}