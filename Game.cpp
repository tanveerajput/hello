#include "Game.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <cctype>

Game::Game() : currentPlayer(nullptr), gameRunning(false), totalGames(0) {
}

void Game::initializePlayers(const std::string& player1Name, const std::string& player2Name) {
    player1 = std::make_unique<Player>('X', player1Name);
    player2 = std::make_unique<Player>('O', player2Name);
    currentPlayer = player1.get(); // Player 1 (X) starts first
}

void Game::run() {
    std::cout << "\n" << std::string(60, '*') << std::endl;
    std::cout << "                  WELCOME TO TIC-TAC-TOE!" << std::endl;
    std::cout << std::string(60, '*') << std::endl;
    
    displayInstructions();
    
    std::string player1Name, player2Name;
    
    std::cout << "\nEnter name for Player 1 (X): ";
    std::getline(std::cin, player1Name);
    if (player1Name.empty()) player1Name = "Player 1";
    
    std::cout << "Enter name for Player 2 (O): ";
    std::getline(std::cin, player2Name);
    if (player2Name.empty()) player2Name = "Player 2";
    
    initializePlayers(player1Name, player2Name);
    
    gameRunning = true;
    
    while (gameRunning) {
        displayMenu();
        
        int choice;
        std::cout << "\nEnter your choice: ";
        
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input! Please enter a number." << std::endl;
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();
        
        switch (choice) {
            case 1:
                if (playSingleGame()) {
                    totalGames++;
                } else {
                    gameRunning = false;
                }
                break;
            case 2:
                displayFinalStats();
                break;
            case 3:
                displayInstructions();
                break;
            case 4:
                player1->resetStats();
                player2->resetStats();
                totalGames = 0;
                std::cout << "\nStatistics have been reset!" << std::endl;
                break;
            case 5:
                std::cout << "\nThank you for playing Tic-Tac-Toe!" << std::endl;
                std::cout << "Final Statistics:" << std::endl;
                displayFinalStats();
                gameRunning = false;
                break;
            default:
                std::cout << "Invalid choice! Please select 1-5." << std::endl;
                break;
        }
        
        if (gameRunning && choice != 2 && choice != 3) {
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
        }
    }
}

bool Game::playSingleGame() {
    board.reset();
    currentPlayer = player1.get(); // Player 1 always starts
    
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "           STARTING NEW GAME" << std::endl;
    std::cout << player1->getName() << " (X) vs " << player2->getName() << " (O)" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    
    while (true) {
        board.display();
        
        std::cout << "\n" << currentPlayer->getName() << "'s turn (" 
                  << currentPlayer->getSymbol() << ")" << std::endl;
        
        int row, col;
        if (!getPlayerInput(row, col)) {
            std::cout << "Invalid input! Please try again." << std::endl;
            continue;
        }
        
        // Convert from 1-based to 0-based indexing
        row--;
        col--;
        
        if (!board.makeMove(row, col, currentPlayer->getSymbol())) {
            std::cout << "Invalid move! That position is already occupied or out of bounds." << std::endl;
            continue;
        }
        
        char winner = board.checkWinner();
        if (winner != ' ') {
            board.display();
            handleGameEnd(winner);
            return askPlayAgain();
        }
        
        if (board.isFull()) {
            board.display();
            handleGameEnd(' '); // Draw
            return askPlayAgain();
        }
        
        switchPlayer();
    }
}

void Game::switchPlayer() {
    currentPlayer = (currentPlayer == player1.get()) ? player2.get() : player1.get();
}

bool Game::getPlayerInput(int& row, int& col) {
    std::cout << "Enter row (1-3): ";
    if (!(std::cin >> row)) {
        clearInputBuffer();
        return false;
    }
    
    std::cout << "Enter column (1-3): ";
    if (!(std::cin >> col)) {
        clearInputBuffer();
        return false;
    }
    
    clearInputBuffer();
    
    return isValidInput(row, 1, 3) && isValidInput(col, 1, 3);
}

void Game::displayMenu() const {
    std::cout << "\n" << std::string(40, '=') << std::endl;
    std::cout << "              MAIN MENU" << std::endl;
    std::cout << std::string(40, '=') << std::endl;
    std::cout << "1. Play Game" << std::endl;
    std::cout << "2. View Statistics" << std::endl;
    std::cout << "3. View Instructions" << std::endl;
    std::cout << "4. Reset Statistics" << std::endl;
    std::cout << "5. Quit" << std::endl;
    std::cout << std::string(40, '=') << std::endl;
}

void Game::displayInstructions() const {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "                    HOW TO PLAY" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    std::cout << "1. The game is played on a 3x3 grid." << std::endl;
    std::cout << "2. Player 1 uses 'X' and Player 2 uses 'O'." << std::endl;
    std::cout << "3. Players take turns placing their symbol on the grid." << std::endl;
    std::cout << "4. Enter row and column numbers (1-3) to make your move." << std::endl;
    std::cout << "5. The first player to get 3 symbols in a row wins!" << std::endl;
    std::cout << "   (horizontally, vertically, or diagonally)" << std::endl;
    std::cout << "6. If all 9 squares are filled and no one wins, it's a draw." << std::endl;
    std::cout << std::string(60, '=') << std::endl;
}

void Game::displayFinalStats() const {
    std::cout << "\n" << std::string(60, '*') << std::endl;
    std::cout << "                  GAME STATISTICS" << std::endl;
    std::cout << std::string(60, '*') << std::endl;
    std::cout << "Total games played: " << totalGames << std::endl;
    
    player1->displayStats();
    player2->displayStats();
    
    std::cout << std::string(60, '*') << std::endl;
}

void Game::handleGameEnd(char winner) {
    if (winner == ' ') {
        std::cout << "\n" << std::string(40, '=') << std::endl;
        std::cout << "              IT'S A DRAW!" << std::endl;
        std::cout << std::string(40, '=') << std::endl;
        player1->addDraw();
        player2->addDraw();
    } else {
        Player* winningPlayer = (winner == player1->getSymbol()) ? player1.get() : player2.get();
        Player* losingPlayer = (winner == player1->getSymbol()) ? player2.get() : player1.get();
        
        std::cout << "\n" << std::string(50, '*') << std::endl;
        std::cout << "          🎉 " << winningPlayer->getName() << " WINS! 🎉" << std::endl;
        std::cout << "              (" << winner << " is the winner)" << std::endl;
        std::cout << std::string(50, '*') << std::endl;
        
        winningPlayer->addWin();
        losingPlayer->addLoss();
    }
}

bool Game::askPlayAgain() const {
    char choice;
    std::cout << "\nDo you want to play another game? (y/n): ";
    std::cin >> choice;
    clearInputBuffer();
    
    return (std::tolower(choice) == 'y');
}

void Game::clearInputBuffer() const {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool Game::isValidInput(int input, int min, int max) const {
    return input >= min && input <= max;
}