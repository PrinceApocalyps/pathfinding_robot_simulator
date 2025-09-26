cmake_minimum_required(VERSION 3.16)

project(pathfinding_robot_simulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(pathfinding_robot_simulator main.cpp
        ./class_headers/point.h ./class_implements/point.cpp
        ./class_headers/robot.h ./class_implements/robot.cpp
        ./class_headers/world.h ./class_implements/world.cpp)

include(GNUInstallDirs)
install(TARGETS pathfinding_robot_simulator
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
