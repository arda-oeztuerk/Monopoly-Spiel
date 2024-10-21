#include "field.h"

/*
 * Hilfsfunktion zum Definieren der Farb-Paare von ncurses
 */
void initColor(){
    init_pair(BG_BLACK, COLOR_WHITE, COLOR_BLACK);
    init_pair(BG_RED, COLOR_WHITE, COLOR_RED);
    init_pair(BG_GREEN, COLOR_WHITE, COLOR_GREEN);
    init_pair(BG_YELLOW, COLOR_BLACK, COLOR_YELLOW);
    init_pair(BG_BLUE, COLOR_WHITE, COLOR_BLUE);
    init_pair(BG_MAGENTA, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(BG_CYAN, COLOR_WHITE, COLOR_CYAN);
    init_pair(BG_WHITE, COLOR_BLACK, COLOR_WHITE);
    init_pair(C_P1, COLOR_GREEN, COLOR_BLACK);
    init_pair(C_P2, COLOR_BLUE, COLOR_BLACK);
    init_pair(C_P3, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(C_P4, COLOR_RED, COLOR_BLACK);
}

/*
 * Initialisierung des Spielfeldes mit allen Linien, Texten und Beträgen
 */
void initBuffer(int outputBuffer[][FIELD_WIDTH]){
    // -------------------------------------------------------------------
    // Füllen des Basis-Feldes mit Leerzeichen und Zeilenumbrüchen am Ende
    // -------------------------------------------------------------------
    for(int i = 0; i < FIELD_HEIGHT; i++){
        for(int j = 0; j < FIELD_WIDTH; j++){
            if(j == FIELD_WIDTH - 1){
                outputBuffer[i][j] = '\n';
            }else{
                outputBuffer[i][j] = ' ';
            }
        }
    }
    
    // ----------------------------
    // Texte und Beträge hinzufügen
    // ----------------------------
    {
        writeToBuffer(outputBuffer, "LOS", 38, 6, 0);
        writeToBuffer(outputBuffer, "Erhalte  60.-", 43, 2, 0);

        writeToBuffer(outputBuffer, "LFA", 33, 2, 1);
        writeToBuffer(outputBuffer, "15.-", 34, 12, 0);

        writeToBuffer(outputBuffer, "Semester-", 29, 4, 0);
        writeToBuffer(outputBuffer, "beitrag", 30, 5, 0);
        writeToBuffer(outputBuffer, "60.-", 31, 7, 0);

        writeToBuffer(outputBuffer, "EVT", 25, 2, 1);
        writeToBuffer(outputBuffer, "15.-", 26, 12, 0);

        writeToBuffer(outputBuffer, "Bus-", 21, 6, 0);
        writeToBuffer(outputBuffer, "haltestelle", 22, 3, 0);
        writeToBuffer(outputBuffer, "60.-", 23, 7, 0);

        writeToBuffer(outputBuffer, "DOD", 17, 2, 1);
        writeToBuffer(outputBuffer, "30.-", 18, 12, 0);

        writeToBuffer(outputBuffer, "Ereignis-", 13, 4, 0);
        writeToBuffer(outputBuffer, "karte", 15, 6, 0);

        writeToBuffer(outputBuffer, "TNT", 9, 2, 1);
        writeToBuffer(outputBuffer, "30.-", 10, 12, 0);

        writeToBuffer(outputBuffer, "Nicht zum", 1, 4, 0);
        writeToBuffer(outputBuffer, "Essen", 2, 6, 0);
        writeToBuffer(outputBuffer, "MENSA", 6, 9, 0);

        writeToBuffer(outputBuffer, "ITSC", 2, 18, 0);
        writeToBuffer(outputBuffer, "40.-", 7, 19, 0);

        writeToBuffer(outputBuffer, "Biblio-", 2, 25, 0);
        writeToBuffer(outputBuffer, "thek", 3, 26, 0);
        writeToBuffer(outputBuffer, "40.-", 7, 27, 0);

        writeToBuffer(outputBuffer, "TMDT", 2, 34, 0);
        writeToBuffer(outputBuffer, "40.-", 7, 35, 0);

        writeToBuffer(outputBuffer, "Bahn-", 2, 42, 0);
        writeToBuffer(outputBuffer, "hof", 3, 43, 0);
        writeToBuffer(outputBuffer, "60.-", 7, 43, 0);

        writeToBuffer(outputBuffer, "LGOE", 2, 50, 0);
        writeToBuffer(outputBuffer, "60.-", 7, 51, 0);

        writeToBuffer(outputBuffer, "Ereig", 2, 58, 0);
        writeToBuffer(outputBuffer, "nis-", 3, 59, 0);
        writeToBuffer(outputBuffer, "karte", 6, 58, 0);

        writeToBuffer(outputBuffer, "LART", 2, 66, 0);
        writeToBuffer(outputBuffer, "60.-", 7, 67, 0);

        writeToBuffer(outputBuffer, "Semester-", 2, 76, 0);
        writeToBuffer(outputBuffer, "ferien", 4, 77, 0);

        writeToBuffer(outputBuffer, "EMT", 9, 74, 1);
        writeToBuffer(outputBuffer, "75.-", 10, 84, 0);

        writeToBuffer(outputBuffer, "Ereignis-", 13, 76, 0);
        writeToBuffer(outputBuffer, "karte", 15, 78, 0);

        writeToBuffer(outputBuffer, "DMT", 17, 74, 1);
        writeToBuffer(outputBuffer, "75.-", 18, 84, 0);

        writeToBuffer(outputBuffer, "Bus-", 21, 78, 0);
        writeToBuffer(outputBuffer, "haltestelle", 22, 75, 0);
        writeToBuffer(outputBuffer, "60.-", 23, 79, 0);

        writeToBuffer(outputBuffer, "EES", 25, 74, 1);
        writeToBuffer(outputBuffer, "90.-", 26, 84, 0);

        writeToBuffer(outputBuffer, "Photovoltaik", 30, 75, 0);
        writeToBuffer(outputBuffer, "40.-", 31, 79, 0);

        writeToBuffer(outputBuffer, "EMA", 33, 74, 1);
        writeToBuffer(outputBuffer, "90.-", 34, 84, 0);

        writeToBuffer(outputBuffer, "Gehe in die", 38, 75, 0);
        writeToBuffer(outputBuffer, "MENSA", 41, 78, 0);

        writeToBuffer(outputBuffer, "BSMK", 38, 66, 0);
        writeToBuffer(outputBuffer, "105.-", 43, 66, 0);

        writeToBuffer(outputBuffer, "Ereig", 38, 58, 0);
        writeToBuffer(outputBuffer, "nis-", 39, 59, 0);
        writeToBuffer(outputBuffer, "karte", 42, 58, 0);

        writeToBuffer(outputBuffer, "LFEB", 38, 50, 0);
        writeToBuffer(outputBuffer, "105.-", 43, 50, 0);

        writeToBuffer(outputBuffer, "Bahn-", 38, 42, 0);
        writeToBuffer(outputBuffer, "hof", 39, 43, 0);
        writeToBuffer(outputBuffer, "60.-", 43, 43, 0);

        writeToBuffer(outputBuffer, "LPMSS", 38, 34, 0);
        writeToBuffer(outputBuffer, "120.-", 43, 34, 0);

        writeToBuffer(outputBuffer, "Eis-", 38, 26, 0);
        writeToBuffer(outputBuffer, "essen", 39, 26, 0);
        writeToBuffer(outputBuffer, "30.-", 43, 27, 0);

        writeToBuffer(outputBuffer, "EM", 38, 19, 0);
        writeToBuffer(outputBuffer, "120.-", 43, 18, 0);
    }
    
    // ---------------------
    // Hinzufügen der Linien
    // ---------------------
    // Ecke links oben
    outputBuffer[0][0] = ACS_ULCORNER;
    
    // Eine horizontale Linie
    for(int i = 1; i < FIELD_WIDTH - 2; i++){
        if(i % 8 == 0 && i != 8 && i != 80){
            outputBuffer[0][i] = ACS_TTEE;
        }else{
            outputBuffer[0][i] = ACS_HLINE;
        }
    }
    
    // Ecke rechts oben
    outputBuffer[0][FIELD_WIDTH - 2] = ACS_URCORNER;
    
    for(int i = 1; i < FIELD_HEIGHT - 1; i++){
        for(int j = 0; j < FIELD_WIDTH - 1; j++){
            if((j == 16 || j == 72) && (i == 8 || i == 36)){
                outputBuffer[i][j] = ACS_PLUS;
            }else if(j == 0 || j == FIELD_WIDTH - 2){
                if(i % 4 == 0 && i != 4 && i != 40){
                    if(j == 0){
                        outputBuffer[i][j] = ACS_LTEE;
                    }else{
                        outputBuffer[i][j] = ACS_RTEE;
                    }
                }else{
                    outputBuffer[i][j] = ACS_VLINE;
                }
            }else if(j == 16 || j == 72){
                if(i % 4 == 0 && i > 8 && i < 36){
                    outputBuffer[i][j] = (j == 16) ? ACS_RTEE : ACS_LTEE;
                }else{
                    outputBuffer[i][j] = ACS_VLINE;
                }
            }else if(i == 8 || i == 36){
                if(j % 8 == 0 && j > 16 && j < 72){
                    outputBuffer[i][j] = (i == 8) ? ACS_BTEE : ACS_TTEE;
                }else{
                    outputBuffer[i][j] = ACS_HLINE;
                }
            }else if(j % 8 == 0 && j > 16 && j < 72 && (i < 8 || i > 36)){
                outputBuffer[i][j] = ACS_VLINE;
            }else if(i % 4 == 0 && i > 8 && i < 36 && (j < 16 || j > 72)){
                outputBuffer[i][j] = ACS_HLINE;
            }
        }
    }
    
    // Ecke links unten
    outputBuffer[FIELD_HEIGHT - 1][0] = ACS_LLCORNER;
    
    // Eine horizontale Linie
    for(int i = 1; i < FIELD_WIDTH - 2; i++){
        if(i % 8 == 0 && i != 8 && i != 80){
            outputBuffer[FIELD_HEIGHT - 1][i] = ACS_BTEE;
        }else{
            outputBuffer[FIELD_HEIGHT - 1][i] = ACS_HLINE;
        }
    }
    
    // Ecke rechts unten
    outputBuffer[FIELD_HEIGHT - 1][FIELD_WIDTH - 2] = ACS_LRCORNER;
    
    // ----------------------------
    // Einzeichnen der Mensa-Linien
    // ----------------------------
    outputBuffer[4][16] = ACS_RTEE;
    
    for(int i = 7; i < 16; i++){
        outputBuffer[4][i] = ACS_HLINE;
    }
    
    outputBuffer[4][6] = ACS_ULCORNER;
    
    for(int i = 5; i < 8; i++){
        outputBuffer[i][6] = ACS_VLINE;
    }
    
    outputBuffer[8][6] = ACS_BTEE;
}

/*
 * Hilfsfunktion zum Schreiben von Texten in den Buffer
 */
void writeToBuffer(int outputBuffer[][FIELD_WIDTH], char* input, int start_height, int start_width, int vertical){
    // Hier fehlen noch Sicherheitsprüfungen
    if(start_width < FIELD_WIDTH && start_height < FIELD_HEIGHT){
        while(*input != '\0'){
            outputBuffer[start_height][start_width] = *input;
            input++;
            if(vertical){
                start_height++;
            }else{
                start_width++;
            }
        }
    }
}

/*
 * Ausgabe des gesamten Buffers inklusive der Hintergrundfarben für die Felder
 */
void printBuffer(int outputBuffer[][FIELD_WIDTH]){
    for(int i = 0; i < FIELD_HEIGHT; i++){
        for(int j = 0; j < FIELD_WIDTH; j++){
            if(j > 0 && j < 16 && ((i > 24 && i < 28) || (i > 32 && i < 36))){
                attron(COLOR_PAIR(BG_WHITE));
                addch(outputBuffer[i][j]);
                attroff(COLOR_PAIR(BG_WHITE));
            }else if(j > 0 && j < 16 && ((i > 8 && i < 12) || (i > 16 && i < 20))){
                attron(COLOR_PAIR(BG_CYAN));
                addch(outputBuffer[i][j]);
                attroff(COLOR_PAIR(BG_CYAN));
            }else if(i > 0 && i < 8 && ((j > 16 && j < 24) || (j > 32 && j < 40))){
                attron(COLOR_PAIR(BG_MAGENTA));
                addch(outputBuffer[i][j]);
                attroff(COLOR_PAIR(BG_MAGENTA));
            }else if(i > 0 && i < 8 && ((j > 48 && j < 56) || (j > 64 && j < 72))){
                attron(COLOR_PAIR(BG_MAGENTA));
                addch(outputBuffer[i][j]);
                attroff(COLOR_PAIR(BG_MAGENTA));
            }else if(j > 72 && j < 88 && ((i > 8 && i < 12) || (i > 16 && i < 20))){
                attron(COLOR_PAIR(BG_RED));
                addch(outputBuffer[i][j]);
                attroff(COLOR_PAIR(BG_RED));
            }else if(j > 72 && j < 88 && ((i > 24 && i < 28) || (i > 32 && i < 36))){
                attron(COLOR_PAIR(BG_YELLOW));
                addch(outputBuffer[i][j]);
                attroff(COLOR_PAIR(BG_YELLOW));
            }else if(i > 36 && i < 44 && ((j > 16 && j < 24) || (j > 32 && j < 40))){
                attron(COLOR_PAIR(BG_BLUE));
                addch(outputBuffer[i][j]);
                attroff(COLOR_PAIR(BG_BLUE));
            }else if(i > 36 && i < 44 && ((j > 48 && j < 56) || (j > 64 && j < 72))){
                attron(COLOR_PAIR(BG_GREEN));
                addch(outputBuffer[i][j]);
                attroff(COLOR_PAIR(BG_GREEN));
            }else{
                addch(outputBuffer[i][j]);
            }
        }
    }
}