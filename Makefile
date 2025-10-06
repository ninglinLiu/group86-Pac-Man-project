# Makefile for Pac-Man Game
# Compiles with C11 standard and strict warnings

CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -O2 -g
SRCDIR = src
OBJDIR = obj

# Source files
SOURCES = $(SRCDIR)/game.c $(SRCDIR)/board.c $(SRCDIR)/render.c \
          $(SRCDIR)/input.c $(SRCDIR)/ghost.c $(SRCDIR)/rng.c
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
MAIN_OBJECT = main.o
TEST_OBJECT = tests.o

# Default target
all: pacman

# Create object directory
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Compile object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile main executable
pacman: $(OBJECTS) $(MAIN_OBJECT)
	$(CC) $(CFLAGS) -o pacman $(MAIN_OBJECT) $(OBJECTS)

# Compile test executable
tests: $(OBJECTS) $(TEST_OBJECT)
	$(CC) $(CFLAGS) -o tests $(TEST_OBJECT) $(OBJECTS)

# Run the game with default parameters
run: pacman
	./pacman -s 12345 -g 4

# Run all tests
test: tests
	./tests

# Clean build artifacts
clean:
	rm -f pacman tests *.o $(OBJDIR)/*.o
	rm -rf $(OBJDIR)
	rm -f tests/*.txt

# Install dependencies (none required for standard C)
install:
	@echo "No external dependencies required"

# Show help
help:
	@echo "Available targets:"
	@echo "  all     - Build the main game (default)"
	@echo "  pacman  - Build the main game executable"
	@echo "  tests   - Build the test suite"
	@echo "  run     - Run the game with default parameters"
	@echo "  test    - Run all tests"
	@echo "  clean   - Remove all build artifacts"
	@echo "  help    - Show this help message"

.PHONY: all pacman tests run test clean install help
