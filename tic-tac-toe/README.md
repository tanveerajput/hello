# 🎮 Tic Tac Toe - C++ WebAssembly Game

A modern, interactive Tic Tac Toe game built with C++ and compiled to WebAssembly for web browsers.

## ✨ Features

- **C++ Game Logic**: Core game mechanics implemented in C++
- **WebAssembly Performance**: Compiled to WASM for near-native performance
- **Modern UI**: Beautiful, responsive web interface
- **Real-time Updates**: Instant game state updates
- **Cross-platform**: Runs in any modern web browser

## 🛠️ Prerequisites

To build this project, you need:

1. **Emscripten SDK**: For compiling C++ to WebAssembly
   ```bash
   # Install Emscripten
   git clone https://github.com/emscripten-core/emsdk.git
   cd emsdk
   ./emsdk install latest
   ./emsdk activate latest
   source ./emsdk_env.sh
   ```

2. **CMake**: Version 3.16 or higher
   ```bash
   # On Ubuntu/Debian
   sudo apt install cmake
   
   # On macOS
   brew install cmake
   ```

## 🚀 Quick Start

1. **Clone and navigate to the project:**
   ```bash
   cd tic-tac-toe
   ```

2. **Build the WebAssembly module:**
   ```bash
   ./build.sh
   ```

3. **Start a local web server:**
   ```bash
   cd web
   python3 -m http.server 8000
   # or use any other static file server
   # npx serve .
   # php -S localhost:8000
   ```

4. **Open your browser:**
   Navigate to `http://localhost:8000`

## 📁 Project Structure

```
tic-tac-toe/
├── src/
│   ├── tictactoe.cpp      # C++ game logic and WASM bindings
│   └── test.cpp           # Native testing (optional)
├── web/
│   ├── index.html         # Game HTML structure
│   ├── style.css          # Modern CSS styling
│   ├── game.js            # JavaScript UI controller
│   ├── tictactoe.js       # Generated WASM JavaScript glue
│   └── tictactoe.wasm     # Generated WebAssembly binary
├── build/                 # Build artifacts
├── CMakeLists.txt         # Build configuration
├── build.sh              # Build script
└── README.md             # This file
```

## 🎯 How It Works

1. **C++ Core**: The game logic is implemented in C++ with a `TicTacToe` class that manages:
   - Game state (board, current player, winner)
   - Move validation and execution
   - Win condition checking
   - Game reset functionality

2. **WebAssembly Bridge**: C++ functions are exported to WebAssembly using Emscripten bindings:
   ```cpp
   extern "C" {
       bool makeMove(int row, int col);
       char getCell(int row, int col);
       char getCurrentPlayer();
       // ... more functions
   }
   ```

3. **JavaScript Interface**: The web UI communicates with the C++ code through WASM:
   ```javascript
   const moveSuccess = Module.ccall('makeMove', 'boolean', ['number', 'number'], [row, col]);
   ```

## 🎨 Features Showcase

- **Responsive Design**: Works on desktop and mobile devices
- **Visual Feedback**: Hover effects, animations, and winner highlighting
- **Real-time Status**: Shows current player and game status
- **Modern Styling**: Gradient backgrounds, smooth transitions, and clean typography
- **Performance**: C++ logic ensures fast game state calculations

## 🔧 Development

### Native Testing
You can test the C++ logic natively without WebAssembly:

```bash
mkdir build-native
cd build-native
cmake ..
make
./tictactoe_test
```

### Customization
- Modify `src/tictactoe.cpp` for game logic changes
- Update `web/style.css` for visual customization
- Edit `web/game.js` for UI behavior modifications

## 🌐 Browser Compatibility

This game works in all modern browsers that support WebAssembly:
- Chrome 57+
- Firefox 52+
- Safari 11+
- Edge 16+

## 📝 License

This project is open source and available under the MIT License.

## 🤝 Contributing

Feel free to fork this project and submit pull requests for improvements!

---

**Enjoy playing Tic Tac Toe with the power of C++ and WebAssembly! 🎉**