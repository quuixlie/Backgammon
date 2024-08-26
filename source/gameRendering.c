#include "../headers/gameRendering.h"
#include "../headers/loadAsset.h"


Point drawGameBoard() {
    Point topLeftCornerOfGameBoard = {0, 0};
    setColor(gameBoardColor);
    topLeftCornerOfGameBoard = printAsciiArt("../assets/gameBoard.txt", topLeftCornerOfGameBoard);
    Point leftDownPointOfGameboard = {0, topLeftCornerOfGameBoard.y};
    setColor(defaultColors);
    return leftDownPointOfGameboard;
}

void numberOfSpotsToAsciiArt(short numberOfSpots, char asciiArt[]) {
    switch (numberOfSpots) {
        case 1:
            strcpy(asciiArt, ".  ");
            break;
        case 2:
            strcpy(asciiArt, ".. ");
            break;
        case 3:
            strcpy(asciiArt, "...");
            break;
        case 4:
            strcpy(asciiArt, ":..");
            break;
        case 5:
            strcpy(asciiArt, "::.");
            break;
        case 6:
            strcpy(asciiArt, ":::");
            break;
        default:
            strcpy(asciiArt, "   ");
    }
}

void drawDice(Point topLeftCornerOfDice, char numberOfSpotsAsText[]) {
    move(topLeftCornerOfDice.y++, topLeftCornerOfDice.x);
    printw("%s", "+---+");
    move(topLeftCornerOfDice.y++, topLeftCornerOfDice.x);
    printw("|%s|", numberOfSpotsAsText);
    move(topLeftCornerOfDice.y, topLeftCornerOfDice.x);
    printw("%s", "+---+");
}

void drawDiceOnGameBoard(Dice dice, short numberOfSpots, Colors colorPalette) {
    char numberOfSpotsAsText[3];
    numberOfSpotsToAsciiArt(numberOfSpots, numberOfSpotsAsText);
    Point topLeftCornerOfDice = {0, 0};

    if (dice == firstDice) {
        topLeftCornerOfDice.x = 3;
        topLeftCornerOfDice.y = 9;
    }
    else if (dice == secondDice) {
        topLeftCornerOfDice.x = 3;
        topLeftCornerOfDice.y = 13;
    }

    setColor(colorPalette);
    drawDice(topLeftCornerOfDice, numberOfSpotsAsText);
    setColor(defaultColors);
}

Point drawVerticalLine(Point topLeftCornerOfLine, short length) {
    for (unsigned short i = 0; i < length; i++) {
        move(topLeftCornerOfLine.y, topLeftCornerOfLine.x);
        addch('|');
        move(topLeftCornerOfLine.y++, topLeftCornerOfLine.x + 3);
        addch('|');
    }

    return topLeftCornerOfLine;
}

Point drawHorizontalLine(Point topLeftCornerOfLine) {
    move(topLeftCornerOfLine.y++, topLeftCornerOfLine.x+1);
    printw("%s", "__");

    return topLeftCornerOfLine;
}

Point drawFieldArrow(Point topLeftCornerOfField, short rowOfFields) {
    if (rowOfFields == 1) {
        move(topLeftCornerOfField.y++, topLeftCornerOfField.x);
        printw("\\  /");
        move(topLeftCornerOfField.y++, topLeftCornerOfField.x);
        printw(" \\/");
    }
    else if (rowOfFields == 2) {
        move(topLeftCornerOfField.y++, topLeftCornerOfField.x);
        printw(" /\\ ");
        move(topLeftCornerOfField.y++, topLeftCornerOfField.x);
        printw("/  \\");
    }

    return topLeftCornerOfField;
}

Point getTopLeftCornerOfField(short fieldNumber) {
    fieldNumber--;
    Point topLeftCornerOfField = {0, 0};

    if (fieldNumber >= 12) {
        topLeftCornerOfField.y += 3;
        fieldNumber = 23 - fieldNumber;
    }
    else
        topLeftCornerOfField.y += 15;

    if (fieldNumber < 6) {
        topLeftCornerOfField.x += 91 - 6 * fieldNumber;
    }
    else if (fieldNumber < 12) {
        topLeftCornerOfField.x += (91 - 8) - 6 * fieldNumber; // 8 is the distance between field 6 and 7.
    }

    return topLeftCornerOfField;
}

void drawFieldOnGameBoard(short fieldNumber) {
    short rowOfFields = (fieldNumber <= 12 ? 2 : 1);
    Point topLeftCornerOfField = getTopLeftCornerOfField(fieldNumber);

    if (rowOfFields == 1) {
        topLeftCornerOfField = drawVerticalLine(topLeftCornerOfField, 5);
        drawFieldArrow(topLeftCornerOfField, rowOfFields);
    }
    else if (rowOfFields == 2) {
        topLeftCornerOfField = drawFieldArrow(topLeftCornerOfField, rowOfFields);
        drawVerticalLine(topLeftCornerOfField, 5);
    }
}

void highlightFieldOnGameBoard(short fieldNumber) {
    setColor(highlightField);
    drawFieldOnGameBoard(fieldNumber);
    setColor(defaultColors);
}

void unHighlightFieldOnGameBoard(short fieldNumber) {
    setColor(fieldsColor);
    drawFieldOnGameBoard(fieldNumber);
    setColor(defaultColors);
}

void drawNumberOfPawnsAboveField(short fieldNumber, short numberOfPawns) {
    setColor(fieldsColor);
    Point topLeftCornerOfField = getTopLeftCornerOfField(fieldNumber);
    const short heightOfField = 7;
    char* textFormat = (numberOfPawns < 10 ? " 0%d " : " %d ");

    if (fieldNumber > 12) {
        move(topLeftCornerOfField.y + heightOfField, topLeftCornerOfField.x);
        printw(textFormat, numberOfPawns);
    }
    else {
        move(topLeftCornerOfField.y - 1, topLeftCornerOfField.x);
        printw(textFormat, numberOfPawns);
    }
    setColor(defaultColors);
}

void drawPawnOnField(TypeOfPawn typeOfPawn, short fieldNumber, short originYOffset) {
    Point topLeftCornerOfField = getTopLeftCornerOfField(fieldNumber);
    char pawn[] = "@@";
    const short heightOfField = 7;
    Colors colorPalette = (typeOfPawn == redPawn ? redPawns : whitePawns);

    setColor(colorPalette);
    if (fieldNumber > 12) {
        move(topLeftCornerOfField.y + (originYOffset - 1), ++topLeftCornerOfField.x);
        printw("%s", pawn);
    }
    else {
        move(topLeftCornerOfField.y + heightOfField - 1 - (originYOffset - 1), ++topLeftCornerOfField.x);
        printw("%s", pawn);
    }
    setColor(defaultColors);
}

void erasePawnFromField(short fieldNumber, short originYOffset) {
    Point topLeftCornerOfField = getTopLeftCornerOfField(fieldNumber);
    char pawn[] = "  ";
    const short heightOfField = 7;

    setColor(defaultColors);
    if (fieldNumber > 12) {
        move(topLeftCornerOfField.y + (originYOffset - 1), ++topLeftCornerOfField.x);
        printw("%s", pawn);
    }
    else {
        move(topLeftCornerOfField.y + heightOfField - 1 - (originYOffset - 1), ++topLeftCornerOfField.x);
        printw("%s", pawn);
    }
}

Point getTopLeftCornerOfBar(Bar bar) {
    Point topLeftCornerOfBar = {0, 0};

    switch (bar) {
        case redPawnsBar:
            topLeftCornerOfBar.x += 54;
            topLeftCornerOfBar.y += 15;
            break;
        case whitePawnsBar:
            topLeftCornerOfBar.x += 54;
            topLeftCornerOfBar.y += 3;
    }

    return topLeftCornerOfBar;
}

void drawPawnBar(TypeOfPawn typeOfPawn) {
    Bar bar = (typeOfPawn == redPawn ? redPawnsBar : whitePawnsBar);
    Point topLeftCornerOfBar = getTopLeftCornerOfBar(bar);

    switch (typeOfPawn) {
        case whitePawn:
            move(topLeftCornerOfBar.y, topLeftCornerOfBar.x);
            topLeftCornerOfBar = drawHorizontalLine(topLeftCornerOfBar);
            drawVerticalLine(topLeftCornerOfBar, 6);
            break;
        case redPawn:
            move(topLeftCornerOfBar.y, topLeftCornerOfBar.x);
            topLeftCornerOfBar = drawVerticalLine(topLeftCornerOfBar, 6);
            topLeftCornerOfBar.y -= 1;
            drawHorizontalLine(topLeftCornerOfBar);
    }
}

void highlightPawnBar(TypeOfPawn typeOfPawn) {
    setColor(highlightField);
    drawPawnBar(typeOfPawn);
    setColor(defaultColors);
}

void unHighlightPawnBar(TypeOfPawn typeOfPawn) {
    setColor(fieldsColor);
    drawPawnBar(typeOfPawn);
    setColor(defaultColors);
}

void drawPawnOnBar(TypeOfPawn typeOfPawn, short originYOffset) {
    Bar bar = (typeOfPawn == redPawn ? redPawnsBar : whitePawnsBar);
    Point topLeftCornerOfBar = getTopLeftCornerOfBar(bar);
    short barOffset = 5;
    char* pawn = "@@";

    switch (typeOfPawn) {
        case redPawn:
            setColor(redPawns);
            move(topLeftCornerOfBar.y + barOffset - originYOffset, topLeftCornerOfBar.x + 1);
            printw("%s", pawn);
            break;
        case whitePawn:
            setColor(whitePawns);
            move(topLeftCornerOfBar.y + 1 + originYOffset, topLeftCornerOfBar.x + 1);
            printw("%s", pawn);
    }
    setColor(defaultColors);
}

void erasePawnFromBar(TypeOfPawn typeOfPawn, short originYOffset) {
    Bar bar = (typeOfPawn == redPawn ? redPawnsBar : whitePawnsBar);
    Point topLeftCornerOfBar = getTopLeftCornerOfBar(bar);
    short barOffset = 5;
    char* pawn = "  ";

    switch (typeOfPawn) {
        case redPawn:
            setColor(redPawns);
            move(topLeftCornerOfBar.y + barOffset - originYOffset, topLeftCornerOfBar.x + 1);
            printw("%s", pawn);
            break;
        case whitePawn:
            setColor(whitePawns);
            move(topLeftCornerOfBar.y + 1 + originYOffset, topLeftCornerOfBar.x + 1);
            printw("%s", pawn);
    }
    setColor(defaultColors);
}

void drawNumberOfPawnsAboveBar(TypeOfPawn typeOfPawn, short numberOfPawns) {
    setColor(fieldsColor);
    Bar bar = (typeOfPawn == redPawn ? redPawnsBar : whitePawnsBar);
    Point topLeftCornerOfBar = getTopLeftCornerOfBar(bar);
    short redBarOffset = -2;
    short whiteBarOffset = 8;
    char* textFormat = (numberOfPawns < 10 ? "0%d" : "%d");

    switch (typeOfPawn) {
        case redPawn:
            move(topLeftCornerOfBar.y + redBarOffset, topLeftCornerOfBar.x + 1);
            break;
        case whitePawn:
            move(topLeftCornerOfBar.y + whiteBarOffset, topLeftCornerOfBar.x + 1);
    }
    printw(textFormat, numberOfPawns);
    setColor(defaultColors);
}

Point getTopLeftCornerOfYard(Yard yard) {
    Point topLeftCornerOfYard = {0, 0};

    switch (yard) {
        case redPawnsYard:
            topLeftCornerOfYard.x += 103;
            topLeftCornerOfYard.y += 15;
            break;
        case whitePawnsYard:
            topLeftCornerOfYard.x += 103;
            topLeftCornerOfYard.y += 3;
    }

    return topLeftCornerOfYard;
}

void drawPawnYard(TypeOfPawn pawn) {
    Yard yard = (pawn == redPawn ? redPawnsYard : whitePawnsYard);
    Point topLeftCornerOfYard = getTopLeftCornerOfYard(yard);

    switch (yard) {
        case redPawnsYard:
            move(topLeftCornerOfYard.y, topLeftCornerOfYard.x);
            topLeftCornerOfYard = drawVerticalLine(topLeftCornerOfYard, 6);
            topLeftCornerOfYard.y -= 1;
            drawHorizontalLine(topLeftCornerOfYard);
            break;
        case whitePawnsYard:
            move(topLeftCornerOfYard.y, topLeftCornerOfYard.x);
            topLeftCornerOfYard = drawHorizontalLine(topLeftCornerOfYard);;
            drawVerticalLine(topLeftCornerOfYard, 6);
    }
}

void highlightPawnYard(TypeOfPawn pawn) {
    setColor(highlightField);
    drawPawnYard(pawn);
    setColor(defaultColors);
}

void unHighlightPawnYard(TypeOfPawn pawn) {
    setColor(fieldsColor);
    drawPawnYard(pawn);
    setColor(defaultColors);
}

void drawNumberOfPawnsAboveYard(TypeOfPawn typeOfPawn, short numberOfPawns) {
    setColor(fieldsColor);
    Yard yard = (typeOfPawn == redPawn ? redPawnsYard : whitePawnsYard);
    Point topLeftCornerOfYard = getTopLeftCornerOfYard(yard);
    short redYardOffset = -2;
    short whiteYardOffset = 8;
    char* textFormat = (numberOfPawns < 10 ? "0%d" : "%d");

    switch (typeOfPawn) {
        case redPawn:
            move(topLeftCornerOfYard.y + redYardOffset, topLeftCornerOfYard.x + 1);
            break;
        case whitePawn:
            move(topLeftCornerOfYard.y + whiteYardOffset, topLeftCornerOfYard.x + 1);

    }
    printw(textFormat, numberOfPawns);
    setColor(defaultColors);
}

void drawPawnOnYard(TypeOfPawn typeOfPawn, short originYOffset) {
    Yard yard = (typeOfPawn == redPawn ? redPawnsYard : whitePawnsYard);
    Point topLeftCornerOfYard = getTopLeftCornerOfYard(yard);
    short yardHeightOffset = 5;
    char* pawn = "@@";

    switch (typeOfPawn) {
        case redPawn:
            setColor(redPawns);
            move(topLeftCornerOfYard.y + yardHeightOffset - originYOffset, topLeftCornerOfYard.x + 1);
            printw("%s", pawn);
            break;
        case whitePawn:
            setColor(whitePawns);
            move(topLeftCornerOfYard.y + 1 + originYOffset, topLeftCornerOfYard.x + 1);
            printw("%s", pawn);
    }

    setColor(defaultColors);
}

void drawFields() {
    for (unsigned short i = 1; i <= 24; i++) {
        setColor(fieldsColor);
        drawFieldOnGameBoard(i);
        drawNumberOfPawnsAboveField(i, 0);
    }
    setColor(defaultColors);
}

void drawBars() {
    setColor(fieldsColor);
    drawPawnBar(redPawn);
    drawNumberOfPawnsAboveBar(redPawn, 0);
    setColor(fieldsColor);
    drawPawnBar(whitePawn);
    drawNumberOfPawnsAboveBar(whitePawn, 0);
    setColor(defaultColors);
}

void drawYards() {
    setColor(fieldsColor);
    drawPawnYard(redPawn);
    drawNumberOfPawnsAboveYard(redPawn, 0);
    setColor(fieldsColor);
    drawPawnYard(whitePawn);
    drawNumberOfPawnsAboveYard(whitePawn, 0);
    setColor(defaultColors);
}

Point drawGame() {
    Point topLeftCornerOfMenu;
    topLeftCornerOfMenu = drawGameBoard();
    drawFields();
    drawBars();
    drawYards();
    topLeftCornerOfMenu.x = (GAME_WIDTH - 96) / 2;

    return topLeftCornerOfMenu;
}

void drawPawnsOnBar(TypeOfPawn typeOfPawn, short numberOfPawns) {
    for (unsigned short i = 1; i <= numberOfPawns; i++) {
        if (i <= 5)
            drawPawnOnBar(typeOfPawn, i);
        else
            break;
    }
    drawNumberOfPawnsAboveBar(typeOfPawn, numberOfPawns);
}

void drawPawnsOnField(TypeOfPawn typeOfPawn, short fieldNumber, short numberOfPawns) {
    for (unsigned short i = 1; i <= numberOfPawns; i++) {
        if (i <= 5)
            drawPawnOnField(typeOfPawn, fieldNumber, i);
        else
            break;
    }
    drawNumberOfPawnsAboveField(fieldNumber, numberOfPawns);
}

void drawPawnsOnYard(TypeOfPawn typeOfPawn, short numberOfPawns) {
    for (unsigned short i = 1; i <= numberOfPawns; i++) {
        if (i <= 5)
            drawPawnOnYard(typeOfPawn, i);
        else
            break;
    }
    drawNumberOfPawnsAboveYard(typeOfPawn, numberOfPawns);
}