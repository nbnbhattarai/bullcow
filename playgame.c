/**
 * It has functions for playing game , menus
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

#include "playgame.h"
#include "BCscoring.h"
	#include <stdio.h>
	#include "playgame.h"
	#define NUMS guess_len
	#define MAX_HISTORY 10
	#define MAX_TURNS 8
	#define VERSION "1.0.0 (Beta)"
	
	// It prints game playing general instructions
	void printgameins(void)
	{	
		// this is instruction to play game
		printf( "Instruction.\n"\
				"====================\n"\
				"Keep a  number of digit 4 (default) or english word of 4 chars (default).\n"\
				"You can change length of number or word using -l (--length) <length> flag.\n"\
				"And you have to guess computer's number or word.\n"\
				"Computer gives you number of bulls and cows  which helps you to guess correct number.\n\n"\
				"Bulls: \n"\
				"   It is number of char (or digit) of a word (or number) which matches and are in same position too.\n"\
				"   in number 4672(correct) and 6874(guessed) number of bull is 1 because only 7 has same position on both number.\n"\
				"   in word  alpha(correct) and alloy(guessed) number of bulls are 2 because both \'a\' and \'l\' has same position on both word.\n"\
				"Cows : \n"\
				"   It is number of char (or digit) of a word (or number) which matches but are in different position.\n"\
				"   in number 4672(correct) and 6874(guessed) number of cows are 2 because 4 and 6 are in correct number but the position is not correct.\n"\
				"   in word alpha(correct) and alloy(guessed) number of cow is 1 because \'l\' has different positon but is in both word.\n\n"\
				"There are mainly two types of game: \n"\
				"1. Number game: \n"\
				"   In this you have to guess number and\n"\
				"   Repeatation of digit is not allowed.\n"\
				"2. Word game: \n"\
				"   In this you have to guess valid english word.\n"\
				"   Repeatation of char is allowed but it should be valid english word.\n\n"\
				"And type of games are: \n"\
				"1. Play with computer: \n"\
				"   In this, guessing of word or number is done against computer, which also guessed your number or word.\n"\
				"   Who guessed correct first will win the game.\n"\
				"2. Guess game: \n"\
				"   In this, you have to guess number or word within 8 guesses.\n"\
				"   If you guessed right within 8 steps you will win the game.\n"\
				"   Otherwise you will lose.\n"\
				"3. Play for me: \n"\
				"   In this type computer will give you guessing number or word.\n"\
				"   and you have to give bulls and cows number.\n"\
				"   It is used when you are playing with other and you want computer to play for you.\n\n"\
				"(c) 2014 - Nabin Bhattarai , contact nbn.bhattarai99@hotmail.com for bug report.\n"\
				"                             visit http://www.nbhattarai.com.np\n"\
				);
	}
	
	// Usage print function
	void print_usage ()
	{
		printf(	"Usage: bullcow [options ...] [arguments] \n");
	}
	
	// prints version
	void print_version ()
	{
		printf ("Version : "VERSION" Copyright (c) 2014 - Nabin Bhattarai\n");
	}
	
	// print help documents
	void print_help ()
	{
		print_usage ();
		print_version ();
		printf ("\nHelp.\n"\
				"====================================\n"\
				"Options.\n"\
				" -t --type          Type of game to play\n"
				"                    \"word\" for word guessing game.\n"\
				"                    \"number\" for number guessing game.\n"\
				" -g --game          Type of game.\n"\
				"                    \"withcomputer\" to play guessing game with computer\n"\
				"                    \"guess\" to guess computer's number or word within 8 guesses.\n"\
				"                    \"playforme\" to take help of computer to guess number or word.\n"\
				" -l --length        It define length of word or number for guessing game.\n"\
				"                    Length will be 4 (default) if you are not specified.\n"\
				"                    Valid length for game are: 3 , 4 , 5 , 6 only.\n"\
				" -m --menu          It takes us to menu interface to select options and play game.\n"\
				" -p --player        Player name, default player name is : Unknown.\n"\
				" -c --clear         Clear score history.\n"\
				" -i --instruction   print game playing instruction.\n"\
				" -H --hint          print list of charecter used to form word in word guessing game.\n"\
				" -h --help          print help document.\n\n"\
				"(c) 2014 - Nabin Bhattarai , contact nbn.bhattarai99@hotmail.com for bug report.\n"\
				"                             visit http://www.nbhattarai.com.np\n"\
				);
		
	}
	
	// this is main menu which takes argument as selected item
	// and show menu if selected index of menu if 0
	int main_menu (int in)
	{
	int i , j;
	i = in%10;
	j = (int)in/10;
	// this is menu first which lets player to choose wheather play with
	// digit or play with words ( 4 chars)
	
	if ( j == 0){
	do{
		printf ("\n========================================\n"\
				"1. PLAY WITH 4 DIGIT.\n"\
				"2. PLAY WITH 4 CHARECTER WORD.\n"\
				"0. EXIT.\n"\
				"> "\
				);
			// print menu untill user gives invalid inputs
	}while ( (scanf ("%d", &j) == -1) || (j<0 || j >2));
	}
	// if selected to exit from game then return 0
	// ...  also can use exit (0) to exit
	if ( j == 0)
		return 0;
	
	if ( i == 0){
	// this is second menu for type of game
	do{
		printf(	"\n========================================\n"\
			"BULL-COW GAME.\n"\
			"1. Play with computer.\n"\
			"2. Guess Number (Word).\n"\
			"3. Make computer play for you.\n"\
			">  "\
		);
		// print menu untill user gives invalid inputs
	}while ((scanf ("%d", &i) == -1) || ( i <= 0 || i > 3));
	}
	
	// return both selected menu in single integer value
	// first digit gives wheather play with digit or word from 1st menu
	// second digit gives type of game to play from second menu
	return j*10+i;	// if every thing all right returns selected index
	}
	
	// It is main game playing function
	// game_type are 1 -> human and computer
	// 3 -> make computer to play for you
	// 2 -> human vs human which is not given here because bluetooth or any connection between computer is not made

	// Here game type is received from main menu and passed to it
	int playgame(int dgt_chars , int game_type , int givehint)
	{
		int nb1, nc1;
		int score = 0;
		int gam = 0;
		char *sp1 = calloc(guess_len+1, sizeof(char));
		char *spc = calloc(guess_len+1, sizeof(char));
		char *s   = calloc(guess_len+1, sizeof(char));
		char c[3];
		srand(time(NULL));	// to generate random number , here seed is time(NULL)
		
		// It is used to store every guess of computer with their's bull and cow number for further number prediction
		struct numstatus *ns = calloc(MAX_HISTORY, sizeof(struct numstatus)); 
		
		printf ("GAME TYPE : ");
			if ( dgt_chars == DIGIT_GAME)
				printf ("DIGTI GAME\n");
			else
				printf ("WORD GAME\n");
		
		printf ("Play Game : ");
		if ( game_type == WITH_COMPUTER){	// play game with computer, 
            printf ("Thinking...");
			getnextnumber (ns , s , 0 , dgt_chars);
		printf ("WITH COMPUTER.\n");
			do{
				while(1){
				printf ("\nGAME #%d :\n",gam +1);
				printf ("Enter your guess: ");
					if ( scanf ("%s", sp1) == -1){
						printf("Error: Wrong input.\n");
						continue;
					}
					tolower_str (sp1);
					if (is_valid_input (sp1 , dgt_chars))
						break;
					else{
						if (dgt_chars == DIGIT_GAME)
							printf ("Error: Length of input must be equal to $length (default 4) and repeatation is not allowed.\n");
						else
							printf ("Error: Entered word must be a valid english word of exact length = $length (default 4) characters.\n");
					}
				}
				if ( strcmp(sp1, s) == 0){ // if guess is matched so is winner
					printf ("Congratulations !!, You won the game!\n");
					savescore (dgt_chars , game_type , gam + 1 , &score , 1);
					printf ("Your Score : %d\n", score);
					break;
				}

                printf ("Thinking...");
				printf ("Bull no: %d Cow no: %d\n",noofbull(s,sp1),noofcow(s,sp1));
				getscore (noofbull (s, sp1) , noofcow (s ,sp1)  , &score);
				getnextnumber(ns, spc, gam + 1 , dgt_chars);
				printf ("\n===========================\n"\
						"computer's guess: %s ",spc);
				do{
					// ask if computer's guess matched or not
					printf(", Is this correct (y/n)?");
					
				}while (scanf ("%s",c) == -1);
				
				// if guess is right
				if(c[0] == 'y'){
					printf ("Sorry !!, Computer won the game!\n");
					printf ("The number in computer's mind is : %s\n",s);
					savescore (dgt_chars , game_type , gam + 1, &score , 0);
					printf ("Your Score : %d\n", score);
					break;
				}
				// if not right
				do{
					// ask for no. of bulls and cows
					printf ("Bull\\Cow : ");
				}while (scanf ("%d%d", &nb1, &nc1) == -1);
				// store number (word) and it's bull and cows number in ns structure
				strcpy ( ns[gam].num, spc );
				(ns+gam)->noofbull = nb1;
				(ns+gam)->noofcow  = nc1;
				printf  ("===========================\n");
				
				// next turn
				gam++;
			}while(1);
		}else if (game_type == WITH_HUMAN){ // This allows you to make the computer play for you
		printf ("COMPUTER PLAYS FOR YOU.\n");
			gam = 0;
			//getnextnumber (ns , s , 0 , dgt_chars);
			do{
                printf ("Thinking...");
				getnextnumber (ns , s , gam + 1 , dgt_chars);
				printf ("\n#%d : guess : %s ", gam + 1 , s);
				do{
				printf ("\nIs this correst(y/n)? : ");
				}while(scanf("%s",c) == -1);
				 if (c[0] == 'y'){
					printf ("Ok bye!\n");
					break;
				 }
				 do{
					printf ("Bull\\Cow : ");
				}while (scanf("%d%d", &nb1 , &nc1) == -1);
				// store number (word) and it's bull and cows number in ns structure
					strcpy ( ns[gam].num, s );
					(ns+gam)->noofbull = nb1;
					(ns+gam)->noofcow  = nc1;
					printf  ("===========================\n");
				gam++;
			}while(1);
		}else if (game_type == PLAY_ALONE){ // In this game you have to
		if (dgt_chars == WORD_GAME)
			printf ("GUESS COMPUTER'S WORD.\n");
		else
			printf ("GUESS COMPUTER'S NUMBER.\n");
			// guess number or word computer choose within 8 guess
			// otherwise you will lose game
			// It give you number of bulls and cows of your guess
			// start from 0
			gam = 0;
            printf ("Thinking...");
			getnextnumber (ns , s , 0 , dgt_chars);
			
			if (dgt_chars == WORD_GAME && givehint)
				print_charlist (s);
			do{
				
				// game end after 8 guesses
				if (gam == 8){
					printf ("Game Over! You lose!\n");
					printf ("The right answer is : %s\n", s);
					savescore (dgt_chars , game_type , gam + 1, &score , 0);
					printf ("Your Score : %d\n", score);
					break; // end game
				}
				
				while(1){
					do{
						// ask for player's guess
						printf ("\n#%d : Enter your guess : ", gam+1);
					}while (scanf ("%s", sp1) == -1);
					
					tolower_str (sp1);
					
					if (is_valid_input (sp1 , dgt_chars))
						break;
					else{
						if (dgt_chars == DIGIT_GAME)
							printf ("Error: Length of input must be equal to length ( %d ) and repeatation is not allowed.\n", guess_len);
						else
							printf ("Error: Entered word must be valid english word of exact length ( %d ) charecters.\n", guess_len);
					}
				}
				// if user entered right answer 
				// he will be the winner
				if (strcmp (s , sp1) == 0){
					printf ("Congratulation!! You win the game.\n");
					savescore (dgt_chars , game_type , gam + 1 , &score , 1);
					printf ("Your Score : %d\n", score);
					exit (EXIT_SUCCESS); // end game
				}
				
				// if wrong input 
				// print number of bulls and cows
				printf ("Bull no: %d Cow no: %d\n", noofbull (s , sp1) , noofcow (s , sp1));
				getscore (noofbull (s , sp1) , noofcow (s , sp1) , &score);
				gam++;
				
			} while (1);
		} else{
			printf ("Invald game type selected !"); // Option other then defined 3 options
		}
	return 0;
	}
