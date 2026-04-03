#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>
#include <cctype>
#include <memory>
#include "ShapeTwoD.h"
#include "Square.h"
#include "Rectangle.h"
#include "Cross.h"
#include "Circle.h"
#include <climits>

using namespace std;

//tolerance for shape sorting
const double AREA_TOLERANCE = 0.0001;

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//ensure that user input is standardised before storing
string toLowercase(const string& str) {
    string lowerStr;
    for (char c : str) {
        lowerStr += tolower(c);
    }
    return lowerStr;
}

void displayMainMenu() {
    cout << "Student ID: 1035289\n";
    cout << "Student Name: Ayken Kang Lee\n";
    cout << "----------------------------------\n";
    cout << "Welcome to Assn2 program!\n";
    cout << "1) Input sensor data\n";
    cout << "2) Compute area (for all records)\n";
    cout << "3) Print shapes report\n";
    cout << "4) Sort shape data\n";
    cout << "5) Search shapes by coordinates\n";
    cout << "6) Edit shape\n";
    cout << "7) Delete shape\n";
    cout << "8) Exit\n";
    cout << "Please enter your choice: ";
}

int getValidatedInt(const string& prompt, int min = INT_MIN, int max = INT_MAX) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            if (value >= min && value <= max) {
                clearInputBuffer();
                return value;
            }
            cout << "Value must be between " << min << " and " << max << ".\n";
        } else {
            cout << "Invalid input. Please enter an integer.\n";
        }
        clearInputBuffer();
    }
}

string getValidatedShapeName() {
    string name;
    while (true) {
        cout << "Please enter name of shape (Square, Rectangle, Cross, Circle): ";
        cin >> name;
        string lowerName = toLowercase(name);
        
        if (lowerName == "square") return "Square";
        if (lowerName == "rectangle") return "Rectangle";
        if (lowerName == "cross") return "Cross";
        if (lowerName == "circle") return "Circle";
        
        cout << "Invalid shape name. Please try again.\n";
        clearInputBuffer();
    }
}

string getValidatedSpecialType() {
    string type;
    while (true) {
        cout << "Please enter special type (WS/NS): ";
        cin >> type;
        string lowerType = toLowercase(type);
        
        if (lowerType == "ws") return "WS";
        if (lowerType == "ns") return "NS";
        
        cout << "Invalid type. Please enter WS or NS.\n";
        clearInputBuffer();
    }
}

void inputSquare(vector<ShapeTwoD*>& shapes, const string& name, bool warpSpace) {
    int vertices[4][2];
    cout << "Enter 4 vertices (x y) in order (clockwise or counter-clockwise):\n";
    
    for (int i = 0; i < 4; i++) {
        cout << "Point " << i+1 << ": ";
        while (!(cin >> vertices[i][0] >> vertices[i][1])) {
            cout << "Invalid input. Please enter two integers separated by space.\n";
            clearInputBuffer();
            cout << "Point " << i+1 << ": ";
        }
    }
    
    try {
        Square* square = new Square(name, warpSpace, vertices);
        if (!square->validateShape()) {
            cout << "Error: The points don't form a valid square!\n";
            delete square;
            return;
        }
        shapes.push_back(square);
        cout << "Square successfully created.\n";
    } catch (const exception& e) {
        cout << "Error creating square: " << e.what() << endl;
    }
}

void inputRectangle(vector<ShapeTwoD*>& shapes, const string& name, bool warpSpace) {
    int vertices[4][2];
    cout << "Enter 4 vertices (x y) in order (clockwise or counter-clockwise):\n";
    
    for (int i = 0; i < 4; i++) {
        cout << "Point " << i+1 << ": ";
        while (!(cin >> vertices[i][0] >> vertices[i][1])) {
            cout << "Invalid input. Please enter two integers separated by space.\n";
            clearInputBuffer();
            cout << "Point " << i+1 << ": ";
        }
    }
    
    try {
        Rectangle* rect = new Rectangle(name, warpSpace, vertices);
        if (!rect->validateShape()) {
            cout << "Error: The points don't form a valid rectangle!\n";
            delete rect;
            return;
        }
        shapes.push_back(rect);
        cout << "Rectangle successfully created.\n";
    } catch (const exception& e) {
        cout << "Error creating rectangle: " << e.what() << endl;
    }
}

void inputCross(vector<ShapeTwoD*>& shapes, const string& name, bool warpSpace) {
    int vertices[12][2];
    cout << "Enter 12 vertices (x y) in order:\n";
    
    for (int i = 0; i < 12; i++) {
        cout << "Point " << i+1 << ": ";
        while (!(cin >> vertices[i][0] >> vertices[i][1])) {
            cout << "Invalid input. Please enter two integers separated by space.\n";
            clearInputBuffer();
            cout << "Point " << i+1 << ": ";
        }
    }
    
    try {
        Cross* cross = new Cross(name, warpSpace, vertices);
        if (!cross->validateShape()) {
            cout << "Error: The points don't form a valid cross!\n";
            delete cross;
            return;
        }
        shapes.push_back(cross);
        cout << "Cross successfully created.\n";
    } catch (const exception& e) {
        cout << "Error creating cross: " << e.what() << endl;
    }
}

void inputCircle(vector<ShapeTwoD*>& shapes, const string& name, bool warpSpace) {
    int centerX, centerY, radius;
    
    centerX = getValidatedInt("Enter center x-coordinate: ");
    centerY = getValidatedInt("Enter center y-coordinate: ");
    
    while (true) {
        radius = getValidatedInt("Enter radius (must be positive): ");
        if (radius > 0) break;
        cout << "Radius must be positive. Please try again.\n";
    }
    
    try {
        shapes.push_back(new Circle(name, warpSpace, centerX, centerY, radius));
        cout << "Circle successfully created.\n";
    } catch (const exception& e) {
        cout << "Error creating circle: " << e.what() << endl;
    }
}

//main func for adding shape data
void inputSensorData(vector<ShapeTwoD*>& shapes) {
    cout << "\n[Input sensor data]\n";
    string name = getValidatedShapeName();
    string specialType = getValidatedSpecialType();
    bool warpSpace = (specialType == "WS");
    
    if (name == "Square") {
        inputSquare(shapes, name, warpSpace);
    } 
    else if (name == "Rectangle") {
        inputRectangle(shapes, name, warpSpace);
    } 
    else if (name == "Cross") {
        inputCross(shapes, name, warpSpace);
    } 
    else if (name == "Circle") {
        inputCircle(shapes, name, warpSpace);
    }
    
    cout << "Record successfully stored. Going back to main menu...\n";
}

void computeAreas(vector<ShapeTwoD*>& shapes) {
    for (auto shape : shapes) {
        shape->setArea(shape->computeArea());
    }
    cout << "Computation completed! (" << shapes.size() << " records were updated)\n";
}

void printPoints(const vector<pair<int, int>>& points) {
    if (points.empty()) {
        cout << "none!";
        return;
    }
    
    for (size_t i = 0; i < points.size(); ++i) {
        cout << "(" << points[i].first << ", " << points[i].second << ")";
        if (i != points.size() - 1) cout << ", ";
    }
}

void printShapesReport(vector<ShapeTwoD*>& shapes) {
    cout << "\nTotal no. of records available = " << shapes.size() << "\n";
    
    for (size_t i = 0; i < shapes.size(); i++) {
        cout << "\nShape [" << i << "]\n";
        cout << shapes[i]->toString();
        cout << "\n";
    }
}

bool compareAreaAsc(ShapeTwoD* a, ShapeTwoD* b) {
    double areaDiff = a->getArea() - b->getArea();
    if (fabs(areaDiff) > AREA_TOLERANCE) {
        return areaDiff < 0;
    }
    
    if (a->getContainsWarpSpace() != b->getContainsWarpSpace()) {
        return a->getContainsWarpSpace();
    }
    
    return a->getName() < b->getName();
}

bool compareAreaDesc(ShapeTwoD* a, ShapeTwoD* b) {
    double areaDiff = a->getArea() - b->getArea();
    if (fabs(areaDiff) > AREA_TOLERANCE) {
        return areaDiff > 0;
    }
    
    if (a->getContainsWarpSpace() != b->getContainsWarpSpace()) {
        return a->getContainsWarpSpace();
    }
    
    return a->getName() < b->getName();
}

bool compareSpecialTypeAndArea(ShapeTwoD* a, ShapeTwoD* b) {
    if (a->getContainsWarpSpace() != b->getContainsWarpSpace()) {
        return a->getContainsWarpSpace();
    }
    
    double areaDiff = a->getArea() - b->getArea();
    if (fabs(areaDiff) > AREA_TOLERANCE) {
        return areaDiff > 0;
    }
    
    return a->getName() < b->getName();
}

void sortShapes(vector<ShapeTwoD*>& shapes) {
    cout << "\na) Sort by area (ascending)\n";
    cout << "b) Sort by area (descending)\n";
    cout << "c) Sort by special type and area\n";
    cout << "Please select sort option ('q' to go back): ";
    
    char option;
    cin >> option;
    clearInputBuffer();
    
    switch (option) {
        case 'a':
            sort(shapes.begin(), shapes.end(), compareAreaAsc);
            cout << "Sort by area (smallest to largest)...\n";
            break;
        case 'b':
            sort(shapes.begin(), shapes.end(), compareAreaDesc);
            cout << "Sort by area (largest to smallest)...\n";
            break;
        case 'c':
            sort(shapes.begin(), shapes.end(), compareSpecialTypeAndArea);
            cout << "Sort by special type (WS first) and area (largest to smallest)...\n";
            break;
        default:
            return;
    }
    
    printShapesReport(shapes);
}

//search shapes by inputting coordinates
void searchShapesByCoordinates(const vector<ShapeTwoD*>& shapes) {
    cout << "\n[Search by Coordinates]\n";
    int x = getValidatedInt("Enter x coordinate: ");
    int y = getValidatedInt("Enter y coordinate: ");
    
    cout << "\nSearch results for point (" << x << "," << y << "):\n";
    
    bool found = false;
    for (size_t i = 0; i < shapes.size(); i++) {
        bool inShape = shapes[i]->isPointInShape(x, y);
        bool onShape = shapes[i]->isPointOnShape(x, y);
        
        if (inShape || onShape) {
            found = true;
            cout << "- Shape [" << i << "] (" << shapes[i]->getName() 
                 << ", " << shapes[i]->getSpecialType() << "): ";
            if (inShape && onShape) {
                cout << "Point is both inside and on the perimeter\n";
            } else if (inShape) {
                cout << "Point is inside the shape\n";
            } else {
                cout << "Point is on the perimeter\n";
            }
        }
    }
    
    if (!found) {
        cout << "Point is not contained in or on any shape\n";
    }
}

void editShape(vector<ShapeTwoD*>& shapes) {
    if (shapes.empty()) {
        cout << "No shapes available to edit.\n";
        return;
    }
    
    printShapesReport(shapes);
    int index = getValidatedInt("Enter shape index to edit: ", 0, shapes.size() - 1);
    
    ShapeTwoD* shape = shapes[index];
    cout << "\nEditing Shape [" << index << "]:\n";
    cout << shape->toString() << endl;
    
    cout << "\nWhat would you like to edit?\n";
    cout << "1) Name\n";
    cout << "2) Special Type\n";
    cout << "3) Shape Data\n";
    cout << "4) Cancel\n";
    int choice = getValidatedInt("Choice: ", 1, 4);
    
    switch (choice) {
        case 1: {
            string newName = getValidatedShapeName();
            shape->setName(newName);
            cout << "Name updated successfully.\n";
            break;
        }
        case 2: {
            string newType = getValidatedSpecialType();
            shape->setContainsWarpSpace(newType == "WS");
            cout << "Special type updated successfully.\n";
            break;
        }
        case 3: {
            string name = shape->getName();
            bool warpSpace = shape->getContainsWarpSpace();
            
            if (name == "Square" || name == "Rectangle") {
                int vertices[4][2];
                cout << "Enter new 4 vertices (x y):\n";
                for (int i = 0; i < 4; i++) {
                    cout << "Point " << i+1 << ": ";
                    while (!(cin >> vertices[i][0] >> vertices[i][1])) {
                        cout << "Invalid input. Please enter two integers separated by space.\n";
                        clearInputBuffer();
                        cout << "Point " << i+1 << ": ";
                    }
                }
                
                ShapeTwoD* newShape;
                if (name == "Square") {
                    newShape = new Square(name, warpSpace, vertices);
                } else {
                    newShape = new Rectangle(name, warpSpace, vertices);
                }
                
                if (newShape->validateShape()) {
                    delete shapes[index];
                    shapes[index] = newShape;
                    cout << "Shape data updated successfully.\n";
                } else {
                    cout << "Invalid shape data. Changes discarded.\n";
                    delete newShape;
                }
            }
            else if (name == "Cross") {
                int vertices[12][2];
                cout << "Enter new 12 vertices (x y):\n";
                for (int i = 0; i < 12; i++) {
                    cout << "Point " << i+1 << ": ";
                    while (!(cin >> vertices[i][0] >> vertices[i][1])) {
                        cout << "Invalid input. Please enter two integers separated by space.\n";
                        clearInputBuffer();
                        cout << "Point " << i+1 << ": ";
                    }
                }
                
                Cross* newCross = new Cross(name, warpSpace, vertices);
                if (newCross->validateShape()) {
                    delete shapes[index];
                    shapes[index] = newCross;
                    cout << "Cross data updated successfully.\n";
                } else {
                    cout << "Invalid cross data. Changes discarded.\n";
                    delete newCross;
                }
            }
            else if (name == "Circle") {
                int centerX = getValidatedInt("Enter new center x-coordinate: ");
                int centerY = getValidatedInt("Enter new center y-coordinate: ");
                int radius = getValidatedInt("Enter new radius (must be positive): ", 1);
                
                Circle* newCircle = new Circle(name, warpSpace, centerX, centerY, radius);
                delete shapes[index];
                shapes[index] = newCircle;
                cout << "Circle data updated successfully.\n";
            }
            break;
        }
        case 4:
            cout << "Edit cancelled.\n";
            return;
    }
    
    shapes[index]->computeArea();
}

void deleteShape(vector<ShapeTwoD*>& shapes) {
    if (shapes.empty()) {
        cout << "No shapes available to delete.\n";
        return;
    }
    
    printShapesReport(shapes);
    int index = getValidatedInt("Enter shape index to delete: ", 0, shapes.size() - 1);
    
    cout << "\nAre you sure you want to delete Shape [" << index << "]? (y/n): ";
    char confirm;
    cin >> confirm;
    clearInputBuffer();
    
    if (tolower(confirm) == 'y') {
        delete shapes[index];
        shapes.erase(shapes.begin() + index);
        cout << "Shape deleted successfully.\n";
    } else {
        cout << "Deletion cancelled.\n";
    }
}

int main() {
    vector<ShapeTwoD*> shapes;
    int choice;
    
    do {
        displayMainMenu();
        choice = getValidatedInt("", 1, 8);
        
        switch (choice) {
            case 1:
                inputSensorData(shapes);
                break;
            case 2:
                computeAreas(shapes);
                break;
            case 3:
                printShapesReport(shapes);
                break;
            case 4:
                sortShapes(shapes);
                break;
            case 5:
                searchShapesByCoordinates(shapes);
                break;
            case 6:
                editShape(shapes);
                break;
            case 7:
                deleteShape(shapes);
                break;
            case 8:
                cout << "Exiting program...\n";
                break;
        }
    } while (choice != 8);
    
    //clean up
    for (auto shape : shapes) {
        delete shape;
    }
    
    return 0;
}