#ifndef SUDOKUHEADER_H
#define SUDOKUHEADER_H
#define _CRT_SECURE_NO_WARNINGS

#include "listsAndTreesHeader.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#define BASE_SIZE 9
#define SQUARE_SIZE 3
#define EMPTY_CELL -1
#define MAX_NAME_LEN 100
#define FINISH_SUCCESS 1
#define NOT_FINISH 4
#define FINISH_FAILURE -3
#define FILLED 2
#define FAIL -2



typedef struct _Array
{
    short* arr;
    unsigned short size;
} Array;

typedef struct listNodePlayer {
    char* name;
    short** sudokuBoard;
    Array*** possibilities;
    int numFilled;
    struct listNodePlayer* next;
}ListNodePlayer;

typedef struct listPlayers
{
    ListNodePlayer* head;
    ListNodePlayer* tail;
}ListPlayers;

typedef struct cellPosition {
    int row;
    int col;
} CellPosition;

typedef struct listNodeOptions {  
    CellPosition pos;
    struct listNodeOptions* next; 
} ListNodeOptions;


typedef struct listOptions
{
    ListNodeOptions* head;
    ListNodeOptions* tail;
}ListOptions;

typedef struct treeNode {
    ListNodePlayer* player;
    struct treeNode* left;  
    struct treeNode* right;
} TreeNode;

typedef struct tree {

    struct treeNode* root;

} Tree;


// first question
Array*** PossibleDigits(short** sudokuBoard);


// Second question
int OneStage(short** board, Array*** possibilities, int* x, int* y);
void updatePossibilities(short** board, Array*** possibilities, int row, int col);

// Third question
int FillBoard(short** board, Array*** possibilities);

//The course of the program
void InOrderTraversal(TreeNode* root, ListPlayers* winners, ListPlayers* active);

//Rndom board
short** allocateAndInitializeBoard();
void initializeAvailableCells(ListOptions* availableCells);
void fillRandomCells(short** board, ListOptions* availableCells, Array*** possibilities, int N);
short** createRandomBoard(int* numFilled);



//Additional functions
void AlloCheck(void* ptr);
void sudokuPrintBoard(short** board);
void bubbleSortPtrArr(ListNodePlayer** ptrArr, int size);
void swap(ListNodePlayer** a, ListNodePlayer** b);
int nextPowerOfTwo(int x);
ListNodePlayer** expandArray(ListNodePlayer** sortedArray, int size, int newSize);
void removeFromArray(Array* array, short num);
bool isBoardComplete(short** board);
bool isPossible(short** board, int row, int col, int myNum);



//Free functions

void freeBoard(short** board);
void freeResources(short** board, Array*** possibilities, char* name);
void freePossibilities(Array*** possibilities);

#endif // SUDOKUHEADER_H

