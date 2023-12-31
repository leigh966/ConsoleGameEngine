#pragma once
#include<cmath>
float getDistance(float x1, float y1, float x2, float y2);

int roundToInt(float f);
/**
 * Calculate the hypotenuse^2 of a right-angled triangle given the length of the opposite and adjacent
 * @param a
 * @param b
 * @return a^2 + b^2
 */
float pythagorasTheoremSquared(float a, float b);

/**
 * Calculate the hypotenuse^2 of a right-angled triangle given the length of the opposite and adjacent
 * @param a
 * @param b
 * @return sqrt(a^2 + b^2)
 */
float pythagorasTheorem(float a, float b);

/**
 * Calculate the length^2 of the line segment such that (x1,y1) is one end and (x2,y2) is the other
 * @param x1 The x coordinate of point 1 of the line segment
 * @param y1 The y coordinate of point 1 of the line segment
 * @param x2 The x coordinate of point 2 of the line segment
 * @param y2 The y coordinate of point 2 of the line segment
 * @return (x1-x2)^2 + (y1-y2)^2
 */
float calculatePointDistanceSquared(float x1, float y1, float x2, float y2);
/**
 * Calculate the length of the line segment such that (x1,y1) is one end and (x2,y2) is the other
 * @param x1 The x coordinate of point 1 of the line segment
 * @param y1 The y coordinate of point 1 of the line segment
 * @param x2 The x coordinate of point 2 of the line segment
 * @param y2 The y coordinate of point 2 of the line segment
 * @return sqrt( (x1-x2)^2 + (y1-y2)^2 )
 */
float calculatePointDistance(float x1, float y1, float x2, float y2);
