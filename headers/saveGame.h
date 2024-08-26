#pragma once
#include "../headers/gameRendering.h"
#include "../headers/game.h"

void createTempSave(GameStatus* gameStatus);
void appendTourInfoToTempSave(GameBoard* gameBoard, GameStatus* gameStatus);
void createSaveGameScreen();