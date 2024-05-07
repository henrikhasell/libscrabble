cmake_minimum_required(VERSION 3.5)
project("libscrabble")

include(GNUInstallDirs) # Required for CMAKE_INSTALL_INCLUDEDIR
include(FetchContent) # Required to install GoogleTest

set(CMAKE_CXX_STANDARD 14)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(INSTALL_GTEST OFF)

FetchContent_MakeAvailable(googletest)

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
    PRIVATE
    "${PROJECT_SOURCE_DIR}/include"
)

target_include_directories(
    libscrabble_test
    PRIVATE
    "${PROJECT_SOURCE_DIR}/include"
)

target_link_libraries(
    libscrabble_test
    PRIVATE
    GTest::gmock
    GTest::gmock_main
    GTest::gtest
    GTest::gtest_main
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
