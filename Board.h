#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>

/**
 * @brief Represents the tic-tac-toe game board
 * 
 * This class manages the 3x3 game board, including placing moves,
 * checking for wins, and displaying the current state.
 */
class Board {
private:
    static const int BOARD_SIZE = 3;
    std::vector<std::vector<char>> grid;  // 3x3 grid to store the board state
    int movesCount;                       // Number of moves made

public:
    /**
     * @brief Construct a new Board object
     * 
     * Initializes an empty 3x3 board with spaces
     */
    Board();

    /**
     * @brief Display the current board state
     * 
     * Shows the board with row and column numbers for easy reference
     */
    void display() const;

    /**
     * @brief Check if a position is valid and empty
     * 
     * @param row Row index (0-2)
     * @param col Column index (0-2)
     * @return true if the position is valid and empty
     * @return false if the position is invalid or occupied
     */
    bool isValidMove(int row, int col) const;

    /**
     * @brief Place a symbol on the board
     * 
     * @param row Row index (0-2)
     * @param col Column index (0-2)
     * @param symbol Player's symbol ('X' or 'O')
     * @return true if the move was successful
     * @return false if the move was invalid
     */
    bool makeMove(int row, int col, char symbol);

    /**
     * @brief Check if there's a winner
     * 
     * @return char The winning symbol ('X' or 'O'), or ' ' if no winner
     */
    char checkWinner() const;

    /**
     * @brief Check if the board is full
     * 
     * @return true if all positions are occupied
     * @return false if there are empty positions
     */
    bool isFull() const;

    /**
     * @brief Reset the board to initial empty state
     */
    void reset();

    /**
     * @brief Get the current number of moves
     * 
     * @return int Number of moves made
     */
    int getMoveCount() const;

    /**
     * @brief Get the symbol at a specific position
     * 
     * @param row Row index (0-2)
     * @param col Column index (0-2)
     * @return char The symbol at the position, or ' ' if empty
     */
    char getSymbolAt(int row, int col) const;

private:
    /**
     * @brief Check for a winner in rows
     * 
     * @return char The winning symbol or ' ' if no row winner
     */
    char checkRows() const;

    /**
     * @brief Check for a winner in columns
     * 
     * @return char The winning symbol or ' ' if no column winner
     */
    char checkColumns() const;

    /**
     * @brief Check for a winner in diagonals
     * 
     * @return char The winning symbol or ' ' if no diagonal winner
     */
    char checkDiagonals() const;
};

#endif // BOARD_H