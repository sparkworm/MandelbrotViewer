CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Iinclude -Iexternal/lodepng

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o) external/lodepng/lodepng.o

TARGET = viewer

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

external/lodepng/lodepng.o: external/lodepng/lodepng.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f src/*.o external/lodepng/*.o $(TARGET)
