#include "Collision2D.h"

/**
* Detect a collision between 2 lines
* @param x1 Line segment 1, point 1, x coordinate
* @param y1 Line segment 1, point 1, y coordinate
* @param x2 Line segment 1, point 2, x coordinate
* @param y2 Line segment 1, point 2, y coordinate
* @param x3 Line segment 2, point 1, x coordinate
* @param y3 Line segment 2, point 1, y coordinate
* @param x4 Line segment 2, point 2, x coordinate
* @param y4 Line segment 2, point 2, y coordinate
* @return Collision2D object representing where and whether a collision took place
*/
Collision2D Collision2D::LineLine(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
	// calculate the distance to intersection point
	float denominator = ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
	float uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / denominator;
	float uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / denominator;

	// if uA and uB are between 0-1, lines are colliding
	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {
		float intersectionX = x1 + (uA * (x2 - x1));
		float intersectionY = y1 + (uA * (y2 - y1));
		return Collision2D(true, intersectionX, intersectionY);
	}
	else return Collision2D();
}