#	Makefile
#   Authors: M00909998, M00906834
#   Created: 29/03/2024
#   Updated: 21/04/2024

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic  
SOURCES = main.cpp bus.cpp
TEST_SOURCES = test.cpp bus.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)
TARGET = bustracking
TEST_TARGET = testbus

all: $(TARGET) $(TEST_TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Compiling the test executable into testbus.exe
$(TEST_TARGET): $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJECTS)

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJECTS) $(TEST_OBJECTS) $(TARGET) $(TEST_TARGET)

.PHONY: all clean
