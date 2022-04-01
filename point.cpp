#include <iostream>
#include <sstream>
#include <cmath>
#include "point.h"

using std::ostringstream;
using std::sqrt;
using std::pow;

/**
 * @brief Construct a new Point object
 * set x and y points to the numbers 
 * specified by the arguments.
 * 
 * @param _x point on x axis
 * @param _y point on y axis
 */
Point::Point(double _x, double _y)
{
    x = _x;
    y = -_y;
}

/**
 * @brief Constructs a string with the two points
 * surrounded by parenthases separated by a comma
 * 
 * @return string returns the constructed string
 */
string Point::toString()
{
    ostringstream strs;
    string s;

    strs << '(' << x << ',' << y << ')';
    s = strs.str();

    return s;
}

/**
 * @brief Calculates the euclidean distance
 * between the two points. (y2 - y1) / (x2 - x1)
 * 
 * @param p second point in the equation
 * @return double 
 */
double Point::distanceTo(Point p)
{
    double rise, run;

    run = x - p.getX();
    rise = y - p.getY();

    return sqrt(pow(run, 2) + pow(rise, 2));
}