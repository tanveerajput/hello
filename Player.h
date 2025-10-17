#ifndef PLAYER_H
#define PLAYER_H

#include <string>

/**
 * @brief Represents a player in the tic-tac-toe game
 * 
 * This class encapsulates player information including their symbol ('X' or 'O'),
 * name, and score tracking for multiple games.
 */
class Player {
private:
    char symbol;        // Player's symbol ('X' or 'O')
    std::string name;   // Player's name
    int wins;          // Number of games won
    int losses;        // Number of games lost
    int draws;         // Number of games drawn

public:
    /**
     * @brief Construct a new Player object
     * 
     * @param playerSymbol The symbol for this player ('X' or 'O')
     * @param playerName The name of the player
     */
    Player(char playerSymbol, const std::string& playerName);

    /**
     * @brief Get the player's symbol
     * 
     * @return char The player's symbol
     */
    char getSymbol() const;

    /**
     * @brief Get the player's name
     * 
     * @return std::string The player's name
     */
    std::string getName() const;

    /**
     * @brief Get the number of wins
     * 
     * @return int Number of wins
     */
    int getWins() const;

    /**
     * @brief Get the number of losses
     * 
     * @return int Number of losses
     */
    int getLosses() const;

    /**
     * @brief Get the number of draws
     * 
     * @return int Number of draws
     */
    int getDraws() const;

    /**
     * @brief Increment the win count
     */
    void addWin();

    /**
     * @brief Increment the loss count
     */
    void addLoss();

    /**
     * @brief Increment the draw count
     */
    void addDraw();

    /**
     * @brief Reset all statistics to zero
     */
    void resetStats();

    /**
     * @brief Display player statistics
     */
    void displayStats() const;
};

#endif // PLAYER_H