#include <stdlib.h>
#include <time.h>
#include "../headers/game.h"
#include "../headers/dataStructures.h"
#include "../headers/endScreen.h"
#include "../headers/ranking.h"
#include "../headers/saveGame.h"

void handleInGameMenu(Menu* menu, GameBoard* gameBoard, GameStatus* gameStatus);
void startNewRound(GameBoard* gameBoard, GameStatus* gameStatus);
void resetGameStatus(GameStatus* gameStatus);
void initializeGameBoard(GameBoard* gameBoard);
void resetGameBoard(GameBoard* gameBoard);
void addPawnsToField(TypeOfPawn typeOfPawn, short fieldNumber, short numberOfPawns, GameBoard* gameBoard);
void addPawnToField(TypeOfPawn typeOfPawn, short fieldNumber, GameBoard* gameBoard);
void onRollDiceButtonClick(GameBoard* gameBoard, GameStatus* gameStatus);
void waitForPawnsToDecideWhoStartsGame(GameBoard* gameBoard);
short playerHasNoPossibleMoves(GameBoard* gameBoard);
void changeGameTurn(GameBoard* gameBoard, GameStatus* gameStatus);
void simulateRollDiceByPawn(Dice dice, TypeOfPawn typeOfPawn, GameBoard* gameBoard);
short getRandomNumberInRange(short minInclusive, short maxInclusive);
void decideWhoStartsTheGame(GameBoard* gameBoard);
void getAllFieldsFromWhichPlayerCanMove(TypeOfPawn typeOfPawn, LinkedList* possibleMoves, GameBoard* gameBoard);
short playerHavePawnsOnBar(GameBoard* gameBoard);
short canPawnMoveFromBar(TypeOfPawn typeOfPawn, GameBoard* gameBoard);
void getPossibleMovesOfPawnFromField(TypeOfPawn typeOfPawn, short fieldNumber, LinkedList* possibleMoves, GameBoard* gameBoard);
void getDiceFromGameBoard(GameBoard* gameBoard, short dice[4]);
void getSumOfDices(short dice[4]);
void filterDice(TypeOfPawn typeOfPawn, short fieldNumber, short dice[4], LinkedList* possibleMoves, GameBoard* gameBoard);
void filter4Dice(TypeOfPawn typeOfPawn, short fieldNumber, short dice[4], LinkedList* possibleMoves, GameBoard* gameBoard);
void filter2Dice(TypeOfPawn typeOfPawn, short fieldNumber, short dice[4], LinkedList* possibleMoves, GameBoard* gameBoard);
short pawnCanBePlacedOnField(TypeOfPawn typeOfPawn, short fieldNumber, GameBoard* gameBoard);
short playerCanRemovePawnsFromGameBoard(TypeOfPawn player, GameBoard* gameBoard);
short getNumberOfPawnsInHome(TypeOfPawn pawnHome, GameBoard* gameBoard);
short getNumberOfPawnsOnYard(TypeOfPawn pawn, GameBoard* gameBoard);
short capturingOfEnemyPawnIsAvailable(TypeOfPawn pawn, short fieldNumber, GameBoard* gameBoard);
short playerCanRemoveLastPawnFromHome(TypeOfPawn typeOfPawn, GameBoard* gameBoard);
short getFieldNumberOfLastPawnInHome(TypeOfPawn typeOfPawn, GameBoard* gameBoard);
short getIndexOfMaxDice(GameBoard* gameBoard, short lessThen);
void getRemovePawnMove(LinkedList* possibleMoves);
short checkIfCapturingOfPawnIsAvailableFromField(TypeOfPawn typeOfPawn, LinkedList* possibleMoves, GameBoard* gameBoard);
void getCapturingMove(TypeOfPawn typeOfPawn, LinkedList* possibleMoves, short fieldNumber, GameBoard* gameBoard);
void getPossibleMovesFromFields(TypeOfPawn typeOfPawn, LinkedList* possibleMoves, GameBoard* gameBoard);
void getRemovePawnMoves(TypeOfPawn typeOfPawn, LinkedList* possibleMoves, GameBoard* gameBoard);
short playerHavePawnToRemove(TypeOfPawn typeOfPawn, LinkedList* possibleRemoves, GameBoard* gameBoard);
short checkIfPlayerCanCaptureAnyEnemyPawn(TypeOfPawn typeOfPawn, LinkedList* possibleMoves, GameBoard* gameBoard);
void getNearestEnemyHomeCapturingMove(TypeOfPawn typeOfPawn, LinkedList* possibleMoves, GameBoard* gameBoard);
void checkIfCurrentMoveCanCaptureNearestEnemyHomePawn(TypeOfPawn typeOfPawn, short currenMove, short* nearestEnemyHome, short* fieldNumber, GameBoard* gameBoard);
short getDistanceFromEnemyHome(TypeOfPawn typeOfPawn, short fieldNumber);
void simulateRollTwoDiceByPawn(TypeOfPawn typeOfPawn, GameBoard* gameBoard);
void sortDice(GameBoard* gameBoard);
void onSelectPawnButtonClick(GameBoard* gameBoard, GameStatus* gameStatus);
short pawnCanUseSelectPawnButton(GameBoard* gameBoard, GameStatus* gameStatus);
void selectPawnFromGameBoard(GameBoard* gameBoard, GameStatus* gameStatus);
short waitForPawnToSelectField(LinkedList* possibleMoves, TypeOfPawn pawn);
void highlightSelectedField(short currentSelectedField, TypeOfPawn playerTurn);
void selectNextField(LinkedListNode** currentField, TypeOfPawn playerTurn);
void unHighlightSelectedField(short previousSelectedField, TypeOfPawn playerTurn);
void selectPrevField(LinkedListNode** currentField, TypeOfPawn playerTurn);
void onMoveSelectedPawnButtonClick(GameBoard* gameBoard, GameStatus* gameStatus, Menu* menu);
short getDestinationField(GameBoard* gameBoard, short selectedField);
void movePawnFromSelectedField(GameBoard* gameBoard, short selectedField, short destinationField);
void movePawnFromBarToField(GameBoard* gameBoard, short destinationField);
void captureEnemyPawn(GameBoard* gameBoard, short fieldNumber);
void removePawnFromField(short fieldNumber, GameBoard* gameBoard);
void removePawnFromBar(TypeOfPawn pawn, GameBoard* gameBoard);
void addPawnToBar(TypeOfPawn pawn, GameBoard* gameBoard);
void useDice(GameBoard* gameBoard, short number);
void movePawnFromFieldToYard(GameBoard* gameBoard, short selectedField);
void useMaxDice(GameBoard* gameBoard);
void addPawnToYard(TypeOfPawn pawn, GameBoard* gameBoard);
void movePawnFromFieldToField(GameBoard* gameBoard, short selectedField, short destinationField);
void analyseGameAfterMove(GameBoard* gameBoard, GameStatus* gameStatus, Menu* menu);
short checkIfPlayerWonGame(TypeOfPawn pawn, GameBoard* gameBoard);
void endGame(GameBoard* gameBoard, GameStatus* gameStatus, Menu* menu);
short calculatePointsOfWinner(GameBoard* gameBoard);
short getNumberOfPawnsOnEnemyYard(GameBoard* gameBoard);
short getNumberOfPawnsOnEnemyBar(GameBoard* gameBoard);
void updateRanking(TypeOfPawn winner, GameStatus* gameStatus);
void redrawGame(GameBoard* gameBoard, Menu* menu);
void onSaveButtonClick(Menu* menu, GameBoard* gameBoard);
void onBackToHomeScreenButtonClick(Menu* menu, short* isGameRunning);


void playGame(char redPawnsNickname[PLAYER_NICKNAME_MAX_LENGTH], char whitePawnsNickname[PLAYER_NICKNAME_MAX_LENGTH]) {
    GameBoard gameBoard = { 0 };
    GameStatus gameStatus = { 0 };
    strcpy(gameStatus.redPawnsNickname, redPawnsNickname);
    strcpy(gameStatus.whitePawnsNickname, whitePawnsNickname);
    createTempSave(&gameStatus);
    Point downLeftCornerOfGameBoard = drawGame();
    startNewRound(&gameBoard, &gameStatus);
    Menu* menu = createInGameMenu(downLeftCornerOfGameBoard);
    handleInGameMenu(menu, &gameBoard, &gameStatus);
}

void startNewRound(GameBoard* gameBoard, GameStatus* gameStatus) {
    resetGameStatus(gameStatus);
    initializeGameBoard(gameBoard);
    appendTourInfoToTempSave(gameBoard, gameStatus);
}

void resetGameStatus(GameStatus* gameStatus) {
    gameStatus->playerHasThrownDice = 0;
    gameStatus->selectedField = 0;
    gameStatus->playerHasSelectedField = 0;
}

void initializeGameBoard(GameBoard* gameBoard) {
    resetGameBoard(gameBoard);
    addPawnsToField(redPawn, 6, 5, gameBoard);
    addPawnsToField(redPawn, 8, 3, gameBoard);
    addPawnsToField(redPawn, 13, 5, gameBoard);
    addPawnsToField(redPawn, 24, 2, gameBoard);
    addPawnsToField(whitePawn, 19, 5, gameBoard);
    addPawnsToField(whitePawn, 17, 3, gameBoard);
    addPawnsToField(whitePawn, 12, 5, gameBoard);
    addPawnsToField(whitePawn, 1, 2, gameBoard);
}

void resetGameBoard(GameBoard* gameBoard) {
    for (unsigned short i = 0; i < 24; i++) {
        gameBoard->field[i].pawnType = noneType;
        gameBoard->field[i].totalPawnsOnField = 0;
    }
    for (unsigned short i = 0; i < 2; i++) {
        gameBoard->bar[i].totalPawnsOnField = 0;
        gameBoard->yard[i].totalPawnsOnField = 0;
    }
    for (unsigned short i = 0; i < 4; i++) {
        gameBoard->dice[i].numberOfSpots = 0;
    }
    gameBoard->playerTurn = noneType;
}

void addPawnsToField(TypeOfPawn typeOfPawn, short fieldNumber, short numberOfPawns, GameBoard* gameBoard) {
    for (unsigned short i = 0; i < numberOfPawns; i++)
        addPawnToField(typeOfPawn, fieldNumber, gameBoard);
}

void addPawnToField(TypeOfPawn typeOfPawn, short fieldNumber, GameBoard* gameBoard) {
    gameBoard->field[fieldNumber - 1].pawnType = typeOfPawn;
    gameBoard->field[fieldNumber - 1].totalPawnsOnField += 1;

    if (gameBoard->field[fieldNumber - 1].totalPawnsOnField <= 5)
        drawPawnOnField(typeOfPawn, fieldNumber, gameBoard->field[fieldNumber - 1].totalPawnsOnField);
    drawNumberOfPawnsAboveField(fieldNumber, gameBoard->field[fieldNumber - 1].totalPawnsOnField);
}


void handleInGameMenu(Menu* menu, GameBoard* gameBoard, GameStatus* gameStatus) {
    short isGameRunning = 1;

    while (isGameRunning) {
        MenuOption menuOption = waitForPlayerToSelectMenuOption(menu);

        switch (menuOption) {
            case rollDice:
                onRollDiceButtonClick(gameBoard, gameStatus);
                break;
            case selectPawn:
                onSelectPawnButtonClick(gameBoard, gameStatus);
                break;
            case moveSelectedPawn:
                onMoveSelectedPawnButtonClick(gameBoard, gameStatus, menu);
                break;
            case saveGame:
                onSaveButtonClick(menu, gameBoard);
                break;
            case backToHomeScreen:
                onBackToHomeScreenButtonClick(menu, &isGameRunning);
                break;
        }
    }
}

void onRollDiceButtonClick(GameBoard* gameBoard, GameStatus* gameStatus) {
    if (gameBoard->playerTurn == noneType) {
        gameStatus->playerHasThrownDice = 0;
        waitForPawnsToDecideWhoStartsGame(gameBoard);
    }
    else if (gameStatus->playerHasThrownDice == 0 || playerHasNoPossibleMoves(gameBoard)) {
        if(playerHasNoPossibleMoves(gameBoard)) {
            changeGameTurn(gameBoard, gameStatus);
        }

        simulateRollTwoDiceByPawn(gameBoard->playerTurn, gameBoard);
        gameStatus->playerHasThrownDice = 1;
        appendTourInfoToTempSave(gameBoard, gameStatus);
    }
}

void waitForPawnsToDecideWhoStartsGame(GameBoard* gameBoard) {
    static TypeOfPawn pawnTurn = redPawn;
    static short numberOfDiceThrown = 0;

    switch (pawnTurn) {
        case redPawn:
            simulateRollDiceByPawn(firstDice, redPawn, gameBoard);
            numberOfDiceThrown += 1;
            pawnTurn = whitePawn;
            break;
        case whitePawn:
            simulateRollDiceByPawn(secondDice, whitePawn, gameBoard);
            pawnTurn = redPawn;
            numberOfDiceThrown += 1;
    }
    if (numberOfDiceThrown == 2) {
        decideWhoStartsTheGame(gameBoard);
        numberOfDiceThrown = 0;
    }
}

void simulateRollDiceByPawn(Dice dice, TypeOfPawn typeOfPawn, GameBoard* gameBoard) {
    short numberOfSpotsOnDice = getRandomNumberInRange(1, 6);
    Colors colorPalette = (typeOfPawn == redPawn ? redPawnsDice : whitePawnsDice);

    drawDiceOnGameBoard(dice, numberOfSpotsOnDice, colorPalette);
    gameBoard->dice[dice].numberOfSpots = numberOfSpotsOnDice;
}

short getRandomNumberInRange(short minInclusive, short maxInclusive) {
    srand(time(NULL) + rand() % 10000);
    return rand() % (maxInclusive - minInclusive + 1) + minInclusive;
}

void decideWhoStartsTheGame(GameBoard* gameBoard) {
    if (gameBoard->dice[firstDice].numberOfSpots > gameBoard->dice[secondDice].numberOfSpots)
        gameBoard->playerTurn = redPawn;
    else if (gameBoard->dice[firstDice].numberOfSpots < gameBoard->dice[secondDice].numberOfSpots)
        gameBoard->playerTurn = whitePawn;
}

short playerHasNoPossibleMoves(GameBoard* gameBoard) {
    LinkedList* possibleMovesOfPawn = createLinkedList();
    getAllFieldsFromWhichPlayerCanMove(gameBoard->playerTurn, possibleMovesOfPawn, gameBoard);
    short playerHasNoPossibleMoves = 0;

    if (getLengthOfLinkedList(possibleMovesOfPawn) == 0) {
        playerHasNoPossibleMoves = 1;
    }

    destroyLinkedList(possibleMovesOfPawn);
    return playerHasNoPossibleMoves;
}

void changeGameTurn(GameBoard* gameBoard, GameStatus* gameStatus) {
    gameBoard->playerTurn = (gameBoard->playerTurn == redPawn ? whitePawn : redPawn);
    gameStatus->playerHasThrownDice = 0;
    gameStatus->playerHasSelectedField = 0;
}

void getAllFieldsFromWhichPlayerCanMove(TypeOfPawn typeOfPawn, LinkedList* possibleMoves, GameBoard* gameBoard) {
    if (playerHavePawnsOnBar(gameBoard) && canPawnMoveFromBar(typeOfPawn, gameBoard))
        appendToLinkedList(possibleMoves, 0);
    else {
        getPossibleMovesFromFields(typeOfPawn, possibleMoves, gameBoard);

        if (playerCanRemovePawnsFromGameBoard(typeOfPawn, gameBoard))
            getRemovePawnMoves(typeOfPawn, possibleMoves, gameBoard);
        else
        if (checkIfPlayerCanCaptureAnyEnemyPawn(typeOfPawn, possibleMoves, gameBoard))
            getNearestEnemyHomeCapturingMove(typeOfPawn, possibleMoves, gameBoard);
    }

}

short playerHavePawnsOnBar(GameBoard* gameBoard) {
    return gameBoard->bar[gameBoard->playerTurn].totalPawnsOnField > 0;
}

short canPawnMoveFromBar(TypeOfPawn typeOfPawn, GameBoard* gameBoard) {
    short canPawnMoveFromBar = 0;
    LinkedList* possibleMovesFromField = createLinkedList();
    getPossibleMovesOfPawnFromField(typeOfPawn, 0, possibleMovesFromField, gameBoard);
    if (getLengthOfLinkedList(possibleMovesFromField) > 0)
        canPawnMoveFromBar = 1;

    destroyLinkedList(possibleMovesFromField);
    return canPawnMoveFromBar;
}

void getPossibleMovesOfPawnFromField(TypeOfPawn typeOfPawn, short fieldNumber, LinkedList* possibleMoves, GameBoard* gameBoard) {
    short dices[4];
    getDiceFromGameBoard(gameBoard, dices);

    if (fieldNumber == 0) // Bar
        fieldNumber = (typeOfPawn == redPawn ? 25 : 0);

    getSumOfDices(dices);
    filterDice(typeOfPawn, fieldNumber, dices, possibleMoves, gameBoard);

    if (playerCanRemovePawnsFromGameBoard(typeOfPawn, gameBoard)) {
        getRemovePawnMove(possibleMoves);
    }
    else if (checkIfCapturingOfPawnIsAvailableFromField(typeOfPawn, possibleMoves, gameBoard)) {
        getCapturingMove(typeOfPawn, possibleMoves, fieldNumber, gameBoard);
    }
}

void getDiceFromGameBoard(GameBoard* gameBoard, short dice[4]) {
    for (unsigned short i = 0; i < 4; i++)
        dice[i] = gameBoard->dice[i].numberOfSpots;
}

void getSumOfDices(short dice[4]) {
    if (dice[3] > 0) {
        for (unsigned short i = 1; i < 4; i++)
            if (dice[i - 1] > 0)
                dice[i] += dice[i - 1];
    }
    else if (dice[0] != dice[1] && (dice[0] > 0 && dice[1] > 0)) {
        dice[2] = dice[0] + dice[1];
        dice[3] = 0;
    }
}

void filterDice(TypeOfPawn typeOfPawn, short fieldNumber, short dice[4], LinkedList* possibleMoves, GameBoard* gameBoard) {
    if (dice[3] > 0) {
        filter4Dice(typeOfPawn, fieldNumber, dice, possibleMoves, gameBoard);
    }
    else {
        filter2Dice(typeOfPawn, fieldNumber, dice, possibleMoves, gameBoard);
    }
    if (playerCanRemoveLastPawnFromHome(typeOfPawn, gameBoard))
        if (fieldNumber == getFieldNumberOfLastPawnInHome(typeOfPawn, gameBoard))
            appendToLinkedList(possibleMoves, 25);
}

void filter4Dice(TypeOfPawn typeOfPawn, short fieldNumber, short dice[4], LinkedList* possibleMoves, GameBoard* gameBoard) {
    short moveDirection = (typeOfPawn == redPawn ? -1 : 1);

    for (unsigned short i = 0; i < 4; i++) {
        if (dice[i] > 0) {
            if (!pawnCanBePlacedOnField(typeOfPawn, fieldNumber + moveDirection * dice[i], gameBoard))
                break;
            else {
                if (fieldNumber + moveDirection * dice[i] == 0)
                    appendToLinkedList(possibleMoves, 25);
                else
                    appendToLinkedList(possibleMoves, fieldNumber + moveDirection * dice[i]);
            }
        }
    }
}

void filter2Dice(TypeOfPawn typeOfPawn, short fieldNumber, short dice[4], LinkedList* possibleMoves, GameBoard* gameBoard) {
    short moveDirection = (typeOfPawn == redPawn ? -1 : 1);

    short canBePlaced = 0;
    for (unsigned short i = 0; i < 3; i++) {
        if (dice[i] > 0) {
            if (i == 2 && canBePlaced == 0)
                break;
            if (pawnCanBePlacedOnField(typeOfPawn, fieldNumber + moveDirection * dice[i], gameBoard)) {
                if (fieldNumber + moveDirection * dice[i] == 0) {
                    appendToLinkedList(possibleMoves, 25);
                }
                else {
                    appendToLinkedList(possibleMoves, fieldNumber + moveDirection * dice[i]);
                    canBePlaced += 1;
                }
            }
        }
    }
}

short pawnCanBePlacedOnField(TypeOfPawn typeOfPawn, short fieldNumber, GameBoard* gameBoard) {
    if ((fieldNumber == 0 || fieldNumber == 25) && playerCanRemovePawnsFromGameBoard(typeOfPawn, gameBoard)) // Yard
        return 1;
    else if (fieldNumber >= 1 && fieldNumber <= 24) {
        if (capturingOfEnemyPawnIsAvailable(typeOfPawn, fieldNumber, gameBoard))
            return 1;
        else if (gameBoard->field[fieldNumber - 1].pawnType == noneType || gameBoard->field[fieldNumber - 1].pawnType == typeOfPawn)
            return 1;
    }

    return 0;
}

short playerCanRemovePawnsFromGameBoard(TypeOfPawn player, GameBoard* gameBoard) {
    short numberOfPawnsInHome = getNumberOfPawnsInHome(player, gameBoard);
    short numberOfPawnsOnYard = getNumberOfPawnsOnYard(player, gameBoard);

    if ((numberOfPawnsInHome + numberOfPawnsOnYard) == 15)
        return 1;
    else
        return 0;
}

short getNumberOfPawnsInHome(TypeOfPawn pawnHome, GameBoard* gameBoard) {
    short startingFieldOfHome = (pawnHome == redPawn ? 1 : 19);
    short endFieldOfHome = (pawnHome == redPawn ? 6 : 24);
    short numberOfPawnsInHome = 0;

    for (unsigned short i = startingFieldOfHome; i <= endFieldOfHome; i++)
        if (gameBoard->field[i - 1].pawnType == pawnHome)
            numberOfPawnsInHome += gameBoard->field[i - 1].totalPawnsOnField;

    return numberOfPawnsInHome;
}

short getNumberOfPawnsOnYard(TypeOfPawn pawn, GameBoard* gameBoard) {
    return gameBoard->yard[pawn].totalPawnsOnField;
}

short capturingOfEnemyPawnIsAvailable(TypeOfPawn pawn, short fieldNumber, GameBoard* gameBoard) {
    TypeOfPawn enemyPawn = (pawn == redPawn ? whitePawn : redPawn);
    if (fieldNumber <= 0 || fieldNumber >= 25)
        return 0;
    if (gameBoard->field[fieldNumber - 1].pawnType == enemyPawn && gameBoard->field[fieldNumber - 1].totalPawnsOnField < 2)
        return 1;
    else
        return 0;
}

// If number of spots on the dice is greater than field number of last pawn in home.
short playerCanRemoveLastPawnFromHome(TypeOfPawn typeOfPawn, GameBoard* gameBoard) {
    short lastPawnInHome = getFieldNumberOfLastPawnInHome(typeOfPawn, gameBoard);
    short distance = (typeOfPawn == redPawn ? lastPawnInHome : abs(25 - lastPawnInHome));

    if (playerCanRemovePawnsFromGameBoard(typeOfPawn, gameBoard)) {
        short index = getIndexOfMaxDice(gameBoard, 6);
        if (gameBoard->dice[index].numberOfSpots >= distance)
            return 1;
    }

    return 0;
}

short getFieldNumberOfLastPawnInHome(TypeOfPawn typeOfPawn, GameBoard* gameBoard) {
    short startingField = (typeOfPawn == redPawn ? 6 : 19);
    short endField = (typeOfPawn == redPawn ? 1 : 24);

    if (typeOfPawn == redPawn) {
        for (unsigned short i = startingField; i >= endField; i--)
            if (gameBoard->field[i - 1].totalPawnsOnField > 0 && gameBoard->field[i - 1].pawnType == typeOfPawn)
                return i;
    }
    else if (typeOfPawn == whitePawn) {
        for (unsigned short i = startingField; i <= endField; i++)
            if (gameBoard->field[i - 1].totalPawnsOnField > 0 && gameBoard->field[i - 1].pawnType == typeOfPawn)
                return i;
    }
}

short getIndexOfMaxDice(GameBoard* gameBoard, short lessThen) {
    short max = 0, index = 0;
    for (unsigned short i = 0; i < 4; i++)
        if (gameBoard->dice[i].numberOfSpots > max && gameBoard->dice[i].numberOfSpots <= lessThen) {
            max = gameBoard->dice[i].numberOfSpots;
            index = i;
        }

    return index;
}

void getRemovePawnMove(LinkedList* possibleMoves) {
    LinkedListNode* currentMove = possibleMoves->head;
    while (currentMove != NULL) {
        if (currentMove->data == 25) {
            removeAllElementsFromLinkedList(possibleMoves);
            appendToLinkedList(possibleMoves, 25);
            return;
        }
        currentMove = currentMove->nextNode;
    }
}

short checkIfCapturingOfPawnIsAvailableFromField(TypeOfPawn typeOfPawn, LinkedList* possibleMoves, GameBoard* gameBoard) {
    LinkedListNode* currentMove = possibleMoves->head;

    if (getLengthOfLinkedList(possibleMoves) > 0) {
        while (currentMove != NULL) {
            if (capturingOfEnemyPawnIsAvailable(typeOfPawn, currentMove->data, gameBoard))
                return 1;
            currentMove = currentMove->nextNode;
        }
    }
    return 0;
}

void getCapturingMove(TypeOfPawn typeOfPawn, LinkedList* possibleMoves, short fieldNumber, GameBoard* gameBoard) {
    short distance = 25;
    short nearestPawn = 0;
    LinkedListNode* currentNode = possibleMoves->head;

    while (currentNode != NULL) {
        if (capturingOfEnemyPawnIsAvailable(typeOfPawn, currentNode->data, gameBoard)) {
            if (abs(currentNode->data - fieldNumber) < distance) {
                distance = abs(currentNode->data - fieldNumber);
                nearestPawn = currentNode->data;
            }
        }
        currentNode = currentNode->nextNode;
    }

    removeAllElementsFromLinkedList(possibleMoves);
    appendToLinkedList(possibleMoves, nearestPawn);
}

void getPossibleMovesFromFields(TypeOfPawn typeOfPawn, LinkedList* possibleMoves, GameBoard* gameBoard) {
    for (unsigned short i = 1; i <= 24; i++)
        if (gameBoard->field[i - 1].pawnType == typeOfPawn && gameBoard->field[i - 1].totalPawnsOnField > 0) {
            LinkedList* possibleMovesFromField = createLinkedList();
            getPossibleMovesOfPawnFromField(typeOfPawn, i, possibleMovesFromField, gameBoard);
            if (getLengthOfLinkedList(possibleMovesFromField) > 0)
                appendToLinkedList(possibleMoves, i);
            destroyLinkedList(possibleMovesFromField);
        }
}

void getRemovePawnMoves(TypeOfPawn typeOfPawn, LinkedList* possibleMoves, GameBoard* gameBoard) {
    LinkedList* possibleRemoves = createLinkedList();
    playerHavePawnToRemove(typeOfPawn, possibleRemoves, gameBoard);
    if (getLengthOfLinkedList(possibleRemoves) > 0) {
        removeAllElementsFromLinkedList(possibleMoves);
        LinkedListNode* currentNode = possibleRemoves->head;
        while (currentNode != NULL) {
            appendToLinkedList(possibleMoves, currentNode->data);
            currentNode = currentNode->nextNode;
        }
    }
    destroyLinkedList(possibleRemoves);
}

short playerHavePawnToRemove(TypeOfPawn typeOfPawn, LinkedList* possibleRemoves, GameBoard* gameBoard) {
    for (unsigned short i = 1; i <= 24; i++) {
        if (gameBoard->field[i - 1].pawnType == typeOfPawn) {
            LinkedList *possibleMoves = createLinkedList();
            getPossibleMovesOfPawnFromField(typeOfPawn, i, possibleMoves, gameBoard);
            if (possibleMoves->head != NULL && possibleMoves->head->data == 25) {
                appendToLinkedList(possibleRemoves, i);
            }
            destroyLinkedList(possibleMoves);
        }
    }

    return 0;
}

short checkIfPlayerCanCaptureAnyEnemyPawn(TypeOfPawn typeOfPawn, LinkedList* possibleMoves, GameBoard* gameBoard) {
    LinkedListNode* currentMove = possibleMoves->head;

    while (currentMove != NULL) {
        LinkedList* movesFromField = createLinkedList();
        getPossibleMovesOfPawnFromField(typeOfPawn, currentMove->data, movesFromField, gameBoard);
        if (capturingOfEnemyPawnIsAvailable(typeOfPawn, movesFromField->head->data, gameBoard)) {
            destroyLinkedList(movesFromField);
            return 1;
        }
        destroyLinkedList(movesFromField);
        currentMove = currentMove->nextNode;
    }

    return 0;
}

void getNearestEnemyHomeCapturingMove(TypeOfPawn typeOfPawn, LinkedList* possibleMoves, GameBoard* gameBoard) {
    LinkedListNode* currentMove = possibleMoves->head;
    short nearestEnemyHome = 25;
    short fieldNumber = 0;

    while (currentMove != NULL) {
        checkIfCurrentMoveCanCaptureNearestEnemyHomePawn(typeOfPawn, currentMove->data, &nearestEnemyHome, &fieldNumber, gameBoard);
        currentMove = currentMove->nextNode;
    }

    removeAllElementsFromLinkedList(possibleMoves);
    appendToLinkedList(possibleMoves, fieldNumber);
}

void checkIfCurrentMoveCanCaptureNearestEnemyHomePawn(TypeOfPawn typeOfPawn, short currenMove, short* nearestEnemyHome, short* fieldNumber, GameBoard* gameBoard) {
    LinkedList* pM = createLinkedList(); // possible moves - pM
    getPossibleMovesOfPawnFromField(typeOfPawn, currenMove, pM, gameBoard);
    if (capturingOfEnemyPawnIsAvailable(typeOfPawn, pM->head->data, gameBoard)) {
        if (getDistanceFromEnemyHome(typeOfPawn, pM->head->data) < *nearestEnemyHome) {
            *nearestEnemyHome = getDistanceFromEnemyHome(typeOfPawn, pM->head->data);
            *fieldNumber = currenMove;
        }
    }
    destroyLinkedList(pM);
}

short getDistanceFromEnemyHome(TypeOfPawn typeOfPawn, short fieldNumber) {
    short enemyHome = (typeOfPawn == redPawn ? 24 : 1);

    return abs(enemyHome - fieldNumber);
}

void simulateRollTwoDiceByPawn(TypeOfPawn typeOfPawn, GameBoard* gameBoard) {
    simulateRollDiceByPawn(firstDice, typeOfPawn, gameBoard);
    simulateRollDiceByPawn(secondDice, typeOfPawn, gameBoard);

    if (gameBoard->dice[firstDice].numberOfSpots == gameBoard->dice[secondDice].numberOfSpots) {
        gameBoard->dice[2].numberOfSpots = gameBoard->dice[firstDice].numberOfSpots;
        gameBoard->dice[3].numberOfSpots = gameBoard->dice[firstDice].numberOfSpots;
    }
    else {
        gameBoard->dice[2].numberOfSpots = gameBoard->dice[3].numberOfSpots = 0;
    }
    sortDice(gameBoard);
}

void sortDice(GameBoard* gameBoard) {
    if (gameBoard->dice[0].numberOfSpots > gameBoard->dice[1].numberOfSpots) {
        short temp = gameBoard->dice[0].numberOfSpots;
        gameBoard->dice[0].numberOfSpots = gameBoard->dice[1].numberOfSpots;
        gameBoard->dice[1].numberOfSpots = temp;
    }
}

void onSelectPawnButtonClick(GameBoard* gameBoard, GameStatus* gameStatus) {
    if (pawnCanUseSelectPawnButton(gameBoard, gameStatus)) {
        selectPawnFromGameBoard(gameBoard, gameStatus);
    }
}

short pawnCanUseSelectPawnButton(GameBoard* gameBoard, GameStatus* gameStatus) {
    if (gameStatus->playerHasThrownDice == 0 || playerHasNoPossibleMoves(gameBoard))
        return 0;
    else
        return 1;
}

void selectPawnFromGameBoard(GameBoard* gameBoard, GameStatus* gameStatus) {
    LinkedList* possibleMovesOfPawn = createLinkedList();
    getAllFieldsFromWhichPlayerCanMove(gameBoard->playerTurn, possibleMovesOfPawn, gameBoard);

    gameStatus->selectedField = waitForPawnToSelectField(possibleMovesOfPawn, gameBoard->playerTurn);
    gameStatus->playerHasSelectedField = 1;
    destroyLinkedList(possibleMovesOfPawn);
}

short waitForPawnToSelectField(LinkedList* possibleMoves, TypeOfPawn pawn) {
    short isFieldSelected = 0;
    LinkedListNode* currentField = possibleMoves->head;
    highlightSelectedField(currentField->data, pawn);

    while (isFieldSelected == 0) {
        switch (getch()) {
            case KEY_LEFT:
                selectNextField(&currentField, pawn);
                break;
            case KEY_RIGHT:
                selectPrevField(&currentField, pawn);
                break;
            case '\n':
                isFieldSelected = 1;
                unHighlightSelectedField(currentField->data, pawn);
        }
    }

    return currentField->data;
}

void highlightSelectedField(short currentSelectedField, TypeOfPawn playerTurn) {
    if (currentSelectedField == 0)
        highlightPawnBar(playerTurn);
    else if (currentSelectedField == 25)
        highlightPawnYard(playerTurn);
    else
        highlightFieldOnGameBoard(currentSelectedField);
}

void selectNextField(LinkedListNode** currentField, TypeOfPawn playerTurn) {
    if ((*currentField)->nextNode != NULL) {
        unHighlightSelectedField((*currentField)->data, playerTurn);
        (*currentField) = (*currentField)->nextNode;
        highlightSelectedField((*currentField)->data, playerTurn);
    }
}

void unHighlightSelectedField(short previousSelectedField, TypeOfPawn playerTurn) {
    if (previousSelectedField == 0)
        unHighlightPawnBar(playerTurn);
    else if (previousSelectedField == 25)
        unHighlightPawnYard(playerTurn);
    else
        unHighlightFieldOnGameBoard(previousSelectedField);
}

void selectPrevField(LinkedListNode** currentField, TypeOfPawn playerTurn) {
    if ((*currentField)->prevNode != NULL) {
        unHighlightSelectedField((*currentField)->data, playerTurn);
        (*currentField) = (*currentField)->prevNode;
        highlightSelectedField((*currentField)->data, playerTurn);
    }
}

void onMoveSelectedPawnButtonClick(GameBoard* gameBoard, GameStatus* gameStatus, Menu* menu) {
    if (gameStatus->playerHasSelectedField) {
        short destinationField = getDestinationField(gameBoard, gameStatus->selectedField);
        movePawnFromSelectedField(gameBoard, gameStatus->selectedField, destinationField);
        gameStatus->playerHasSelectedField = 0;
        analyseGameAfterMove(gameBoard, gameStatus, menu);
    }
}

short getDestinationField(GameBoard* gameBoard, short selectedField) {
    LinkedList* possibleMoves = createLinkedList();

    getPossibleMovesOfPawnFromField(gameBoard->playerTurn, selectedField, possibleMoves, gameBoard);

    short destinationField = waitForPawnToSelectField(possibleMoves, gameBoard->playerTurn);
    return destinationField;
}

void movePawnFromSelectedField(GameBoard* gameBoard, short selectedField, short destinationField) {
    if (selectedField == 0)
        movePawnFromBarToField(gameBoard, destinationField);
    else if (destinationField == 25)
        movePawnFromFieldToYard(gameBoard, selectedField);
    else
        movePawnFromFieldToField(gameBoard, selectedField, destinationField);
}

void movePawnFromBarToField(GameBoard* gameBoard, short destinationField) {
    if (capturingOfEnemyPawnIsAvailable(gameBoard->playerTurn, destinationField, gameBoard))
        captureEnemyPawn(gameBoard, destinationField);

    removePawnFromBar(gameBoard->playerTurn, gameBoard);
    addPawnToField(gameBoard->playerTurn, destinationField, gameBoard);
    short selectedField = (gameBoard->playerTurn == redPawn ? 25 : 0);
    useDice(gameBoard, abs(destinationField - selectedField));
}

void captureEnemyPawn(GameBoard* gameBoard, short fieldNumber) {
    TypeOfPawn enemyPawn = (gameBoard->playerTurn == redPawn ? whitePawn : redPawn);
    removePawnFromField(fieldNumber, gameBoard);
    addPawnToBar(enemyPawn, gameBoard);
}

void removePawnFromField(short fieldNumber, GameBoard* gameBoard) {
    if (gameBoard->field[fieldNumber - 1].totalPawnsOnField <= 5)
        erasePawnFromField(fieldNumber, gameBoard->field[fieldNumber - 1].totalPawnsOnField);

    gameBoard->field[fieldNumber - 1].totalPawnsOnField -= 1;

    if (gameBoard->field[fieldNumber - 1].totalPawnsOnField == 0)
        gameBoard->field[fieldNumber - 1].pawnType = noneType;

    drawNumberOfPawnsAboveField(fieldNumber, gameBoard->field[fieldNumber - 1].totalPawnsOnField);
}

void addPawnToBar(TypeOfPawn pawn, GameBoard* gameBoard) {
    gameBoard->bar[pawn].totalPawnsOnField += 1;
    if (gameBoard->bar[pawn].totalPawnsOnField <= 5)
        drawPawnOnBar(pawn, gameBoard->bar[pawn].totalPawnsOnField);
    drawNumberOfPawnsAboveBar(pawn, gameBoard->bar[pawn].totalPawnsOnField);
}

void removePawnFromBar(TypeOfPawn pawn, GameBoard* gameBoard) {
    if (gameBoard->bar[pawn].totalPawnsOnField > 0)
        erasePawnFromBar(pawn, gameBoard->bar[pawn].totalPawnsOnField);
    gameBoard->bar[pawn].totalPawnsOnField -= 1;
    drawNumberOfPawnsAboveBar(pawn, gameBoard->bar[pawn].totalPawnsOnField);
}

void useDice(GameBoard* gameBoard, short number) {
    while (number > 0) {
        short index = getIndexOfMaxDice(gameBoard, number);

        if (number - gameBoard->dice[index].numberOfSpots >= 0) {
            number -= gameBoard->dice[index].numberOfSpots;
            gameBoard->dice[index].numberOfSpots = 0;
        }
    }

    drawDiceFromGameBoard(gameBoard);
}

void drawDiceFromGameBoard(GameBoard* gameBoard) {
    Colors colorPalette = (gameBoard->playerTurn == redPawn ? redPawnsDice : whitePawnsDice);

    if (gameBoard->playerTurn != noneType) {
        drawDiceOnGameBoard(firstDice, gameBoard->dice[0].numberOfSpots, colorPalette);
        drawDiceOnGameBoard(secondDice, gameBoard->dice[1].numberOfSpots, colorPalette);
    }
}

void movePawnFromFieldToYard(GameBoard* gameBoard, short selectedField) {
    short destinationField = (gameBoard->playerTurn == redPawn ? 0 : 25);

    if (selectedField == getFieldNumberOfLastPawnInHome(gameBoard->playerTurn, gameBoard))
        useMaxDice(gameBoard);
    else
        useDice(gameBoard, abs(destinationField - selectedField));

    removePawnFromField(selectedField, gameBoard);
    addPawnToYard(gameBoard->playerTurn, gameBoard);
}

void useMaxDice(GameBoard* gameBoard) {
    short lastPawnInHome = getFieldNumberOfLastPawnInHome(gameBoard->playerTurn, gameBoard);
    short distance = (gameBoard->playerTurn == redPawn ? lastPawnInHome : abs(25 - lastPawnInHome));

    while (distance > 0) {
        short index = getIndexOfMaxDice(gameBoard, 6);
        distance -= gameBoard->dice[index].numberOfSpots;
        gameBoard->dice[index].numberOfSpots = 0;
    }

    drawDiceFromGameBoard(gameBoard);
}

void addPawnToYard(TypeOfPawn pawn, GameBoard* gameBoard) {
    gameBoard->yard[pawn].totalPawnsOnField += 1;
    if (gameBoard->yard[pawn].totalPawnsOnField <= 5)
        drawPawnOnYard(pawn, gameBoard->yard[pawn].totalPawnsOnField);
    drawNumberOfPawnsAboveYard(pawn, gameBoard->yard[pawn].totalPawnsOnField);
}

void movePawnFromFieldToField(GameBoard* gameBoard, short selectedField, short destinationField) {
    if (capturingOfEnemyPawnIsAvailable(gameBoard->playerTurn, destinationField, gameBoard))
        captureEnemyPawn(gameBoard, destinationField);

    addPawnToField(gameBoard->playerTurn, destinationField, gameBoard);
    removePawnFromField(selectedField, gameBoard);

    useDice(gameBoard, abs(destinationField - selectedField));
}

void analyseGameAfterMove(GameBoard* gameBoard, GameStatus* gameStatus, Menu* menu) {
    if (!checkIfPlayerWonGame(gameBoard->playerTurn, gameBoard))
        appendTourInfoToTempSave(gameBoard, gameStatus);
    if (checkIfPlayerWonGame(gameBoard->playerTurn, gameBoard))
        endGame(gameBoard, gameStatus, menu);
}

short checkIfPlayerWonGame(TypeOfPawn pawn, GameBoard* gameBoard) {
    if (getNumberOfPawnsOnYard(pawn, gameBoard) == 15)
        return 1;
    else
        return 0;
}

void endGame(GameBoard* gameBoard, GameStatus* gameStatus, Menu* menu) {
    TypeOfPawn winner = gameBoard->playerTurn;
    switch (winner) {
        case redPawn:
            gameStatus->redPawnPoints += calculatePointsOfWinner(gameBoard);
            break;
        case whitePawn:
            gameStatus->whitePawnPoints += calculatePointsOfWinner(gameBoard);
    }

    updateRanking(winner, gameStatus);
    createEndScreen(gameStatus);
    startNewRound(gameBoard, gameStatus);
    redrawGame(gameBoard, menu);
}

short calculatePointsOfWinner(GameBoard* gameBoard) {
    short points = 1;

    if (getNumberOfPawnsOnEnemyYard(gameBoard) == 0)
        points += 1;
    if (getNumberOfPawnsOnEnemyBar(gameBoard) > 0)
        points += 2;

    return points;
}

short getNumberOfPawnsOnEnemyYard(GameBoard* gameBoard) {
    TypeOfPawn enemyPawn = (gameBoard->playerTurn == redPawn ? whitePawn : redPawn);

    return gameBoard->yard[enemyPawn].totalPawnsOnField;
}

short getNumberOfPawnsOnEnemyBar(GameBoard* gameBoard) {
    TypeOfPawn enemyPawn = (gameBoard->playerTurn == redPawn ? whitePawn : redPawn);

    return gameBoard->bar[enemyPawn].totalPawnsOnField;
}

void updateRanking(TypeOfPawn winner, GameStatus* gameStatus) {
    switch (winner) {
        case redPawn:
            savePlayerScoreToRanking(gameStatus->redPawnsNickname, gameStatus->redPawnPoints);
            break;
        case whitePawn:
            savePlayerScoreToRanking(gameStatus->whitePawnsNickname, gameStatus->whitePawnPoints);
    }
}

void redrawGame(GameBoard* gameBoard, Menu* menu) {
    drawGame();
    drawPawnsFromGameBoard(gameBoard);
    drawDiceFromGameBoard(gameBoard);
    redrawMenu(menu);
}

void onSaveButtonClick(Menu* menu, GameBoard* gameBoard) {
    createSaveGameScreen();
    redrawGame(gameBoard, menu);
}

void onBackToHomeScreenButtonClick(Menu* menu, short* isGameRunning) {
    destroyMenu(menu);
    *isGameRunning = 0;
}

void playGameFromFile(GameBoard* gameBoard, GameStatus* gameStatus) {
    Point downLeftCornerOfGameBoard = drawGame();
    Menu* menu = createInGameMenu(downLeftCornerOfGameBoard);
    drawPawnsFromGameBoard(gameBoard);
    drawDiceFromGameBoard(gameBoard);
    createTempSave(gameStatus);
    appendTourInfoToTempSave(gameBoard, gameStatus);
    handleInGameMenu(menu, gameBoard, gameStatus);
}

void drawPawnsFromGameBoard(GameBoard* gameBoard) {
    drawPawnsOnBar(redPawn, gameBoard->bar[redPawn].totalPawnsOnField);
    drawPawnsOnBar(whitePawn, gameBoard->bar[whitePawn].totalPawnsOnField);

    for (unsigned short i = 0; i < 24; i++) {
        drawPawnsOnField(gameBoard->field[i].pawnType, i + 1, gameBoard->field[i].totalPawnsOnField);
    }

    drawPawnsOnYard(redPawn, gameBoard->yard[redPawn].totalPawnsOnField);
    drawPawnsOnYard(whitePawn, gameBoard->yard[whitePawn].totalPawnsOnField);
}