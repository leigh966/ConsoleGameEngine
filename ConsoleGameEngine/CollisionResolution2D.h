#pragma once
#include "Line.h"
#include "Vector2D.h"
#include "Collision2D.h"
#include "ConsoleEngineMath.h"

const float PLAYER_RADIUS = 1.0f;

void ResolvePlayerLineCollision(Vector2D* pos, Line lines[], int numberOfLines)
{
	for (int i = 0; i < numberOfLines; i++)
	{
		Collision2D col = Collision2D::CircleLine(pos->x, pos->y, PLAYER_RADIUS, lines[i].x1, lines[i].y1, lines[i].x2, lines[i].y2);
		if (col.getCollisionOccurred())
		{
			float* intersection = col.getIntersection();
			Vector2D toPlayer = {pos->x-intersection[0], pos->y-intersection[1]};
			float currentDistance = pythagorasTheorem(toPlayer.x, toPlayer.y);
			toPlayer.normalize();
			float deltaDistance = PLAYER_RADIUS - currentDistance;
			pos->transform(toPlayer.x * deltaDistance, toPlayer.y * deltaDistance);
		}
	}
}