#include <stdio.h>
#include "string.h"
#include "../headers/loadAsset.h"
#include "../headers/game.h"

typedef struct PlayerRecord {
    char nickname[PLAYER_NICKNAME_MAX_LENGTH];
    short points;
} PlayerRecord;

short checkIfPlayerIsInRanking(char playerNickname[]);
void updatePlayerPoints(char playerNickname[], short pointsToAdd);
void addPlayerToRanking(char playerNickname[]);
short getPointsOfPlayer(char playerNickname[]);
Point drawRanking(Point beginningOfRanking);
Point drawTopPlayers(Point beginningOfTopPlayers);
void getTop3PlayersFromRanking(char playersNicknames[3][PLAYER_NICKNAME_MAX_LENGTH], short playersPoints[3]);
PlayerRecord* getPlayersRecords();
short getNumberOfPlayersInRanking();
int comparePoints(const void* player1, const void* player2);


void savePlayerScoreToRanking(char playerNickname[], short playerPoints) {
    if (checkIfPlayerIsInRanking(playerNickname) == 1)
        updatePlayerPoints(playerNickname, playerPoints);
    else {
        addPlayerToRanking(playerNickname);
        updatePlayerPoints(playerNickname, playerPoints);
    }
}

void addPlayerToRanking(char playerNickname[]) {
    FILE* file = fopen("../Data/ranking.txt", "a");
    fprintf(file, "%s 00\n", playerNickname);
    fclose(file);
}

short checkIfPlayerIsInRanking(char playerNickname[]) {
    FILE* file = fopen("../Data/ranking.txt", "r");
    char playerNicknameFromFile[25];
    short playerPoints;
    char line[100];

    while (fgets(line, sizeof(line), file) != NULL) {
        if (sscanf(line, "%s %hd", playerNicknameFromFile, &playerPoints) == 2) {
            if (strcmp(playerNickname, playerNicknameFromFile) == 0) {
                fclose(file);
                return 1;
            }
        }
    }

    fclose(file);
    return 0;
}

void updatePlayerPoints(char playerNickname[], short pointsToAdd) {
    FILE* file = fopen("../Data/ranking.txt", "r+");
    char tempNickname[25];
    short playerPoints;
    char line[100];

    while (fgets(line, sizeof(line), file) != NULL) {
        if (sscanf(line, "%s %hd", tempNickname, &playerPoints) == 2) {
            if (strcmp(playerNickname, tempNickname) == 0) {
                printf("%s %hd\n", tempNickname, playerPoints);
                fseek(file, ftell(file) - strlen(line), SEEK_SET);
                char* textFormat = (pointsToAdd + playerPoints < 10 ? "%s 0%d\n" : "%s %d\n");
                fprintf(file, textFormat, playerNickname, pointsToAdd + playerPoints);
                break;
            }
        }
    }

    fclose(file);
}

short getPlayerScoreFromRanking(char playerNickname[]) {
    if (checkIfPlayerIsInRanking(playerNickname) == 1)
        getPointsOfPlayer(playerNickname);
    else {
        addPlayerToRanking(playerNickname);
        getPointsOfPlayer(playerNickname);
    }
}

short getPointsOfPlayer(char playerNickname[]) {
    FILE* file = fopen("../Data/ranking.txt", "r");
    char playerNicknameFromFile[25];
    short playerPoints;
    char line[100];

    while (fgets(line, sizeof(line), file) != NULL) {
        if (sscanf(line, "%s %hd", playerNicknameFromFile, &playerPoints) == 2) {
            if (strcmp(playerNickname, playerNicknameFromFile) == 0) {
                break;
            }
        }
    }

    fclose(file);
    return playerPoints;
}

void createRankingScreen() {
    Point beginningOfHallOfFame = {(GAME_WIDTH - 50) / 2, 0};
    beginningOfHallOfFame = drawRanking(beginningOfHallOfFame);
    beginningOfHallOfFame.y += 2;
    beginningOfHallOfFame.x = (GAME_WIDTH - 24) / 2;
    Menu* menu = createBackToHomeScreenMenu(beginningOfHallOfFame);
    handleBackToHomeScreenMenu(menu);
}

Point drawRanking(Point beginningOfRanking) {
    clear();
    setColor(asciiArt);
    beginningOfRanking = printAsciiArt("../assets/ranking.txt", beginningOfRanking);
    setColor(defaultColors);
    beginningOfRanking.y += 1;
    beginningOfRanking.x = 0;
    beginningOfRanking = drawTopPlayers(beginningOfRanking);

    Point endOfRanking = {beginningOfRanking.x, beginningOfRanking.y};

    return endOfRanking;
}

Point drawTopPlayers(Point beginningOfTopPlayers) {
    short place = 0;
    short playersPoints[3];
    char playersNicknames[3][PLAYER_NICKNAME_MAX_LENGTH];
    getTop3PlayersFromRanking(playersNicknames, playersPoints);
    while (place < 3) {

        move(beginningOfTopPlayers.y, beginningOfTopPlayers.x+=25);
        printw("%d. %s %hd", place + 1, playersNicknames[place], playersPoints[place]);
        place++;
    }
    beginningOfTopPlayers.y += 1;
    return beginningOfTopPlayers;
}

void getTop3PlayersFromRanking(char playersNicknames[3][PLAYER_NICKNAME_MAX_LENGTH], short playersPoints[3]) {
    PlayerRecord* playersRecords = getPlayersRecords();
    qsort(playersRecords, getNumberOfPlayersInRanking(), sizeof(PlayerRecord), comparePoints);
    for (unsigned short i = 0; i < 3; i++) {
        strcpy(playersNicknames[i], playersRecords[i].nickname);
        playersPoints[i] = playersRecords[i].points;
    }
    free(playersRecords);
}

PlayerRecord* getPlayersRecords() {
    PlayerRecord* playersRecords = (PlayerRecord*) malloc(getNumberOfPlayersInRanking() * sizeof(PlayerRecord));
    short playerNumber = 0;
    FILE* file = fopen("../Data/ranking.txt", "r");

    while (fscanf(file, "%s %hd", playersRecords[playerNumber].nickname, &playersRecords[playerNumber].points) == 2) {
        playerNumber++;
    }

    fclose(file);
    return playersRecords;
}

short getNumberOfPlayersInRanking() {
    short numberOfPlayers = 0;
    char line[100];
    FILE* file = fopen("../Data/ranking.txt", "r");

    while (fgets(line, sizeof(line), file) != NULL) {
        numberOfPlayers++;
    }

    fclose(file);
    return numberOfPlayers;
}

int comparePoints(const void* player1, const void* player2) {
    return ((PlayerRecord*) player2)->points - ((PlayerRecord*) player1)->points;
}