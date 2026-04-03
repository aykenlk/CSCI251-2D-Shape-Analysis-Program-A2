#ifndef CIRCLE_H
#define CIRCLE_H

#include "ShapeTwoD.h"
#include <utility>
#include <vector>

class Circle : public ShapeTwoD {
private:
    std::pair<int, int> center;
    int radius;
    
    double distanceFromCenter(int x, int y) const;
    std::string getPointsString() const;
    
public:
    Circle(std::string name, bool warpSpace, int centerX, int centerY, int radius);
    
    double computeArea() override;
    bool isPointInShape(int x, int y) const override;
    bool isPointOnShape(int x, int y) const override;
    std::string toString() const override;
    
    int getVertexCount() const override { return 0; }
    std::pair<int, int> getVertex(int index) const override;
    bool validateShape() const override;
    
    std::vector<std::pair<int, int>> getPointsOnPerimeter() const override;
    std::vector<std::pair<int, int>> getPointsWithinShape() const override;
    
    std::pair<int, int> getCenter() const { return center; }
    int getRadius() const { return radius; }
};

#endif