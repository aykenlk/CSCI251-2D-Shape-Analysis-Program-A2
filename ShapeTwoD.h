#ifndef SHAPE_TWO_D_H
#define SHAPE_TWO_D_H

#include <string>
#include <vector>
#include <utility>

class ShapeTwoD {
protected:
    std::string name;
    bool containsWarpSpace;
    double area;
    
public:
    ShapeTwoD(std::string name, bool warpSpace);
    virtual ~ShapeTwoD() = default;
    
    virtual double computeArea() = 0;
    virtual bool isPointInShape(int x, int y) const = 0;
    virtual bool isPointOnShape(int x, int y) const = 0;
    virtual std::string toString() const = 0;
    
    virtual int getVertexCount() const = 0;
    virtual std::pair<int, int> getVertex(int index) const = 0;
    virtual bool validateShape() const = 0;
    
    virtual std::vector<std::pair<int, int>> getPointsOnPerimeter() const = 0;
    virtual std::vector<std::pair<int, int>> getPointsWithinShape() const = 0;
    
    std::string getName() const;
    bool getContainsWarpSpace() const;
    std::string getSpecialType() const;
    double getArea() const;
    
    void setName(std::string name);
    void setContainsWarpSpace(bool warpSpace);
    void setArea(double area);
};

#endif