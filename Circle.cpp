#include "Circle.h"
#include <cmath>
#include <sstream>
#include <stdexcept>
#include <vector>

Circle::Circle(std::string name, bool warpSpace, int centerX, int centerY, int radius) 
    : ShapeTwoD(name, warpSpace), center(centerX, centerY), radius(radius) {
    if (!validateShape()) {
        throw std::invalid_argument("Invalid circle parameters");
    }
    computeArea();
}

double Circle::computeArea() {
    area = M_PI * radius * radius;
    return area;
}

bool Circle::isPointInShape(int x, int y) const {
    double distance = distanceFromCenter(x, y);
    return distance < radius;
}

bool Circle::isPointOnShape(int x, int y) const {
    double distance = distanceFromCenter(x, y);
    return std::abs(distance - radius) < 0.5;
}

std::string Circle::toString() const {
    std::ostringstream oss;
    oss << "Name: " << name << "\n"
        << "Special Type: " << getSpecialType() << "\n"
        << "Area: " << area << " units square\n"
        << "Center: (" << center.first << ", " << center.second << ")\n"
        << "Radius: " << radius << " units\n";
    
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

std::pair<int, int> Circle::getVertex(int index) const {
    throw std::logic_error("Circles don't have vertices");
}

bool Circle::validateShape() const {
    return radius > 0;
}

std::vector<std::pair<int, int>> Circle::getPointsOnPerimeter() const {
    std::vector<std::pair<int, int>> points;
    
    // Only include the 4 cardinal points as required
    points.emplace_back(center.first, center.second + radius); // North
    points.emplace_back(center.first, center.second - radius); // South
    points.emplace_back(center.first + radius, center.second); // East
    points.emplace_back(center.first - radius, center.second); // West
    
    return points;
}

std::vector<std::pair<int, int>> Circle::getPointsWithinShape() const {
    std::vector<std::pair<int, int>> points;
    
    for (int x = center.first - radius + 1; x < center.first + radius; x++) {
        for (int y = center.second - radius + 1; y < center.second + radius; y++) {
            if (distanceFromCenter(x, y) < radius) {
                points.emplace_back(x, y);
            }
        }
    }
    
    return points;
}

double Circle::distanceFromCenter(int x, int y) const {
    int dx = x - center.first;
    int dy = y - center.second;
    return std::sqrt(dx * dx + dy * dy);
}

std::string Circle::getPointsString() const {
    std::ostringstream oss;
    oss << "Center: (" << center.first << ", " << center.second << ")\n"
        << "Radius: " << radius << " units";
    return oss.str();
}