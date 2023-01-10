cmake_minimum_required(VERSION 3.16)
add_compile_options(-Wall -Wextra -pedantic -Werror)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
project(agario)

find_package(GTest REQUIRED)
find_package(
    SFML 2.5
    COMPONENTS
    system window graphics network audio REQUIRED
)
include_directories(include)
enable_testing()
file(GLOB SOURCES "src/*.cpp")
add_executable(
    agario
    Agario.cpp
    ${SOURCES}
)
target_link_libraries(
    agario
    sfml-graphics
)

add_executable(
    playerTest
    ./tests/PlayerTest.cpp
    ${SOURCES}
)

target_link_libraries(
    playerTest
    GTest::gtest_main
    sfml-graphics
)

include(GoogleTest)
gtest_discover_tests(playerTest)


