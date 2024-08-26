#include "../headers/ncurses.h"

#define COLOR_BROWN 20
#define COLOR_DARK_BROWN 21
#define COLOR_LIGHT_DARK 19
#define COLOR_LIGHT 18
#define COLOR_LIGHT_RED 17

void initializeColors();
void initializePairs();


void initializeNcurses() {
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    resize_term(400, 200);
    start_color();
    initializeColors();
    initializePairs();
    attron(COLOR_PAIR(defaultColors));
}

void initializeColors() {
    init_color(COLOR_LIGHT_DARK, 898, 796, 695);
    init_color(COLOR_BROWN, 687, 535, 406);
    init_color(COLOR_DARK_BROWN, 496, 332, 222);
    init_color(COLOR_LIGHT, 925, 875, 828);
    init_color(COLOR_LIGHT_RED, 785, 93, 289);
}

void initializePairs() {
    init_pair(defaultColors, COLOR_LIGHT, COLOR_BLACK);
    init_pair(highlightButton, COLOR_BLACK, COLOR_LIGHT);
    init_pair(redPawnsDice, COLOR_LIGHT, COLOR_LIGHT_RED);
    init_pair(whitePawnsDice, COLOR_BLACK, COLOR_LIGHT);
    init_pair(redPawns, COLOR_LIGHT_RED, COLOR_BLACK);
    init_pair(whitePawns, COLOR_LIGHT, COLOR_BLACK);
    init_pair(highlightField, COLOR_LIGHT_DARK, COLOR_BLACK);
    init_pair(gameBoardColor, COLOR_DARK_BROWN, COLOR_BLACK);
    init_pair(fieldsColor, COLOR_BROWN, COLOR_BLACK);
    init_pair(asciiArt, COLOR_DARK_BROWN, COLOR_BLACK);
}

void setColor(Colors color) {
    attron(COLOR_PAIR(color));
}

void destroyNcurses() {
    endwin();
}