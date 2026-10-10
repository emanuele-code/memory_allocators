CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2
TARGET = arena

SRCS = arena.cc main.cc
OBJS = $(SRCS:.cc=.o)


.PHONY: all clean run


all: $(TARGET)


$(TARGET): $(OBJS) 
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)


%.o: %.cc arena.h
	$(CXX) $(CXXFLAGS) -c $< -o $@


run: $(TARGET)
	./$(TARGET)


clean:
	rm -f $(OBJS) $(TARGET)
