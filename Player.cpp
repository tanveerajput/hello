#include "Player.h"
#include <iostream>
#include <iomanip>

Player::Player(char playerSymbol, const std::string& playerName) 
    : symbol(playerSymbol), name(playerName), wins(0), losses(0), draws(0) {
}

char Player::getSymbol() const {
    return symbol;
}

std::string Player::getName() const {
    return name;
}

int Player::getWins() const {
    return wins;
}

int Player::getLosses() const {
    return losses;
}

int Player::getDraws() const {
    return draws;
}

void Player::addWin() {
    wins++;
}

void Player::addLoss() {
    losses++;
}

void Player::addDraw() {
    draws++;
}

void Player::resetStats() {
    wins = 0;
    losses = 0;
    draws = 0;
}

void Player::displayStats() const {
    std::cout << "\n" << std::string(40, '=') << std::endl;
    std::cout << "Statistics for " << name << " (" << symbol << ")" << std::endl;
    std::cout << std::string(40, '=') << std::endl;
    std::cout << std::left << std::setw(15) << "Wins:" << wins << std::endl;
    std::cout << std::left << std::setw(15) << "Losses:" << losses << std::endl;
    std::cout << std::left << std::setw(15) << "Draws:" << draws << std::endl;
    
    int totalGames = wins + losses + draws;
    if (totalGames > 0) {
        double winPercentage = (static_cast<double>(wins) / totalGames) * 100.0;
        std::cout << std::left << std::setw(15) << "Win Rate:" 
                  << std::fixed << std::setprecision(1) << winPercentage << "%" << std::endl;
    }
    std::cout << std::string(40, '=') << std::endl;
}