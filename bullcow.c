/**
 * It is main of this game which handles command arguments
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

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "util.h"
#include "playgame.h"
#include "BCscoring.h"

int guess_len = 4;
char playername[32] = "Unknown";

int main (int argc , char **argv)
{
	struct option longOption[] = {
			{"game", required_argument , 0 , 'g'},	// with computer/guess/play for you
			{"type", required_argument , 0 , 't'},	// chars or number
			{"menu" , no_argument , 0 , 'm'},
			{"help" , no_argument , 0 , 'h'},
			{"instruction" , no_argument , 0 , 'i'},
			{"length" , required_argument , 0 , 'l'},
			{"hint" , no_argument , 0 , 'H'}, // this will print char list to form word
			{"player", required_argument, 0 , 'p'},
			{"scoreboard" , no_argument , 0 , 's'},
			{"clean" , no_argument , 0 , 'c'},
			{ 0 , 0 , 0 , 0 }
		};
	
	int i , in_menu;
	int dc , gt;
	
	int help_flag = 0;
	int menu_flag = 0;
	int game_flag = 0;
	int type_flag = 0;
	int inst_flag = 0;
	int len_flag = 0;
	int hint_flag = 0;
	int score_board_flag = 0;
	
	int option_index = 0;
	int opt;
	int length_input;
	
	while (1){
		opt = getopt_long (argc , argv , "t:g:mhil:Hp:sc" ,longOption , &option_index);
		if ( opt == -1)
			break;
		switch (opt){
			case 't':
				if ( strcmp (optarg , "word") == 0)
					type_flag = WORD_GAME;
				else if (strcmp (optarg , "number") == 0)
					type_flag = DIGIT_GAME;
				else{
					printf ("Invalid argument for -t --type flag.\n");
					//printf ("\nUse -h --help flag for help.");
					//exit(EXIT_FAILURE);
				}
					break;
			case 'g':
				if (strcmp (optarg , "withcomputer") == 0 || strcmp (optarg , "computer") == 0)
					game_flag = WITH_COMPUTER;
				else if (strcmp (optarg , "guess") == 0)
					game_flag = PLAY_ALONE;
				else if (strcmp	(optarg , "playforme") == 0)
					game_flag = WITH_HUMAN;
				else{
					printf ("Invalid argument for -g --game flag.\n");
					//printf ("\nUse -h --help flag for help.");
					//exit (EXIT_FAILURE);
				}
				break;
			case 'm':
				menu_flag = 1;
				break;
			case 'i':
				inst_flag = 1;
				break;
			case 'l':
				len_flag = 1;
				length_input = (int)stringtointeger (optarg);
				
				break;
			case 'H':
				hint_flag = 1;
				break;
			case 'p':
				strcpy (playername , optarg);
				break;
			case 's':
				score_board_flag = 1;
				break;
			case 'c':
				cleanscores ();
				break;
			case 'h':
				help_flag = 1;
				break;
		}
	}
	
	if ( len_flag == 1 && (type_flag != 0 || game_flag != 0)){
		if (length_input <3 || length_input > 6)
			printf(	"Invalid length provided.\n"\
					"Length is made default of length : 4\n"\
					);
		else{
			guess_len = length_input;
			printf ("Guess length is define to : %d .\n" , guess_len );
		}
	}
	
	in_menu = type_flag * 10 + game_flag;
	if (in_menu != 0){
		i = main_menu(in_menu);
		if ( i > 10){
			dc = i/10;
			gt = i%10;
			playgame (dc , gt , hint_flag);
		}
	}
	
	if (help_flag)
		print_help ();
	
	if (menu_flag){
		i = main_menu(0);
		playgame (i/10 , i%10 , hint_flag);
	}
	
	if (score_board_flag)
			printscore ();
	if (inst_flag)
		printgameins ();
	
	if (argc == 1){
		print_usage ();
		printf ("Use -h --help flag for help.\n");
	}
return 0;
}
