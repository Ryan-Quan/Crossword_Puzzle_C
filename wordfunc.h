/* Ryan Quan
 * CSE 20311
 * Lab 8
 * Crossword */

#include <stdbool.h>

//import boardsize global variable 
extern int boardsize;



void fill_solution(char solution_board[][boardsize]);
void fill_puzzle(char puzzle_board[][boardsize]);
void display_board(char board[][boardsize]);
int read_cmd(char words[][boardsize]);
int read_file(char words[][boardsize],char *filename);
void upper2lower(char word[]);
bool lettersonly(char string[]);
void lengthsort(char words[][boardsize],int wordcount);
bool vertical_fit(char board[][boardsize],int wordlength,int n,int y,int x);
bool horizontal_fit(char board[][boardsize],int wordlength,int n,int y,int x); 
void build_solution(char board[][boardsize],char words[][boardsize],int words_direction[],int words_x[],int words_y[],bool word_placed[], int wordcount);
void build_puzzle(char board[][boardsize],char puzzle_board[][boardsize]);
void word_scramble(char words[][boardsize],char words_scramble[][boardsize],int wordcount);
void build_clues(char words_scramble[][boardsize], int words_direction[], int words_x[], int words_y[],bool word_placed[], int wordcount);
void print2file(char solution_board[][boardsize],char puzzle_board[][boardsize],char words_scramble[][boardsize],int words_direction[],int words_x[],int words_y[],bool word_placed[],int wordcount,char *fileout);
