#pragma once
#include "ConsoleEngineMath.h"
#include "Vector2D.h"
class Collision2D
{
private:
	bool collisionOccurred;
	float intersection[2];
public:
	Collision2D(bool ocurred, float x, float y)
	{
		collisionOccurred = ocurred;
		intersection[0] = x;
		intersection[1] = y;
	}
	Collision2D()
	{
		collisionOccurred = false;
		intersection[0] = 0;
		intersection[1] = 0;
	}


	/**
	 *
	 * @return Boolean representing whether the collision took place
	 */
	bool getCollisionOccurred()
	{
		return collisionOccurred;
	}

	/**
	 * Get the point at which the collision took place
	 * @return Float array representing the point that this collision took place such that arr[0] is the x coordinate
	 * and arr[1] is the y coordinate
	 */
	float* getIntersection()
	{
		return intersection;
	}
	static Collision2D LineLine(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
	static Collision2D CircleLine(float circleX, float circleY, float circleRadius, float lineX1, float lineY1, float lineX2, float lineY2);
	static Collision2D LinePoint(float pointX, float pointY, float lineX1, float lineY1, float lineX2, float lineY2);
};