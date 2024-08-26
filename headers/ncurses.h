#pragma once
#include <ncurses.h>

typedef enum Colors { defaultColors = 1, highlightButton, highlightField, redPawnsDice, whitePawnsDice, redPawns, whitePawns,
                      gameBoardColor, fieldsColor, asciiArt } Colors;

void initializeNcurses();
void setColor(Colors color);
void destroyNcurses();