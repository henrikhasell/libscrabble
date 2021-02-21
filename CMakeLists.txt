cmake_minimum_required(VERSION 2.6)
project("libscrabble")

set(CMAKE_CXX_STANDARD 14)
include_directories(/usr/local/include include)
link_directories(/usr/local/lib)

add_library(
    scrabble
    SHARED
    src/grid.cpp
    src/solution.cpp
    src/trie.cpp
)

add_executable(
    libscrabble_test
    src/test.cpp
)

target_link_libraries(
    libscrabble_test
    scrabble
)
