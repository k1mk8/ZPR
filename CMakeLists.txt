cmake_minimum_required(VERSION 3.16)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
project(agario)

find_package(SFML 2.5
    COMPONENTS
    system window graphics network audio REQUIRED
)
include_directories(include)
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



