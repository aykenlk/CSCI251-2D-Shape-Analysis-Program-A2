#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Square.h"

class Rectangle : public Square {
public:
    Rectangle(std::string name, bool warpSpace, int vertices[4][2]);
    bool validateShape() const override;
    
    using Square::computeArea;
    using Square::isPointInShape;
    using Square::isPointOnShape;
    using Square::toString;
    using Square::getPointsOnPerimeter;
    using Square::getPointsWithinShape;
    using Square::getVertex;
    using Square::getVertexCount;
};

#endif