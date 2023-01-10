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

add_executable(
    buttonTest
    ./tests/ButtonTest.cpp
    ${SOURCES}
)

add_executable(
    staticPointsTest
    ./tests/StaticPointsTest.cpp
    ${SOURCES}
)

add_executable(
    gameTest
    ./tests/GameTest.cpp
    ${SOURCES}
)

target_link_libraries(
    playerTest
    GTest::gtest_main
    sfml-graphics
)

target_link_libraries(
    buttonTest
    GTest::gtest_main
    sfml-graphics
)

target_link_libraries(
    staticPointsTest
    GTest::gtest_main
    sfml-graphics
)

target_link_libraries(
    gameTest
    GTest::gtest_main
    sfml-graphics
)

include(GoogleTest)
gtest_discover_tests(playerTest)
gtest_discover_tests(buttonTest)
gtest_discover_tests(staticPointsTest)
gtest_discover_tests(gameTest)


