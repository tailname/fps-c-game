cmake_minimum_required(VERSION 3.10)
project(fps-cpp-game)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

# Добавление include-путей (автоматически настраивается find_package)
include_directories(${SFML_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/include)

find_library(SFML_GRAPHICS_LIBRARY NAMES sfml-graphics PATHS /usr/lib/x86_64-linux-gnu)
find_library(SFML_WINDOW_LIBRARY NAMES sfml-window PATHS /usr/lib/x86_64-linux-gnu)
find_library(SFML_SYSTEM_LIBRARY NAMES sfml-system PATHS /usr/lib/x86_64-linux-gnu)
find_library(SFML_AUDIO_LIBRARY NAMES sfml-audio PATHS /usr/lib/x86_64-linux-gnu)
find_library(SFML_NETWORK_LIBRARY NAMES sfml-network PATHS /usr/lib/x86_64-linux-gnu)

add_executable(fps-cpp-game src/main.cpp
        include/Background.h)

target_link_libraries(fps-cpp-game
        ${SFML_GRAPHICS_LIBRARY}
        ${SFML_WINDOW_LIBRARY}
        ${SFML_SYSTEM_LIBRARY}
        ${SFML_AUDIO_LIBRARY}
        ${SFML_NETWORK_LIBRARY}
)
