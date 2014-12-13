/**
 * Filename: BCscoring.c
 *
 * It has functions to give score, save it , print score
 * 
 * It is a simple number and word guessing game
 * developed by Nabin Bhattarai
 * 
 * It is free to use, modify, copy and redistribute
 * and modification must be free and opensource
 * 
 * If you have any bug report ,modification/Improvement of code, suggestion
 * contact me on : nbn.bhattarai99@hotmail.com
 * 
 * copyright (c) 2014 , Nabin Bhattarai
 * */

#include "BCscoring.h"
#include <stdlib.h>

#define SCOREFILE_PATH "./.DATA/.data"

extern char playername[32];

extern int guess_len;

// it gives scores of your guess
void getscore (int bull , int cow , int *score)
{
	*score += bull*guess_len + cow;
}

// this save scores and information about game played 
int savescore (int dgt_chars, int game_type , int gam, int *score , int won)
{
    // Receive current system time and date
    time_t t = time(NULL);

	FILE *fscore = fopen(SCOREFILE_PATH, "a+");
	SCOREBOARD sb;
	if (won)
		*score += 300/gam;
	sb.date_time = *localtime(&t);
	sb.date_time.tm_year += 1900;
	sb.date_time.tm_mon += 1;
	
	if (fscore == NULL){
		system ("mkdir .DATA");
		fscore = fopen (SCOREFILE_PATH,"a+");
		if (fscore == NULL)
			return -1;
	}
	if (won)
		*score += 100;
	sb.score = *score;
	strcpy (sb.playername , playername);
	sb.dgt_chars = dgt_chars;
	sb.game_type = game_type;
	sb.won = won;
	
	fwrite (&sb , sizeof(SCOREBOARD) , 1, fscore);
	fclose (fscore);
	return 1;
}

// This print all the score history saved
void printscore ()
{
	FILE *fscore = fopen (SCOREFILE_PATH, "r");
	int i = 1;
	SCOREBOARD *sb;
	int size_f , n ;
	if (fscore == NULL){
		printf ("score is not available.\n"
				"You might not played any game yet ,\n"
				"or score history cleared recently.\n"
				);
		return;
	}
	printf ("Scores.\n");
	
	// get file size
	fseek (fscore , 0 , SEEK_END);
	size_f = ftell (fscore);
	fseek (fscore , 0 , SEEK_SET);
	
	// number of game score saved --> 'n'
	n = (size_f / sizeof(SCOREBOARD));
	
	sb = calloc ( n , sizeof(SCOREBOARD));
	
	fread (sb , sizeof(SCOREBOARD) , n , fscore);
	
	// print all scores one by one
	for ( i = 0 ; i < n ; i++){
	//fread (&sb , sizeof(SCOREBOARD) , 2 , fscore);
			printf ("=================================\n"\
					"%.4d : %.2d : %.2d      %.2d : %.2d\n"\
					"Player \t: %s\n",	sb[i].date_time.tm_year,\
										sb[i].date_time.tm_mon,\
										sb[i].date_time.tm_mday,\
										sb[i].date_time.tm_hour,\
										sb[i].date_time.tm_min,\
										sb[i].playername);
			if (sb[i].dgt_chars == DIGIT_GAME)
				printf ("Game  \t: Digit game\n");
			else
				printf ("Game  \t: Word game.\n");
			if (sb[i].game_type == WITH_COMPUTER)
				printf ("Played \t: with computer.\n");
			else
				printf ("Played \t: guess\n");
			printf ("Score \t: %d\n",sb[i].score);
			if(sb[i].won)
				printf ("Status \t: won!\n");
			else
				printf ("Status \t: losed!\n");
	}
	fclose (fscore);
}

// This clears score history
void cleanscores ()
{
	FILE *f = fopen ("./.DATA/.data", "r");
	char *cmd = calloc (16, sizeof(char));
	
	if (f != NULL){
		strcpy (cmd , "rm ");
		strcat (cmd , SCOREFILE_PATH);
		system (cmd);
		printf ("\nScore History cleared.\n");
	fclose (f);
	}
}
