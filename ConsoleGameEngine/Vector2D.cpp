#include "Vector2D.h"
void Vector2D::rotateVector(Vector2D* vect, float deg)
{
    float newX = vect->x * cos(deg) - vect->y * sin(deg);
    vect->y = vect->x * sin(deg) + vect->y * cos(deg);
    vect->x = newX;
}

void Vector2D::normalize()
{
    float magnitude = sqrt(this->x * this->x + this->y * this->y);
    this->x /= magnitude;
    this->y /= magnitude;
}

void Vector2D::transform(float x, float y)
{
    this->x += x;
    this->y += y;
}