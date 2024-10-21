#ifndef GAME_H
#define GAME_H
#include <curses.h>
#include "field.h"

#define START_MONEY 450
#define ROUND_MONEY 60
#define MAX_NAME_LENGTH 15

typedef struct
{
    char *name;
    int position;
    int money;
} player;

typedef struct
{
    char *name;
    int owner; // 0 = niemand 1 = P1, 2 = P2, 3 = P3, 4 = P4
    int number;
    int fieldNumber;
    int price;
    int build;// 0 = nichts, 1 = 1 Haus, 2 = 2 Häuser, 3 = Hotel
    int color;
} property;

void game(int playerNumber, player *players, int playersMove, int newTurn, property *properties);
void createNewGame(int playerNumber);

// Spiel speichern und laden
void saveGame(int playerNumber, player *players, int playersMove, property *properties);
void loadPlayers(char arr[50], int i, player *players);
void loadProperties(char arr[50], int i, property *properties);
void loadGame();

int rollDice();
int fieldTyp(player *players, int playersMove);

// Property Zeug
int searchProperty(player *players, int playersMove, property *properties);
int checkColorForBuildability(player *players, int playersMove, property *properties);
int checkPropertyPriceAndOwner(player *players, int playersMove, property *properties);
void buyProperty(player *players, int playersMove, property *properties);
void buildHouseOrHotel(player *players, int playersMove, property *properties);
void payRent(player *players, int playersMove, property *properties);
property *createProperties();

void drawEventCard(int playerNumber, player *players, int playersMove, property *properties);

#endif
