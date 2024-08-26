#include "headers/startscreen.h"

int main(void) {
    initializeNcurses();
    createStartScreen();
    destroyNcurses();

    return 0;
}
