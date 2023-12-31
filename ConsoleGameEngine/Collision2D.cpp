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

/**
 * Detect a collision between a line and a point
 * @param pointX The x coordinate of the point
 * @param pointY The y coordinate of the point
 * @param lineX1 The x coordinate of point 1 of the line
 * @param lineY1 The y coordinate of point 1 of the line
 * @param lineX2 The x coordinate of point 2 of the line
 * @param lineY2 The y coordinate of point 2 of the line
 * @return Collision2D object representing where and whether a collision took place
 */
Collision2D Collision2D::LinePoint(float pointX, float pointY, float lineX1, float lineY1, float lineX2, float lineY2)
{
    float lineLen = calculatePointDistance(lineX1, lineY1, lineX2, lineY2);
    float d1 = calculatePointDistance(pointX, pointY, lineX1, lineY1);
    float d2 = calculatePointDistance(pointX, pointY, lineX2, lineY2);
    const float BUFFER = 0.1f; // floats aren't accurate so check within this distance
    float min = lineLen - BUFFER, max = lineLen + BUFFER;
    if (d1 + d2 >= min && d1 + d2 <= max)
    {
        Vector2D vector = { lineX2 - lineX1, lineY2 - lineY1 };
        vector.normalize();
        return Collision2D(true, vector.x * d1, vector.y * d1);
    }
    return Collision2D();
}

/**
 * Detect a collision between a circle and a line
 * @param circleX The x coordinate of the centre of the circle
 * @param circleY The y coordinate of the centre of the circle
 * @param circleRadius The radius of the circle
 * @param lineX1 The x coordinate of point 1 of the line segment
 * @param lineY1 The y coordinate of point 1 of the line segment
 * @param lineX2 The x coordinate of point 2 of the line segment
 * @param lineY2 The y coordinate of point 2 of the line segment
 *
 * @return Collision2D object representing where and whether a collision took place
 */
Collision2D Collision2D::CircleLine(float circleX, float circleY, float circleRadius, float lineX1, float lineY1, float lineX2, float lineY2)
{
    float len = calculatePointDistance(lineX1, lineY1, lineX2, lineY2);
    float dot = (((circleX - lineX1) * (lineX2 - lineX1)) + ((circleY - lineY1) * (lineY2 - lineY1))) / (float)(len*len);
    float closestX = lineX1 + (dot * (lineX2 - lineX1));
    float closestY = lineY1 + (dot * (lineY2 - lineY1));
    Collision2D onSegmentCollision = LinePoint(closestX, closestY, lineX1, lineY1, lineX2, lineY2);
    bool onSegment = onSegmentCollision.getCollisionOccurred();
    if (!onSegment) return onSegmentCollision;

    float squareDistance = calculatePointDistanceSquared(closestX, closestY, circleX, circleY);

    if (squareDistance <= circleRadius * circleRadius)
    {
        return Collision2D(true, closestX, closestY);
    }
    return Collision2D();
}
