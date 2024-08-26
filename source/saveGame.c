#include "stdio.h"
#include "../headers/saveGame.h"
#include "../headers/loadGame.h"
#include "../headers/loadAsset.h"

void createTempSave(GameStatus* gameStatus) {
    FILE* file = fopen("../Data/save/temp.txt", "w");
    fprintf(file, "%s\n", gameStatus->whitePawnsNickname);
    fprintf(file, "%s\n", gameStatus->redPawnsNickname);
    fclose(file);
}

void writePlayerPoints(GameStatus* gameStatus, FILE* file) {
    char* whitePawnPointsFormat = (gameStatus->whitePawnPoints < 10 ? "P 0%dW " : "P %dW ");
    char* redPawnPointsFormat = (gameStatus->redPawnPoints < 10 ? "0%dR\n" : "%dR\n");

    fprintf(file, whitePawnPointsFormat, gameStatus->whitePawnPoints);
    fprintf(file, redPawnPointsFormat, gameStatus->redPawnPoints);
}

void writePlayerTurn(GameBoard* gameBoard, FILE* file) {
    char playerTurn;

    switch (gameBoard->playerTurn) {
        case redPawn:
            playerTurn = 'R';
            break;
        case whitePawn:
            playerTurn = 'W';
            break;
        case noneType:
            playerTurn = 'N';
    }

    fprintf(file, "T %c\n", playerTurn);
}

void writeDice(GameBoard* gameBoard, FILE* file) {
    fprintf(file, "D %hd %hd %hd %hd\n", gameBoard->dice[0].numberOfSpots, gameBoard->dice[1].numberOfSpots,
                                         gameBoard->dice[2].numberOfSpots, gameBoard->dice[3].numberOfSpots);
}

void writeBar(GameBoard* gameBoard, FILE* file) {
    char* whitePawnsFormat = (gameBoard->bar[0].totalPawnsOnField < 10 ? "B 0%dW " : "P %dW ");
    char* redPawnsFormat = (gameBoard->bar[1].totalPawnsOnField  < 10 ? "0%dR\n" : "%dR\n");

    fprintf(file, whitePawnsFormat, gameBoard->bar[0].totalPawnsOnField);
    fprintf(file, redPawnsFormat, gameBoard->bar[1].totalPawnsOnField);
}

void writeFields(GameBoard* gameBoard, FILE* file) {
    fprintf(file, "%c", 'G');
    for (unsigned short i = 0; i < 24; i++) {
        char* numberOfPawns = (gameBoard->field[i].totalPawnsOnField < 10 ? " 0%d" : " %d");
        char typeOfPawns;

        switch (gameBoard->field[i].pawnType) {
            case redPawn:
                typeOfPawns = 'R';
                break;
            case whitePawn:
                typeOfPawns = 'W';
                break;
            case noneType:
                typeOfPawns = 'N';
        }

        fprintf(file, numberOfPawns, gameBoard->field[i].totalPawnsOnField);
        fprintf(file, "%c", typeOfPawns);
        if (i == 23)
            fprintf(file, "%c", '\n');
    }
}

void writeYard(GameBoard* gameBoard, FILE* file) {
    char* whitePawnsFormat = (gameBoard->yard[0].totalPawnsOnField < 10 ? "Y 0%dW " : "Y %dW ");
    char* redPawnsFormat = (gameBoard->yard[1].totalPawnsOnField  < 10 ? "0%dR\n" : "%dR\n");

    fprintf(file, whitePawnsFormat, gameBoard->yard[0].totalPawnsOnField);
    fprintf(file, redPawnsFormat, gameBoard->yard[1].totalPawnsOnField);
}

void appendTourInfoToTempSave(GameBoard* gameBoard, GameStatus* gameStatus) {
    FILE* file = fopen("../Data/save/temp.txt", "a");
    fprintf(file, "%c\n", '{');
    writePlayerPoints(gameStatus, file);
    writePlayerTurn(gameBoard, file);
    writeDice(gameBoard, file);
    writeBar(gameBoard, file);
    writeFields(gameBoard, file);
    writeYard(gameBoard, file);
    fprintf(file, "%c\n", '}');
    fclose(file);
}

void saveTempSaveToSlot(MenuOption menuOption) {
    char filePath[40];
    char line[100];
    getFilePathOfSaveSlot(menuOption, filePath);

    FILE* saveSlot = fopen(filePath, "w");
    FILE* tempSave = fopen("../Data/save/temp.txt", "r");

    while (fgets(line, sizeof(line), tempSave) != NULL) {
        fputs(line, saveSlot);
    }

    fclose(tempSave);
    fclose(saveSlot);
}

Point drawSaveGameAsciiArt(Point topLeftCornerOfAsciiArt) {
    setColor(asciiArt);
    char filePath[] = "../assets/saveGame.txt";
    topLeftCornerOfAsciiArt = printAsciiArt(filePath, topLeftCornerOfAsciiArt);
    setColor(defaultColors);

    return topLeftCornerOfAsciiArt;
}

void handleSaveGameMenu(Menu* menu) {
    MenuOption menuOption = waitForPlayerToSelectMenuOption(menu);
    saveTempSaveToSlot(menuOption);
    destroyMenu(menu);
}

void createSaveGameScreen() {
    clear();
    Point topLeftCornerOfAsciiArt = {(GAME_WIDTH - 65) / 2, 0};
    topLeftCornerOfAsciiArt = drawSaveGameAsciiArt(topLeftCornerOfAsciiArt);
    topLeftCornerOfAsciiArt.y += 4;
    topLeftCornerOfAsciiArt.x += 6;
    Menu* menu = createSaveSlotsMenu(topLeftCornerOfAsciiArt);
    handleSaveGameMenu(menu);
}