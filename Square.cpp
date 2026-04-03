#include "Square.h"
#include <algorithm>
#include <sstream>
#include <cmath>
#include <vector>


Square::Square(std::string name, bool warpSpace, int vertices[4][2]) 
    : ShapeTwoD(name, warpSpace) {
    for (int i = 0; i < 4; i++) {
        this->vertices[i][0] = vertices[i][0];
        this->vertices[i][1] = vertices[i][1];
    }
}

double Square::computeArea() {
    double minX = getMinX(), maxX = getMaxX();
    double minY = getMinY(), maxY = getMaxY();
    this->area = (maxX - minX) * (maxY - minY);
    return this->area;
}

bool Square::isPointInShape(int x, int y) const {
    int minX = getMinX(), maxX = getMaxX();
    int minY = getMinY(), maxY = getMaxY();
    return (x > minX && x < maxX && y > minY && y < maxY);
}

bool Square::isPointOnShape(int x, int y) const {
    int minX = getMinX(), maxX = getMaxX();
    int minY = getMinY(), maxY = getMaxY();
    bool onTopOrBottom = (y == minY || y == maxY) && (x >= minX && x <= maxX);
    bool onLeftOrRight = (x == minX || x == maxX) && (y >= minY && y <= maxY);
    return onTopOrBottom || onLeftOrRight;
}

std::string Square::toString() const {
    std::ostringstream oss;
    oss << "Name: " << name << "\n"
        << "Special Type: " << getSpecialType() << "\n"
        << "Area: " << area << " units square\n"
        << "Vertices:\n" << getPointsString();
    
    auto perimeterPoints = getPointsOnPerimeter();
    auto withinPoints = getPointsWithinShape();
    
    oss << "Points on perimeter: ";
    if (perimeterPoints.empty()) oss << "none!";
    else {
        for (size_t i = 0; i < perimeterPoints.size(); i++) {
            if (i > 0) oss << ", ";
            oss << "(" << perimeterPoints[i].first << ", " << perimeterPoints[i].second << ")";
        }
    }
    
    oss << "\nPoints within shape: ";
    if (withinPoints.empty()) oss << "none!";
    else {
        for (size_t i = 0; i < withinPoints.size(); i++) {
            if (i > 0) oss << ", ";
            oss << "(" << withinPoints[i].first << ", " << withinPoints[i].second << ")";
        }
    }
    
    return oss.str();
}

std::string Square::getPointsString() const {
    std::ostringstream oss;
    for (int i = 0; i < 4; i++) {
        oss << "Point [" << i << "] : (" << vertices[i][0] << ", " 
            << vertices[i][1] << ")\n";
    }
    return oss.str();
}

int Square::getMinX() const {
    return std::min({vertices[0][0], vertices[1][0], vertices[2][0], vertices[3][0]});
}

int Square::getMaxX() const {
    return std::max({vertices[0][0], vertices[1][0], vertices[2][0], vertices[3][0]});
}

int Square::getMinY() const {
    return std::min({vertices[0][1], vertices[1][1], vertices[2][1], vertices[3][1]});
}

int Square::getMaxY() const {
    return std::max({vertices[0][1], vertices[1][1], vertices[2][1], vertices[3][1]});
}

std::pair<int, int> Square::getVertex(int index) const {
    if (index < 0 || index >= 4) throw std::out_of_range("Invalid vertex index");
    return {vertices[index][0], vertices[index][1]};
}

bool Square::validateShape() const {
    double side1 = hypot(vertices[1][0]-vertices[0][0], vertices[1][1]-vertices[0][1]);
    double side2 = hypot(vertices[2][0]-vertices[1][0], vertices[2][1]-vertices[1][1]);
    double side3 = hypot(vertices[3][0]-vertices[2][0], vertices[3][1]-vertices[2][1]);
    double side4 = hypot(vertices[0][0]-vertices[3][0], vertices[0][1]-vertices[3][1]);
    double tolerance = 0.0001;
    return (abs(side1-side2) < tolerance && abs(side2-side3) < tolerance && abs(side3-side4) < tolerance);
}

std::vector<std::pair<int, int>> Square::getPointsOnPerimeter() const {
    std::vector<std::pair<int, int>> points;
    int minX = getMinX(), maxX = getMaxX();
    int minY = getMinY(), maxY = getMaxY();

    for (int x = minX + 1; x < maxX; x++) {
        points.emplace_back(x, minY);
        points.emplace_back(x, maxY);
    }

    for (int y = minY + 1; y < maxY; y++) {
        points.emplace_back(minX, y);
        points.emplace_back(maxX, y);
    }

    return points;
}

std::vector<std::pair<int, int>> Square::getPointsWithinShape() const {
    std::vector<std::pair<int, int>> points;
    int minX = getMinX(), maxX = getMaxX();
    int minY = getMinY(), maxY = getMaxY();

    for (int x = minX + 1; x < maxX; x++) {
        for (int y = minY + 1; y < maxY; y++) {
            points.emplace_back(x, y);
        }
    }
    return points;
}