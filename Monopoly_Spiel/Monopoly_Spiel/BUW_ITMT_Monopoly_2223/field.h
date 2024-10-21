#ifndef FIELD_H
#define FIELD_H

#include <curses.h>

#define FIELD_WIDTH 90
#define FIELD_HEIGHT 45
#define N_PROP 20
#define GAME_FIELDS 32

typedef enum { BG_BLACK, BG_RED, BG_GREEN, BG_YELLOW, BG_BLUE, BG_MAGENTA, BG_CYAN, BG_WHITE, C_P1, C_P2, C_P3, C_P4 } bg_color_t;

//Spielfeld Funktionen
void initColor();
void initBuffer(int outputBuffer[][FIELD_WIDTH]);
void writeToBuffer(int outputBuffer[][FIELD_WIDTH], char*, int, int, int);
void printBuffer(int outputBuffer[][FIELD_WIDTH]);

#endif