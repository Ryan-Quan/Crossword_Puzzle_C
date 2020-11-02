/* Ryan Quan
 * CSE 20311
 * Lab 8
 * Crossword */

#include <stdio.h>
#include <stdbool.h>
#include "wordfunc.h"

int boardsize = 15;//global variable for board size
int maxarray=20;
int maxfilename=256;

// MAIN

int main(int argc,char *argv[]){

// Initialize Variables

	char solution_board[boardsize][boardsize];//board to contain solutions
	char puzzle_board[boardsize][boardsize];//board to contain puzzle
	char words[maxarray][boardsize]; // array to store words
	char words_scramble[maxarray][boardsize];//array to store scrambled words
	int words_direction[maxarray];//array to save direction of words
	int words_x[maxarray]; //array to save x location of words
	int words_y[maxarray]; //array to save y location of words
	bool word_placed[maxarray];//array of boolean values to store whether or not word has been placed
	int wordcount;//used to retrieve #of words entered by user	
	char *filein[maxfilename];//pointer to 
	char *fileout[maxfilename];

	fill_solution(solution_board);
	fill_puzzle(puzzle_board);

	
//Interactive Mode

	if(argc == 1){ // Execute if one command line argument (executable)
		wordcount=read_cmd(words);//read in words and #of words from cmd line
		lengthsort(words,wordcount);//sort words by length
		word_scramble(words,words_scramble,wordcount);//fill array of scrambled words
		build_solution(solution_board,words,words_direction,words_x,words_y,word_placed,wordcount);//build solution to crossword
		printf("\n");
		printf("Solution: \n");
		display_board(solution_board);//print solution board
		printf("\n");
		printf("\n");
		printf("Crossword Puzzle: \n");
		build_puzzle(solution_board,puzzle_board);//construct puzzle board based on solution board
		display_board(puzzle_board);// print puzzle board
		printf("\n");
		printf("Clues:\n");
		printf("\n");
		build_clues(words_scramble,words_direction,words_x,words_y,word_placed,wordcount);//construct and display clues
		printf("\n");
	}

// Command Line input from file containing the words, with standard output

	else if(argc == 2){ // Execute if two command line arguments (including input file)
		*filein = argv[1]; // save 2nd argument from command line to pointer
		wordcount = read_file(words,*filein);// read in words and # of words from file
		lengthsort(words,wordcount);//sort words by length
		word_scramble(words,words_scramble,wordcount);//fill array of scrambled words
		build_solution(solution_board,words,words_direction,words_x,words_y,word_placed,wordcount);//build crossword solution
		printf("\n");
		printf("Solution: \n");
		display_board(solution_board);//display solution board
		printf("\n");
		printf("\n");
		printf("Crossword Puzzle: \n");
		build_puzzle(solution_board,puzzle_board);//build puzzle board
		display_board(puzzle_board);//display puzzle board
		printf("\n");
		printf("Clues:\n");
		printf("\n");
		build_clues(words_scramble,words_direction,words_x,words_y,word_placed,wordcount);//construct and display clues
		printf("\n");
	}

// Command Line input from a file and command line output to another file

	else if(argc == 3){ // Execute if three command line arguments (including input file and output file)
		*filein = argv[1]; //save 2nd argument from command line to pointer (input file)
		*fileout = argv[2]; //saves third argument from command line to pointer (output file)
		wordcount= read_file(words,*filein); // read in words and # of words from input file
		lengthsort(words,wordcount); // sort words by length 
		word_scramble(words,words_scramble,wordcount); //fill array of scrambled words
		build_solution(solution_board,words,words_direction,words_x,words_y,word_placed,wordcount);//construct crossword solution
		build_puzzle(solution_board,puzzle_board); // build crossword puzzle
		print2file(solution_board,puzzle_board,words_scramble,words_direction,words_x,words_y,word_placed,wordcount,*fileout); //prints output to file specified in command line by user
	


	}

	else {
		printf("Invalid number of arguments in command line \n");
		return 1;
	}
	return 0;
}

