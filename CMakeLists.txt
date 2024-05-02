cmake_minimum_required(VERSION 2.6)
project("libscrabble")

include(GNUInstallDirs) # Required for CMAKE_INSTALL_INCLUDEDIR

set(CMAKE_CXX_STANDARD 14)

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

set(
    SCRABBLE_PUBLIC_HEADERS
    "${PROJECT_SOURCE_DIR}/include/grid.hpp"
    "${PROJECT_SOURCE_DIR}/include/solution.hpp"
    "${PROJECT_SOURCE_DIR}/include/trie.hpp"
)

set_target_properties(
    scrabble
    PROPERTIES PUBLIC_HEADER
    "${SCRABBLE_PUBLIC_HEADERS}"
)

install(
    TARGETS scrabble
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/scrabble
)

enable_testing()

add_test(
    NAME scrabble_test_suite
    COMMAND libscrabble_test
)

file(
    COPY ${CMAKE_CURRENT_SOURCE_DIR}/dictionary.txt
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)
