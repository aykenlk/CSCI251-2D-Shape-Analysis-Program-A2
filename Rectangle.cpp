#include "Rectangle.h"
#include <cmath>

Rectangle::Rectangle(std::string name, bool warpSpace, int vertices[4][2]) 
    : Square(name, warpSpace, vertices) {}

bool Rectangle::validateShape() const {
    double side1 = hypot(vertices[1][0]-vertices[0][0], vertices[1][1]-vertices[0][1]);
    double side2 = hypot(vertices[2][0]-vertices[1][0], vertices[2][1]-vertices[1][1]);
    double side3 = hypot(vertices[3][0]-vertices[2][0], vertices[3][1]-vertices[2][1]);
    double side4 = hypot(vertices[0][0]-vertices[3][0], vertices[0][1]-vertices[3][1]);
    double tolerance = 0.0001;
    return (abs(side1-side3) < tolerance && abs(side2-side4) < tolerance);
}