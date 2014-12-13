/**
 * It has utility functions
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

#include "util.h"

	extern int NUMBER_OF_CHAR_SHOW;

// It converts uppercase chars of string s to lowercase
void tolower_str (char *s)
{
	int i = 0;
	while (*(s + i)){
		if (*(s + i) >= 65 && *(s + i) <= 90)
			*(s + i) += 32;
		i++;
	}
}

// It gives the value of ten to the power of p
int tentopow ( int p)
{
	int ans = 1;
	for (; p > 0; p--)
		ans *= 10;
	return ans;
}

// It converts string s to long value (integer )
long long stringtointeger ( char *s )
{
	int i = strlen (s) - 1 , j = 0;
	long long result = 0;
	while ( *(s + i) ){
		if (*(s + i) > 57 || *(s + i) < 48)
			return -1;
		result += ((long long) *(s + i) - 48) * tentopow(j);
		i--;
		j++;
	}
	return result;
}

// Confirms if a is in char array or not
int isnotinstring ( char c, int n, char *s )
{
	int i = 0;
	if ( n == 0)
		return 1;
	while(i < n){
		if (*(s + i) == c)
			return 0;
	i++;
	}
	return 1;
}


// This gives a random number of n digit with no repeatation of digit 
// and stores list in char array.
void getint (char *st,  int n )
{
	int i = 0, s;
		while ( i < n){
			s = rand();
			s %= 10;
			if ( isnotinstring( s + 48 , n , st) ){
				*( st + i) = (char) (s + 48);
				i++;
			}else{
				continue;
			}
		}
		*(st + i) = '\0';
}

// returns no of bulls between in and num
unsigned int noofbull (char *in, char *num)
{
	unsigned int bullno = 0 , i = 0;
	while(*(in + i) && *(num + i) ){
		if (*(in + i) == *( num + i))
			bullno++;
	i++;
	}
	return bullno;
}

// gives no of cows between arguments in and num
unsigned int noofcow (char *in, char *num)
{
	unsigned int cowno = 0, i = 0, j = 0;
	while ( *(num + i)){
		j = 0;
		while (*(in + j)){
			if(( *(in +j) == *(num + i)) && i!= j)
				cowno++;
		j++;
		}
	i++;
	}
	return cowno;
}

// This gives total number of bulls and cows for previous inputs
// in structure numstatus
unsigned int totalbullsandcows (struct numstatus *sn, int n)
{
	unsigned int total = 0;
	int i;
	for ( i = 0; i < n; i++)
		total += (sn + i)->noofbull + (sn + i)->noofcow;
	return total;
}

// This returns TRUE if in satisfy all the values of bull and cow for 
// above's history
int cansetisfy (struct numstatus *ns, char *in, int n)
{
		int i;
		for(i = 0; i< n ; i++){
			if (!((noofbull((*(ns+i)).num, in) == (*(ns+i)).noofbull) && (noofcow ((*(ns+i)).num, in) == (*(ns+i)).noofcow)))
				return 0;
		}
		return 1;
}

// This functions is used to get next list of integer which is probable 
// for the result according to the history of input and result on sn
void getnextnumber(struct numstatus *sn, char *out, int n , int dgt_chars) // dgt_chars are : 1 -> digit 2 -> word
{
	char *temp = calloc(guess_len + 1, sizeof(char));
	FILE *fin = NULL;
	unsigned int k = 0;
	int s;
	int i;
	if ( dgt_chars == DIGIT_GAME){
		if(n <= 2){
			getint (out, guess_len);
		}else{
			while(1){
				k++;
				getint(temp, guess_len );
				//printf ("%s\t",temp);
				if (cansetisfy(sn, temp, n)){
					strcpy (out, temp);
					break;
				}
			if ( k > 1000000){
				printf ("You might enterd wrong bull and cow numbers.\n");
				break;
			}
		}
		}
	}else{
	// if game is word guess game then 
	// guess english word of 4chars from file FNAME
		
		fin = fopen (FNAME , "r");
	// for first two guess random word is choosen
		if ( n <= 2){
			s = rand ();
			s %= 4000 ;
			for ( i = 0 ; i < s ; i++)
				fscanf (fin , "%s" , temp);
			while(!feof(fin)){
				fscanf (fin , "%s" , temp);
				if (strlen (temp) == guess_len){
					strcpy (out , temp);
					break;
				}
			}
		// from third move ...
		}else{
			while (!feof (fin)){
				fscanf ( fin , "%s" , temp);
				// copy value to out iff temp satisfy all the bulls and
				// cows number for above's guess ( 1st and 2nd)
				if (strlen (temp) != guess_len)
					continue;
				else if(cansetisfy (sn , temp , n) && strlen(temp) == guess_len){
					strcpy (out , temp);
					fclose (fin);
					return;
				}
			}
			
			// if value of temp is not changed then there is no word 
			// which matches to guess. 
			// It happens if wrong bulls and cows nuber is given
			// for above's guesses
			printf ("you might enterd wrong bull cow number.\nPlay again .\n");

			// close dictionary file	
			fclose (fin);
		
		}
	}
}

// check if user input word is valid word or not
int is_valid_input (char *s , int dgt_word)
{
	int i , j;
	FILE *f;
	if ( strlen (s) != guess_len)
		return 0;
	if (dgt_word == DIGIT_GAME){
		for ( i = 0 ; i < strlen(s) ; i++){
			for ( j = 0 ; j < strlen (s) ; j++){
				if ( i == j)
					continue;
				else if ( s[i] == s[j] )
					return 0;
			}
		}
	return 1;
	}else {
		f = fopen (FNAME, "r");
		char *temp = calloc (8 , sizeof (char));
		while (!(feof(f))){
			fscanf (f , "%s" , temp);
			if ( strcmp (temp , s) == 0){
				fclose (f);
				free (temp);
				return 1;
			}
		}
		fclose (f);
		free (temp);
	return 0;
	}
	return 0;
}

// It count number of unique chars present in string s
int number_of_chars (char *s)
{
	int n = 0 , i = 0;
	while (*(s + i)){
		if (isnotinstring (*(s + i) , i , s))
			n++;
		i++;
	}
	return n;
}

// It generate list of chars in between of them right chars are also
// present which forms right word
// It is only for "word game" and "guess game"
void charlist_to_help_guess (char *guess , char *s)
{
	// It sets value to NUMBER_OF_CHAR_SHOW
	if (guess_len >= 5 )
		NUMBER_OF_CHAR_SHOW = guess_len * 2;
	else
		NUMBER_OF_CHAR_SHOW = guess_len	* 2 + 2;

	int n_is = 0 , n_isnot = 0;
	int n_of_chars = number_of_chars (guess);
	int rand_char;
	printf ("Number of chars in %s : %d\n", guess , n_of_chars);
	int i;
	for ( i = 0; i < NUMBER_OF_CHAR_SHOW ; ){
		// get random char
		rand_char = rand() % 26 + 97;
		if (isnotinstring (rand_char , guess_len , guess) &&\
			isnotinstring (rand_char , i , s) &&\
			(n_isnot - n_is) < 3 &&\
			n_isnot < (NUMBER_OF_CHAR_SHOW - n_of_chars)){
				s[i] = (char) rand_char;
				i++;
				n_isnot ++;
			}
		else if (!isnotinstring (rand_char , guess_len , guess) &&\
				 isnotinstring (rand_char , i , s) &&\
				 n_is < n_of_chars){
					 s[i] = (char) rand_char;
					 i++;
					 n_is++;
				 }
	}
	// end of string
	s[NUMBER_OF_CHAR_SHOW ] = '\0';
}

// It print collection of chars, which also has correct chars from which
// correct guess word is formed
void print_charlist (char *guess)
{
	if (guess_len >= 5 )
		NUMBER_OF_CHAR_SHOW = guess_len * 2;
	else
		NUMBER_OF_CHAR_SHOW = guess_len	* 2 + 2;

	char *p = calloc (NUMBER_OF_CHAR_SHOW + 1 , sizeof (char));
	int i = 0;
	charlist_to_help_guess (guess , p);
	printf ("\nThese characters are used to form this word: \n\t\t< ");
	while (*(p + i) != '\0'){
		printf (" %c " , *(p + i));
		i++;
	}
	printf (">\n");
}
