# GNU Makefile for C project

# Compiler
CC := gcc

# Compiler flags
CFLAGS := -Wall -Wextra -std=gnu99 -lm

# Source files directory
SRC_DIR := src

# Output directory
OUT_DIR := build

# Executable name
EXECUTABLE := my_program

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OUT_DIR)/%.o, $(SRCS))

# Target: all (default target)
all: $(OUT_DIR)/$(EXECUTABLE)

# Rule to build the executable
$(OUT_DIR)/$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Rule to build object files
$(OUT_DIR)/%.o: $(SRC_DIR)/%.c | $(OUT_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create output directory
$(OUT_DIR):
	mkdir -p $(OUT_DIR)

# Target: clean
clean:
	rm -rf $(OUT_DIR)

# Phony targets
.PHONY: all clean
