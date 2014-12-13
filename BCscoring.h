#ifndef BCSCORING
#define BCSCORING
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <time.h>
	#include "playgame.h"
	#include "util.h"
	
	// New data type to save score and game's information
	typedef struct{
		int score;		// obtained score
		char playername[32];  // name of player
		int dgt_chars;  // digit game or char game
		int game_type;  // type of game WITHCOMPUTER , PLAY_ALONE or PLAYFORME
		int won;        // did player won game or loosed.
		struct tm date_time; // date and time of game played
	} SCOREBOARD;
	
	// it cleans score history
	void cleanscores (void);
	
	// it used to increase score according to player's guess
	void getscore (int , int , int *);
	
	// It saves score and about game in file
	int savescore (int , int , int , int * , int);
	
	// It print score if available
	void printscore (void);
	
#endif
