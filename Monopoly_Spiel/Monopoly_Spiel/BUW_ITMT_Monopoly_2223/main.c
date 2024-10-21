/*
 * Rahmenprogramm IT-Projekt 2022/2023
 *
 * Kompilieren mit: gcc -Wall -std=c11 main.c field.c input.c game.c -lncurses
 */

#include "field.h"
#include "input.h"
#include "game.h"

int main(void)
{
    int outputBuffer[FIELD_HEIGHT][FIELD_WIDTH];

    /* curses initialisieren */
    initscr();

    start_color();
    initColor();

    clear();
    cbreak();
    noecho();

    // Spielfeld
    initBuffer(outputBuffer);
    printBuffer(outputBuffer);
    refresh();

    while (1)
    {
        int c = mainMenu();

        if (c == 0)
        { // Neues Spiel
            createNewGame(playerNumberMenu() + 2);
        }
        else if (c == 1)
        { // Spiel laden ----> bei der game funktion muss roll gleich 0,
            loadGame();
        }
        else
            break; // Spiel Verlassen
    }

    endwin();

    return 0;
}
