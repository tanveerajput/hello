# Makefile for Tic-Tac-Toe Game
# Simple build system for compiling the game

# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -O2
DEBUG_FLAGS = -g -O0 -DDEBUG
RELEASE_FLAGS = -O3 -DNDEBUG

# Project settings
TARGET = tictactoe
SOURCES = main.cpp Game.cpp Board.cpp Player.cpp
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = Game.h Board.h Player.h

# Build directories
BUILD_DIR = build
BIN_DIR = bin

# Default target
all: $(TARGET)

# Create executable
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(BIN_DIR)/$(TARGET)
	@echo "Build complete! Executable: $(BIN_DIR)/$(TARGET)"

# Compile source files to object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Debug build
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: clean $(TARGET)
	@echo "Debug build complete!"

# Release build
release: CXXFLAGS += $(RELEASE_FLAGS)
release: clean $(TARGET)
	@echo "Release build complete!"

# Create directories
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Run the game
run: $(TARGET)
	./$(BIN_DIR)/$(TARGET)

# Clean build artifacts
clean:
	rm -f $(OBJECTS)
	rm -rf $(BIN_DIR)
	@echo "Clean complete!"

# Install (copy to /usr/local/bin)
install: $(TARGET)
	sudo cp $(BIN_DIR)/$(TARGET) /usr/local/bin/
	@echo "Installation complete! You can now run 'tictactoe' from anywhere."

# Uninstall
uninstall:
	sudo rm -f /usr/local/bin/$(TARGET)
	@echo "Uninstallation complete!"

# Show help
help:
	@echo "Available targets:"
	@echo "  all      - Build the game (default)"
	@echo "  debug    - Build with debug flags"
	@echo "  release  - Build with optimization flags"
	@echo "  run      - Build and run the game"
	@echo "  clean    - Remove build artifacts"
	@echo "  install  - Install to system (requires sudo)"
	@echo "  uninstall- Remove from system (requires sudo)"
	@echo "  help     - Show this help message"

# Phony targets
.PHONY: all debug release run clean install uninstall help