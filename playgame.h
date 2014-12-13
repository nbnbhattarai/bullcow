#ifndef PLAYGAMEf
	#define PLAYGAME
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include "util.h"
	
	#define WITH_COMPUTER 1	// Play game with computer
	#define PLAY_ALONE 2 	// Play game with two humans with (W)LAN connection
	#define WITH_HUMAN 3	// Play game with computer as you which gives you to set number for computer
	
	extern int guess_len; // declaration of variable 
	
	// This is Main Menu
	int main_menu(int);
	
	// This will print game playing instruction
	void printgameins(void);
	
	void print_help (void);
	
	// print current version of game
	void print_version (void);
	
	// print Usage
	void print_usage (void);
	
	// This is function to play game
	int playgame (int , int , int);

#endif
