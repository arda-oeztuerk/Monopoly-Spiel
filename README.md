# Monopoly-Game

An ASCII text-based implementation of the classic Monopoly board game, written in pure C.

## Features

- ASCII-Based Game UI: Play Monopoly in a lightweight, terminal-based interface.
- Local Multiplayer Mode: Supports 2 to 4 players for an interactive gaming experience.
- Save and Load Game: Continue your game anytime by saving and reloading progress.
- Includes buying and selling properties, going to jail(goint to mensa), and drawing event cards.

![Start game](https://github.com/user-attachments/assets/f6d4bece-a12d-411b-837c-20b75eb2ca2c)

![In Game](https://github.com/user-attachments/assets/4a8b6924-8396-4710-9557-4f61c7aae3b5)

![Event Card](https://github.com/user-attachments/assets/fb72ceb0-961d-4e02-960b-c73131aa540e)

# Installation

To install and play the game, follow these steps:

1. Clone the Repository:
```bash
git clone https://github.com/arda-oeztuerk/Monopoly-Spiel.git
cd Monopoly-Spiel/Monopoly_Spiel/Monopoly_Spiel/BUW_ITMT_Monopoly_2223
```
2. Compile the Code:
```bash
gcc -Wall -std=c11 main.c field.c input.c game.c -lncurses -o monopoly
```
3. Run the Game:
```bash
./monopoly
```
