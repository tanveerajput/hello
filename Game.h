#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"
#include <memory>

/**
 * @brief Main game controller for tic-tac-toe
 * 
 * This class manages the overall game flow, including player turns,
 * game state, and user interaction.
 */
class Game {
private:
    Board board;                           // The game board
    std::unique_ptr<Player> player1;       // Player 1 (X)
    std::unique_ptr<Player> player2;       // Player 2 (O)
    Player* currentPlayer;                 // Pointer to current player
    bool gameRunning;                      // Game state flag
    int totalGames;                        // Total games played

public:
    /**
     * @brief Construct a new Game object
     */
    Game();

    /**
     * @brief Initialize the game with player names
     * 
     * @param player1Name Name for player 1 (X)
     * @param player2Name Name for player 2 (O)
     */
    void initializePlayers(const std::string& player1Name, const std::string& player2Name);

    /**
     * @brief Start and run the main game loop
     */
    void run();

    /**
     * @brief Play a single game
     * 
     * @return true if players want to continue playing
     * @return false if players want to quit
     */
    bool playSingleGame();

    /**
     * @brief Switch to the other player
     */
    void switchPlayer();

    /**
     * @brief Get player input for their move
     * 
     * @param row Reference to store the row input
     * @param col Reference to store the column input
     * @return true if input is valid
     * @return false if input is invalid
     */
    bool getPlayerInput(int& row, int& col);

    /**
     * @brief Display the game menu
     */
    void displayMenu() const;

    /**
     * @brief Display game instructions
     */
    void displayInstructions() const;

    /**
     * @brief Display final statistics for both players
     */
    void displayFinalStats() const;

    /**
     * @brief Handle the end of a single game
     * 
     * @param winner The winning symbol, or ' ' for a draw
     */
    void handleGameEnd(char winner);

    /**
     * @brief Ask if players want to play another game
     * 
     * @return true if players want to continue
     * @return false if players want to quit
     */
    bool askPlayAgain() const;

    /**
     * @brief Clear the input buffer
     */
    void clearInputBuffer() const;

    /**
     * @brief Validate integer input within a range
     * 
     * @param input The input value
     * @param min Minimum valid value
     * @param max Maximum valid value
     * @return true if input is valid
     * @return false if input is invalid
     */
    bool isValidInput(int input, int min, int max) const;
};

#endif // GAME_H