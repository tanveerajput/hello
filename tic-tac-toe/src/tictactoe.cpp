#include <iostream>
#include <vector>
#include <string>

#ifdef __EMSCRIPTEN__
#include <emscripten/bind.h>
#include <emscripten.h>
#endif

class TicTacToe {
private:
    std::vector<std::vector<char>> board;
    char currentPlayer;
    bool gameOver;
    char winner;

public:
    TicTacToe() : board(3, std::vector<char>(3, ' ')), currentPlayer('X'), gameOver(false), winner(' ') {}

    bool makeMove(int row, int col) {
        if (gameOver || row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ') {
            return false;
        }

        board[row][col] = currentPlayer;
        
        if (checkWinCondition()) {
            gameOver = true;
            winner = currentPlayer;
        } else if (isBoardFull()) {
            gameOver = true;
            winner = 'T'; // Tie
        } else {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }

        return true;
    }

    char getCell(int row, int col) const {
        if (row >= 0 && row < 3 && col >= 0 && col < 3) {
            return board[row][col];
        }
        return ' ';
    }

    char getCurrentPlayer() const {
        return currentPlayer;
    }

    char getWinner() const {
        return winner;
    }

    bool isGameOver() const {
        return gameOver;
    }

    void resetGame() {
        board = std::vector<std::vector<char>>(3, std::vector<char>(3, ' '));
        currentPlayer = 'X';
        gameOver = false;
        winner = ' ';
    }

    std::string getBoardString() const {
        std::string result = "";
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                result += board[i][j];
            }
        }
        return result;
    }

private:
    bool checkWinCondition() {
        // Check rows
        for (int i = 0; i < 3; i++) {
            if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
                return true;
            }
        }

        // Check columns
        for (int j = 0; j < 3; j++) {
            if (board[0][j] != ' ' && board[0][j] == board[1][j] && board[1][j] == board[2][j]) {
                return true;
            }
        }

        // Check diagonals
        if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
            return true;
        }
        if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
            return true;
        }

        return false;
    }

    bool isBoardFull() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    return false;
                }
            }
        }
        return true;
    }
};

// Global game instance
TicTacToe game;

// C-style wrapper functions for WebAssembly
extern "C" {
    bool makeMove(int row, int col) {
        return game.makeMove(row, col);
    }

    char getCell(int row, int col) {
        return game.getCell(row, col);
    }

    char getCurrentPlayer() {
        return game.getCurrentPlayer();
    }

    char getWinner() {
        return game.getWinner();
    }

    bool isGameOver() {
        return game.isGameOver();
    }

    void resetGame() {
        game.resetGame();
    }

    const char* getBoardString() {
        static std::string boardStr;
        boardStr = game.getBoardString();
        return boardStr.c_str();
    }
}

#ifdef __EMSCRIPTEN__
// Emscripten bindings
EMSCRIPTEN_BINDINGS(tictactoe) {
    emscripten::function("makeMove", &makeMove);
    emscripten::function("getCell", &getCell);
    emscripten::function("getCurrentPlayer", &getCurrentPlayer);
    emscripten::function("getWinner", &getWinner);
    emscripten::function("isGameOver", &isGameOver);
    emscripten::function("resetGame", &resetGame);
    emscripten::function("getBoardString", &getBoardString);
}
#endif

#ifndef __EMSCRIPTEN__
// Main function for native testing
int main() {
    std::cout << "Tic Tac Toe Game (Native Test)" << std::endl;
    std::cout << "Current player: " << game.getCurrentPlayer() << std::endl;
    
    // Test some moves
    game.makeMove(0, 0); // X
    game.makeMove(1, 1); // O
    game.makeMove(0, 1); // X
    game.makeMove(1, 0); // O
    game.makeMove(0, 2); // X wins
    
    std::cout << "Winner: " << game.getWinner() << std::endl;
    std::cout << "Game over: " << (game.isGameOver() ? "Yes" : "No") << std::endl;
    
    return 0;
}
#endif