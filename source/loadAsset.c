#include "../headers/loadAsset.h"
#include "stdio.h"

Point printAsciiArt(char asciiArtPath[], Point topLeftCornerOfAsciiArt) {
    FILE* file = fopen(asciiArtPath, "r");
    char line[2048];

    while (fgets(line, sizeof(line), file) != NULL) {
        move(topLeftCornerOfAsciiArt.y++, topLeftCornerOfAsciiArt.x);
        printw("%s", line);
    }

    fclose(file);

    return topLeftCornerOfAsciiArt;
}