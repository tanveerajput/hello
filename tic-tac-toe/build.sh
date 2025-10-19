#!/bin/bash

# Tic Tac Toe C++ WebAssembly Build Script

set -e  # Exit on any error

echo "🎮 Building Tic Tac Toe C++ WebAssembly Game..."

# Check if Emscripten is installed
if ! command -v emcc &> /dev/null; then
    echo "❌ Error: Emscripten not found!"
    echo "Please install Emscripten first:"
    echo "1. Download and install from: https://emscripten.org/docs/getting_started/downloads.html"
    echo "2. Run: source /path/to/emsdk/emsdk_env.sh"
    exit 1
fi

echo "✅ Emscripten found: $(emcc --version | head -n1)"

# Create build directory
mkdir -p build
cd build

echo "🔧 Configuring with CMake..."
emcmake cmake ..

echo "🔨 Building WebAssembly module..."
emmake make

echo "📁 Files generated:"
ls -la tictactoe.*

echo "🎉 Build completed successfully!"
echo ""
echo "📋 To run the game:"
echo "1. Start a local web server in the 'web' directory:"
echo "   cd ../web"
echo "   python3 -m http.server 8000"
echo "   # or"
echo "   npx serve ."
echo ""
echo "2. Open http://localhost:8000 in your browser"
echo ""
echo "🎮 Enjoy your C++ WebAssembly Tic Tac Toe game!"