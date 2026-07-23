# compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g

# files
TARGET = main
SRCS = main.cpp
OBJS = $(SRCS .cpp=.o)

# default target (type make)
all: $(TARGET)

# link object files into finaL executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(OBJS)

# compile each .cpp into a .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# remove build artifacts
clean:
	rm -rf $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run