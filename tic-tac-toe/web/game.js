class TicTacToeUI {
    constructor() {
        this.wasmModule = null;
        this.isLoading = true;
        this.initializeUI();
        this.waitForWasm();
    }

    initializeUI() {
        // Get DOM elements
        this.board = document.getElementById('game-board');
        this.currentPlayerElement = document.getElementById('current-player');
        this.gameStatusElement = document.getElementById('game-status');
        this.resetButton = document.getElementById('reset-button');
        this.loadingElement = document.getElementById('loading');
        this.techInfoElement = document.getElementById('tech-info');

        // Add event listeners
        this.resetButton.addEventListener('click', () => this.resetGame());
        this.board.addEventListener('click', (e) => this.handleCellClick(e));

        // Initially disable interactions
        this.setInteractionsEnabled(false);
    }

    async waitForWasm() {
        // Wait for the module to load (WebAssembly or JavaScript fallback)
        const checkModule = () => {
            if (typeof Module !== 'undefined' && Module.ccall) {
                this.wasmModule = Module;
                this.onWasmReady();
            } else {
                setTimeout(checkModule, 100);
            }
        };
        checkModule();
    }

    onWasmReady() {
        console.log('Game engine loaded successfully!');
        this.isLoading = false;
        
        // Hide loading, show tech info
        this.loadingElement.style.display = 'none';
        this.techInfoElement.style.display = 'block';
        
        // Enable interactions
        this.setInteractionsEnabled(true);
        
        // Initialize game
        this.updateUI();
    }

    setInteractionsEnabled(enabled) {
        const cells = this.board.querySelectorAll('.cell');
        cells.forEach(cell => {
            cell.style.pointerEvents = enabled ? 'auto' : 'none';
            cell.style.opacity = enabled ? '1' : '0.5';
        });
        this.resetButton.disabled = !enabled;
    }

    handleCellClick(event) {
        if (this.isLoading || !this.wasmModule) return;

        const cell = event.target;
        if (!cell.classList.contains('cell')) return;

        const row = parseInt(cell.dataset.row);
        const col = parseInt(cell.dataset.col);

        // Try to make the move using C++ function
        const moveSuccess = this.wasmModule.ccall('makeMove', 'boolean', ['number', 'number'], [row, col]);
        
        if (moveSuccess) {
            this.updateUI();
        }
    }

    updateUI() {
        if (!this.wasmModule) return;

        // Update board display
        const cells = this.board.querySelectorAll('.cell');
        cells.forEach(cell => {
            const row = parseInt(cell.dataset.row);
            const col = parseInt(cell.dataset.col);
            const cellValue = this.wasmModule.ccall('getCell', 'number', ['number', 'number'], [row, col]);
            
            // Convert char code to character
            const cellChar = cellValue === 32 ? '' : String.fromCharCode(cellValue); // 32 is space
            
            cell.textContent = cellChar;
            cell.className = 'cell';
            if (cellChar === 'X') {
                cell.classList.add('x');
            } else if (cellChar === 'O') {
                cell.classList.add('o');
            }
        });

        // Update current player
        const currentPlayer = String.fromCharCode(this.wasmModule.ccall('getCurrentPlayer', 'number', [], []));
        this.currentPlayerElement.textContent = currentPlayer;
        this.currentPlayerElement.className = currentPlayer === 'X' ? 'player-x' : 'player-o';

        // Check game status
        const isGameOver = this.wasmModule.ccall('isGameOver', 'boolean', [], []);
        if (isGameOver) {
            const winner = String.fromCharCode(this.wasmModule.ccall('getWinner', 'number', [], []));
            this.handleGameEnd(winner);
        } else {
            this.gameStatusElement.textContent = `Player ${currentPlayer}'s turn`;
        }
    }

    handleGameEnd(winner) {
        if (winner === 'T') {
            this.gameStatusElement.textContent = "It's a tie! 🤝";
        } else {
            this.gameStatusElement.textContent = `Player ${winner} wins! 🎉`;
            this.highlightWinningCells();
        }
    }

    highlightWinningCells() {
        // Simple winning line detection for visual effect
        const cells = this.board.querySelectorAll('.cell');
        
        // Check rows
        for (let i = 0; i < 3; i++) {
            const row = [
                cells[i * 3],
                cells[i * 3 + 1], 
                cells[i * 3 + 2]
            ];
            if (this.isWinningLine(row)) {
                row.forEach(cell => cell.classList.add('winner-cell'));
                return;
            }
        }

        // Check columns
        for (let i = 0; i < 3; i++) {
            const col = [
                cells[i],
                cells[i + 3],
                cells[i + 6]
            ];
            if (this.isWinningLine(col)) {
                col.forEach(cell => cell.classList.add('winner-cell'));
                return;
            }
        }

        // Check diagonals
        const diag1 = [cells[0], cells[4], cells[8]];
        const diag2 = [cells[2], cells[4], cells[6]];
        
        if (this.isWinningLine(diag1)) {
            diag1.forEach(cell => cell.classList.add('winner-cell'));
        } else if (this.isWinningLine(diag2)) {
            diag2.forEach(cell => cell.classList.add('winner-cell'));
        }
    }

    isWinningLine(cells) {
        const values = cells.map(cell => cell.textContent);
        return values[0] !== '' && values[0] === values[1] && values[1] === values[2];
    }

    resetGame() {
        if (!this.wasmModule) return;

        this.wasmModule.ccall('resetGame', null, [], []);
        
        // Clear visual effects
        const cells = this.board.querySelectorAll('.cell');
        cells.forEach(cell => {
            cell.classList.remove('winner-cell');
        });

        this.updateUI();
    }
}

// Initialize the game when the page loads
document.addEventListener('DOMContentLoaded', () => {
    new TicTacToeUI();
});