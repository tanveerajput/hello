# Tic-Tac-Toe Game in C++

A comprehensive, object-oriented implementation of the classic Tic-Tac-Toe game written in modern C++17.

## 🎮 Features

- **Interactive Console Interface**: Clean, user-friendly text-based interface
- **Player Statistics**: Track wins, losses, draws, and win rates
- **Input Validation**: Robust error handling for all user inputs
- **Modern C++ Design**: Uses smart pointers, RAII, and proper OOP principles
- **Cross-Platform**: Works on Windows, macOS, and Linux
- **Multiple Build Systems**: Support for both CMake and traditional Makefile

## 🏗️ Architecture

The game is built with a clean, modular architecture:

### Core Classes

- **`Game`**: Main game controller managing the overall flow
- **`Board`**: Manages the 3x3 game board and win detection
- **`Player`**: Represents players with statistics tracking

### Key Design Principles

- **Single Responsibility**: Each class has a clear, focused purpose
- **Encapsulation**: Private members with controlled public interfaces
- **Resource Management**: Smart pointers for automatic memory management
- **Error Handling**: Comprehensive input validation and exception handling

## 🚀 Quick Start

### Prerequisites

- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- CMake 3.12+ (optional, for CMake build)
- Make (optional, for Makefile build)

### Building the Game

#### Option 1: Using CMake (Recommended)

```bash
# Create build directory
mkdir build && cd build

# Configure the project
cmake ..

# Build the game
make

# Run the game
./bin/TicTacToe
```

#### Option 2: Using Makefile

```bash
# Build the game
make

# Run the game
make run
```

#### Option 3: Manual Compilation

```bash
# Compile all source files
g++ -std=c++17 -Wall -Wextra -O2 main.cpp Game.cpp Board.cpp Player.cpp -o tictactoe

# Run the game
./tictactoe
```

## 🎯 How to Play

1. **Start the Game**: Run the executable and enter player names
2. **Make Moves**: Enter row and column numbers (1-3) when prompted
3. **Win Condition**: Get three of your symbols in a row (horizontal, vertical, or diagonal)
4. **Game Modes**: 
   - Play single games
   - View statistics
   - Reset statistics
   - Read instructions

### Game Board Layout

```
    1   2   3
   +---+---+---+
1  |   |   |   |
   +---+---+---+
2  |   |   |   |
   +---+---+---+
3  |   |   |   |
   +---+---+---+
```

## 📁 Project Structure

```
tic-tac-toe/
├── main.cpp           # Entry point
├── Game.h/.cpp        # Game controller
├── Board.h/.cpp       # Board management
├── Player.h/.cpp      # Player representation
├── CMakeLists.txt     # CMake build configuration
├── Makefile           # Traditional make build
└── README.md          # This file
```

## 🔧 Build Options

### CMake Build Types

```bash
# Debug build (with debugging symbols)
cmake -DCMAKE_BUILD_TYPE=Debug ..
make

# Release build (optimized)
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

### Makefile Targets

```bash
make all      # Build the game (default)
make debug    # Build with debug flags
make release  # Build with optimization
make run      # Build and run
make clean    # Clean build artifacts
make install  # Install system-wide (requires sudo)
make help     # Show all available targets
```

## 🎨 Code Examples

### Creating and Running a Game

```cpp
#include "Game.h"

int main() {
    Game game;
    game.run();
    return 0;
}
```

### Working with the Board

```cpp
Board board;
board.display();                    // Show current state
board.makeMove(0, 0, 'X');         // Place X at position (0,0)
char winner = board.checkWinner();  // Check for winner
bool full = board.isFull();         // Check if board is full
```

### Player Management

```cpp
Player player('X', "Alice");
player.addWin();                    // Record a win
player.displayStats();              // Show statistics
```

## 🧪 Testing

The game includes comprehensive input validation and error handling:

- **Invalid Coordinates**: Handles out-of-bounds moves
- **Occupied Positions**: Prevents overwriting existing moves
- **Invalid Input Types**: Handles non-numeric input gracefully
- **Memory Safety**: Uses smart pointers to prevent memory leaks

## 🔍 Advanced Features

### Statistics Tracking

- **Win/Loss/Draw Counts**: Complete game history
- **Win Rate Calculation**: Percentage-based performance metrics
- **Session Persistence**: Statistics maintained during game session
- **Reset Functionality**: Clear statistics when needed

### Input Validation

- **Range Checking**: Ensures coordinates are within 1-3
- **Type Validation**: Handles non-integer input
- **Buffer Clearing**: Prevents input stream corruption
- **Error Recovery**: Allows users to retry after invalid input

## 🤝 Contributing

This is a complete, educational implementation. Potential enhancements:

- AI opponent with different difficulty levels
- Network multiplayer support
- GUI interface using Qt or similar
- Save/load game functionality
- Tournament mode with multiple players

## 📄 License

This project is provided as-is for educational purposes. Feel free to use, modify, and distribute.

## 🐛 Troubleshooting

### Common Issues

1. **Compilation Errors**
   - Ensure C++17 support: `g++ --version`
   - Check compiler flags: `-std=c++17`

2. **Runtime Issues**
   - Verify executable permissions: `chmod +x tictactoe`
   - Check terminal compatibility for special characters

3. **Build System Issues**
   - CMake: Ensure version 3.12+: `cmake --version`
   - Make: Verify GNU Make: `make --version`

### Getting Help

If you encounter issues:
1. Check the compiler error messages carefully
2. Ensure all source files are in the same directory
3. Verify your C++ compiler supports C++17 features
4. Try the manual compilation method if build systems fail

---

**Enjoy playing Tic-Tac-Toe!** 🎉