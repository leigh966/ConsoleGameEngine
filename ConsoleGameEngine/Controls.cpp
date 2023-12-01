#include "Controls.h"

bool keyDown(char keyCode)
{
    return GetKeyState(keyCode) & 0x8000;
}


void moveForward(Vector2D* pos, Vector2D* facing, float speed)
{
    
    pos->x += facing->x * speed;
    pos->y += facing->y * speed;
}

void moveRight(Vector2D* pos, Vector2D* facing, float speed)
{
    Vector2D right = *facing;
    Vector2D::rotateVector(&right, 3.14/2);
    moveForward(pos, &right, speed);
}

bool handleControls(Vector2D* pos, Vector2D* facing)
{
    const float speed = 0.1f;
    if (keyDown('Q'))
    {
        return false;
    }
    if (keyDown('W'))
    {
        moveForward(pos, facing, speed);
    }
    if (keyDown('S'))
    {
        moveForward(pos, facing, -speed);
    }
    if (keyDown('A'))
    {
        moveRight(pos, facing, -speed);
    }
    if (keyDown('D'))
    {
        moveRight(pos, facing, speed);
    }

    const float turnSpeed = 0.1f;
    if (keyDown('P'))
    {
        Vector2D::rotateVector(facing, turnSpeed);
    }
    if (keyDown('O'))
    {
        Vector2D::rotateVector(facing, -turnSpeed);
    }
    return true;
}