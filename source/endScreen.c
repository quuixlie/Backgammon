#include "../headers/menu.h"
#include "../headers/game.h"
#include "../headers/loadAsset.h"


Point drawGameSummaryAsciiArt(Point topLeftCornerOfAsciiArt);
Point drawGameSummary(Point topLeftCornerOfGameSummary, GameStatus* gameStatus);
void handleEndScreenMenu(Menu* menu);


void createEndScreen(GameStatus* gameStatus) {
    Point topLeft = {10, 0};
    topLeft = drawGameSummaryAsciiArt(topLeft);
    topLeft = drawGameSummary(topLeft, gameStatus);
    topLeft.y += 3;
    topLeft.x += 36;
    Menu* menu = createEndScreenMenu(topLeft);
    handleEndScreenMenu(menu);
}

Point drawGameSummaryAsciiArt(Point topLeftCornerOfAsciiArt) {
    clear();
    setColor(asciiArt);
    topLeftCornerOfAsciiArt = printAsciiArt("../assets/gameSummary.txt", topLeftCornerOfAsciiArt);
    setColor(defaultColors);
    Point downLeftCornerOfGameSummaryAsciiArt = {topLeftCornerOfAsciiArt.x, topLeftCornerOfAsciiArt.y};
    return downLeftCornerOfGameSummaryAsciiArt;
}

Point drawGameSummary(Point topLeftCornerOfGameSummary, GameStatus* gameStatus) {
    topLeftCornerOfGameSummary.y += 1;
    move(topLeftCornerOfGameSummary.y, (GAME_WIDTH - 23) / 2);
    printw("%s: %d", gameStatus->whitePawnsNickname, gameStatus->whitePawnPoints);
    printw("%s", "   ");
    printw("%s: %d", gameStatus->redPawnsNickname, gameStatus->redPawnPoints);

    return topLeftCornerOfGameSummary;
}

void handleEndScreenMenu(Menu* menu) {
    MenuOption menuOption = waitForPlayerToSelectMenuOption(menu);
        switch (menuOption) {
            case nextRound:
                destroyMenu(menu);
        }
}

