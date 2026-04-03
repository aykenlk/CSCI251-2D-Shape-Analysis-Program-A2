#include "Cross.h"
#include <algorithm>
#include <sstream>
#include <cmath>
#include <stdexcept>
#include <vector>

Cross::Cross(std::string name, bool warpSpace, int vertices[12][2]) 
    : ShapeTwoD(name, warpSpace), area(0) {
    for (int i = 0; i < 12; i++) {
        this->vertices[i][0] = vertices[i][0];
        this->vertices[i][1] = vertices[i][1];
    }
    if (!validateShape()) {
        throw std::invalid_argument("Invalid cross shape");
    }
    computeArea();
}

//bounding rectangle subtract 4 corner rectangles
void Cross::calculateBoundingRectangle(int& minX, int& maxX, int& minY, int& maxY) const {
    minX = vertices[0][0];
    maxX = vertices[0][0];
    minY = vertices[0][1];
    maxY = vertices[0][1];
    
    for (int i = 1; i < 12; i++) {
        minX = std::min(minX, vertices[i][0]);
        maxX = std::max(maxX, vertices[i][0]);
        minY = std::min(minY, vertices[i][1]);
        maxY = std::max(maxY, vertices[i][1]);
    }
}

void Cross::getBoundingRectangle(int& minX, int& maxX, int& minY, int& maxY) const {
    calculateBoundingRectangle(minX, maxX, minY, maxY);
}

double Cross::computeArea() {
    double area = 0.0;
    
    for (int i = 0; i < 11; i++) {
        area += (vertices[i][0] * vertices[i+1][1]) - 
                (vertices[i+1][0] * vertices[i][1]);
    }
    
    area += (vertices[11][0] * vertices[0][1]) - 
            (vertices[0][0] * vertices[11][1]);
    
    this->area = fabs(area) / 2.0;
    return this->area;
}


bool Cross::validateShape() const {
    // Only check that it has cross-like properties
    return validateCross();
}

bool Cross::validateCross() const {
    // Count direction changes to ensure cross shape
    int directionChanges = 0;
    for (int i = 1; i < 11; i++) {
        int dx1 = vertices[i][0] - vertices[i-1][0];
        int dy1 = vertices[i][1] - vertices[i-1][1];
        int dx2 = vertices[i+1][0] - vertices[i][0];
        int dy2 = vertices[i+1][1] - vertices[i][1];
        
        if (dx1*dy2 - dy1*dx2 != 0) {
            directionChanges++;
        }
    }
    
    // Also check that have both vertical and horizontal segments
    bool hasVertical = false;
    bool hasHorizontal = false;
    
    for (int i = 1; i < 12; i++) {
        if (vertices[i][0] == vertices[i-1][0]) hasVertical = true;
        if (vertices[i][1] == vertices[i-1][1]) hasHorizontal = true;
    }
    
    return (directionChanges >= 6) && hasVertical && hasHorizontal;
}

bool Cross::isPointInShape(int x, int y) const {
    bool inside = false;
    
    // Ray casting algorithm
    for (int i = 0, j = 11; i < 12; j = i++) {
        int xi = vertices[i][0], yi = vertices[i][1];
        int xj = vertices[j][0], yj = vertices[j][1];
        
        bool intersect = ((yi > y) != (yj > y)) &&
            (x < (xj - xi) * (y - yi) / (double)(yj - yi) + xi);
        if (intersect) {
            inside = !inside;
        }
    }
    return inside;
}

bool Cross::isPointOnShape(int x, int y) const {
    for (int i = 0; i < 12; i++) {
        int next = (i + 1) % 12;
        int x1 = vertices[i][0], y1 = vertices[i][1];
        int x2 = vertices[next][0], y2 = vertices[next][1];
        
        // Check if point is on the line segment
        int cross = (x - x1) * (y2 - y1) - (y - y1) * (x2 - x1);
        if (std::abs(cross) != 0) continue;
        
        // Check if within segment bounds
        if (x >= std::min(x1, x2) && x <= std::max(x1, x2) &&
            y >= std::min(y1, y2) && y <= std::max(y1, y2)) {
            return true;
        }
    }
    return false;
}

bool Cross::isPointOnLine(int x1, int y1, int x2, int y2, int px, int py) const {
    if (px < std::min(x1, x2) || px > std::max(x1, x2) ||
        py < std::min(y1, y2) || py > std::max(y1, y2)) {
        return false;
    }
    
    if (x1 == x2) return px == x1;
    if (y1 == y2) return py == y1;
    
    double slope = static_cast<double>(y2 - y1) / (x2 - x1);
    double expectedY = y1 + slope * (px - x1);
    return std::abs(py - expectedY) < 0.0001;
}

std::string Cross::toString() const {
    std::ostringstream oss;
    int minX, maxX, minY, maxY;
    calculateBoundingRectangle(minX, maxX, minY, maxY);
    
    oss << "Name: " << getName() << "\n"
        << "Special Type: " << getSpecialType() << "\n"
        << "Area: " << area << " units square\n"
        << "Bounding Rectangle: (" << minX << "," << minY << ") to (" 
        << maxX << "," << maxY << ")\n"
        << "Vertices:\n";
    
    for (int i = 0; i < 12; i++) {
        oss << "Point [" << i << "] : (" << vertices[i][0] << ", " 
            << vertices[i][1] << ")\n";
    }

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

std::pair<int, int> Cross::getVertex(int index) const {
    if (index < 0 || index >= 12) {
        throw std::out_of_range("Invalid vertex index");
    }
    return {vertices[index][0], vertices[index][1]};
}

std::vector<std::pair<int, int>> Cross::getPointsOnPerimeter() const {
    std::vector<std::pair<int, int>> points;
    
    for (int i = 0; i < 12; i++) {
        int next = (i + 1) % 12;
        int x1 = vertices[i][0], y1 = vertices[i][1];
        int x2 = vertices[next][0], y2 = vertices[next][1];
        
        int dx = x2 - x1;
        int dy = y2 - y1;
        int steps = std::max(std::abs(dx), std::abs(dy));
        
        for (int j = 1; j < steps; j++) {
            points.emplace_back(
                x1 + j * dx / steps,
                y1 + j * dy / steps
            );
        }
    }
    
    return points;
}

std::vector<std::pair<int, int>> Cross::getPointsWithinShape() const {
    std::vector<std::pair<int, int>> points;
    int minX, maxX, minY, maxY;
    calculateBoundingRectangle(minX, maxX, minY, maxY);
    
    // Check all points in bounding rectangle
    for (int x = minX + 1; x < maxX; x++) {
        for (int y = minY + 1; y < maxY; y++) {
            if (isPointInShape(x, y) && !isPointOnShape(x, y)) {
                points.emplace_back(x, y);
            }
        }
    }
    
    return points;
}