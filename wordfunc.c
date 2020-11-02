/* Ryan Quan
 * CSE 20311
 * Lab 8
 * Crossword */

// Include Relevant libraries
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include "wordfunc.h"

// import global value for boardsize
extern int boardsize;

//Fxn to fill solution board with '.'
void fill_solution(char solution_board[][boardsize]){
	char fill = '.';
	int i;
	int j;
	for (i=0;i<boardsize;i++){
		for (j=0;j<boardsize;j++){
			solution_board[i][j] = fill;
		}
	}
}

//Fxn to fill puzzle board with #
void fill_puzzle(char puzzle_board[][boardsize]){
	char fill = '#';
	int i;
	int j;
	for (i=0;i<boardsize;i++){
		for (j=0;j<boardsize;j++){
			puzzle_board[i][j]= fill;
		}
	}
}

//Fxn to display a board
void display_board(char board[][boardsize]){
	int i;
	int j;
	for (i=-1;i<=boardsize;i++)
		printf("-");
	printf("\n");
	for (i=0;i<boardsize;i++){
		printf("|");
		for (j=0;j<boardsize;j++) printf("%c", board[i][j]);
		printf("|");
		printf("\n");	
	}
	for (i=-1;i<=boardsize;i++){
		printf("-");
	}
	printf("\n");

}

//Fxn to read words from command line and output # of words read in
int read_cmd(char words[][boardsize]){ //function to read words in from command line
	int wordcount=0;
	char temp[boardsize];
	char *result; // pointer for substring
	printf("Please enter a list of words consisting of 2-15 letters followed by a \".\"\n");
	while (wordcount<20){
		scanf("%s", temp);
		if (((strlen(temp)) <= boardsize && strlen(temp)>=2) || strstr(temp,".") )  { //ensure that inputted word is no longer than 15 characters
			if (lettersonly(temp)){ //check that word contains only alphabetical chars
				upper2lower(temp);//call upper2lower fxn to capitalize word
				strcpy(words[wordcount],temp); //copy temp word to word data structure
				result=strstr(temp,".");
				if (result) break; //if a period is detected, stop reading
				wordcount++;
			}
			else printf("Word contains non-alphabetical character and cannot be displayed in the crossword puzzle\n");
		}
		else 
			printf("Error: Invalid String length\n"); //error message if string is too long
	}
	return wordcount;
}

// Fxn to read words from a file and output # of words read in
int read_file(char words[][boardsize],char *filename){
	int wordcount=0;
	char temp[boardsize];
	FILE *fp;//pointer for file
	
	fp=fopen(filename,"r");
	if (!fp){
		printf("file %s is not found\n",filename);
		return 1; //exit program if incorrect filename entered
	}
	while (wordcount<20){
		fscanf(fp,"%s",temp);
		upper2lower(temp);//call upper2lower fxn to capitalize word
		if (feof(fp)) break;
		if (((strlen(temp)) <= boardsize && strlen(temp)>=2) || strstr(temp,".")) {
			if(lettersonly(temp)){
				strcpy(words[wordcount],temp);
				if ((strcmp(temp,".")) == 0) break;
				wordcount++;
			}
			else printf("A word in the file contains a non-alphabetical character and will not be displayed in the crossword puzzle\n");
		}
		else
			printf("Error: Invalid word length within file\n");

	}
	return wordcount;
}

//Fxn to turn capitalize all the letters in a string
void upper2lower(char string[]){
	int i;
	for (i=0;i<strlen(string);i++){
		string[i]=toupper(string[i]);
	}
}

bool lettersonly(char string[]){
	int i;
	bool flag=true;
	for (i=0;i<strlen(string);i++){
		if(isdigit(string[i]) != 0){
			flag=false;
		}

	}
	return flag;
}

//Fxn that sorts an array of strings in descending order of length
void lengthsort(char words[][boardsize],int wordcount){
	int i;
	int j;
	char temp[boardsize];
	char temp2[boardsize];
	for (j=0;j<=wordcount;j++){
		for (i=0;i<wordcount-j-1;i++){
			strcpy(temp,words[i]);
			strcpy(temp2,words[i+1]);
			if ((strlen(words[i])) < (strlen(words[i+1]))){
				strcpy(words[i],temp2);
				strcpy(words[i+1],temp);
			}
		}
	}
}

//Fxn checks if a word can fit horizontally on board and returns T/F value
bool vertical_fit(char board[][boardsize],int wordlength,int n,int y,int x){ //n is where letter falls in string, y is row in board, x is column in board
	bool verticalfit;
	if((y-n >= 0) && ((y + (wordlength-n)) < boardsize)) verticalfit=true;
	else verticalfit=false;
//check to make sure word will occupy blank spaces
	int i;
	int j;
	for (i=y-n;i<y;i++){
		if (board[i][x] != '.') verticalfit = false;
		if (y-n > 0){
			for (j=-1;j<=1;j++){
				if (board[i][x+j] != '.') verticalfit = false;
			}
		}
	}

//Check that word will be separated by at least one space
	for (i=y+1; i< (y+wordlength-n); i++){
		if (board[i][x] != '.') verticalfit = false;
		if (y+wordlength-n < boardsize){
			for (j=-1;j<=1;j++){
				if (board[i][x+j] != '.') verticalfit = false;
			}
		}
	}

	return verticalfit;
}

//fxn checks if a word can fit horizontally on board
bool horizontal_fit(char board[][boardsize],int wordlength,int n,int y,int x){
	bool horizontalfit;
	if ((x-n >= 0) && ((x + (wordlength-n)) < boardsize)) horizontalfit=true;
	else horizontalfit =false;
//check that word will occupy blank spaces
	int i;
	int j;
	for (i=x-n;i<x;i++){
		if (board[y][i] != '.') horizontalfit=false;
		if (x-n > 0){
			for (j=-1;j<=1;j++){
				if (board[y+j][i] != '.') horizontalfit = false;
			}
		}
	}
//check that word will be separated by at least one space
	for (i=x+1; i< (x+wordlength-n);i++){
		if (board[y][i] != '.') horizontalfit = false;
		if (x+wordlength-n < boardsize) {
			for (j=-1;j<=1;j++){
				if (board[y+j][i] != '.') horizontalfit = false;
			}
		}
	}
	return horizontalfit;
}


//Fxn that builds solution for crosword puzzle
void build_solution(char board[][boardsize],char words[][boardsize],int words_direction[],int words_x[], int words_y[], bool word_placed[], int wordcount){
	int i;
	int j;
	int k;
	int m=0;
	int n=0;
	int mid;
	//Place first word centered in board
	mid = strlen(words[0])/2;
	board[7][7]= words[0][mid];
	words_direction[0] = 0; //first word is placed horizontally
	words_x[0]=7-mid; //column of first word
	words_y[0]=7;//row of first word
	word_placed[0]=true;//first word is placed
	for (i=7-mid;i<7;i++){ //place first word in the middle of the board
		board[7][i] = words[0][n];
		n++;
	}
	for (i=7;i<=7+mid;i++){
		board[7][i] = words[0][n];
		n++;
	}

	//Place remaining words
	for (i=1;i<wordcount;i++){//run through all words
		int placed =0;
		for (j=0;j<strlen(words[i]);j++){//run through all chars in word
			for (k=0;k<boardsize;k++){ //run through each char in board
				for (m=0;m<boardsize;m++){
					if (placed==0 && board[k][m] == words[i][j] && vertical_fit(board,strlen(words[i]),i,k,m)){ //matching letter and word fits vertically
						for (n=0;n<strlen(words[i]);n++){
							board[k-j+n][m] = words[i][n];
						}	
						placed =1;
						words_direction[i]=1; //save as 1 if vertical
						words_x[i]= m;//save column
						words_y[i]= k-j;//save row
						word_placed[i]= true; //word is placed
					}
					else if (placed==0 && board[k][m] == words[i][j] && horizontal_fit(board,strlen(words[i]),i,k,m)){ //matching letter and word fits horizontally
						for(n=0;n<strlen(words[i]);n++){
							board[k][m-j+n] = words[i][n];
						}
						placed =1;
						words_direction[i] = 0; //save as 0 if horizontal
						words_x[i]= m-j; //save column
						words_y[i]= k; //save row
						word_placed[i]= true; //word is placed
					}
				}
			}
		}
		//Extra Credit a
		printf("\n");
			if(!word_placed[i]){
				printf("Word %s could not be placed\n",words[i]);
			}
	}

	//Extra Credit b
	for (i=1;i<wordcount;i++){//run through all words
		if(!word_placed[i]){
			int placed =0;
			for (j=0;j<strlen(words[i]);j++){//run through all chars in word
				for (k=0;k<boardsize;k++){ //run through each char in board
					for (m=0;m<boardsize;m++){
						if (placed==0 && board[k][m] == words[i][j] && vertical_fit(board,strlen(words[i]),i,k,m)){ //matching letter and word fits vertically
							for (n=0;n<strlen(words[i]);n++){
								board[k-j+n][m] = words[i][n];
							}	
							placed =1;
							words_direction[i]=1; //save as 1 if vertical
							words_x[i]= m;//save column
							words_y[i]= k-j;//save row
							word_placed[i]= true; //word is placed
						}
						else if (placed==0 && board[k][m] == words[i][j] && horizontal_fit(board,strlen(words[i]),i,k,m)){ //matching letter and word fits horizontally
							for(n=0;n<strlen(words[i]);n++){
								board[k][m-j+n] = words[i][n];
							}
							placed =1;
							words_direction[i] = 0; //save as 0 if horizontal
							words_x[i]= m-j; //save column
							words_y[i]= k; //save row
							word_placed[i]= true; //word is placed
						}
					}
				}
			}
			if(word_placed[i]){
				printf("Word %s has now been placed\n",words[i]);
			}
		}
	}

}

//Fxn that fills array of scrambled words with scrambled versions of words 
void word_scramble(char words[][boardsize],char words_scramble[][boardsize],int wordcount){
	int i;
	char temp[boardsize];
	for (i=0;i<wordcount;i++){
		strcpy(temp,words[i]);
		strfry(temp);//scramble word
		strcpy(words_scramble[i],temp);
	}
}

//Fxn to build puzzle for crosword
void build_puzzle(char board[][boardsize],char puzzle_board[][boardsize]){
	int i;
	int j;
	for (i=0;i<boardsize;i++){
		for (j=0;j<boardsize;j++){
			if (board[i][j] != '.'){
				puzzle_board[i][j] = ' ';
			}	
		}
	}
}

//Fxn to construct and print clues for crossword
void build_clues(char words_scramble[][boardsize],int words_direction[],int words_x[],int words_y[],bool word_placed[],int wordcount){
	printf("Location | Direction | Anagram\n");
	int i;
	for (i=0;i<wordcount;i++){
		if (word_placed[i]){
			printf("  %2d, ",words_y[i]);
			printf("%2d | ",words_x[i]);
			if (words_direction[i] == 1){
			printf(" Down     |");
			}
			else if (words_direction[i] == 0){
			printf(" Across   |");
			}

			printf(" %s\n", words_scramble[i]);
		}
	}
}

//Fxn to print output to a file inputted by user in command line
void print2file(char solution_board[][boardsize],char puzzle_board[][boardsize],char words_scramble[][boardsize],int words_direction[],int words_x[],int words_y[],bool word_placed[],int wordcount,char *fileout){
	FILE *fp;
	fp=fopen(fileout, "w");
	//Populate file
	int i;
	int j;
	fputs("Solution: \n",fp);

	// Displays Solution board
	for (i=-1;i<=boardsize;i++)
		fputs("-",fp);
	fputc('\n',fp);

	for(i=0;i<boardsize;i++){
		fputs("|",fp);
		for (j=0;j<boardsize;j++){
			fputc(solution_board[i][j],fp);
		}
		fputs("|",fp);
		fputc('\n',fp);

	}	
	
	for(i=-1;i<=boardsize;i++){
		fputs("-",fp);
	}
	fputc('\n',fp);
	fputc('\n',fp);
	fputs("Crossword Puzzle: \n",fp);

	// Displays Puzzle Board	
	for (i=-1;i<=boardsize;i++)
		fputs("-",fp);
	fputc('\n',fp);

	for(i=0;i<boardsize;i++){
		fputs("|",fp);
		for (j=0;j<boardsize;j++){
			fputc(puzzle_board[i][j],fp);
		}
		fputs("|",fp);
		fputc('\n',fp);

	}	
	
	for(i=-1;i<=boardsize;i++){
		fputs("-",fp);
	}
	fputc('\n',fp);
	fputc('\n',fp);
	// Display Clues
	fputs("Clues:\n",fp);
	fputs("Location | Direction | Anagram\n",fp);
	for(i=0;i<wordcount;i++){
		if (word_placed[i]){
			fprintf(fp,"  %2d, ",words_y[i]);
			fprintf(fp,"%2d | ",words_x[i]);
			if(words_direction[i] == 1){
				fprintf(fp," Down     |",fp);
			}	
			else if(words_direction[i] == 0){
				fputs(" Across   | ",fp);
			}
			
			fprintf(fp," %s",words_scramble[i]);
			fputc('\n',fp);
			

		}

	}
	fclose(fp);	
}




