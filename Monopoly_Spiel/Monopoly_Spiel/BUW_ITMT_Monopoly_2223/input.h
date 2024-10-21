#ifndef INPUT_H
#define INPUT_H

#include <curses.h>
#include <stdlib.h>
#include "game.h"
#include "field.h"

#define MENU_B_WIDTH 20
#define MENU_B_HEIGHT 3
#define NAME_MENU_WIDTH 51
#define PLAYER_STATUS_COLUMNS 54

// Würfel & Rechteck Funktionen
void displayDice(int diceA, int diceB);
void rectangle(int rows, int columns, int arr[rows][columns]);
void printRectangle(int x, int y, int rows, int columns, int arr[rows][columns]);
void deleteRectangle(int startX, int startY, int rows, int columns);

// User Input & Menüs
void pressEnter();
int mainMenu();
void menuButton(char *text, int arr[MENU_B_HEIGHT][MENU_B_WIDTH]);
int highlightMenu(int startX, int startY, int numberChoises, int verticalDistance);
int playerNumberMenu();
void nameMenu(char *text, int arr[MENU_B_HEIGHT][NAME_MENU_WIDTH]);
char *playerNameMenu(int i, player *players);
int gameMenu(player *players, int playersMove, property *properties);

// Spiel Status Funktionen
void playerStatus(int playerNumber, player *players, int playersMove);
void deletePlayerStatus(int playerNumber);
void updatePlayerStatus(int playerNumber, player *players, int playersMove);
void movePlayer(int oldField, int newField, int playersMove);
void Move(int Field, char *str, int playersMove, int c);
void displayPropertiesAndBuildings(property *properties);

void playerWon(player *players, int playersMove);

void displayEventCard(char *str_1, char *str_2, char *str_3);

#endif
