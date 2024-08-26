#include "../headers/startscreen.h"
#include "../headers/game.h"
#include "../headers/loadGame.h"
#include "../headers/loadAsset.h"
#include "../headers/ranking.h"
#include "../headers/aboutMe.h"

Point drawLogoOnStartScreen(Point beginningOfText);
void handleStartScreenMenuOptions(Menu* menu);
void onStartGameButtonClick();
void drawNicknameInput(Point beginningOfNicknameInput, char redPawnsNickname[25], char whitePawnsNickname[25]);
void getPlayerNickname(char nickname[]);
void onLoadGameButtonClick();
void onHallOfFameButtonClick();
void onAboutAuthorButtonClick();


void createStartScreen() {
    clear();
    Point beginningOfStartScreen = {(GAME_WIDTH - 99) / 2, 0};
    Point topLeftCornerOfMenu = drawLogoOnStartScreen(beginningOfStartScreen);
    topLeftCornerOfMenu.x = 11;
    topLeftCornerOfMenu.y += 4;

    Menu* menu = createStartScreenMenu(topLeftCornerOfMenu);
    handleStartScreenMenuOptions(menu);
}

Point drawLogoOnStartScreen(Point beginningOfText) {
    clear();
    setColor(asciiArt);
    beginningOfText = printAsciiArt("../assets/logo.txt", beginningOfText);

    Point endOfText = {0, beginningOfText.y};
    setColor(defaultColors);
    return endOfText;
}

void handleStartScreenMenuOptions(Menu* menu) {
    MenuOption menuOption = startGame;

    while (menuOption != exitGame) {
        menuOption = waitForPlayerToSelectMenuOption(menu);
        switch (menuOption) {
            case startGame:
                onStartGameButtonClick();
                redrawStartScreen(menu);
                break;
            case loadGame:
                onLoadGameButtonClick();
                redrawStartScreen(menu);
                break;
            case hallOfFame:
                onHallOfFameButtonClick();
                redrawStartScreen(menu);
                break;
            case aboutAuthor:
                onAboutAuthorButtonClick();
                redrawStartScreen(menu);
                break;
            case exitGame:
                destroyMenu(menu);
        }
    }
}

void onStartGameButtonClick() {
    char redPawnsNickname[PLAYER_NICKNAME_MAX_LENGTH], whitePawnsNickname[PLAYER_NICKNAME_MAX_LENGTH];
    Point beginningOfNicknameInput = {0, 0};
    drawNicknameInput(beginningOfNicknameInput, redPawnsNickname, whitePawnsNickname);
    playGame(redPawnsNickname, whitePawnsNickname);
}

void drawNicknameInput(Point beginningOfNicknameInput, char redPawnsNickname[PLAYER_NICKNAME_MAX_LENGTH], char whitePawnsNickname[PLAYER_NICKNAME_MAX_LENGTH]) {
    clear();
    echo();
    move(beginningOfNicknameInput.y++, beginningOfNicknameInput.x);
    printw("%s", "Whitespace characters will be ignored!");
    move(beginningOfNicknameInput.y++, beginningOfNicknameInput.x);
    printw("%s", "Red pawns nickname: ");
    getPlayerNickname(redPawnsNickname);
    move(beginningOfNicknameInput.y++, beginningOfNicknameInput.x);
    printw("%s", "White pawns nickname: ");
    getPlayerNickname(whitePawnsNickname);
    noecho();
}

void getPlayerNickname(char nickname[]) {
    short playerHasEnteredNickname = 0;
    short nicknameIndex = 0;
    char enteredChar;

    while (playerHasEnteredNickname == 0) {
        enteredChar = getch();

        if (enteredChar == '\n' || nicknameIndex == 24) {
            playerHasEnteredNickname = 1;
            nickname[nicknameIndex] = '\0';
        }
        else if (enteredChar == ' ') // Don't allow to use space.
            continue;
        else if (nicknameIndex < 24) {
            nickname[nicknameIndex] = enteredChar;
            nicknameIndex += 1;
        }
    }
}

void redrawStartScreen(Menu* menu) {
    clear();
    Point beginningOfStartScreen = {(GAME_WIDTH - 99) / 2, 0};
    drawLogoOnStartScreen(beginningOfStartScreen);
    redrawMenu(menu);
}

void onLoadGameButtonClick() {
    createLoadGameScreen();
}

void onHallOfFameButtonClick() {
    createRankingScreen();
}

void onAboutAuthorButtonClick() {
    createAboutMeScreen();
}

void handleBackToHomeScreenMenu(Menu* menu) {
    MenuOption menuOption = waitForPlayerToSelectMenuOption(menu);

    switch (menuOption) {
        case backToHomeScreen:
            destroyMenu(menu);
    }
}