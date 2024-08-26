cmake_minimum_required(VERSION 3.26)
project(Backgammon C)

set(CMAKE_C_STANDARD 11)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
add_executable(Backgammon main.c
        source/menu.c
        headers/menu.h
        source/ncurses.c
        headers/ncurses.h
        source/startscreen.c
        headers/startscreen.h
        source/game.c
        headers/game.h
        source/gameRendering.c
        headers/gameRendering.h
        source/dataStructures.c
        headers/dataStructures.h
        headers/saveGame.h
        headers/endScreen.h
        source/endScreen.c
        source/saveGame.c
        headers/ranking.h
        source/ranking.c
        headers/loadGame.h
        source/loadGame.c
        headers/loadAsset.h
        source/loadAsset.c
        source/aboutMe.c
        headers/aboutMe.h
)
target_link_libraries(Backgammon ${CURSES_LIBRARIES})
