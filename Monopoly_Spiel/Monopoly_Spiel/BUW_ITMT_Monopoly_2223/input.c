#include "input.h"

/*
 * Gewürfelte Werte Anzeigen und durch drücken von Taste (Enter) wieder Löschen
 */
void displayDice(int diceAValue, int diceBValue)
{
    int diceA[5][11] = {0}, diceB[5][11] = {0};

    // Würfel außenlinien erstellen (5 Zeilen, 11 Spalten)
    rectangle(5, 11, diceA);
    rectangle(5, 11, diceB);

    // Würfel A Punkte erstellen
    if (diceAValue % 2 != 0)
        diceA[2][5] = 'o';
    if (diceAValue > 1)
    {
        diceA[1][7] = 'o';
        diceA[3][3] = 'o';
    }
    if (diceAValue > 3)
    {
        diceA[3][7] = 'o';
        diceA[1][3] = 'o';
    }
    if (diceAValue == 6)
    {
        diceA[2][7] = 'o';
        diceA[2][3] = 'o';
        diceA[2][3] = 'o';
        diceA[2][7] = 'o';
    }

    // Würfel B Punkte erstellen
    if (diceBValue % 2 != 0)
        diceB[2][5] = 'o';
    if (diceBValue > 1)
    {
        diceB[1][7] = 'o';
        diceB[3][3] = 'o';
    }
    if (diceBValue > 3)
    {
        diceB[3][7] = 'o';
        diceB[1][3] = 'o';
    }
    if (diceBValue == 6)
    {
        diceB[2][7] = 'o';
        diceB[2][3] = 'o';
        diceB[2][3] = 'o';
        diceB[2][7] = 'o';
    }

    printRectangle(31, 20, 5, 11, diceA);
    printRectangle(47, 20, 5, 11, diceB);

    pressEnter();

    deleteRectangle(31, 20, 5, 11);
    deleteRectangle(47, 20, 5, 11);
}

/*
 * Rechteck in Array speichern
 */
void rectangle(int rows, int columns, int arr[rows][columns])
{

    // Mit Leerzeichen füllen
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            arr[i][j] = ' ';
        }
    }

    // Ecken
    arr[0][0] = ACS_ULCORNER;
    arr[rows - 1][0] = ACS_LLCORNER;
    arr[0][columns - 1] = ACS_URCORNER;
    arr[rows - 1][columns - 1] = ACS_LRCORNER;

    // Linien
    for (int i = 1; i < columns - 1; i++)
    {
        arr[0][i] = ACS_HLINE;
        arr[rows - 1][i] = ACS_HLINE;
    }
    for (int i = 1; i < rows - 1; i++)
    {
        arr[i][0] = ACS_VLINE;
        arr[i][columns - 1] = ACS_VLINE;
    }
}

/*
 * Rechteck Array an bestimmter Stelle ausgeben
 */
void printRectangle(int startX, int startY, int rows, int columns, int arr[rows][columns])
{
    for (int i = 0; i < rows; i++)
    {
        move(startY + i, startX);
        for (int j = 0; j < columns; j++)
        {
            addch(arr[i][j]);
        }
    }
    move(45, 0);
}

/*
 * Rechteck Array an bestimmter Stelle löschen
 */
void deleteRectangle(int startX, int startY, int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        move(startY + i, startX);
        for (int j = 0; j < columns; j++)
        {
            addch(' ');
        }
    }
    move(45, 0);
}

/*
 * Auf drücken von Enter warten
 */
void pressEnter()
{
    while (1)
    {
        int ch = getch();
        if (ch == '\n')
            break;
    }
}

/*
 * Hauptmenü
 */
int mainMenu()
{
    int ch;
    int choiceA[MENU_B_HEIGHT][MENU_B_WIDTH];
    int choiceB[MENU_B_HEIGHT][MENU_B_WIDTH];
    int choiceC[MENU_B_HEIGHT][MENU_B_WIDTH];

    // Menüknöpfe erstellen
    menuButton("Neues Spiel", choiceA);
    menuButton("Spiel Laden", choiceB);
    menuButton("Spiel Verlassen", choiceC);
    printRectangle(34, 18, MENU_B_HEIGHT, MENU_B_WIDTH, choiceA);
    printRectangle(34, 21, MENU_B_HEIGHT, MENU_B_WIDTH, choiceB);
    printRectangle(34, 24, MENU_B_HEIGHT, MENU_B_WIDTH, choiceC);

    ch = highlightMenu(35, 19, 2, 3); // numberChoises beginnt bei 0

    deleteRectangle(34, 18, MENU_B_HEIGHT, MENU_B_WIDTH);
    deleteRectangle(34, 21, MENU_B_HEIGHT, MENU_B_WIDTH);
    deleteRectangle(34, 24, MENU_B_HEIGHT, MENU_B_WIDTH);

    return ch;
}

/*
 * Menüknopf in Array speichern
 */
void menuButton(char *text, int arr[MENU_B_HEIGHT][MENU_B_WIDTH])
{
    rectangle(MENU_B_HEIGHT, MENU_B_WIDTH, arr);

    for (int i = 0; *(text + i) != '\0'; i++)
    {
        arr[1][2 + i] = *(text + i);
    }
}

/*
 * Menüknopf auswählen und anzeigen
 */
int highlightMenu(int startX, int startY, int numberChoises, int verticalDistance)
{
    int choice = 0, tmp = choice, input;
    keypad(stdscr, TRUE);

    mvchgat(startY + choice * verticalDistance, startX, 18, A_STANDOUT, 0, NULL);
    move(45, 0);

    while (1)
    {
        input = getch();
        switch (input)
        {
        case KEY_UP:
            choice--;
            if (choice < 0)
                choice = 0;
            break;
        case KEY_DOWN:
            choice++;
            if (choice > numberChoises)
                choice = numberChoises;
            break;
        default:
            break;
        }
        mvchgat(startY + choice * verticalDistance, startX, 18, A_STANDOUT, 0, NULL);

        if (tmp != choice)
        {
            mvchgat(startY + tmp * verticalDistance, startX, 18, A_NORMAL, 0, NULL);
            tmp = choice;
        }
        move(45, 0);
        if (input == '\n')
            break;
    }
    return choice;
}

/*
 * Anzahl Spieler Menü
 */
int playerNumberMenu()
{
    int ch;
    int choiceA[MENU_B_HEIGHT][MENU_B_WIDTH];
    int choiceB[MENU_B_HEIGHT][MENU_B_WIDTH];
    int choiceC[MENU_B_HEIGHT][MENU_B_WIDTH];

    // Menüknöpfe erstellen
    menuButton("Zwei Spieler", choiceA);
    menuButton("Drei Spieler", choiceB);
    menuButton("Vier Spieler", choiceC);
    printRectangle(34, 18, MENU_B_HEIGHT, MENU_B_WIDTH, choiceA);
    printRectangle(34, 21, MENU_B_HEIGHT, MENU_B_WIDTH, choiceB);
    printRectangle(34, 24, MENU_B_HEIGHT, MENU_B_WIDTH, choiceC);

    ch = highlightMenu(35, 19, 2, 3); // numberChoises beginnt bei 0

    deleteRectangle(34, 18, MENU_B_HEIGHT, MENU_B_WIDTH);
    deleteRectangle(34, 21, MENU_B_HEIGHT, MENU_B_WIDTH);
    deleteRectangle(34, 24, MENU_B_HEIGHT, MENU_B_WIDTH);

    return ch;
}

/*
 * Namens eingabe Menü in Array speichern
 */
void nameMenu(char *text, int arr[MENU_B_HEIGHT][NAME_MENU_WIDTH])
{
    rectangle(MENU_B_HEIGHT, NAME_MENU_WIDTH, arr);

    for (int i = 0; *(text + i) != '\0'; i++)
    {
        arr[1][2 + i] = *(text + i);
    }
}

/*
 * Spieler Namen eingabe Menü
 */
char *playerNameMenu(int i, player *players)
{
    char text[30];

    int arr[MENU_B_HEIGHT][NAME_MENU_WIDTH];
    
    char *name = calloc(MAX_NAME_LENGTH + 1, sizeof(char));
    
    sprintf(text, "Spieler %d Namen eingeben: ", i + 1);

    nameMenu(text, arr);
    printRectangle(19, 21, MENU_B_HEIGHT, NAME_MENU_WIDTH, arr);

    move(22, 46);
    
    int k = 0;
    
    while(true){
        int c = getch();
        
        if(c == KEY_BACKSPACE){
            k--;
            move(22, 46 + k);
            addch(' ');
            move(22, 46 + k);
        }
        else if(c == '\n'){
            name[k] = '\0';
            break;
        }
        else if((k != MAX_NAME_LENGTH) && ((c >= 33) && (c <= 126))){//nur ASCII Zeichen 
            addch(c);
            
            name[k] = c;
            k++;
        }
    }
     
    (players + i)->name = name;
    
    deleteRectangle(19, 21, MENU_B_HEIGHT, NAME_MENU_WIDTH);

    return name;
}

/*
 * Spiel Menü
 */
int gameMenu(player *players, int playersMove, property *properties)
{
    int ch;
    int buyOrBuild = false;
    int chModifier = 0;
    
    int choiceA[MENU_B_HEIGHT][MENU_B_WIDTH];
    int choiceB[MENU_B_HEIGHT][MENU_B_WIDTH];
    int choiceC[MENU_B_HEIGHT][MENU_B_WIDTH];
    int choiceD[MENU_B_HEIGHT][MENU_B_WIDTH];

    // Menüknöpfe erstellen
    if((fieldTyp(players, playersMove) == 1) || (fieldTyp(players, playersMove) == 3)){
        if(checkPropertyPriceAndOwner(players, playersMove, properties) == 0){
            menuButton("Kaufen", choiceA);
            buyOrBuild = true;
            chModifier = -1;
        }
        else if(checkPropertyPriceAndOwner(players, playersMove, properties) == 1){
            menuButton("Bauen", choiceA);
            buyOrBuild = true;
            chModifier = 1;
        }
    }
    menuButton("Zug beenden", choiceB);
    menuButton("Speichern", choiceC);
    menuButton("Spiel Verlassen", choiceD);

    if(buyOrBuild == true){
        printRectangle(34, 17, MENU_B_HEIGHT, MENU_B_WIDTH, choiceA);
    }
    printRectangle(34, 20, MENU_B_HEIGHT, MENU_B_WIDTH, choiceB);
    printRectangle(34, 23, MENU_B_HEIGHT, MENU_B_WIDTH, choiceC);
    printRectangle(34, 26, MENU_B_HEIGHT, MENU_B_WIDTH, choiceD);
    
    // Auswahl von Optionen ermöglichen
    ch = highlightMenu(35, 21 - (buyOrBuild * 3), 2 + buyOrBuild, 3); // numberChoises beginnt bei 0
    
    // Menüknöpfe wieder löschen
    if(buyOrBuild == true){
        deleteRectangle(34, 17, MENU_B_HEIGHT, MENU_B_WIDTH);
    }
    deleteRectangle(34, 20, MENU_B_HEIGHT, MENU_B_WIDTH);
    deleteRectangle(34, 23, MENU_B_HEIGHT, MENU_B_WIDTH);
    deleteRectangle(34, 26, MENU_B_HEIGHT, MENU_B_WIDTH);
    
    // Abhängig davon ob man kaufen oder bauen konnte ch modifizieren
    if((buyOrBuild == true) && (chModifier == 1)){
        ch += chModifier;
    }
    else if((buyOrBuild == true) && (chModifier == -1)){
        if(ch >= 1) ch += 1;
    }
    else{
        ch += 2;
    }

    return ch;
}

/*
 * Spieler Status anzeigen
 */
void playerStatus(int playerNumber, player *players, int playersMove)
{
    char playerStatus[playerNumber][PLAYER_STATUS_COLUMNS];

    for (int i = 0; i < playerNumber; i++)
    {
        int k = 0;

        // Mit leerteichen auffüllen
        for (int x = 0; x < PLAYER_STATUS_COLUMNS; x++)
        {
            playerStatus[i][x] = ' ';
        }

        // Länge Namen bestimmen
        for (char *tmp = (players + i)->name; *tmp != '\0'; tmp++)
        {
            k++;
        }
        
        // Array mit Leerzeichen abhängig von der nameslänge füllen -> um gleichen Abstand zwischen Namen und "Geld" zu erzielen
        char filler[(MAX_NAME_LENGTH - k) + 1];
        for (int j = 0; j < ((MAX_NAME_LENGTH - k) + 1); j++)
        {
            filler[j] = ' ';
        }
        filler[MAX_NAME_LENGTH - k] = '\0'; // Add null terminator to prevent control characters in filler
        
        if ((players + i)->money < 0){
            sprintf(playerStatus[i], " P%d: \"%s\"%s Geld:%d $ PLEITE", (i + 1), (players + i)->name, filler, (players + i)->money);
        }
        else if (i + 1 == playersMove)
        {
            sprintf(playerStatus[i], ">P%d: \"%s\"%s Geld:%d $<", (i + 1), (players + i)->name, filler, (players + i)->money);
        }
        else
        {
            sprintf(playerStatus[i], " P%d: \"%s\"%s Geld:%d $ ", (i + 1), (players + i)->name, filler, (players + i)->money);
        }
    }

    // Ausgabe des Spiel Status
    for (int i = 0; i < playerNumber; i++)
    {
        attron(COLOR_PAIR(8 + i));// Spieler Farben
        attron(A_BOLD);// Heller machen
            
        move(9 + i, 17);
        refresh();
        for (char* tmp = playerStatus[i]; *tmp != '\0'; tmp++)
        {
            addch(*tmp);
        }
        
        attroff(A_BOLD);
        attroff(COLOR_PAIR(8 + i));        
    }
    move(45, 0);
}

/*
 * Spieler Status löschen
 */
void deletePlayerStatus(int playerNumber)
{ 
    for (int i = 0; i < playerNumber; i++)
    {
        move(9 + i, 17);
        for (int j = 0; j < PLAYER_STATUS_COLUMNS; j++)
        {
            addch(' ');
        }
    }
    move(45, 0);
}

/*
 * Spieler Status aktualisieren
 */
void updatePlayerStatus(int playerNumber, player *players, int playersMove)
{
    deletePlayerStatus(playerNumber);
    playerStatus(playerNumber, players, playersMove);
}

/*
 * Spieler bewegung managen
 */
void movePlayer(int oldField, int newField, int playersMove)
{
    char str[3];
    sprintf(str, "P%d", playersMove);
    
    // Heller machen und herrausheben   
    attron(A_BOLD);
    // Die 1 bedeutet Spieler Farben verwenden
    Move(newField, str, playersMove, 1);
    attroff(A_BOLD);    
    Move(oldField, "  ", playersMove, 0);
}

/*
 * Spieler bewegen
 */
void Move(int Field, char *str, int playersMove, int c)
{
    // x y Verschiebung abhängig von der Spieler Nummer
    int x = 0, y = 0;
    if ((Field == 1) || (Field == 3) || (Field == 5) || (Field == 7) || ((Field >= 9) && (Field <= 15)) || (Field == 17) || (Field == 19) || (Field == 21) || (Field == 23) || ((Field >= 25) && (Field <= 31)))
    {
        if (playersMove == 2)
            x = 3;
        if (playersMove == 3)
            y = 1;
        if (playersMove == 4)
        {
            x = 3;
            y = 1;
        }
    }
    else if (Field == 8)
    {
        if (playersMove == 2)
            x = 3;
        if (playersMove == 3)
            y = 1;
        if (playersMove == 4)
        {
            x = 2;
            y = 1;
        }
    }
    else if (Field == -1)
    {
        if (playersMove == 2)
            x = 5;
        if (playersMove == 3)
            y = 2;
        if (playersMove == 4)
        {
            x = 5;
            y = 2;
        }
    }
    else
    {
        if (playersMove == 2)
            x = 13;
        if (playersMove == 3)
            y = 2;
        if (playersMove == 4)
        {
            x = 13;
            y = 2;
        }
    }

    if (Field == 0)
        move(37 + y, 1 + x);
    else if (Field == 1)
        move(33 + y, 4 + x);
    else if (Field == 2)
        move(29 + y, 1 + x);
    else if (Field == 3)
        move(25 + y, 4 + x);
    else if (Field == 4)
        move(21 + y, 1 + x);
    else if (Field == 5)
        move(17 + y, 4 + x);
    else if (Field == 6)
        move(13 + y, 1 + x);
    else if (Field == 7)
        move(9 + y, 4 + x);
    else if (Field == 8)
        move(4 + y, 1 + x);
    else if (Field == 9)
        move(4 + y, 18 + x);
    else if (Field == 10)
        move(4 + y, 26 + x);
    else if (Field == 11)
        move(4 + y, 34 + x);
    else if (Field == 12)
        move(4 + y, 42 + x);
    else if (Field == 13)
        move(4 + y, 50 + x);
    else if (Field == 14)
        move(4 + y, 58 + x);
    else if (Field == 15)
        move(4 + y, 66 + x);
    else if (Field == 16)
        move(5 + y, 73 + x);
    else if (Field == 17)
        move(9 + y, 76 + x);
    else if (Field == 18)
        move(13 + y, 73 + x);
    else if (Field == 19)
        move(17 + y, 76 + x);
    else if (Field == 20)
        move(21 + y, 73 + x);
    else if (Field == 21)
        move(25 + y, 76 + x);
    else if (Field == 22)
        move(29 + y, 73 + x);
    else if (Field == 23)
        move(33 + y, 76 + x);
    else if (Field == 24)
        move(37 + y, 73 + x);
    else if (Field == 25)
        move(40 + y, 66 + x);
    else if (Field == 26)
        move(40 + y, 58 + x);
    else if (Field == 27)
        move(40 + y, 50 + x);
    else if (Field == 28)
        move(40 + y, 42 + x);
    else if (Field == 29)
        move(40 + y, 34 + x);
    else if (Field == 30)
        move(40 + y, 26 + x);
    else if (Field == 31)
        move(40 + y, 18 + x);
    else if (Field == -1)
        move(7 + y, 8 + x);
    if(c == 0){
        if ((Field == 1) || (Field == 3))
        {
            attron(COLOR_PAIR(BG_WHITE));
            addstr(str);
            attroff(COLOR_PAIR(BG_WHITE));
        }
        else if ((Field == 5) || (Field == 7))
        {
            attron(COLOR_PAIR(BG_CYAN));
            addstr(str);
            attroff(COLOR_PAIR(BG_CYAN));
        }
        else if ((Field == 9) || (Field == 11) || (Field == 13) || (Field == 15))
        {
            attron(COLOR_PAIR(BG_MAGENTA));
            addstr(str);
            attroff(COLOR_PAIR(BG_MAGENTA));
        }
        else if ((Field == 17) || (Field == 19))
        {
            attron(COLOR_PAIR(BG_RED));
            addstr(str);
            attroff(COLOR_PAIR(BG_RED));
        }
        else if ((Field == 21) || (Field == 23))
        {
            attron(COLOR_PAIR(BG_YELLOW));
            addstr(str);
            attroff(COLOR_PAIR(BG_YELLOW));
        }
        else if ((Field == 29) || (Field == 31))
        {
            attron(COLOR_PAIR(BG_BLUE));
            addstr(str);
            attroff(COLOR_PAIR(BG_BLUE));
        }
        else if ((Field == 25) || (Field == 27))
        {
            attron(COLOR_PAIR(BG_GREEN));
            addstr(str);
            attroff(COLOR_PAIR(BG_GREEN));
        }
        else
        {
            addstr(str);
        }
    }
    else{
        attron(COLOR_PAIR(7 + playersMove)); 
        addstr(str);
        attroff(COLOR_PAIR(7 + playersMove)); 
    }
}

/*
 * Spieler Grundstücke und Häuser färben
 */
void displayPropertiesAndBuildings(property *properties)
{
    // Die + 7 um die richtige Spieler Farbe anzuzeigen. Zb.: die Farbe C_P1 von P1 hat den Wert 8 und P1 hat die owner Nummer 1 hat also 7 + 1 = C_P1
    if((properties + 0)->owner != 0) mvchgat(34, 12, 4, A_BOLD, ((properties + 0)->owner + 7), NULL);// LFA
    if((properties + 1)->owner != 0) mvchgat(26, 12, 4, A_BOLD, ((properties + 1)->owner + 7), NULL);// EVT
    if((properties + 2)->owner != 0) mvchgat(18, 12, 4, A_BOLD, ((properties + 2)->owner + 7), NULL);// DOD
    if((properties + 3)->owner != 0) mvchgat(10, 12, 4, A_BOLD, ((properties + 3)->owner + 7), NULL);// TNT
    if((properties + 4)->owner != 0) mvchgat(7, 19, 4, A_BOLD, ((properties + 4)->owner + 7), NULL);// ITSC
    if((properties + 5)->owner != 0) mvchgat(7, 35, 4, A_BOLD, ((properties + 5)->owner + 7), NULL);// TMDT
    if((properties + 6)->owner != 0) mvchgat(7, 51, 4, A_BOLD, ((properties + 6)->owner + 7), NULL);// LGOE
    if((properties + 7)->owner != 0) mvchgat(7, 67, 4, A_BOLD, ((properties + 7)->owner + 7), NULL);// LART
    if((properties + 8)->owner != 0) mvchgat(10, 84, 4, A_BOLD, ((properties + 8)->owner + 7), NULL);// EMT
    if((properties + 9)->owner != 0) mvchgat(18, 84, 4, A_BOLD, ((properties + 9)->owner + 7), NULL);// DMT
    if((properties + 10)->owner != 0) mvchgat(26, 84, 4, A_BOLD, ((properties + 10)->owner + 7), NULL);// EES
    if((properties + 11)->owner != 0) mvchgat(34, 84, 4, A_BOLD, ((properties + 11)->owner + 7), NULL);// EMA
    if((properties + 12)->owner != 0) mvchgat(43, 66, 5, A_BOLD, ((properties + 12)->owner + 7), NULL);// BSMK
    if((properties + 13)->owner != 0) mvchgat(43, 50, 5, A_BOLD, ((properties + 13)->owner + 7), NULL);// LFEB
    if((properties + 14)->owner != 0) mvchgat(43, 34, 5, A_BOLD, ((properties + 14)->owner + 7), NULL);// LPMSS
    if((properties + 15)->owner != 0) mvchgat(43, 18, 5, A_BOLD, ((properties + 15)->owner + 7), NULL);// EM
    
    // Bus/Bahn
    if((properties + 16)->owner != 0) mvchgat(23, 7, 4, A_BOLD, ((properties + 16)->owner + 7), NULL);// Bus haltestelle 1    
    if((properties + 17)->owner != 0) mvchgat(7, 43, 4, A_BOLD, ((properties + 17)->owner + 7), NULL);// Bahnhof 1    
    if((properties + 18)->owner != 0) mvchgat(23, 79, 4, A_BOLD, ((properties + 18)->owner + 7), NULL);// Bus haltestelle 2    
    if((properties + 19)->owner != 0) mvchgat(43, 43, 4, A_BOLD, ((properties + 19)->owner + 7), NULL);// Bahnhof 2
    
    // Häuser anzeigen
    for(int i = 0; i < N_PROP; i++){
        if((properties + i)->build > 0){
            char str[3][8] = {"Haus  ", "Häuser", "Hotel "};
            int c = 0;
            
            if((properties + i)->build == 1){
                c = 0;
            }
            if((properties + i)->build == 2){
                c = 1;
            }
            if((properties + i)->build == 3){
                c = 2;
            }
            move(45,0);
            
            if(i == 0) move(33,10);
            if(i == 1) move(25,10);
            if(i == 2) move(17,10);
            if(i == 3) move(9,10);
            if(i == 4) move(6,17);
            if(i == 5) move(6,33);
            if(i == 6) move(6,49);
            if(i == 7) move(6,65);
            if(i == 8) move(9,82);
            if(i == 9) move(17,82);
            if(i == 10) move(25,82);
            if(i == 11) move(33,82);
            if(i == 12) move(42,65);
            if(i == 13) move(42,49);
            if(i == 14) move(42,33);
            if(i == 15) move(42,17);
            
            attron(COLOR_PAIR((properties + i)->owner + 7));
            attron(A_BOLD);
            
            addstr(str[c]);
            
            attroff(A_BOLD);
            attroff(COLOR_PAIR((properties + i)->owner + 7));
        }
    }
    move(45,0);
}

/*
 * Spieler hat gewonnen
 */
void playerWon(player *players, int playersMove){
    int arr[3][35];
    char str[31];
    
    sprintf(str, "%s hat gewonnen !", (players + playersMove - 1)->name);
    
    rectangle(3, 35, arr);
    
    for (int i = 0; *(str + i) != '\0'; i++)
    {
        arr[1][2 + i] = *(str + i);
    }
    
    
    printRectangle(27, 21, 3, 35, arr);
    
    pressEnter();
    
    deleteRectangle(27, 21, 3, 35);
    move(45,0);
}

/*
 * Gezogene Ereignisskarte anzeigen
 */
void displayEventCard(char *str_1, char *str_2, char *str_3){
    int arr[8][25];
    char *str = "   Ereigniskarte:    ";
    rectangle(8, 25, arr);
    
    for (int i = 0; *(str + i) != '\0'; i++)
    {
        arr[1][2 + i] = *(str + i);
    }
    
    for (int i = 0; *(str_1 + i) != '\0'; i++)
    {
        arr[3][2 + i] = *(str_1 + i);
    }
    
    for (int i = 0; *(str_2 + i) != '\0'; i++)
    {
        arr[4][2 + i] = *(str_2 + i);
    }
    
    for (int i = 0; *(str_3 + i) != '\0'; i++)
    {
        arr[6][2 + i] = *(str_3 + i);
    }
    
    printRectangle(30, 18, 8, 25, arr);
    
    pressEnter();
    
    deleteRectangle(30, 18, 8, 25);
    
    move(45,0);
}