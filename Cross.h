#ifndef CROSS_H
#define CROSS_H

#include "ShapeTwoD.h"
#include <vector>
#include <utility>

class Cross : public ShapeTwoD {
private:
    int vertices[12][2];
    double area;
    
    bool isPointOnLine(int x1, int y1, int x2, int y2, int px, int py) const;
    void calculateBoundingRectangle(int& minX, int& maxX, int& minY, int& maxY) const;
    bool validateCross() const;
    
public:
    Cross(std::string name, bool warpSpace, int vertices[12][2]);
    
    double computeArea() override;
    bool isPointInShape(int x, int y) const override;
    bool isPointOnShape(int x, int y) const override;
    std::string toString() const override;
    
    int getVertexCount() const override { return 12; }
    std::pair<int, int> getVertex(int index) const override;
    bool validateShape() const override;
    
    std::vector<std::pair<int, int>> getPointsOnPerimeter() const override;
    std::vector<std::pair<int, int>> getPointsWithinShape() const override;
    
    void getBoundingRectangle(int& minX, int& maxX, int& minY, int& maxY) const;
};

#endif