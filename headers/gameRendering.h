#pragma once
#include "../headers/startscreen.h"

#define GAME_WIDTH 111

typedef enum Dice { firstDice, secondDice } Dice;
typedef enum Bar { whitePawnsBar, redPawnsBar } Bar;
typedef enum Yard { whitePawnsYard, redPawnsYard } Yard;
typedef enum TypeOfPawn { whitePawn, redPawn, noneType } TypeOfPawn;

Point drawGameBoard();
void drawDiceOnGameBoard(Dice dice, short numberOfSpots, Colors colorPalette);
void drawFieldOnGameBoard(short fieldNumber);
void highlightFieldOnGameBoard(short fieldNumber);
void unHighlightFieldOnGameBoard(short fieldNumber);
void drawNumberOfPawnsAboveField(short fieldNumber, short numberOfPawns);
void drawPawnOnField(TypeOfPawn typeOfPawn, short fieldNumber, short originYOffset);
void erasePawnFromField(short fieldNumber, short originYOffset);
void drawPawnBar(TypeOfPawn typeOfPawn);
void highlightPawnBar(TypeOfPawn typeOfPawn);
void unHighlightPawnBar(TypeOfPawn typeOfPawn);
void drawPawnOnBar(TypeOfPawn pawn, short originYOffset);
void erasePawnFromBar(TypeOfPawn typeOfPawn, short originYOffset);
void drawNumberOfPawnsAboveBar(TypeOfPawn typeOfPawn, short numberOfPawns);
void drawPawnYard(TypeOfPawn typeOfPawn);
void highlightPawnYard(TypeOfPawn pawn);
void unHighlightPawnYard(TypeOfPawn pawn);
void drawNumberOfPawnsAboveYard(TypeOfPawn typeOfPawn, short numberOfPawns);
void drawPawnOnYard(TypeOfPawn typeOfPawn, short originYOffset);
void drawFields();
void drawBars();
void drawYards();
Point drawGame();
void drawPawnsOnBar(TypeOfPawn typeOfPawn, short numberOfPawns);
void drawPawnsOnField(TypeOfPawn typeOfPawn, short fieldNumber, short numberOfPawns);
void drawPawnsOnYard(TypeOfPawn typeOfPawn, short numberOfPawns);