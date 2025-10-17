#include "Board.h"
#include <iomanip>

Board::Board() : movesCount(0) {
    // Initialize the 3x3 grid with empty spaces
    grid.resize(BOARD_SIZE, std::vector<char>(BOARD_SIZE, ' '));
}

void Board::display() const {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "                TIC-TAC-TOE BOARD" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    
    // Display column numbers
    std::cout << "    ";
    for (int col = 0; col < BOARD_SIZE; col++) {
        std::cout << "  " << col + 1 << "   ";
    }
    std::cout << std::endl;
    
    // Display the board with row numbers
    for (int row = 0; row < BOARD_SIZE; row++) {
        // Display row separator
        std::cout << "   ";
        for (int col = 0; col < BOARD_SIZE; col++) {
            std::cout << "+-----";
        }
        std::cout << "+" << std::endl;
        
        // Display row with data
        std::cout << " " << row + 1 << " ";
        for (int col = 0; col < BOARD_SIZE; col++) {
            std::cout << "|  " << grid[row][col] << "  ";
        }
        std::cout << "|" << std::endl;
    }
    
    // Display bottom border
    std::cout << "   ";
    for (int col = 0; col < BOARD_SIZE; col++) {
        std::cout << "+-----";
    }
    std::cout << "+" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
}

bool Board::isValidMove(int row, int col) const {
    // Check if coordinates are within bounds
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        return false;
    }
    
    // Check if the position is empty
    return grid[row][col] == ' ';
}

bool Board::makeMove(int row, int col, char symbol) {
    if (!isValidMove(row, col)) {
        return false;
    }
    
    grid[row][col] = symbol;
    movesCount++;
    return true;
}

char Board::checkWinner() const {
    // Check rows, columns, and diagonals
    char winner = checkRows();
    if (winner != ' ') return winner;
    
    winner = checkColumns();
    if (winner != ' ') return winner;
    
    winner = checkDiagonals();
    if (winner != ' ') return winner;
    
    return ' '; // No winner found
}

bool Board::isFull() const {
    return movesCount >= (BOARD_SIZE * BOARD_SIZE);
}

void Board::reset() {
    // Reset all positions to empty
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            grid[row][col] = ' ';
        }
    }
    movesCount = 0;
}

int Board::getMoveCount() const {
    return movesCount;
}

char Board::getSymbolAt(int row, int col) const {
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        return ' ';
    }
    return grid[row][col];
}

char Board::checkRows() const {
    for (int row = 0; row < BOARD_SIZE; row++) {
        if (grid[row][0] != ' ' && 
            grid[row][0] == grid[row][1] && 
            grid[row][1] == grid[row][2]) {
            return grid[row][0];
        }
    }
    return ' ';
}

char Board::checkColumns() const {
    for (int col = 0; col < BOARD_SIZE; col++) {
        if (grid[0][col] != ' ' && 
            grid[0][col] == grid[1][col] && 
            grid[1][col] == grid[2][col]) {
            return grid[0][col];
        }
    }
    return ' ';
}

char Board::checkDiagonals() const {
    // Check main diagonal (top-left to bottom-right)
    if (grid[0][0] != ' ' && 
        grid[0][0] == grid[1][1] && 
        grid[1][1] == grid[2][2]) {
        return grid[0][0];
    }
    
    // Check anti-diagonal (top-right to bottom-left)
    if (grid[0][2] != ' ' && 
        grid[0][2] == grid[1][1] && 
        grid[1][1] == grid[2][0]) {
        return grid[0][2];
    }
    
    return ' ';
}