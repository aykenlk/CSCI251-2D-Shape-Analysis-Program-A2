# 2D Shape Analysis System

A C++ console application that processes sensor data for 2D shapes (Square, Rectangle, Cross, Circle), computes areas, checks point inclusion, and provides interactive reporting, sorting, searching, editing, and deletion of shapes. Implements object‑oriented principles: inheritance, polymorphism, encapsulation.

## Features

- **Input Sensor Data** – Add shapes by entering vertices (Square, Rectangle, Cross) or center+radius (Circle). Validates geometric correctness.
- **Compute Area** – Calculates area for all stored shapes using shape‑specific formulas.
- **Print Shapes Report** – Displays detailed info: vertices, area, special type (WS/NS), points on perimeter and within shape.
- **Sort Shape Data** – Sort by area (ascending/descending) or by special type (WS first) + area.
- **Search Shapes by Coordinates** – Find which shape(s) contain or lie on a given (x,y) point.
- **Edit Shape** – Modify name, special type, or geometric data (vertices/radius) with re‑validation.
- **Delete Shape** – Remove a shape with confirmation prompt.

## Class Hierarchy

- **`ShapeTwoD`** (abstract base class) – Declares pure virtual methods: `computeArea()`, `isPointInShape()`, `isPointOnShape()`, `toString()`, `validateShape()`, plus getters/setters.
- **`Square`** – 4 vertices, equal sides, right angles. Computes area as side².
- **`Rectangle`** – Inherits from Square, validates opposite sides equal.
- **`Cross`** – 12 vertices, plus‑shaped. Area computed via bounding‑rectangle minus four corner rectangles.
- **`Circle`** – Center (x,y) and radius. Area = π·r². Perimeter points: only 4 cardinal points (N,S,E,W).

## Compilation & Execution

### Requirements
- C++11 or later compiler (g++, clang++, MSVC)

### Compile (using provided Makefile)
```bash
make
```

### Compile manually
```bash
g++ -std=c++11 Assn2.cpp ShapeTwoD.cpp Square.cpp Rectangle.cpp Cross.cpp Circle.cpp -o shape_analyzer
```

### Run
```bash
./shape_analyzer
```

## Input Formats

### Square / Rectangle
Enter 4 vertices (x y) in clockwise or counter‑clockwise order:
```
Point 1: 0 0
Point 2: 0 4
Point 3: 4 4
Point 4: 4 0
```

### Cross
Enter 12 vertices (x y) in order:
```
Point 1: 2 0
Point 2: 2 2
...
```

### Circle
```
Enter center x-coordinate: 5
Enter center y-coordinate: 5
Enter radius (must be positive): 3
```

### Special Type
- **WS** – Warp Space (contains warp field)
- **NS** – Normal Space

## Menu Options

```
1) Input sensor data
2) Compute area (for all records)
3) Print shapes report
4) Sort shape data
5) Search shapes by coordinates
6) Edit shape
7) Delete shape
8) Exit
```

## Sample Output (Shape Report)

```
Shape [0]
Name: Square
Special Type: WS
Area: 16 units square
Vertices:
Point [0] : (0, 0)
Point [1] : (0, 4)
Point [2] : (4, 4)
Point [3] : (4, 0)
Points on perimeter: (1,0), (2,0), (3,0), (4,1), (4,2), (4,3), (3,4), (2,4), (1,4), (0,3), (0,2), (0,1)
Points within shape: (1,1), (1,2), (1,3), (2,1), (2,2), (2,3), (3,1), (3,2), (3,3)
```

## Key Technical Details

- **Polymorphism** – All shapes stored as `ShapeTwoD*`, virtual functions ensure correct behaviour.
- **Input Validation** – Rejects non‑integer coordinates, invalid shape geometries, out‑of‑range indices.
- **Memory Management** – Manual `new`/`delete` with cleanup in `main()`.
- **Sorting** – Uses STL `sort` with custom comparators (area, special type, name tie‑breaker).
- **Point‑in‑Shape** – Ray casting for Cross, bounding‑box checks for squares/rectangles, distance for circles.
- **Area Tolerance** – `AREA_TOLERANCE = 0.0001` for floating‑point comparisons.

## Edge Cases Handled

- Shapes with minimal dimensions (side length = 1)
- Points exactly on perimeter
- Duplicate areas (tie‑break by special type then name)
- Invalid cross vertex order (detected and rejected)
- Negative coordinates (allowed)

## Future Improvements

- File I/O (save/load shape configurations)
- GUI visualization
- Support for rotated shapes
- Pathfinding algorithms (A*, Dijkstra) for “2D‑StarFleet” theme
- Smart pointers (`std::unique_ptr`) to replace manual memory management
- Unit testing framework (Google Test)

## Author

Ayken Kang Lee   
CSCI251 Assignment 2
