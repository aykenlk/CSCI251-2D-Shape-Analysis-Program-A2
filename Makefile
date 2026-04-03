# Makefile for Assn2

# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -g -I.
LDFLAGS = 

# Source files
SOURCES = Assn2.cpp \
		  ShapeTwoD.cpp \
		  Square.cpp \
		  Rectangle.cpp \
		  Cross.cpp \
		  Circle.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Executable name
TARGET = assn2

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)

# Compile source files to object files
%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Additional rule for Assn2.cpp (no header)
Assn2.o: Assn2.cpp ShapeTwoD.h Square.h Rectangle.h Cross.h Circle.h
	$(CXX) $(CXXFLAGS) -c Assn2.cpp -o Assn2.o

# Clean up build files
clean:
	rm -f $(OBJECTS) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean run
