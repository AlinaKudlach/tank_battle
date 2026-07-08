cmake_minimum_required(VERSION 3.5)

project(test_tank_battle LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Test Widgets)

qt_add_executable(test_tank_battle
    tst_testtankbattle.cpp
)

target_include_directories(test_tank_battle PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../tank_battle
)

target_sources(test_tank_battle PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../tank_battle/tank.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../tank_battle/tank.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../tank_battle/bullet.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../tank_battle/bullet.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../tank_battle/gameengine.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../tank_battle/gameengine.cpp
)

target_link_libraries(test_tank_battle PRIVATE
    Qt6::Test
    Qt6::Widgets
)