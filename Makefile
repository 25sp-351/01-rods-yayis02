# Compiler and flags
CC = clang
CFLAGS = -g -Wall

# The name of the executable
TARGET = main

# Default target (the target that will be built if no target is specified)
all: $(TARGET)

# Rule for creating the executable
$(TARGET): 01_rods.c
	$(CC) $(CFLAGS) -o $(TARGET) 01_rods.c

# Clean up generated files
clean:
	rm -f $(TARGET)
