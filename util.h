#ifndef UTIL
#define 	UTIL

	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include <time.h>
	#include "playgame.h"
	
	#define DIGIT_GAME 1
	#define WORD_GAME 2
	
	
	#define FNAME "dict"
	extern int guess_len ;
	// default value is 4
	
	int NUMBER_OF_CHAR_SHOW ;
	// <= 5 ? guess_len * 2 + 2 : guess_len * 2
	
	// It stores the number and number of bull and cow 
	struct numstatus {
					unsigned int noofbull;
					unsigned int noofcow;
					char num[5];
	};
	
	// It converts string to lower case if has any uppercase chars
	void tolower_str (char *);
	
	// This gives value of ten to the power of argument passed
	int tentopow ( int );
	
	// This converts the string value of integer to actual int data type
	long long stringtointeger ( char * );
	
	// Check if integer is in char * array or not
	int isnotinstring ( char , int, char * );
	
	// This gives a random number of n digit with no repeatation of digit 
	// and stores list in char array.
	void getint ( char *, int );
	
	// It gives number of cow in two char array.
	/**
	 *  Number of cow means nuber of chars (digit) common in two array
	 *  which have same position.
	 **/
	unsigned int noofbull(char *, char *);
	
	// It gives number of cow in two char array.
	/**
	 *  Number of cow means nuber of chars (digit) common in two array
	 *  which have different position
	 **/
	 
	unsigned int noofcow(char *, char *);
	
	
	// This gives total number of bulls and cows for previous inputs
	unsigned int totalbullsandcows (struct numstatus *, int );
	
	// 
	int cansetisfy (struct numstatus *, char *, int );
	
	// This is used to get number which satisfy above's inputs
	void getnextnumber(struct numstatus *, char *, int , int);
	
	// check if argument string is valid english word or not
	int is_valid_input (char * , int );
	
	// It print list of chars to help player to guess word
	// Only for guess game
	void charlist_to_help_guess (char * , char *);
	 
	// It count number of unique charecter in string
	int number_of_chars (char *);
	
	// this prints char list which are used to form word
	// to help player to guess right word
	void print_charlist (char *);

#endif
