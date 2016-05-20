//////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  *
  * BATTLESHIP GAME
  *
  * CMSC56 - Final Project
  * 
  * Bedio, Aiden Justin
  * Malaki, Earl Timothy
  *
  * BSCS - I | 2nd Semester
  * 
  * University of the Philippines - Cebu
  * Lahug, Cebu City, Cebu
  * Philippines
  *
  */

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <time.h>

/* Declare Constants */
#define ROWS 10
#define COLS 10

#define HORIZONTAL    0
#define VERTICAL      1

#define NUM_OF_SHIPS 5

#define NORTH 0
#define SOUTH 1
#define WEST  2
#define EAST  3

/* Declare Structs */
typedef struct Stats
{
	int life;
	int hit;
	int miss;
} Stats;

typedef enum
{
	FALSE, TRUE
} Boolean;

typedef struct Tile
{
	bool fog;
	char symbol;
} Tile;

typedef struct coordinate
{
	int        row;
	int        column;
} Coordinate;

typedef struct Fleet
{
	char   symbol;
	short  length;
	char   *name;
} Fleet;


/*** Helper Functions ***/


/*
void Display
	Purpose:
		Display of the both boards as playing field
*/
void Display (Tile Player[][COLS], Tile AI[][COLS])
{
	int i = 0, j = 0, n = 0;

	system ("cls");
	printf ("\n\n\t     PLAYER BOARD\t\t\t\t\t\tAI BOARD\n\n");
	printf ("\t  0 1 2 3 4 5 6 7 8 9\t\t\t\t\t  0 1 2 3 4 5 6 7 8 9\n");

	for (i = 0, n = 0; i < 10; ++i,n++)
	{
		printf("\t%d ", n);

		for (j = 0; j < 10; ++j)
		{
			if (Player[i][j].fog == false)
				printf("%c ", Player[i][j].symbol);
			else
				printf("%c ", '~');

		}

		printf ("\t\t\t\t");
		printf("\t%d ", n);

		for (j = 0; j < 10; ++j)
		{
			if (AI[i][j].fog == false)
				printf("%c ", AI[i][j].symbol);
			else
				printf("%c ", 254);

		}
		printf("\n");

	}
}


/*
void updateGameBoard
	Purpose:
		update the values of the corresponding board
*/
void updateGameBoard (Tile gameBoard[][COLS], Coordinate target)
{
	if (gameBoard[target.row][target.column].symbol == '~' || gameBoard[target.row][target.column].symbol == 'm')
	{
		gameBoard[target.row][target.column].fog = false;
	}

	else
	{
		gameBoard[target.row][target.column].symbol = 'X';
		gameBoard[target.row][target.column].fog = false;
	}

}


/*
void ifwithinboard
	Purpose:
		checks cardinals if within the board
*/
void ifwithinboard (Boolean cardinals[], int bound, int direction) 
{
	switch (direction) {
		case NORTH: 
			if (bound < 0) 
				cardinals[0] = FALSE;
			else            
				cardinals[0] = TRUE;
			break;

		case SOUTH:
			if (bound > 9) 
				cardinals[1] = FALSE;
			else            
				cardinals[1] = TRUE;
			break;

		case WEST:
			if (bound < 0)  
				cardinals[2] = FALSE;
			else            
				cardinals[2] = TRUE;
			break;

		case EAST:
			if (bound > 9)  
				cardinals[3] = FALSE;
			else            
				cardinals[3] = TRUE;	
			break;
	}
}


/*
	Boolean checkSunkShip
		purpose:
			Checks if a ship has been sunked
*/
Boolean checkSunkShip (short sunkShip[][NUM_OF_SHIPS], short player, char shipSymbol, Tile Player[][COLS], Tile AI[][COLS])
{
	Boolean sunked = FALSE;

	if (shipSymbol == 'C')
	{

		if (--sunkShip[player][0] == 0)
			{
				system ("cls");
				Display (Player, AI);
				printf ("\n\tBATTLE REPORT:\n");
				if (player == 0)
				{
					printf ("\n\t> AI's Carrier sunked!\n");
				}

				else
				{
					printf ("\n\t> Player's Carrier sunked!\n");
				}


				sunked = TRUE;
				printf ("\n\tPRESS any 'key' to continue...");
				system ("pause>nul");
			}
	}

	else if (shipSymbol == 'B')
	{
		if (--sunkShip[player][1] == 0)
			{
				system ("cls");
				Display (Player, AI);
				printf ("\n\tBATTLE REPORT:\n");
				if (player == 0)
				{
					printf ("\n\t> AI's Battleship sunked!\n");
				}

				else
				{
					printf ("\n\t> Player's Battleship sunked!\n");
				}

				sunked = TRUE;
				printf ("\n\tPRESS any 'key' to continue...");
				system ("pause>nul");
			}
	}

	else if (shipSymbol == 'R')
	{
		if (--sunkShip[player][2] == 0)
			{
				system ("cls");
				Display (Player, AI);
				printf ("\n\tBATTLE REPORT:\n");
				if (player == 0)
				{
					printf ("\n\t> AI's Cruiser sunked!\n");
				}

				else
				{
					printf ("\n\t> Player's Cruiser sunked!\n");
				}

				sunked = TRUE;
				printf ("\n\tPRESS any 'key' to continue...");
				system ("pause>nul");
			}
	}

	else if (shipSymbol == 'S')
	{
		if (--sunkShip[player][3] == 0)
			{
				system ("cls");
				Display (Player, AI);
				printf ("\n\tBATTLE REPORT:\n");
				if (player == 0)
				{
					printf ("\n\t> AI's Submarine sunked!\n");
				}

				else
				{
					printf ("\n\t> Player's Submarine sunked!\n");
				}

				sunked = TRUE;
				printf ("\n\tPRESS any 'key' to continue...");
				system ("pause>nul");
			}
	}

	else if (shipSymbol == 'D')
	{
		if (--sunkShip[player][4] == 0)
			{
					system ("cls");
					Display (Player, AI);
					printf ("\n\tBATTLE REPORT:\n");
					if (player == 0)
					{
						printf ("\n\t> AI's Destroyer sunked!\n");
					}

					else
					{
						printf ("\n\t> Player's Destroyer sunked!\n");
					}

					sunked = TRUE;
					printf ("\n\tPRESS any 'key' to continue...");
					system ("pause>nul");
				}
			}

	return sunked;

}


/*
	short checkShot
		purpose:
			returns 0 if miss, 1 if hit, -1 if invalid
*/
short checkShot (Tile gameBoard[][COLS], Coordinate target)
{
	int hit = -2;

	if ((gameBoard[target.row][target.column].symbol == '~' && gameBoard[target.row][target.column].fog == true) ||
		(gameBoard[target.row][target.column].symbol == 'm' && gameBoard[target.row][target.column].fog == true))
	{
		hit = 0;
	}

	if (gameBoard[target.row][target.column].symbol == 'C' || gameBoard[target.row][target.column].symbol == 'B' ||
		gameBoard[target.row][target.column].symbol == 'R' || gameBoard[target.row][target.column].symbol == 'S' ||
		gameBoard[target.row][target.column].symbol == 'D')

		{
			hit = 1;
		}

	if (gameBoard[target.row][target.column].symbol == 'X' ||
		(gameBoard[target.row][target.column].fog == false && gameBoard[target.row][target.column].symbol == '~') ||
		(gameBoard[target.row][target.column].symbol == 'm' && gameBoard[target.row][target.column].fog == false))
	{
		hit = -1;
	}

	return hit;
}


/*
	Coordinate getTarget
		purpose:
			gets X and Y coordinate
*/
Coordinate getTarget (Tile Player[][COLS], Tile AI[][COLS],int player)
{
	Coordinate target;

	bool check = true;
	do
	{
		fflush (stdin);
		system ("cls");
		Display (Player, AI);
		if (player == 0)
			printf ("\n\tPLAYER's TURN\n");
		else
			printf ("\n\tAI'S TURN\n");
		printf ("\n\tEnter X coordinate: ");
		scanf ("%d",&target.column);
		if (target.column >= 0 && target.column < COLS)
		{
			check = false;
		}
		else
		{
			printf ("\n\tInvalid Input.. Please Try Again..\n\tPress any 'key' to continue..");
			system ("pause>nul");
		}

	} while (check);

	check = true;


	do
	{
		fflush (stdin);
		system ("cls");
		Display (Player, AI);
		if (player == 0)
			printf ("\n\tPLAYER's TURN\n");
		else
			printf ("\n\tAI'S TURN\n");
		printf ("\n\tEnter X coordinate: %d", target.column);
		printf ("\n\tEnter y coordinate: ");
		scanf ("%d",&target.row);
		if (target.row >= 0 && target.row < ROWS)
		{
			check = false;
		}
		else
		{
			printf ("\n\tInvalid Input.. Please Try Again..\n\tPress any 'key' to continue..");
			system ("pause>nul");
		}
	} while (check);


	return target;
}


/*
	int getRandomNumber
		purpose:
			returns 0, or 1 (used anywhere)
*/
int getRandomNumber (int lowest, int highest)
{
	if (lowest == 0)
		return rand () % ++highest;

	if (lowest > 0)
		return rand () % ++highest + lowest;

	return 0;
}


/*
	Coordinate generatePosition
		purpose:
			randomly generates a position
*/
Coordinate generatePosition (int direction, int length) {
	Coordinate position;

	if (direction == HORIZONTAL) {
		position.row    = getRandomNumber (0, ROWS);
		position.column = getRandomNumber (0, COLS - length);
	} 
	else 
	{ /* VERTICAL */
		position.row    = getRandomNumber (0, ROWS - length);
		position.column = getRandomNumber (0, COLS);
	}

	return position;
}


/*
	Boolean isValidLocation
		purpose:
			checks if position is valid
*/
Boolean isValidLocation (Tile gameBoard[][COLS], Coordinate position, int direction, int length,int player)
{
	int i = length - 1;
	Boolean isValid = TRUE;

	for (i = 0; isValid && i < length; i++)
	{
		if (direction == HORIZONTAL)
		{
			if (player == 1)
			{
				if (gameBoard [position.row][position.column + i].symbol != '~' && (position.column + i) < COLS)

				isValid = FALSE;

			}
			else
			{
				if(gameBoard [position.row][position.column + i].symbol != 'm' && (position.column + i) < COLS)
				isValid = FALSE;
			}

		}
		else
		{ /* VERTICAL */

			if (player == 1)
			{
				if (gameBoard [position.row + i][position.column].symbol != '~' && (position.row + i) < ROWS)
				isValid = FALSE;

			}

			else
			{
				if (gameBoard [position.row + i][position.column].symbol != 'm' && (position.row + i) < ROWS)
				isValid = FALSE;
			}


		}
	}

	return isValid;
}


/*
	void initializeship
		purpose:
			Placing the ship to the board
*/
void initializeship (Tile gameBoard[][COLS], Fleet ship, Coordinate position, int direction, int player)
{
	int i = ship.length - 1;

	for (i = 0; i < ship.length; i++)
	{
		if (direction == HORIZONTAL)
		{
			if (player == 1)
			{
				gameBoard [position.row][position.column + i].symbol = ship.symbol;
			}
			else
			{
				gameBoard [position.row][position.column + i].fog = false;
				gameBoard [position.row][position.column + i].symbol = ship.symbol;
			}

		}
		else /* VERTICAL */
		{
			if (player == 1)
			{
				gameBoard [position.row + i][position.column].symbol = ship.symbol;
			}

			else
			{
				gameBoard [position.row + i][position.column].fog = false;
				gameBoard [position.row + i][position.column].symbol = ship.symbol;
			}

		}
	}
}


/*
	void generateposition
		purpose:
			MACRO function for generating the random positions
*/
void generateposition (Tile gameBoard[][COLS], Fleet ship[], int player)
{
	Coordinate position;
	int direction = -1;
	int i = 0;

	for (i = 0; i < NUM_OF_SHIPS; i++)
	{
		while (TRUE)
		{
			direction = getRandomNumber (0, 1); /* 0 -> horizontal, 1 -> vertical */
			position = generatePosition (direction, ship[i].length);

			if (isValidLocation (gameBoard, position, direction, ship[i].length, player))
				break;
		}

		initializeship (gameBoard, ship[i], position, direction, player);
	}
}



													/***** MAIN FUNCTION *****/

int main(int argc, char const *argv[])
{

	srand ((unsigned int) time (NULL));

	int option;
	bool optionchar = true;

	do
	{
		system ("cls");
		printf ("\n\tXXXXX   XXXX  XXXXXX XXXXXX XX     XXXXXX  XXXXX XX  XX XX XXXX\n");
		printf ("\tXX  XX XX  XX   XX     XX   XX     XX     XX     XX  XX XX XX  XX\n");
		printf ("\tXXXXX  XX  XX   XX     XX   XX     XXXX    XXXX  XXXXXX XX XXXX\n");
		printf ("\tXX  XX XXXXXX   XX     XX   XX     XX         XX XX  XX XX XX\n");
		printf ("\tXXXXX  XX  XX   XX     XX   XXXXXX XXXXXX XXXXX  XX  XX XX XX\n\n\n");
		printf ("\t1] TO PLAY\n\t2] HOW TO PLAY\n\t3] CREDITS\n\t4] EXIT\n\n");

		printf ("\n\tEnter Mode\n\tEnter Here: ");
		scanf ("%d", &option);



		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            if (option == 1)
            {

            	// intitializing of boards
            	Tile Player[ROWS][COLS]; // Player gameboard
				Tile AI[ROWS][COLS];	 // AI gameboard

				int v = 0, j = 0;

				for (v = 0; v < ROWS; ++v)
				{
					for (j = 0; j < COLS; ++j)
					{

						Player[v][j].fog = true;
						AI[v][j].fog = true;

						Player[v][j].symbol = 'm';
						AI[v][j].symbol = '~';
					}
				}



			Fleet
		 ship[NUM_OF_SHIPS] = {{'C', 5, "Carrier"},
	                                		 {'B', 4, "Battleship"},
	                                		 {'R', 3, "Cruiser"},
	                                		 {'S', 3, "Submarine"},
	                                		 {'D', 2, "Destroyer"}};

			generateposition (Player, ship, 0);
			generateposition (AI, ship, 1);
			Display(Player, AI);

			Coordinate target;             /* x, y value of a target */
			Coordinate targetTemp;         /* x, y value that holds a temporary value*/
			Coordinate targetOrigin;       /* x, y value of the original target */
			Coordinate targetAI;           /* x, y value of the targets using AI technique */

			Boolean    huntMode       = TRUE;                     /* mode of randomly selecting a target */
			Boolean    sinkmode       = FALSE;                    /* mode when there is a hit */
			Boolean    flipper        = TRUE;	                  /* flips values of boolean */
			Boolean    cardinals[4]   = {TRUE, TRUE, TRUE, TRUE}; /* represents the 4 cardinals, N, S, W, E */
			Boolean    hasAShipSunked = FALSE;                    /* if a ship has sank */
			Boolean    Playersink 	  = FALSE;

			short player  = 0;	           /* 0 -> player1, 1 -> player2 */
			short shot    = 0;             /* holds temp value if ship has been shot */
			int   option  = 0;             /* option for player to place ship manually or randomly */
			int   north   = 0,             /* holds change of value when going north */
				  south   = 0,             /* holds change of value when going south */
				  east    = 0,             /* holds change of value when going east */
				  west    = 0;             /* holds change of value when going west */
			int   i       = 0,
				  counter = 1;             /* i and counter are used as counters */

			char  shipSymbol = '\0';       /* temporary value to save character symbol of the ship */

			short sunkShip[2][NUM_OF_SHIPS] = {{5, 4, 3, 3, 2},
	                                   		   {5, 4, 3, 3, 2}};  /* tracks parts of the ship destroyed */

			Stats Human 			= {17, 0, 0};
			Stats ArtificialInt 	= {17, 0, 0};

			int Turncounter = 1;

			while (true)
			{
				player = 0;
				/////////PLAYER'S TURN///////////////
				printf ("\n\n\tPlayer's Turn:");

				do
				{
					target = getTarget (Player, AI, 0);
					shot = checkShot (AI, target);

					if (shot == -1)
					{
						printf ("\n\tBATTLE REPORT:\n");
						printf ("\n\tTry another target\n\tPress any 'key' to continue");
						system ("pause>nul");
					}

				} while (shot == -1);

				shipSymbol = AI[target.row][target.column].symbol;

				if (shot == 1)
				{ /* HIT */
					ArtificialInt.life--;
					Human.hit++;
					system ("cls");
					Display (Player, AI);
					printf ("\n\tBATTLE REPORT:\n");
					printf ("\n\t>Coordinate: %d, %d is a hit!\n\n\tPress any 'key' to continue...", target.column , target.row);
					system ("pause>nul");


					/* Checks if the ship has sank */
					Playersink = checkSunkShip (sunkShip, player, shipSymbol, Player, AI);

				}

				else
				{        /* MISS */
					Human.miss++;
					system ("cls");
					Display (Player, AI);
					printf ("\n\tBATTLE REPORT:\n");
					printf ("\n\t>Coordinate %d, %d is a miss!\n\n\tPress any 'key' to continue...",target.column , target.row);
					system ("pause>nul");

				}

				updateGameBoard (AI, target);
				Display(Player, AI);
				printf ("\n\tAI's TURN\n\n\tAI INPUTTING COORDINATES....\n\n\t");
				printf ("PRESS any 'key' to continue....");
				system ("pause>nul");


				/**** IMPLEMENTATION OF THE ARTIFICIAL INTELLIGENCE *****/
				//////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////
				player = 1;

				if (hasAShipSunked) 
				{
					hasAShipSunked = FALSE;
					sinkmode = FALSE;
					huntMode = TRUE;
				}


				if (sinkmode) 
				{
					/* retains value of targetAI */
					target = targetAI;

					do 
					{

						if (cardinals[NORTH]) 
						{        /* NORTH */
							target.row = north;
						} 

						else if (cardinals[SOUTH]) 
						{ /* SOUTH */
							target.row = south;
						} 

						else if (cardinals[WEST])
						{  /* WEST */
							target.column = west;
						}

						else if (cardinals[EAST]) 
						{  /* EAST */
							target.column = east;
						} 

						else if (!cardinals[NORTH] && !cardinals[SOUTH] && 
						         !cardinals[WEST]  && !cardinals[EAST]  && 
								 !hasAShipSunked) 
						{
							/* All cardinals are FALSE but has not sunk a ship */
							
							/* reinitiliazes target to the original target value */
							target = targetOrigin;
							targetTemp = target;

							/**
							 * Counter increments by one, when the loop cycles again and
							 * all cardinals are still FALSE. This ensures that we are checking
							 * one cell over the adjacent cells 
							 */
							north = target.row - counter;
							targetTemp.row = north;

							/* checks if the value NORTH of the target is a hit or miss */
							if (checkShot (Player, targetTemp) != -1 && north >= 0) 
							{
								cardinals[NORTH] = TRUE;
							}

							targetTemp = target;
							south = target.row + counter;
							targetTemp.row = south;

							/* checks if the value SOUTH of the target is a hit or miss */
							if (checkShot (Player, targetTemp) != -1 && south <= 9) 
							{
								cardinals[SOUTH] = TRUE;
							}

							targetTemp = target;
							west = target.column - counter;
							targetTemp.column = west;

							/* checks if the value WEST of the target is a hit or miss */
							if (checkShot (Player, targetTemp) != -1 && west >= 0) 
							{
								cardinals[WEST] = TRUE;
							}

							targetTemp = target;
							east = target.column + counter;
							targetTemp.column = east;

							/* checks if the value EAST of the target is a hit or miss */
							if (checkShot (Player, targetTemp) != -1 && east <= 9) 
							{
								cardinals[EAST] = TRUE;
							}

							/**
							 * increments counter every cycle, serves as a addend to how
							 * many cells to check from the target cell
							 */
							counter++;

						} 

						else  
						{
							/* when all conditions are not met, it reverts back to Hunt mode */
							sinkmode = FALSE;
							huntMode = TRUE;
							break;
						}
						
						/* checks if the shot is a hit or miss */
						shot = checkShot (Player, target);

					} while (shot == -1 && sinkmode == TRUE);

					/**
					 * this loop flips the values of the cardinals when it is not needed
					 * takes the cardinal off the stack for directions to check 
					 */
					if (shot == 1 && huntMode == FALSE) 
					{
						for (i = 0; i < 4; i++) 
						{
							if (flipper == FALSE)
								cardinals[i] = FALSE;

							if (cardinals[i] == flipper) 
								flipper = FALSE;
						}
					} 

					else 
					{
						for (i = 0; i < 4; i++) 
						{
							if (flipper == TRUE && cardinals[i] != FALSE) 
							{
								cardinals[i] = FALSE;
								break;
							}
						}
					}

					/* reinitializes the value of flipper */
					flipper = TRUE;
				}

				

				if (huntMode) 
				{	

					/* reinitializes important values */
					counter = 1;
					flipper = TRUE;
					for (i = 0; i < 4; i++)
						cardinals[i] = TRUE;

					/* loop that gets a random number of a cell as target */
					do {
						target.row = getRandomNumber (0, 9);
						target.column = getRandomNumber (0, 9);

						/* checks target if it is a miss or hit cell */
						shot = checkShot (Player, target);
					} while (shot == -1);

					/* if it is a Hit, this saves the value of the original target */
					if (shot == 1) 
						targetOrigin = target;
				}

				if (shot == 1) 
				{

					/**
					 * if all cardinals are false and no ship was sunk,
					 * reintializes target from value of original target 
					 */
					if (!cardinals[NORTH] && !cardinals[SOUTH] && 
						!cardinals[WEST]  && !cardinals[EAST]  && 
						!hasAShipSunked) 

						{ 
							target = targetOrigin; 
						}
					/* hunt mode is false during a target mode */
					huntMode = FALSE;
					sinkmode = TRUE;
					targetAI = target;

					/**
					 * get values of adjacent cells and ensuring that
					 * that it is withing the bounds of gameboard for 
					 * NORTH, SOUTH, WEST & EAST
					 */
					if (cardinals[NORTH] == TRUE) 
					{  /* NORTH */
						north = (targetAI.row - 1);
						ifwithinboard (cardinals, north, NORTH);
						targetTemp = target;
						targetTemp.row = north;
						if (checkShot (Player, targetTemp) == -1)
							cardinals[NORTH] = FALSE;
					}
					
					if (cardinals[SOUTH] == TRUE) 
					{  /* SOUTH */
						south = targetAI.row + 1;
						ifwithinboard (cardinals, south, SOUTH);
						targetTemp = target;
						targetTemp.row = south;
						if (checkShot (Player, targetTemp) == -1)
							cardinals[SOUTH] = FALSE;
					}

					if (cardinals[WEST] == TRUE) 
					{   /* WEST */
						west  = targetAI.column - 1;
						ifwithinboard (cardinals, west, WEST);
						targetTemp = target;
						targetTemp.column = west;
						if (checkShot (Player, targetTemp) == -1)
							cardinals[WEST] = FALSE;
					}

					if (cardinals[EAST] == TRUE) 
					{   /* EAST */
						east  = targetAI.column + 1;
						ifwithinboard (cardinals, east, EAST);
						targetTemp = target;
						targetTemp.column = east;
						if (checkShot (Player, targetTemp) == -1)
							cardinals[EAST] = FALSE;
					}
				}

				/* saves the character of the targeted cell */
				shipSymbol = Player[target.row][target.column].symbol;

				

				if (shot == 1)
				{ /* HIT */
					Human.life--;
					ArtificialInt.hit++;
					system ("cls");
					Display (Player, AI);
					printf ("\n\tBATTLE REPORT:\n");
					printf ("\n\t>Coordinate: %d, %d is a hit!\n\n\tPress any 'key' to continue...",target.column , target.row);
					system ("pause>nul");


					/* Checks if the ship has sank */
					hasAShipSunked = checkSunkShip (sunkShip, player, shipSymbol, Player, AI);


				}

				else
				{        /* MISS */
					ArtificialInt.miss++;
					system ("cls");
					Display (Player, AI);
					printf ("\n\tBATTLE REPORT:\n");
					printf ("\n\t>Coordinate %d, %d is a miss!\n\n\tPress any 'key' to continue...", target.column , target.row);
					system ("pause>nul");

				}

				updateGameBoard (Player, target);
				Display(Player, AI);

				double HA = Human.hit/Turncounter;
				double AIA = ArtificialInt.hit/Turncounter;

				if (Human.life == 0 && ArtificialInt.life == 0)
				{
					printf ("\n\n\tBOTH PLAYER & AI HAS NO SHIPS LEFT");
					printf ("\n\n\tBATTLE IS A DRAW");
					printf ("\n\n\tBATTLE STATS:\n\n\t");
					printf ("NO OF TURNS: %d\n\t", Turncounter);
					printf ("PLAYER:\t\t\tAI:\n\n\t");
					printf ("HITS: %d\t\t\tHITS: %d\n\t",Human.hit, ArtificialInt.hit);
					printf ("MISS: %d\t\t\tMISS: %d\n\t",Human.miss,ArtificialInt.miss);
					system ("pause>nul");
					break;
				}

				else if (Human.life == 0)
				{
					printf ("\n\n\tPLAYER HAS NO SHIPS LEFT\n");
					printf ("\n\tAI WINS");
					printf ("\n\n\tBATTLE STATS:\n\n\t");
					printf ("NO OF TURNS: %d\n\t", Turncounter);
					printf ("PLAYER:\t\t\tAI:\n\n\t");
					printf ("HITS: %d\t\t\tHITS: %d\n\t",Human.hit, ArtificialInt.hit);
					printf ("MISS: %d\t\t\tMISS: %d\n\t",Human.miss,ArtificialInt.miss);
					system ("pause>nul");
					break;
				}

				else if (ArtificialInt.life == 0)
				{

					printf ("\n\n\tAI HAS NO SHIPS LEFT\n");
					printf ("\n\tPLAYER WINS");
					printf ("\n\n\tBATTLE STATS:\n\n\t");
					printf ("NO OF TURNS: %d\n\t", Turncounter);
					printf ("PLAYER:\t\t\tAI:\n\n\t");
					printf ("HITS: %d\t\t\tHITS: %d\n\t",Human.hit, ArtificialInt.hit);
					printf ("MISS: %d\t\t\tMISS: %d\n\t",Human.miss,ArtificialInt.miss);
					system ("pause>nul");
					break;
					
				}

				Turncounter++;

			}
            	
            }
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            else if (option == 2)
            {
            	system ("cls");
            	printf ("\n\n\t");
            	printf ("\t\t\tRULES OF THE GAME:\n\n");
				printf ("\t1. This is a two player game.\n\n");
				printf ("\t2. Player is you and the opponent is an AI.\n\n");
				printf ("\t3. Position of the ships will be generated randomly both for Player and AI.\n\n");
				printf ("\t4. There are five types of ships to be placed by longest length to the\n"); 
				printf ("\t   shortest; [C] Carrier has 5 cells, [B] Battleship has 4 cells, [R] Cruiser\n");
				printf ("\t   has 3 cells, [S] Submarine has 3 cells, [D] Destroyer has 2 cells.\n\n");
				printf ("\t5. The Player gets to guess first but the shots are checked simultaneously\n\n");
				printf ("\t6. The game begins as each player tries to guess the location of the ships\n");
				printf ("\t   of the opposing player's game board; [X] hit,\n");
				printf ("\t   [m] miss (for the board of Player), [~] miss (for the board of AI).\n\n");
				printf ("\t7. First player to guess the location of all ships wins.\n\n\n");
				printf ("\t\t       Press any 'key' To go back to Main Menu");
				system ("\t\tpause>nul");
            }

            else if (option == 3)
            {
            	system ("cls");
            	printf ("\n\n\tDevelopers:");
            	printf ("\n\n\tAiden Justin Bedio\t\t\tEarl Timothy Malaki");
            	printf ("\n\n\n\t\tSPECIAL THANKS");
            	printf ("\n\n\tNico Martin Enego (MENTOR)");
            	printf ("\n\tKurt Espinosa (MENTOR)");
            	printf ("\n\tRyan Dulaca (MENTOR)");
            	printf ("\n\tJedaiah Joel Lumagbas (MENTOR)");
            	printf ("\n\tAllyssa Albores (LAPTOP PROVIDER) (BETA TESTER)");
            	printf ("\n\tDecelle Suarez (BETA TESTER)");
            	printf ("\n\tTim Paler (BETA TESTER)");
            	printf ("\n\n\n\t\tPress any 'key' to go back to Main Menu");
            	system ("pause>nul");
            }

            else if (option == 4)
            {
            	system ("cls");
            	printf ("\n\n\t\tTHANK YOU FOR PLAYING   :D\n\n\n\n\t\t");
            	system ("pause>nul");

            }

            else
            {
            	printf ("Invalid Input Please Try Again.\n\n\t\tPress any 'key' to continue...");
            	system ("pause>nul");
            }

	} while (optionchar);

	return 0;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////