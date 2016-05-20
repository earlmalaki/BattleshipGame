# BattleshipGame

A terminal-based C implementation of a classic game -- Battleship

AI:
  Single difficulty
  Uses "Hunt" and "Target" mode
  Hunt mode randomly generates a target cell. Once a target cell contains a ship, Target mode will commence.
  Target mode focuses on sinking the ship hit by the Hunt mode by targeting adjacent cells.
  
  Rules of the game:
  1. This is a two player game. Player one is the user, while Player two will be an AI.
  2. Ship position will be generated randomly for both User and AI.
  3. There are 5 types of ship: Carrier (5), Battleship (4), Cruiser (3), Submarine (3), Destroyer (2)
  4. Gameplay is turn-based. Once set up, game proper will start with Player 1's turn.
  5. The winner is the first player to sink all the ships of the opposing player.



Developed by:
Bedio, Aiden Justin
Malaki, Earl Timothy

A CMSC56 Final Project

University of the Philippines - Cebu
BSCS - I | 2nd Semester | 2016

NOTE:
"#include <conio.h>"
Uses conio header file which may cause trouble for non-DOS/Windows systems.
