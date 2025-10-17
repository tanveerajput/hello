# CMakeLists.txt for Tic-Tac-Toe Game
# Minimum required version of CMake
cmake_minimum_required(VERSION 3.12)

# Project name and version
project(TicTacToe VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler-specific options
if(MSVC)
    # Microsoft Visual C++ compiler options
    add_compile_options(/W4 /WX)
else()
    # GCC and Clang compiler options
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
    
    # Debug configuration
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
    
    # Release configuration
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
endif()

# Source files
set(SOURCES
    main.cpp
    Game.cpp
    Board.cpp
    Player.cpp
)

# Header files (for IDE support)
set(HEADERS
    Game.h
    Board.h
    Player.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Installation rules
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

# Create a custom target for running the game
add_custom_target(run
    COMMAND ${CMAKE_BINARY_DIR}/bin/${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running Tic-Tac-Toe game..."
)

# Print build information
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Version: ${PROJECT_VERSION}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")

# Optional: Enable testing if CTest is available
include(CTest)
if(BUILD_TESTING)
    message(STATUS "Testing enabled")
    # Add test cases here if needed
endif()