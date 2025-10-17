#!/bin/bash

# Build script for Tic-Tac-Toe Game
# This script provides an easy way to build and run the game

set -e  # Exit on any error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Function to print colored output
print_status() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Function to check if command exists
command_exists() {
    command -v "$1" >/dev/null 2>&1
}

# Function to build with CMake
build_cmake() {
    print_status "Building with CMake..."
    
    if ! command_exists cmake; then
        print_error "CMake not found! Please install CMake or use the Makefile option."
        return 1
    fi
    
    # Create build directory
    mkdir -p build
    cd build
    
    # Configure and build
    cmake .. -DCMAKE_BUILD_TYPE=Release
    make -j$(nproc 2>/dev/null || echo 4)
    
    cd ..
    print_success "CMake build completed! Executable: build/bin/TicTacToe"
}

# Function to build with Makefile
build_makefile() {
    print_status "Building with Makefile..."
    
    if ! command_exists make; then
        print_error "Make not found! Please install make or try manual compilation."
        return 1
    fi
    
    make release
    print_success "Makefile build completed! Executable: bin/tictactoe"
}

# Function to build manually
build_manual() {
    print_status "Building manually with g++..."
    
    if ! command_exists g++; then
        print_error "g++ not found! Please install a C++ compiler."
        return 1
    fi
    
    # Check C++17 support
    if ! g++ -std=c++17 -E -x c++ /dev/null >/dev/null 2>&1; then
        print_error "Your g++ compiler doesn't support C++17!"
        return 1
    fi
    
    mkdir -p bin
    g++ -std=c++17 -Wall -Wextra -O2 main.cpp Game.cpp Board.cpp Player.cpp -o bin/tictactoe
    print_success "Manual build completed! Executable: bin/tictactoe"
}

# Function to run the game
run_game() {
    print_status "Starting Tic-Tac-Toe game..."
    
    if [ -f "build/bin/TicTacToe" ]; then
        ./build/bin/TicTacToe
    elif [ -f "bin/tictactoe" ]; then
        ./bin/tictactoe
    else
        print_error "Game executable not found! Please build first."
        return 1
    fi
}

# Function to clean build artifacts
clean_build() {
    print_status "Cleaning build artifacts..."
    
    rm -rf build/
    rm -rf bin/
    rm -f *.o
    
    print_success "Clean completed!"
}

# Function to show help
show_help() {
    echo "Tic-Tac-Toe Build Script"
    echo "Usage: $0 [OPTION]"
    echo ""
    echo "Options:"
    echo "  build, -b       Build the game (auto-detect best method)"
    echo "  cmake, -c       Build using CMake"
    echo "  make, -m        Build using Makefile"
    echo "  manual, -M      Build manually with g++"
    echo "  run, -r         Run the game (build if necessary)"
    echo "  clean, -C       Clean build artifacts"
    echo "  help, -h        Show this help message"
    echo ""
    echo "Examples:"
    echo "  $0 build       # Build the game"
    echo "  $0 run         # Build and run the game"
    echo "  $0 clean       # Clean all build files"
}

# Main script logic
case "${1:-build}" in
    build|-b)
        print_status "Auto-detecting best build method..."
        if command_exists cmake; then
            build_cmake
        elif command_exists make; then
            build_makefile
        else
            build_manual
        fi
        ;;
    cmake|-c)
        build_cmake
        ;;
    make|-m)
        build_makefile
        ;;
    manual|-M)
        build_manual
        ;;
    run|-r)
        # Build if executable doesn't exist
        if [ ! -f "build/bin/TicTacToe" ] && [ ! -f "bin/tictactoe" ]; then
            print_status "Executable not found. Building first..."
            if command_exists cmake; then
                build_cmake
            elif command_exists make; then
                build_makefile
            else
                build_manual
            fi
        fi
        run_game
        ;;
    clean|-C)
        clean_build
        ;;
    help|-h|--help)
        show_help
        ;;
    *)
        print_error "Unknown option: $1"
        show_help
        exit 1
        ;;
esac