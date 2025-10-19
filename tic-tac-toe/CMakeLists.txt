cmake_minimum_required(VERSION 3.16)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 17)

# Check if we're building for WebAssembly
if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".js")
    
    # Emscripten-specific flags
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s WASM=1")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s EXPORTED_FUNCTIONS='[\"_makeMove\", \"_getBoard\", \"_checkWinner\", \"_resetGame\", \"_getCurrentPlayer\", \"_malloc\", \"_free\"]'")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s EXPORTED_RUNTIME_METHODS='[\"ccall\", \"cwrap\"]'")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s ALLOW_MEMORY_GROWTH=1")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --bind")
    
    add_executable(tictactoe src/tictactoe.cpp)
    
    # Copy the generated files to web directory
    add_custom_command(TARGET tictactoe POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/tictactoe.js ${CMAKE_SOURCE_DIR}/web/
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/tictactoe.wasm ${CMAKE_SOURCE_DIR}/web/
    )
else()
    # Native build for testing
    add_executable(tictactoe_test src/tictactoe.cpp src/test.cpp)
endif()