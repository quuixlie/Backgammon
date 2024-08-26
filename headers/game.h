#pragma once

#include "../headers/gameRendering.h"

#define PLAYER_NICKNAME_MAX_LENGTH 25

typedef struct GameDice {
    short numberOfSpots;
} GameDice;

typedef struct GameBoard {
    TypeOfPawn playerTurn;
    GameDice dice[4];
    struct {
        TypeOfPawn pawnType;
        short totalPawnsOnField;
    } field[24];
    struct {
        short totalPawnsOnField;
    } bar[2], yard[2];
} GameBoard;

typedef struct GameStatus {
    char redPawnsNickname[25];
    char whitePawnsNickname[25];
    short redPawnPoints;
    short whitePawnPoints;
    short playerHasThrownDice;
    short selectedField;
    short playerHasSelectedField;
} GameStatus;

void playGame(char redPawnsNickname[25], char whitePawnsNickname[25]);
void drawDiceFromGameBoard(GameBoard* gameBoard);
void playGameFromFile(GameBoard* gameBoard, GameStatus* gameStatus);
void drawPawnsFromGameBoard(GameBoard* gameBoard);