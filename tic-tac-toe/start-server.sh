#!/bin/bash

echo "🎮 Starting Tic Tac Toe Game Server..."

# Kill any existing server on port 8000
pkill -f "python3 -m http.server 8000" 2>/dev/null || true

# Navigate to web directory
cd "$(dirname "$0")/web"

echo "📁 Serving files from: $(pwd)"
echo "🌐 Starting server on http://localhost:8000"
echo ""
echo "🎯 Game features:"
echo "   ✅ Interactive 3x3 grid"
echo "   ✅ Two-player gameplay (X and O)"
echo "   ✅ Win detection and highlighting"
echo "   ✅ Game reset functionality"
echo "   ✅ Responsive design"
echo ""
echo "📖 Instructions:"
echo "   1. Click on any empty cell to make a move"
echo "   2. Players alternate between X and O"
echo "   3. First to get 3 in a row wins!"
echo "   4. Click 'New Game' to restart"
echo ""
echo "🔗 Open this URL in your browser:"
echo "   http://localhost:8000"
echo ""
echo "⏹️  Press Ctrl+C to stop the server"
echo ""

# Start the server
python3 -m http.server 8000