#pragma once
#include <stdlib.h>
#include <string.h>
#include "ncurses.h"

typedef struct {
    short x, y;
} Point;

typedef enum { startGame, saveGame, loadGame, exitGame, selectPawn, moveSelectedPawn, rollDice, hallOfFame, aboutAuthor,
    backToHomeScreen, nextRound, previousMove, nextMove, beginningOfGame, endOfGame, firstSlot, secondSlot, thirdSlot
} MenuOption;

typedef struct Node {
    MenuOption buttonName;
    char* buttonText;
    Point topLeftCornerOfButton;
    struct Node* nextButton;
    struct Node* previousButton;
} Node;

typedef struct Menu {
    Node* head;
    Node* lastSelectedOption;
    Node* tail;
} Menu;

void destroyMenu(Menu* menu);
Menu* createStartScreenMenu(Point topLeftCornerOfMenu);
Menu* createBackToHomeScreenMenu(Point topLeftCornerOfMenu);
Menu* createInGameMenu(Point topLeftCornerOfMenu);
Menu* createEndScreenMenu(Point topLeftCornerOfMenu);
Menu* createLoadGameMenu(Point topLeftCornerOfMenu);
Menu* createSaveSlotsMenu(Point topLeftCornerOfMenu);
MenuOption waitForPlayerToSelectMenuOption(Menu* menu);
void redrawMenu(Menu* menu);