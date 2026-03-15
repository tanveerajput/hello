# 🚀 Quick Start Guide

## Option 1: Simple JavaScript Version (Recommended)

**Ready to play immediately!**

```bash
cd tic-tac-toe
./start-server.sh
```

Then open **http://localhost:8000** in your browser.

## Option 2: C++ WebAssembly Version (Advanced)

If you want the full C++ WebAssembly experience:

1. **Install Emscripten:**
   ```bash
   # Download and install Emscripten SDK
   git clone https://github.com/emscripten-core/emsdk.git
   cd emsdk
   ./emsdk install latest
   ./emsdk activate latest
   source ./emsdk_env.sh
   ```

2. **Build WebAssembly:**
   ```bash
   cd tic-tac-toe
   ./build.sh
   ```

3. **Update HTML:**
   Edit `web/index.html` and change:
   ```html
   <script src="tictactoe-fallback.js"></script>
   ```
   to:
   ```html
   <script src="tictactoe.js"></script>
   ```

4. **Start server:**
   ```bash
   ./start-server.sh
   ```

## 🎮 How to Play

1. **Click** on any empty cell to place your mark (X or O)
2. **Take turns** - the game automatically switches between players
3. **Win** by getting three in a row (horizontal, vertical, or diagonal)
4. **Reset** the game anytime with the "New Game" button

## 🌟 Features

- ✅ Beautiful, responsive design
- ✅ Smooth animations and hover effects
- ✅ Winner highlighting
- ✅ Real-time game status
- ✅ Works on desktop and mobile
- ✅ No external dependencies

**Enjoy your game! 🎉**