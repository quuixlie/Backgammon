#include "../headers/loadGame.h"
#include "stdio.h"
#include "../headers/game.h"
#include "../headers/loadAsset.h"

MenuOption waitForUserToSelectSave();
Point drawSelectSaveMenu(Point topLeftCornerOfSaveMenu);
GameBoard waitForUserToSelectGameMoment(MenuOption saveSlot);
void handleLoadLastGame(Menu* menu, char filePath[]);
void parseNicknames(GameStatus* gameStatus, FILE* file);
void parseNickname(GameStatus* gameStatus, TypeOfPawn typeOfPawn, char line[]);
void copyStringFromLine(char string[100], char line[]);
void onNextMoveButtonClick(GameBoard* gameBoard, GameStatus* gameStatus, FILE* file);
void parseMove(char line[], GameBoard* gameBoard, GameStatus* gameStatus);
void parsePoints(GameStatus* gameStatus, char line[]);
void parseGameTurn(GameBoard* gameBoard, char line[]);
void parseDice(GameBoard* gameBoard, char line[]);
void parseBar(GameBoard* gameBoard, char line[]);
void parseGameBoard(GameBoard* gameBoard, char line[]);
void parseYard(GameBoard* gameBoard, char line[]);
void handleLoadLastGameMenu(Menu* menu, FILE* file, GameBoard* gameBoard, GameStatus* gameStatus);
void onPlayGameButtonClick(Menu* menu, FILE* file, GameBoard* gameBoard, GameStatus* gameStatus);
void onPreviousMoveButtonClick(GameBoard* gameBoard, GameStatus* gameStatus, FILE* file);
long getPrevGameBoardPos(FILE* file);
void onBeginningOfGameButton(GameBoard* gameBoard, GameStatus* gameStatus, FILE* file);
void onEndGameButtonClick(GameBoard* gameBoard, GameStatus* gameStatus, FILE* file);


void createLoadGameScreen() {
    MenuOption saveSlot = waitForUserToSelectSave();
    waitForUserToSelectGameMoment(saveSlot);
}

MenuOption waitForUserToSelectSave() {
    Point topLeftCornerOfMenu = {(GAME_WIDTH - 67) / 2, 0};
    topLeftCornerOfMenu = drawSelectSaveMenu(topLeftCornerOfMenu);
    topLeftCornerOfMenu.y += 4;
    topLeftCornerOfMenu.x += (GAME_WIDTH - 90) / 2;
    Menu* menu = createSaveSlotsMenu(topLeftCornerOfMenu);
    MenuOption menuOption = waitForPlayerToSelectMenuOption(menu);

    destroyMenu(menu);
    return menuOption;
}

Point drawSelectSaveMenu(Point topLeftCornerOfSaveMenu) {
    clear();
    setColor(asciiArt);
    char filePath[] = "../assets/selectSave.txt";
    topLeftCornerOfSaveMenu = printAsciiArt(filePath, topLeftCornerOfSaveMenu);
    setColor(defaultColors);
    return topLeftCornerOfSaveMenu;
}

GameBoard waitForUserToSelectGameMoment(MenuOption saveSlot) {
    char filePath[40];
    getFilePathOfSaveSlot(saveSlot, filePath);
    Point downLeftCornerOfGameBoard = drawGame();
    downLeftCornerOfGameBoard.x = (GAME_WIDTH - 90) / 2;
    Menu* menu = createLoadGameMenu(downLeftCornerOfGameBoard);
    handleLoadLastGame(menu, filePath);
}

void getFilePathOfSaveSlot(MenuOption saveSlot, char filePath[]) {
    switch (saveSlot) {
        case firstSlot:
            strcpy(filePath, "../Data/save/firstSave.txt");
            break;
        case secondSlot:
            strcpy(filePath, "../Data/save/secondSave.txt");
            break;
        case thirdSlot:
            strcpy(filePath, "../Data/save/thirdSave.txt");
    }
}

void handleLoadLastGame(Menu* menu, char filePath[]) {
    FILE* file = fopen(filePath, "r");
    GameBoard gameBoard;
    GameStatus gameStatus = {0};
    gameStatus.playerHasThrownDice = 1;
    parseNicknames(&gameStatus, file);
    drawGame();
    onNextMoveButtonClick(&gameBoard, &gameStatus, file);
    handleLoadLastGameMenu(menu, file, &gameBoard, &gameStatus);
}

void parseNicknames(GameStatus* gameStatus, FILE* file) {
    char line[100];
    fseek(file, 0, SEEK_SET);

    fgets(line, sizeof(line), file);
    parseNickname(gameStatus, whitePawn, line);

    fgets(line, sizeof(line), file);
    parseNickname(gameStatus, redPawn, line);
}

void parseNickname(GameStatus* gameStatus, TypeOfPawn typeOfPawn, char line[]) {
    char string[100];

    switch (typeOfPawn) {
        case redPawn:
            copyStringFromLine(string, line);
            strcpy(gameStatus->redPawnsNickname, string);
            break;
        case whitePawn:
            copyStringFromLine(string, line);
            strcpy(gameStatus->whitePawnsNickname, string);
    }
}

void copyStringFromLine(char string[100], char line[]) {
    for (unsigned short i = 0; i < 100; i++) {
        if (line[i] == '\n') {
            string[i] = '\0';
            break;
        } else {
            string[i] = line[i];
        }
    }
}

void onNextMoveButtonClick(GameBoard* gameBoard, GameStatus* gameStatus, FILE* file) {
    char line[100];
    short reading = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (line[0] == '{')
            reading = 1;
        if (reading)
            parseMove(line, gameBoard, gameStatus);
        if (line[0] == '}')
            break;
    }

    drawPawnsFromGameBoard(gameBoard);
    drawDiceFromGameBoard(gameBoard);
}

void parseMove(char line[], GameBoard* gameBoard, GameStatus* gameStatus) {
    switch (line[0]) {
        case 'P':
            parsePoints(gameStatus, line);
            break;
        case 'T':
            parseGameTurn(gameBoard, line);
            break;
        case 'D':
            parseDice(gameBoard, line);
            break;
        case 'B':
            parseBar(gameBoard, line);
            break;
        case 'G':
            parseGameBoard(gameBoard, line);
            break;
        case 'Y':
            parseYard(gameBoard, line);
    }
}

void parsePoints(GameStatus* gameStatus, char line[]) {
    short points;
    char typeOfPawnAsChar;

    if (line[0] == 'P') {
        line += 2; // 'P ' 2 chars
        for (unsigned short i = 0; i < 2; i++) {
            sscanf(line, "%hd%c", &points, &typeOfPawnAsChar);
            switch (typeOfPawnAsChar) {
                case 'R':
                    gameStatus->redPawnPoints = points;
                    break;
                case 'W':
                    gameStatus->whitePawnPoints = points;
            }
            line = strchr(line, ' ') + 1;
        }
    }
}

void parseGameTurn(GameBoard* gameBoard, char line[]) {
    if (line[0] == 'T') {
        if (line[2] == 'R')
            gameBoard->playerTurn = redPawn;
        else if(line[2] == 'W')
            gameBoard->playerTurn = whitePawn;
        else if (line[2] == 'N')
            gameBoard->playerTurn = noneType;
    }
}

void parseDice(GameBoard* gameBoard, char line[]) {
    if (line[0] == 'D') {
        gameBoard->dice[0].numberOfSpots = line[2] - '0';
        gameBoard->dice[1].numberOfSpots = line[4] - '0';
        gameBoard->dice[2].numberOfSpots = line[6] - '0';
        gameBoard->dice[3].numberOfSpots = line[8] - '0';
    }
}

void parseBar(GameBoard* gameBoard, char line[]) {
    short numberOfPawns;
    char typeOfPawnAsChar;
    TypeOfPawn typeOfPawn;

    if (line[0] == 'B') {
        line += 2; // 'B ' 2 chars
        for (unsigned short i = 0; i < 2; i++) {
            sscanf(line, "%hd%c", &numberOfPawns, &typeOfPawnAsChar);
            typeOfPawn = (typeOfPawnAsChar == 'R' ? redPawn : whitePawn);
            gameBoard->bar[typeOfPawn].totalPawnsOnField = numberOfPawns;
            line = strchr(line, ' ') + 1;
        }
    }
}

void parseGameBoard(GameBoard* gameBoard, char line[]) {
    drawGame();
    short numberOfPawns;
    char typeOfPawnAsChar;
    TypeOfPawn typeOfPawn;

    if (line[0] == 'G') {
        line += 2; // 'G ' 2 chars
        for (unsigned short i = 0; i < 24; i++) {
            sscanf(line, "%hd%c", &numberOfPawns, &typeOfPawnAsChar);
            switch (typeOfPawnAsChar) {
                case 'R':
                    typeOfPawn = redPawn;
                    break;
                case 'W':
                    typeOfPawn = whitePawn;
                    break;
                case 'N':
                    typeOfPawn = noneType;
            }
            gameBoard->field[i].totalPawnsOnField = numberOfPawns;
            gameBoard->field[i].pawnType = typeOfPawn;
            line = strchr(line, ' ') + 1;
        }
    }
}

void parseYard(GameBoard* gameBoard, char line[]) {
    short numberOfPawns;
    char typeOfPawnAsChar;
    TypeOfPawn typeOfPawn;

    if (line[0] == 'Y') {
        line += 2; // 'Y ' 2 chars
        for (unsigned short i = 0; i < 2; i++) {
            sscanf(line, "%hd%c", &numberOfPawns, &typeOfPawnAsChar);
            typeOfPawn = (typeOfPawnAsChar == 'R' ? redPawn : whitePawn);
            gameBoard->yard[typeOfPawn].totalPawnsOnField = numberOfPawns;
            line = strchr(line, ' ') + 1;
        }
    }
}

void handleLoadLastGameMenu(Menu* menu, FILE* file, GameBoard* gameBoard, GameStatus* gameStatus) {
    MenuOption op = nextMove; // menu option

    while (op != startGame) {
        op = waitForPlayerToSelectMenuOption(menu);

        switch (op) {
            case startGame:
                onPlayGameButtonClick(menu, file, gameBoard, gameStatus);
                break;
            case nextMove:
                onNextMoveButtonClick(gameBoard, gameStatus, file);
                break;
            case previousMove:
                onPreviousMoveButtonClick(gameBoard, gameStatus, file);
                break;
            case beginningOfGame:
                onBeginningOfGameButton(gameBoard, gameStatus, file);
                break;
            case endOfGame:
                onEndGameButtonClick(gameBoard, gameStatus, file);
                break;
        }
    }
}

void onPlayGameButtonClick(Menu* menu, FILE* file, GameBoard* gameBoard, GameStatus* gameStatus) {
    destroyMenu(menu);
    fclose(file);
    playGameFromFile(gameBoard, gameStatus);
}

void onPreviousMoveButtonClick(GameBoard* gameBoard, GameStatus* gameStatus, FILE* file) {
    if (getPrevGameBoardPos(file) > 0) {
        fseek(file, getPrevGameBoardPos(file), SEEK_SET);
        fseek(file, getPrevGameBoardPos(file), SEEK_SET);
        onNextMoveButtonClick(gameBoard, gameStatus, file);
    }
}

long getPrevGameBoardPos(FILE* file) {
    short chunkSize = 146;
    long prevPos = ftell(file) - chunkSize;

    return prevPos;
}

void onBeginningOfGameButton(GameBoard* gameBoard, GameStatus* gameStatus, FILE* file) {
    fseek(file, 0, SEEK_SET);
    onNextMoveButtonClick(gameBoard, gameStatus, file);
}

void onEndGameButtonClick(GameBoard* gameBoard, GameStatus* gameStatus, FILE* file) {
    fseek(file, 0, SEEK_END);
    fseek(file, getPrevGameBoardPos(file), SEEK_SET);
    onNextMoveButtonClick(gameBoard, gameStatus, file);
}