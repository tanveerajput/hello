#pragma once
#include <array>
#include <string>

class TicTacToe {
public:
    enum class Player { None = 0, X, O };

    TicTacToe() { reset(); }

    void reset();
    bool makeMove(int row, int col);
    Player getCurrentPlayer() const { return currentPlayer; }
    Player getWinner() const { return winner; }
    bool isDraw() const { return draw; }
    std::string toString() const; // board as 9-char string

private:
    std::array<std::array<Player, 3>, 3> board{};
    Player currentPlayer{ Player::X };
    Player winner{ Player::None };
    bool draw{ false };

    bool inBounds(int row, int col) const;
    void updateGameState();
};
