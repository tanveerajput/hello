// JavaScript fallback implementation of the C++ TicTacToe game logic
// This allows the game to work without WebAssembly

class TicTacToeGame {
    constructor() {
        this.board = [
            [' ', ' ', ' '],
            [' ', ' ', ' '],
            [' ', ' ', ' ']
        ];
        this.currentPlayer = 'X';
        this.gameOver = false;
        this.winner = ' ';
    }

    makeMove(row, col) {
        if (this.gameOver || row < 0 || row >= 3 || col < 0 || col >= 3 || this.board[row][col] !== ' ') {
            return false;
        }

        this.board[row][col] = this.currentPlayer;
        
        if (this.checkWinCondition()) {
            this.gameOver = true;
            this.winner = this.currentPlayer;
        } else if (this.isBoardFull()) {
            this.gameOver = true;
            this.winner = 'T'; // Tie
        } else {
            this.currentPlayer = (this.currentPlayer === 'X') ? 'O' : 'X';
        }

        return true;
    }

    getCell(row, col) {
        if (row >= 0 && row < 3 && col >= 0 && col < 3) {
            return this.board[row][col];
        }
        return ' ';
    }

    getCurrentPlayer() {
        return this.currentPlayer;
    }

    getWinner() {
        return this.winner;
    }

    isGameOver() {
        return this.gameOver;
    }

    resetGame() {
        this.board = [
            [' ', ' ', ' '],
            [' ', ' ', ' '],
            [' ', ' ', ' ']
        ];
        this.currentPlayer = 'X';
        this.gameOver = false;
        this.winner = ' ';
    }

    checkWinCondition() {
        // Check rows
        for (let i = 0; i < 3; i++) {
            if (this.board[i][0] !== ' ' && 
                this.board[i][0] === this.board[i][1] && 
                this.board[i][1] === this.board[i][2]) {
                return true;
            }
        }

        // Check columns
        for (let j = 0; j < 3; j++) {
            if (this.board[0][j] !== ' ' && 
                this.board[0][j] === this.board[1][j] && 
                this.board[1][j] === this.board[2][j]) {
                return true;
            }
        }

        // Check diagonals
        if (this.board[0][0] !== ' ' && 
            this.board[0][0] === this.board[1][1] && 
            this.board[1][1] === this.board[2][2]) {
            return true;
        }
        if (this.board[0][2] !== ' ' && 
            this.board[0][2] === this.board[1][1] && 
            this.board[1][1] === this.board[2][0]) {
            return true;
        }

        return false;
    }

    isBoardFull() {
        for (let i = 0; i < 3; i++) {
            for (let j = 0; j < 3; j++) {
                if (this.board[i][j] === ' ') {
                    return false;
                }
            }
        }
        return true;
    }
}

// Create a global game instance
window.ticTacToeGame = new TicTacToeGame();

// Mock WebAssembly Module interface for compatibility
window.Module = {
    ccall: function(funcName, returnType, argTypes, args) {
        const game = window.ticTacToeGame;
        
        switch(funcName) {
            case 'makeMove':
                return game.makeMove(args[0], args[1]);
            case 'getCell':
                return game.getCell(args[0], args[1]).charCodeAt(0);
            case 'getCurrentPlayer':
                return game.getCurrentPlayer().charCodeAt(0);
            case 'getWinner':
                return game.getWinner().charCodeAt(0);
            case 'isGameOver':
                return game.isGameOver();
            case 'resetGame':
                game.resetGame();
                return;
            default:
                console.warn('Unknown function:', funcName);
                return null;
        }
    }
};

console.log('JavaScript fallback TicTacToe loaded successfully!');