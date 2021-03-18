cmake_minimum_required(VERSION 2.6)
project("libscrabble")

set(CMAKE_CXX_STANDARD 14)

include(GNUInstallDirs)

add_library(
    scrabble
    SHARED
    include/grid.hpp
    include/solution.hpp
    include/trie.hpp
    src/grid.cpp
    src/solution.cpp
    src/trie.cpp
)

add_executable(
    libscrabble_test
    src/test.cpp
)

target_include_directories(
    scrabble
    PUBLIC
    include
)

target_link_libraries(
    libscrabble_test
    gtest
    pthread
    scrabble
)

set_target_properties(
    scrabble
    PROPERTIES PUBLIC_HEADER
    "include/grid.hpp;include/solution.hpp;include/trie.hpp"
)

install(
    TARGETS scrabble
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/scrabble
)
