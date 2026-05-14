# Variables
# ----------------------------------
# EXEC = dijkstra
# CC = g++
# CFLAGS = -c -Wall
# ----------------------------------
EXEC := dijkstra
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -g -O0 -Iinclude -MMD -MP

SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin

SRCS := src/main.cpp src/util.cpp src/heap.cpp src/graph.cpp src/stack.cpp
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

TARGET := $(BIN_DIR)/$(EXEC)

.PHONY: all run clean rebuild

# $(EXEC) :main.o util.o heap.o Graph.o stack.o
# 	$(CC) -o $(EXEC) main.o util.o heap.o Graph.o stack.o

# main.o :main.cpp
# 	$(CC) $(CFLAGS) main.cpp

# util.o :util.h util.cpp
# 	$(CC) $(CFLAGS) util.cpp

# heap.o :heap.h heap.cpp
# 	$(CC) $(CFLAGS) heap.cpp

# Graph.o :Graph.h Graph.cpp
# 	$(CC) $(CFLAGS) Graph.cpp

# stack.o :stack.h stack.cpp
# 	$(CC) $(CFLAGS) stack.cpp

# clean :
# 	rm *.o

all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR) $(BIN_DIR):
	mkdir -p $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

rebuild: clean all

-include $(DEPS)