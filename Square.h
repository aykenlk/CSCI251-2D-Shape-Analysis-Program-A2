#ifndef SQUARE_H
#define SQUARE_H

#include "ShapeTwoD.h"

class Square : public ShapeTwoD {
protected:
    int vertices[4][2];
    
public:
    Square(std::string name, bool warpSpace, int vertices[4][2]);
    virtual ~Square() = default;
    
    double computeArea() override;
    bool isPointInShape(int x, int y) const override;
    bool isPointOnShape(int x, int y) const override;
    std::string toString() const override;
    
    int getVertexCount() const override { return 4; }
    std::pair<int, int> getVertex(int index) const override;
    bool validateShape() const override;
    
    std::vector<std::pair<int, int>> getPointsOnPerimeter() const override;
    std::vector<std::pair<int, int>> getPointsWithinShape() const override;

protected:
    int getMinX() const;
    int getMaxX() const;
    int getMinY() const;
    int getMaxY() const;
    std::string getPointsString() const;
};

#endif