#include "input.h"
#include "game.h"
#include "field.h"
#include <stdlib.h>
#include <time.h>

/*
 * Spiel, PlayersMove bestimmt welcher Spieler gerade am Zug ist (beginnt mit Spieler 1 als Wert 0)
 * *players ist ein pointer auf ein Array der Struktur player
 */
void game(int playerNumber, player *players, int playersMove, int newTurn, property *properties)
{
    // Damit die Würfel Werte nicht immer die gleichen sind
    srand(time(NULL));

    int diceA, diceB;
    pressEnter();

    // damit zu beginn alle Spieler auf dem Los-Feld angezeigt werden
    for (int i = 1; i <= playerNumber; i++)
    {
        char str[3];
        sprintf(str, "P%d", i);
        attron(A_BOLD);
        Move((players + i - 1)->position, str, i, 1);
        attroff(A_BOLD);
    }
    displayPropertiesAndBuildings(properties);
    
    while (true)
    {
        
        
        // Herrausfinden ob jemand gewonnen hat
        int remainingPlayers = playerNumber;
        for(int k = 0; k < playerNumber; k++){
            if((players + k)->money < 0)
                remainingPlayers--;
        }
        if(remainingPlayers <= 1){
            updatePlayerStatus(playerNumber, players, playersMove);
            int w = 0;
            while(true){
                if((players + w)->money > 0){ 
                    playerWon(players, w + 1);
                    break;
                }
            }
        }
        
        // Neuer Zug
        if((newTurn == true) && ((players + playersMove - 1)->money >= 0))
        {
            updatePlayerStatus(playerNumber, players, playersMove);
            
            //Würfeln
            diceA = rollDice();
            diceB = rollDice();
            displayDice(diceA, diceB);
            
            int oldField;
            
            //Wenn in Mensa, dann verlassen
            if(fieldTyp(players, playersMove) == 7){
                (players + playersMove - 1)->position = 8;
                oldField = -1;
            }
            else{
                oldField = (players + playersMove - 1)->position;            
            }

            (players + playersMove - 1)->position += (diceA + diceB);
            
            // Gehe in die Mensa
            if(fieldTyp(players, playersMove) == 6){
                (players + playersMove - 1)->position = -1;
            }
            else{
                // Wenn das Los Feld überschritten wurde
                if ((players + playersMove - 1)->position >= GAME_FIELDS)
                {
                    (players + playersMove - 1)->position -= GAME_FIELDS;

                    // Geld für das überscheiten des Start Feldes
                    (players + playersMove - 1)->money += ROUND_MONEY;
                }
            }
            
            movePlayer(oldField, (players + playersMove - 1)->position, playersMove);
            
            oldField = (players + playersMove - 1)->position;
            
            if(fieldTyp(players, playersMove) == 2){// Zahl Felder
                if ((players + playersMove - 1)->position == 2)
                    (players + playersMove - 1)->money -= 60;
                if ((players + playersMove - 1)->position == 10)
                    (players + playersMove - 1)->money -= 40;
                if ((players + playersMove - 1)->position == 22)
                    (players + playersMove - 1)->money -= 40;
                if ((players + playersMove - 1)->position == 30)
                    (players + playersMove - 1)->money -= 30;
            }
            else if (fieldTyp(players, playersMove) == 4){// EreignissFelder
                drawEventCard(playerNumber, players, playersMove, properties);
            }
            else if((fieldTyp(players, playersMove) == 1) || (fieldTyp(players, playersMove) == 3)){// Miete bezahlen
                payRent(players, playersMove, properties);
            }
            
            if(oldField != (players + playersMove - 1)->position)
                movePlayer(oldField, (players + playersMove - 1)->position, playersMove);
        }
        
        
        if((players + playersMove - 1)->money >= 0){// Wenn Spieler noch nicht pleite ist
            updatePlayerStatus(playerNumber, players, playersMove);
            int c = gameMenu(players, playersMove, properties);

            if (c == 0)
            { // Kaufen
                buyProperty(players, playersMove, properties);

                displayPropertiesAndBuildings(properties);

                newTurn = false;
            }
            else if (c == 1)
            { // Bauen
                buildHouseOrHotel(players, playersMove, properties);

                displayPropertiesAndBuildings(properties);

                newTurn = false;
            }
            else if (c == 2)
            { // Zug beenden

                newTurn = true;
                playersMove++;

                // Wenn letzter Spieler Zug gemacht hat kommt der erste wieder dran
                if (playersMove > playerNumber)
                    playersMove = 1;
            }
            else if (c == 3)
            { // Speichern
                //+++++
                saveGame(playerNumber, players, playersMove, properties);
                newTurn = false;
            }
            else
            { // Verlassen
                break;
            }
        }
        else{// Wenn Spieler pleite
            // Spieler von Spielfeld entfernen
            Move((players + playersMove - 1)->position, "  ", playersMove, 0); 
            
            newTurn = true;
            playersMove++;
           
            // Wenn letzter Spieler Zug gemacht hat kommt der erste wieder dran
            if (playersMove > playerNumber)
                playersMove = 1;
        }
    }
    
    // Um am Ende das Spielfeld wieder herzustellen wenn man auf Spiel Verlassen geht oder jemand gewonnen hat
    int outputBuffer[FIELD_HEIGHT][FIELD_WIDTH];
    
    move(0,0);
    initBuffer(outputBuffer);
    printBuffer(outputBuffer);
    refresh();
}

/*
 * Neues Spiel erstellen
 */
void createNewGame(int playerNumber)
{

    player *players = (player *)calloc(playerNumber, sizeof(player));

    for (int i = 0; i < playerNumber; i++)
    {
        (players + i)->name = playerNameMenu(i, players);
        (players + i)->position = 0;
        (players + i)->money = START_MONEY;
    }

    property *properties = createProperties();
    game(playerNumber, players, 1, true, properties);
}

/*
 * Spiel Speichern
 */
void saveGame(int playerNumber, player *players, int playersMove, property *properties){
    FILE *fpt;
    
    fpt = fopen("SaveGame.txt", "w");

    
    fprintf(fpt,  "%d %d\n", playerNumber, playersMove);
    
    int n1, n2, n3, n4, n5, n6;
    
    for(int i = 0; i < playerNumber; i++){
        char *str = (players + i)->name;
        n1 = (players + i)->position;
        n2 = (players + i)->money;
        fprintf(fpt, "%d %d %s\n", n1, n2, str);    
    }
    
    for(int i = 0; i < 20; i++){
        char *str = (properties + i)->name; 
        n1  = (properties + i)->owner; 
        n2 = (properties + i)->number; 
        n3 = (properties + i)->fieldNumber; 
        n4 = (properties + i)->price;
        n5 = (properties + i)->build;
        n6 = (properties + i)->color;
        fprintf(fpt, "%d %d %d %d %d %d %s\n", n1, n2, n3, n4, n5, n6, str);        
    }
    
    fclose(fpt);
}

/*
 * Spieler laden
 */
void loadPlayers(char arr[50], int i, player *players){
    char *name = calloc(20, sizeof(char));
    int *numbers = calloc(2, sizeof(int));

    sscanf(arr, "%d %d %s\n", (numbers+0), (numbers+1), name);
    
    (players + i)->position = *(numbers+0);
    (players + i)->money = *(numbers+1);
    (players + i)->name = name;
}

/*
 * Grundstücke laden
 */
void loadProperties(char arr[50], int i, property *properties){
    char *name = calloc(20, sizeof(char));
    int *numbers = calloc(6, sizeof(int));

    sscanf(arr, "%d %d %d %d %d %d %s\n", (numbers+0), (numbers+1), (numbers+2), (numbers+3), (numbers+4), (numbers+5), name);
    
    (properties + i)->owner = *(numbers+0);
    (properties + i)->number = *(numbers+1);
    (properties + i)->fieldNumber = *(numbers+2);
    (properties + i)->price = *(numbers+3);
    (properties + i)->build = *(numbers+4);
    (properties + i)->color = *(numbers+5);
    (properties + i)->name = name;
}

/*
 * Spiel laden
 */
void loadGame(){
    FILE *fpt;
    
    fpt = fopen("SaveGame.txt", "r");
    
    int playerNumber, playersMove;
    char arrd[50];
    fgets(arrd, 50, fpt);
    sscanf(arrd, "%d %d\n", &playerNumber, &playersMove);
    
    player *players = calloc(playerNumber, sizeof(player));
    for(int i = 0; i < playerNumber; i++){
        char arr[50];
        fgets(arr, 50, fpt);
        loadPlayers(arr, i, players);
    }

    property *properties = calloc(20, sizeof(property));
    for(int i = 0; i < 20; i++){
        char arr[50];
        fgets(arr, 50, fpt);
        loadProperties(arr, i, properties);
    }
    
    fclose(fpt);
    
    game(playerNumber, players, playersMove, false, properties);
}

/*
 * Würfeln
 */
int rollDice()
{
    int diceValue = (rand() % 6) + 1;
    return diceValue;
}

/*
 * gibt den Feld typ zurück
 * 0 = Los, 1 = Grundstück, 2 = Zahlfeld, 3 = Bus/bahn, 4 = Ereignisskarte, 
 * 5 = unwichtig(Nicht zum Essen, Semesterferien), 6 = Gehe in die Mensa, 7 = Mensa
 */
int fieldTyp(player *players, int playersMove){
    int position = (players + playersMove -1)->position;
    int field;
    
    if(position == 0) field = 0;// LOS
    if(position == 1) field = 1;// LFA
    if(position == 2) field = 2;// Semesterbeitrag
    if(position == 3) field = 1;// EVT
    if(position == 4) field = 3;// Bushaltestelle
    if(position == 5) field = 1;// DOD
    if(position == 6) field = 4;// Ereignisskarte
    if(position == 7) field = 1;// TNT
    if(position == 8) field = 5;// Nicht zum Essen
    if(position == 9) field = 1;// ITSC
    if(position == 10) field = 2;// Bibliothek
    if(position == 11) field = 1;// TMDT
    if(position == 12) field = 3;// Bahnhof
    if(position == 13) field = 1;// LGOE
    if(position == 14) field = 4;// Ereignisskarte
    if(position == 15) field = 1;// LART
    if(position == 16) field = 5;// Semesterferien
    if(position == 17) field = 1;// EMT
    if(position == 18) field = 4;// Ereignisskarte
    if(position == 19) field = 1;// DMT
    if(position == 20) field = 3;// Bushaltestelle
    if(position == 21) field = 1;// EES
    if(position == 22) field = 2;// Photovoltaik
    if(position == 23) field = 1;// EMA
    if(position == 24) field = 6;// Gehe in die Mensa
    if(position == 25) field = 1;// BSMK
    if(position == 26) field = 4;// Ereignisskarte
    if(position == 27) field = 1;// LFEB
    if(position == 28) field = 3;// Bahnhof
    if(position == 29) field = 1;// LPMSS
    if(position == 30) field = 2;// Eis essen
    if(position == 31) field = 1;// EM
    if(position == -1) field = 7;// MENSA
    
    return field;
}

/*
 * Grundstücke durchsuchen bis das gefunden wurde auf dem der Spieler steht
 */
int searchProperty(player *players, int playersMove, property *properties){
    int i = 0;
    
    while(true){
        if((properties + i)->fieldNumber == (players + playersMove - 1)->position)
            break;        

        i++;
    }

    return i;
}

/*
 * Überprüfung ob man alle Grundstücke einer Farbe besitzt und dadurch bauen kann
 * b = false, Spieler besitzt nicht alle Grundstücke der gleichen Farbe oder Bus/Bahn
 * b = true, Spieler besitzt alle Grundstücke der gleichen Farbe kann also bauen
 */
int checkColorForBuildability(player *players, int playersMove, property *properties){
    int b = false; 
    
    // Bestimmt die Farbe auf dem Grundstück auf dem der Spieler steht
    int color = (properties + searchProperty(players, playersMove, properties))->color;

    
    if(color == -1){// Bus/Bahn
        b = false;
    }
    else{// Ermittle ob der Spieler alle Grundstücke der Farbe hat
        int count = 0;
        for(int i = 0; i < N_PROP; i++){
            if(((properties + i)->color == color) && ((properties + i)->owner == playersMove))
                count++;
        }
        
        if((color != 2) && (count == 2)) b = true;
        else if((color == 2) && (count == 4)) b = true;
        else b = false;
    }

    return b;
}

/*
 * Grundstücks Preis und besitzer überprüfen
 * 0 = genügend Geld für den kauf & niemand hat das Grundstück,
 * 1 = ist bereits der Besitzer und hat genügend Geld zum bauen und kann noch bauen und besitzt alle Grundstücke derselben Farbe,
 * 2 = ist der Besitzter aber hat nicht genügend Geld zum bauen oder hat bereits Hotel oder nicht alle Grundstücke der Farbe (oder Bus/bahn),
 * 3 = Ein anderer Spieler ist der Besitzer,
 * 4 = Spieler hat nicht genügend Geld zum kauf
 */
int checkPropertyPriceAndOwner(player *players, int playersMove, property *properties){
    int i = searchProperty(players, playersMove, properties);
    int b;
        
    // Der Spieler hat genügend Geld & niemand hat das Grundstück    
    if(((properties + i)->price <= (players + playersMove - 1)->money) 
            && ((properties + i)->owner == 0))
        b = 0;
    // Spieler ist bereits der Besitzer und hat genügend Geld zum bauen und kann noch bauen und hat alle Grundstücke derselben Farbe (kein Bus/bahn)
    else if((((properties + i)->owner == playersMove)
            && ((properties + i)->price <= (players + playersMove - 1)->money)
            && ((properties + i)->build) < 3)
            && (fieldTyp(players, playersMove) == 1)
            && (checkColorForBuildability(players, playersMove, properties) == true))
        b = 1;
    // Spieler ist der Besitzter aber hat nicht genügend Geld zum bauen oder hat bereits Hotel oder nicht alle Grundstücke der Farbe (oder Bus/bahn)
    else if(((properties + i)->owner == playersMove)
            && (((properties + i)->price) > ((players + playersMove - 1)->money)
                || ((properties + i)->build == 3)
                || (fieldTyp(players, playersMove) == 3)
                || (checkColorForBuildability(players, playersMove, properties) == false)))
        b = 2;
    // Ein anderer Spieler ist bereits der Besitzer des Grundstücks
    else if((properties + i)->owner != playersMove)
        b = 3;
    // Der Spieler hat nicht genügend Geld zum kauf
    else if((properties + i)->price > (players + playersMove - 1)->money)
        b = 4;
    
    return b;
}

/*
 * Grundstücke kaufen
 */
void buyProperty(player *players, int playersMove, property *properties){
    int i = searchProperty(players, playersMove, properties);
        
    // Besitzer des Grundstücks festlegen und den Preis von seinem Geld abziehen
    (players + playersMove - 1)->money -= (properties + i)->price;    
    (properties + i)->owner = playersMove;
}

/*
 * Haus oder Hotel auf Grundstück bauen
 */
void buildHouseOrHotel(player *players, int playersMove, property *properties){
    int i = searchProperty(players, playersMove, properties);
    
    // Haus oder Hotel bauen und vom Geld des Spielers abziehen
    (players + playersMove - 1)->money -= (properties + i)->price;    
    (properties + i)->build += 1;
}

/*
 * Miete an Spieler zahlen
 */
void payRent(player *players, int playersMove, property *properties){
    // Wenn Fremdes Grundstück
    if(checkPropertyPriceAndOwner(players, playersMove, properties) == 3){
        int i = searchProperty(players, playersMove, properties);
        int fieldOwner = (properties + i)->owner;
        
        if((players + fieldOwner -1)->money >= 0){// Miete wird nicht an bereits pleite Spieler gezahlt
            int change = 0;

            if(fieldTyp(players, playersMove) == 1){// Für normale Grunstücke
                change = ((properties + i)->price + (((properties + i)->price * (properties + i)->build) / 2));

                // Geld vom Mieter abziehen
                (players + playersMove - 1)->money -= change;

                // Geld an Vermieter zahlen
                if((players + playersMove - 1)->money < 0){
                    (players + fieldOwner -1)->money += (change -(players + playersMove - 1)->money);
                }
                else{
                    (players + fieldOwner -1)->money += change;
                }
            }
            else{// für Bus/Bahn

                // Zu zahlender Betrag ist bei Bus/Bahn abhängig davon wie viele ein Spieler an dieser Art von Grundstücken besitzt
                int count = -1;
                for(int k = 16; k < N_PROP; k++){
                    int checkOwner = (properties + k)->owner;
                    if(fieldOwner == checkOwner)
                        count++;
                }

                change = ((properties + i)->price + (((properties + i)->price * count) / 2));

                // Geld vom Mieter abziehen
                (players + playersMove - 1)->money -= change;

                // Geld an Vermieter zahlen
                if((players + playersMove - 1)->money < 0){
                    (players + fieldOwner -1)->money += (change -(players + playersMove - 1)->money);
                }
                else{
                    (players + fieldOwner -1)->money += change;
                }
            }
        }
    }
}

/*
 * Grundstücke
 */
property *createProperties()
{
    property *properties = (property *)calloc(N_PROP, sizeof(property));

    // LFA
    (properties + 0)->name = "LFA";
    (properties + 0)->number = 0;
    (properties + 0)->fieldNumber = 1;
    (properties + 0)->price = 15;
    (properties + 0)->color = 0;
    // EVT
    (properties + 1)->name = "EVT";
    (properties + 1)->number = 1;
    (properties + 1)->fieldNumber = 3;
    (properties + 1)->price = 15;
    (properties + 1)->color = 0;
    // DOD
    (properties + 2)->name = "DOD";
    (properties + 2)->number = 2;
    (properties + 2)->fieldNumber = 5;
    (properties + 2)->price = 30;
    (properties + 2)->color = 1;
    // TNT
    (properties + 3)->name = "TNT";
    (properties + 3)->number = 3;
    (properties + 3)->fieldNumber = 7;
    (properties + 3)->price = 30;
    (properties + 3)->color = 1;
    // ITSC
    (properties + 4)->name = "ITSC";
    (properties + 4)->number = 4;
    (properties + 4)->fieldNumber = 9;
    (properties + 4)->price = 40;
    (properties + 4)->color = 2;
    // TMDT
    (properties + 5)->name = "TMDT";
    (properties + 5)->number = 5;
    (properties + 5)->fieldNumber = 11;
    (properties + 5)->price = 40;
    (properties + 5)->color = 2;
    // LGOE
    (properties + 6)->name = "LGOE";
    (properties + 6)->number = 6;
    (properties + 6)->fieldNumber = 13;
    (properties + 6)->price = 60;
    (properties + 6)->color = 2;
    // LART
    (properties + 7)->name = "LART";
    (properties + 7)->number = 7;
    (properties + 7)->fieldNumber = 15;
    (properties + 7)->price = 60;
    (properties + 7)->color = 2;
    // EMT
    (properties + 8)->name = "EMT";
    (properties + 8)->number = 8;
    (properties + 8)->fieldNumber = 17;
    (properties + 8)->price = 75;
    (properties + 8)->color = 3;
    // DMT
    (properties + 9)->name = "DMT";
    (properties + 9)->number = 9;
    (properties + 9)->fieldNumber = 19;
    (properties + 9)->price = 75;
    (properties + 9)->color = 3;
    // EES
    (properties + 10)->name = "EES";
    (properties + 10)->number = 10;
    (properties + 10)->fieldNumber = 21;
    (properties + 10)->price = 90;
    (properties + 10)->color = 4;
    // EMA
    (properties + 11)->name = "EMA";
    (properties + 11)->number = 11;
    (properties + 11)->fieldNumber = 23;
    (properties + 11)->price = 90;
    (properties + 11)->color = 4;
    // BSMK
    (properties + 12)->name = "BSMK";
    (properties + 12)->number = 12;
    (properties + 12)->fieldNumber = 25;
    (properties + 12)->price = 105;
    (properties + 12)->color = 5;
    // LFEB
    (properties + 13)->name = "LFEB";
    (properties + 13)->number = 13;
    (properties + 13)->fieldNumber = 27;
    (properties + 13)->price = 105;
    (properties + 13)->color = 5;
    // LPMSS
    (properties + 14)->name = "LPMSS";
    (properties + 14)->number = 14;
    (properties + 14)->fieldNumber = 29;
    (properties + 14)->price = 120;
    (properties + 14)->color = 6;
    // EM
    (properties + 15)->name = "EM";
    (properties + 15)->number = 15;
    (properties + 15)->fieldNumber = 31;
    (properties + 15)->price = 120;
    (properties + 15)->color = 6;
    //Bushaltestelle
    (properties + 16)->name = "Bushaltestelle";
    (properties + 16)->number = 16;
    (properties + 16)->fieldNumber = 4;
    (properties + 16)->price = 60;
    (properties + 16)->color = -1;
    //Bahnhof
    (properties + 17)->name = "Bahnhof";
    (properties + 17)->number = 17;
    (properties + 17)->fieldNumber = 12;
    (properties + 17)->price = 60;
    (properties + 17)->color = -1;
    //Bushaltestelle 2
    (properties + 18)->name = "Bushaltestelle 2";
    (properties + 18)->number = 18;
    (properties + 18)->fieldNumber = 20;
    (properties + 18)->price = 60;
    (properties + 18)->color = -1;
    //Bahnhof 2
    (properties + 19)->name = "Bahnhof 2";
    (properties + 19)->number = 19;
    (properties + 19)->fieldNumber = 28;
    (properties + 19)->price = 60;
    (properties + 19)->color = -1;
    
    return properties;
}

/*
 * Ereignisskarten
 */
void drawEventCard(int playerNumber, player *players, int playersMove, property *properties)
{
    int roll = ((rand() % (12 - 1 + 1)) + 1);

    if(roll == 1){
        displayEventCard("    Ruecke vor bis   ", "      auf Los        ", "   ziehe 60.- ein    ");
        (players + playersMove - 1)->money += 60;
        (players + playersMove - 1)->position = 0;
    }
    else if(roll == 2){
        displayEventCard(" Du hast Geburtstag  ", " erhalte von jedem   ", "         30.-        ");
        for(int i = 0; i < playerNumber; i++){
            if(i != (playersMove -1)){
                (players + playersMove - 1)->money += 30;
                (players + i)->money -= 30;
            }
        }
    }
    else if(roll == 3){
        displayEventCard("     Strafzettel !   ", "        Zahle        ", "         15.-        ");
        (players + playersMove - 1)->money -= 15;
    }
    else if(roll == 4){
        displayEventCard("     Gehe in die     ", "        Mensa        ", "                     ");
        (players + playersMove - 1)->position = -1;
    }
    else if(roll == 5){
        displayEventCard("   Bank-Irrtum zu    ", "   deinen Gunsten    ", "   ziehe 200.- ein   ");
        (players + playersMove - 1)->money += 200;
    }    
    else if(roll == 6){
        displayEventCard("Gehe zu einem blauen ", "  Feld ist es frei   ", "bekommst du es gratis");
        int tmp = ((rand() % (2 - 1 + 1)) + 1);
        
        if(tmp == 1){
            (players + playersMove - 1)->position = 29;
            if((properties + 14)->owner == 0)
                (properties + 14)->owner = playersMove;
            else
                payRent(players, playersMove, properties);
        }    
        else{
            (players + playersMove - 1)->position = 31;
            if((properties + 15)->owner == 0)
                (properties + 15)->owner = playersMove;
            else
                payRent(players, playersMove, properties);
        }
        displayPropertiesAndBuildings(properties);
    }    
    else if(roll == 7){
        displayEventCard(" Gehe zu einem roten ", "  Feld ist es frei   ", "bekommst du es gratis");
        int tmp = ((rand() % (2 - 1 + 1)) + 1);
        
        if(tmp == 1){
            (players + playersMove - 1)->position = 17;
            if((properties + 8)->owner == 0)
                (properties + 8)->owner = playersMove;
            else
                payRent(players, playersMove, properties);
        }    
        else{
            (players + playersMove - 1)->position = 19;
            if((properties + 9)->owner == 0)
                (properties + 9)->owner = playersMove;
            else
                payRent(players, playersMove, properties);
        }
        displayPropertiesAndBuildings(properties);
    }    
    else if(roll == 8){
        displayEventCard("Gehe zu einem gruenen", "  Feld ist es frei   ", "bekommst du es gratis");
        int tmp = ((rand() % (2 - 1 + 1)) + 1);
        
        if(tmp == 1){
            (players + playersMove - 1)->position = 25;
            if((properties + 12)->owner == 0)
                (properties + 12)->owner = playersMove;
            else
                payRent(players, playersMove, properties);
        }    
        else{
            (players + playersMove - 1)->position = 27;
            if((properties + 13)->owner == 0)
                (properties + 13)->owner = playersMove;
            else
                payRent(players, playersMove, properties);
        }
        displayPropertiesAndBuildings(properties);
    }    
    else if(roll == 9){
        displayEventCard("   Du hast auf die   ", "   richtigen Aktien  ", "gesetzt -> 7% Gewinnn");
        int tmp = (players + playersMove - 1)->money;
        (players + playersMove - 1)->money = (tmp * 1.07);
    }    
    else if(roll == 10){
        displayEventCard("   Du kaufst einen   ", "   neuen Computer    ", "     zahle 90.-      ");
        (players + playersMove - 1)->money -= 90;
    }    
    else if(roll == 11){
        displayEventCard("   Ruecke vor bis    ", "    zum naechsten    ", "       Bahnhof       ");
        if((players + playersMove - 1)->position <= 11)
            (players + playersMove - 1)->position = 12;
            
        else
            (players + playersMove - 1)->position = 28;
        
        payRent(players, playersMove, properties);
    }    
    else{
        displayEventCard("   Ruecke vor bis    ", "    zumr naechsten   ", "    Bushaltestelle   ");
        if((players + playersMove - 1)->position <= 3)
            (players + playersMove - 1)->position = 4;
            
        else
            (players + playersMove - 1)->position = 20;
        
        payRent(players, playersMove, properties);
    }    
}
