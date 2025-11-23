# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = scooter_rental

# Source files
SOURCES = main.c rental_manager.c
HEADERS = rental_manager.h
OBJECTS = $(SOURCES:.c=.o)

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "Build successful! Run with: ./$(TARGET)"

# Compile source files to object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

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
