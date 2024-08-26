#include "../headers/aboutMe.h"
#include "../headers/startscreen.h"
#include "../headers/loadAsset.h"

Point drawAboutAuthorSection(Point beginningOfAboutAuthorSection);


void createAboutMeScreen() {
    Point beginningOfAboutAuthor = {(GAME_WIDTH - 47) / 2, 0};
    beginningOfAboutAuthor = drawAboutAuthorSection(beginningOfAboutAuthor);
    beginningOfAboutAuthor.x = (GAME_WIDTH - 25) / 2;
    beginningOfAboutAuthor.y += 2;
    Menu* menu = createBackToHomeScreenMenu(beginningOfAboutAuthor);
    handleBackToHomeScreenMenu(menu);
}

Point drawAboutAuthorSection(Point beginningOfAboutAuthorSection) {
    clear();
    setColor(asciiArt);
    beginningOfAboutAuthorSection = printAsciiArt("../assets/aboutMe.txt", beginningOfAboutAuthorSection);
    setColor(defaultColors);
    beginningOfAboutAuthorSection.y++;
    move(beginningOfAboutAuthorSection.y, beginningOfAboutAuthorSection.x);
    printw("%s", "Author of the game: https://quuixlie.github.io/");
    beginningOfAboutAuthorSection.y++;
    Point endOfAboutAuthorSection = {0, beginningOfAboutAuthorSection.y};

    return endOfAboutAuthorSection;
}