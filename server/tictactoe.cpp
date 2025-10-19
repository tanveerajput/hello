#include "tictactoe.h"
#include <sstream>

void TicTacToe::reset() {
    for (auto &row : board) {
        for (auto &cell : row) {
            cell = Player::None;
        }
    }
    currentPlayer = Player::X;
    winner = Player::None;
    draw = false;
}

bool TicTacToe::inBounds(int row, int col) const {
    return row >= 0 && row < 3 && col >= 0 && col < 3;
}

bool TicTacToe::makeMove(int row, int col) {
    if (winner != Player::None || draw) return false;
    if (!inBounds(row, col)) return false;
    if (board[row][col] != Player::None) return false;

    board[row][col] = currentPlayer;
    updateGameState();
    if (winner == Player::None && !draw) {
        currentPlayer = (currentPlayer == Player::X) ? Player::O : Player::X;
    }
    return true;
}

void TicTacToe::updateGameState() {
    // Check rows and cols
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] != Player::None && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            winner = board[i][0];
            return;
        }
        if (board[0][i] != Player::None && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            winner = board[0][i];
            return;
        }
    }
    // Diagonals
    if (board[0][0] != Player::None && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        winner = board[0][0];
        return;
    }
    if (board[0][2] != Player::None && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        winner = board[0][2];
        return;
    }

    // Check draw
    bool anyEmpty = false;
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            if (board[r][c] == Player::None) {
                anyEmpty = true;
                break;
            }
        }
        if (anyEmpty) break;
    }
    draw = !anyEmpty;
}

std::string TicTacToe::toString() const {
    std::string s;
    s.reserve(9);
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            char ch = '.';
            if (board[r][c] == Player::X) ch = 'X';
            else if (board[r][c] == Player::O) ch = 'O';
            s.push_back(ch);
        }
    }
    return s;
}
