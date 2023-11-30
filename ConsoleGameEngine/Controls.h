#pragma once
#include "Vector2D.h"
#include <Windows.h>

bool keyDown(char keyCode);
bool handleControls(Vector2D* pos, Vector2D* facing);
void moveForward(Vector2D* pos, Vector2D* facing, float speed);
void moveRight(Vector2D* pos, Vector2D* facing, float speed);
