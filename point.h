#ifndef POINT_H
#define POINT_H
#include <string>
using std::string;

class Point
{
 public:
    /**
     * @brief Construct a new Point object
     * 
     * @param x x position of the point
     * @param y y position of the point
     */
    Point(double x, double y);

    /**
     * @brief create a string representation of the point
     * 
     * @return string the string representation of the point
     */
    string toString();

    /**
     * @brief Calculate the euclidean distance from this
     * point to point p
     * 
     * @param p second point in the equation
     * @return double euclidean distance between points
     */
    double distanceTo(Point p);

    inline double getX() {return x;}
    inline double getY() {return y;}

 private:
    double x, y;
};

#endif