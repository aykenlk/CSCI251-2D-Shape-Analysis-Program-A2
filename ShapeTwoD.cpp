#include "ShapeTwoD.h"
#include <vector>

ShapeTwoD::ShapeTwoD(std::string name, bool warpSpace) 
    : name(name), containsWarpSpace(warpSpace), area(0.0) {}

std::string ShapeTwoD::getName() const { return name; }
bool ShapeTwoD::getContainsWarpSpace() const { return containsWarpSpace; }
std::string ShapeTwoD::getSpecialType() const { return containsWarpSpace ? "WS" : "NS"; }
double ShapeTwoD::getArea() const { return area; }

void ShapeTwoD::setName(std::string name) { this->name = name; }
void ShapeTwoD::setContainsWarpSpace(bool warpSpace) { containsWarpSpace = warpSpace; }
void ShapeTwoD::setArea(double area) { this->area = area; }

std::vector<std::pair<int, int>> ShapeTwoD::getPointsOnPerimeter() const {
    return {};
}

std::vector<std::pair<int, int>> ShapeTwoD::getPointsWithinShape() const {
    return {};
}