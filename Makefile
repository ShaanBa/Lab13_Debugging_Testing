# Makefile for Lab 13

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -g -Wall

# Target executable name
TARGET = lab13

# Build rule
all: $(TARGET)

$(TARGET): attendance_test.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) attendance_test.cpp

# Clean rule
clean:
	rm -f $(TARGET)