cmake_minimum_required(VERSION 3.5)

project(tank_battle LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_add_executable(tank_battle
    main.cpp
    mainwindow.h
    mainwindow.cpp
    mainmenu.h
    mainmenu.cpp
    gamecanvas.h
    gamecanvas.cpp
    gameengine.h
    gameengine.cpp
    tank.h
    tank.cpp
    bullet.h
    bullet.cpp
)

target_link_libraries(tank_battle PRIVATE Qt6::Widgets)