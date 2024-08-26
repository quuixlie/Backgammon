#include "../headers/menu.h"


void initializeMenu(Menu* menu) {
    menu->head = NULL;
    menu->lastSelectedOption = NULL;
    menu->tail = NULL;
}

void appendButtonToMenu(Menu* menu, MenuOption buttonName, char buttonText[], Point topLeftCornerOfButton) {
    Node* newNode = (Node*) malloc(sizeof(Node));

    newNode->buttonName = buttonName;
    newNode->buttonText = (char*) malloc(strlen(buttonText) * sizeof(char));
    strcpy(newNode->buttonText, buttonText);
    newNode->topLeftCornerOfButton = topLeftCornerOfButton;
    newNode->nextButton = NULL;

    if (menu->head == NULL) {
        newNode->previousButton = NULL;
        menu->head = newNode;
        menu->tail = newNode;
    }
    else {
        newNode->previousButton = menu->tail;
        menu->tail->nextButton = newNode;
        menu->tail = newNode;
    }
}

void destroyMenu(Menu* menu) {
    Node* currentNode = menu->head;
    Node* nextNode = NULL;

    while (currentNode != NULL) {
        nextNode = currentNode->nextButton;
        free(currentNode->buttonText);
        free(currentNode);
        currentNode = nextNode;
    }

    free(menu);
}

void drawButtonLine(short buttonWidth) {
    addch('+');
    for (unsigned short i = 0; i < buttonWidth - 2; i++)
        addch('-');
    addch('+');
}

void drawButtonContent(char buttonContent[]) {
    printw("%s", "|  ");
    printw("%s", buttonContent);
    printw("%s", "  |");
}

Point drawButton(Point topLeftCornerOfButton, char buttonContent[]) {
    Point topRightCornerOfButton = {strlen("|    |") + strlen(buttonContent), topLeftCornerOfButton.y};

    move(topLeftCornerOfButton.y++, topLeftCornerOfButton.x);
    drawButtonLine(strlen("|    |") + strlen(buttonContent));
    move(topLeftCornerOfButton.y++, topLeftCornerOfButton.x);
    drawButtonContent(buttonContent);
    move(topLeftCornerOfButton.y, topLeftCornerOfButton.x);
    drawButtonLine(strlen("|    |") + strlen(buttonContent));

    return topRightCornerOfButton;
}

Menu* createMenu(Point topLeftCornerOfMenu, MenuOption menuOptions[], char* menuContent[], short numberOfButtons) {
    Menu* menu = (Menu*) malloc(sizeof(Menu));
    initializeMenu(menu);

    for (unsigned short i = 0; i < numberOfButtons; i++) {
        appendButtonToMenu(menu, menuOptions[i], menuContent[i], topLeftCornerOfMenu);
        Point topRightCornerOfButton = drawButton(topLeftCornerOfMenu, menuContent[i]);
        topLeftCornerOfMenu.x += topRightCornerOfButton.x;
    }

    return menu;
}

Menu* createStartScreenMenu(Point topLeftCornerOfMenu) {
    MenuOption menuOptions[] = {startGame, loadGame, hallOfFame, aboutAuthor, exitGame};
    char* menuContent[] = {"Start game", "Load game", "Hall of the fame", "About the author", "Exit game"};

    Menu* menu = createMenu(topLeftCornerOfMenu, menuOptions, menuContent, 5);

    return menu;
}

Menu* createBackToHomeScreenMenu(Point topLeftCornerOfMenu) {
    MenuOption menuOptions[] = {backToHomeScreen};
    char* menuContent[] = {"Back to home screen"};

    Menu* menu = createMenu(topLeftCornerOfMenu, menuOptions, menuContent, 1);

    return menu;
}

Menu* createInGameMenu(Point topLeftCornerOfMenu) {
    MenuOption menuOptions[] = {rollDice, selectPawn, moveSelectedPawn, saveGame, backToHomeScreen};
    char* menuContent[] = {"Roll dice", "Select pawn", "Move selected pawn", "Save game", "Back to home screen"};

    Menu* menu = createMenu(topLeftCornerOfMenu, menuOptions, menuContent, 5);

    return menu;
}

Menu* createEndScreenMenu(Point topLeftCornerOfMenu) {
    MenuOption menuOptions[] = {nextRound};
    char* menuContent[] = {"Next round"};

    Menu* menu = createMenu(topLeftCornerOfMenu, menuOptions, menuContent, 1);

    return menu;
}

Menu* createSaveSlotsMenu(Point topLeftCornerOfMenu) {
    MenuOption menuOptions[] = {firstSlot, secondSlot, thirdSlot};
    char* menuContent[] = {"First slot", "Second slot", "Third slot"};

    Menu* menu = createMenu(topLeftCornerOfMenu, menuOptions, menuContent, 3);

    return menu;
}

Menu* createLoadGameMenu(Point topLeftCornerOfMenu) {
    MenuOption menuOptions[] = {startGame, nextMove, previousMove, beginningOfGame, endOfGame};
    char* menuContent[] = {"Start game", "Next move", "Previous move", "Beginning of game", "End of game"};

    Menu* menu = createMenu(topLeftCornerOfMenu, menuOptions, menuContent, 5);

    return menu;
}

void highlightMenuButton(Menu* menu, MenuOption button) {
    Node* currentNode = menu->head;
    setColor(highlightButton);

    while (currentNode != NULL) {
        if (currentNode->buttonName == button) {
            drawButton(currentNode->topLeftCornerOfButton, currentNode->buttonText);
        }
        currentNode = currentNode->nextButton;
    }

    setColor(defaultColors);
}

void unHighlightMenuButton(Menu* menu, MenuOption button) {
    Node* currentNode = menu->head;
    setColor(defaultColors);

    while (currentNode != NULL) {
        if (currentNode->buttonName == button) {
            drawButton(currentNode->topLeftCornerOfButton, currentNode->buttonText);
        }
        currentNode = currentNode->nextButton;
    }
}

void selectPreviousMenuButton(Menu* menu, Node** currentNode) {
    if((*currentNode)->previousButton != NULL) {
        unHighlightMenuButton(menu, (*currentNode)->buttonName);
        (*currentNode) = (*currentNode)->previousButton;
    }
}

void selectNextMenuButton(Menu* menu, Node** currentNode) {
    if((*currentNode)->nextButton != NULL) {
        unHighlightMenuButton(menu, (*currentNode)->buttonName);
        (*currentNode) = (*currentNode)->nextButton;
    }
}

Node* getCurrentNodeFromMenu(Menu* menu) {
    Node* currentNode;
    if (menu->lastSelectedOption != NULL)
        currentNode = menu->lastSelectedOption;
    else
        currentNode = menu->head;
    return currentNode;
}

MenuOption waitForPlayerToSelectMenuOption(Menu* menu) {
    Node* currentNode = getCurrentNodeFromMenu(menu);
    short playerHasNotSelectedMenuOption = 1;

    while(playerHasNotSelectedMenuOption) {
        highlightMenuButton(menu, currentNode->buttonName);

        switch (getch()) {
            case KEY_LEFT:
                selectPreviousMenuButton(menu, &currentNode);
                break;
            case KEY_RIGHT:
                selectNextMenuButton(menu, &currentNode);
                break;
            case '\n':
                unHighlightMenuButton(menu, currentNode->buttonName);
                playerHasNotSelectedMenuOption = 0;
                menu->lastSelectedOption = currentNode;
        }
    }
    return currentNode->buttonName;
}

void redrawMenu(Menu* menu) {
    Node* currentButton = menu->head;

    while (currentButton != NULL) {
        drawButton(currentButton->topLeftCornerOfButton, currentButton->buttonText);
        currentButton = currentButton->nextButton;
    }
}
