CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2 -Iincludes
TARGET = arena

SRCS = src/arena.cc src/main.cc
OBJS = $(SRCS:.cc=.o)


.PHONY: all clean run


all: $(TARGET)


$(TARGET): $(OBJS) 
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)


src/%.o: src/%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@


run: $(TARGET)
	./$(TARGET)


clean:
	rm -f $(OBJS) $(TARGET)
