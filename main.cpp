/**
 * @file main.cpp
 * @brief Entry point for the Tic-Tac-Toe game
 * 
 * This file contains the main function that starts the tic-tac-toe game.
 * The game features a complete object-oriented design with proper separation
 * of concerns between game logic, board management, and player handling.
 * 
 * Features:
 * - Interactive console-based gameplay
 * - Player statistics tracking
 * - Input validation and error handling
 * - Clean, modern C++ design with smart pointers
 * - Comprehensive documentation
 * 
 * @author AI Assistant
 * @date 2025
 */

#include "Game.h"
#include <iostream>
#include <exception>

/**
 * @brief Main entry point of the application
 * 
 * Creates a Game instance and starts the main game loop.
 * Includes basic exception handling for unexpected errors.
 * 
 * @return int Exit code (0 for success, 1 for error)
 */
int main() {
    try {
        Game game;
        game.run();
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        std::cerr << "The game will now exit." << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "An unknown error occurred. The game will now exit." << std::endl;
        return 1;
    }
}