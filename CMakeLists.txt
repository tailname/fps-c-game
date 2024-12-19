cmake_minimum_required(VERSION 3.10)
project(fps-cpp-game)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu/cmake/box2d")

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

# Убираем find_package для Box2D, так как уже используем find_library
# find_package(Box2D REQUIRED)

# Добавление include-путей (автоматически настраивается find_package)
include_directories(${SFML_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/xml_parser/src
        /usr/include/box2d)  # Убедитесь, что указали путь к заголовочным файлам Box2D

# Явное указание на путь к библиотеке Box2D
find_library(Box2D_LIBRARY NAMES box2d PATHS /usr/lib/x86_64-linux-gnu)

find_library(SFML_GRAPHICS_LIBRARY NAMES sfml-graphics PATHS /usr/lib/x86_64-linux-gnu)
find_library(SFML_WINDOW_LIBRARY NAMES sfml-window PATHS /usr/lib/x86_64-linux-gnu)
find_library(SFML_SYSTEM_LIBRARY NAMES sfml-system PATHS /usr/lib/x86_64-linux-gnu)
find_library(SFML_AUDIO_LIBRARY NAMES sfml-audio PATHS /usr/lib/x86_64-linux-gnu)
find_library(SFML_NETWORK_LIBRARY NAMES sfml-network PATHS /usr/lib/x86_64-linux-gnu)

add_executable(fps-cpp-game
        src/main.cpp
        src/GameMenu.cpp
        src/Game.cpp
        src/Level.cpp
        src/TileMap.cpp
        xml_parser/src/tinyxml2.cpp
        include/Level.h
        src/Entity.cpp
        include/Player.h
        src/Player.cpp
)

target_link_libraries(fps-cpp-game
        ${SFML_GRAPHICS_LIBRARY}
        ${SFML_WINDOW_LIBRARY}
        ${SFML_SYSTEM_LIBRARY}
        ${SFML_AUDIO_LIBRARY}
        ${SFML_NETWORK_LIBRARY}
        ${Box2D_LIBRARY}  # Правильная переменная для линковки Box2D
)
