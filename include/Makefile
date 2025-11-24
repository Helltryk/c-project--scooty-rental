# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I../src

# Source directory
SRC_DIR = ../src

# Source files
SOURCES = $(SRC_DIR)/main.c $(SRC_DIR)/rental_manager.c
HEADERS = $(SRC_DIR)/rental_manager.h

# Object files (in current directory - include/)
OBJECTS = main.o rental_manager.o

# Target executable
TARGET = scooter_rental

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "Build successful! Run with: ./$(TARGET)"

# Compile main.c to main.o
main.o: $(SRC_DIR)/main.c $(HEADERS)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o main.o

# Compile rental_manager.c to rental_manager.o
rental_manager.o: $(SRC_DIR)/rental_manager.c $(HEADERS)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/rental_manager.c -o rental_manager.o

# Clean build files
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "Clean complete!"

# Run the program
run: $(TARGET)
	./$(TARGET)

# Rebuild everything
rebuild: clean all

.PHONY: all clean run rebuild
