#Compiler
CXX = g++
CXXFLAGS = -Wall -std=c++17 -I/home/mryvkin/SDL/include
LDFLAGS = /home/mryvkin/SDL/build-static/libSDL3.a -lm -ldl -lpthread

# Executable
TARGET = Hypercube 

# Source Files
SRCS := $(wildcard *.cpp)

# Object Files
OBJS = $(SRCS:.cpp=.o)

# Build the executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile each .cpp into a .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)

	


