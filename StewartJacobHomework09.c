/*
* Write a program that reads in up to 10 strings or to EOF, whichever comes first. 
* Have it offer the user a menu with five choices: 
*	1) print the original list of strings. <><
*	2) print the strings in ASCII collating sequence. <><
*   3) print the strings in order of increasing length. <><
*	4) print the strings in order of the length of the first word in the string. <><
*	5) quit. <><
*	Have the menu recycle until the user enters the quit request. 
*	The program, of course, should actually perform the promised tasks.
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 81 /* string length limit, includes NULL (\0) */
#define LIM 10 /* max number of lines that can be read */

//prototypes
void sortASCII(char* strings[], int num); // sorts by ASCII collating sequence (strcmp)
void sortLength(char* strings[], int num); // sorts by length of strings
int firstWordLength(char*); // gets length (in INT) of first word in string
void sortByFirstWord(char* strings[], int num); // sorts string by length of first word
void menuDisplay(void); // displays menu
char* s_gets(char* string, int num); // gets string

int main(void)
{
	char input[LIM][SIZE]; // array for input
	char* stringP[LIM]; // pointer array for sorting
	int in = 0; // input count
	int out; // output count
	char ch; // char placeholder for menu

	// getting user input
	printf("Enter up to %d lines (enter a blank line to stop):\n", LIM);
	// while lines are less then limit (10), and the string is not null or empty
	while (in < LIM && s_gets(input[in], SIZE) != NULL && input[in][0] != '\0') {
		// setting string pointer to the input array
		stringP[in] = input[in];
		// increasting input counter
		in++;
	}

	menuDisplay();
	while ((ch = getchar()) != '5') {
		// discard extra input (only getting first char)
		if (ch != '\n')
			while (getchar() != '\n')
				continue;
		// switch to handle menu options;
		switch (ch) {
		// original order
		case ('1'):
			for (out = 0; out < in; out++) {
				puts(input[out]);
			}
			break;
		// ASCII order
		case('2'):
			sortASCII(stringP, in);
			for (out = 0; out < in; out++) {
				puts(stringP[out]);
			}
			break;
		// string length
		case('3'):
			sortLength(stringP, in);
			for (out = 0; out < in; out++) {
				puts(stringP[out]);
			}
			break;
		// first word length
		case('4'):
			sortByFirstWord(stringP, in);
			for (out = 0; out < in; out++) {
				puts(stringP[out]);
			}
			break;
		default:
			printf("Invalid input. Try again.\n");
			menuDisplay();
			continue;
		}
		puts("");
		menuDisplay();
	}

	return 0;
}

/* sorts by ASCII using strcmp function */
void sortASCII(char* strings[], int num) {
	char* temp;
	for (int i = 0; i < num - 1; i++) {
		for (int j = i + 1; j < num; j++) {
			if (strcmp(strings[i], strings[j]) > 0) {
				temp = strings[i];
				strings[i] = strings[j];
				strings[j] = temp;
			}
		}
	}
}

/* sorts by length of string */
void sortLength(char* strings[], int num) {
	// sort array of string pointers by length
	char* tmp;
	for (int i = 0; i < num - 1; i++)
		for (int j = i + 1; j < num; j++) {
			if (strlen(strings[i]) > strlen(strings[j])) {
				tmp = strings[i];
				strings[i] = strings[j];
				strings[j] = tmp;
			}
		}
}

/* finds the length of first word in string */
int firstWordLength(char* string)
{
	// skipping leading whitespaces (unless its null)
	while (isspace(*string) && *string != '\0')
		string++;
	// counter
	int count = 0;
	// while there isnt a space, if its null (dont read anymore)
	while (!isspace(*string) && *string != '\0')
	{
		// iterating through string and increasing counter
		string++;
		count++;
	}

	// returning count
	return count;
}

/* sorts string by length of first word */
void sortByFirstWord(char* strings[], int num) {
	char* temp;
	for (int i = 0; i < num - 1; i++) {
		for (int j = i + 1; j < num; j++) {
			if (firstWordLength(strings[i]) > firstWordLength(strings[j])) {
				temp = strings[i];
				strings[i] = strings[j];
				strings[j] = temp;
			}
		}
	}
}

/* displays menu */
void menuDisplay(void) {
	printf("Menu (Options: 1, 2, 3, 4 ,5):\n");
	printf("[1] Print strings in their original order.\n");
	printf("[2] Print strings in ASCII collating sequence.\n");
	printf("[3] Print strings by length.\n");
	printf("[4] Print strings by length of their first word.\n");
	printf("[5] Quit.\n");
	printf("Enter a menu option: ");
}

/* from textbook, gets a string with specified size, places null at end. */
char* s_gets(char* string, int num) {
	char* ret_val;
	int i = 0;
	ret_val = fgets(string, num, stdin);
	if (ret_val) {
		while (string[i] != '\n' && string[i] != '\0')
			i++;
		if (string[i] == '\n')
			string[i] = '\0';
		else
			while (getchar() != '\n')
				continue;
	}
	return ret_val;
}