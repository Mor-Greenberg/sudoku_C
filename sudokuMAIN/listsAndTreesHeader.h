#ifndef LISTS_AND_TREES_HEADER_H
#define LISTS_AND_TREES_HEADER_H

#include "sudokuHeader.h"
#include <stdbool.h>




// Function Declarations
//List functions
void makeEmptyList(ListPlayers* lst);
bool isEmptyList(ListPlayers* lst);
void insertDataToEndList(ListPlayers* lst, char *newName, Array*** possibilities, short **sudokuBoard, int numFilled); 
void insertNodeToEndListOptions(ListOptions* lst, ListNodeOptions* newTail);
ListNodePlayer* createNewListNode(char* newName, Array*** possibilities, short** sudokuBoard, int numFilled, ListNodePlayer* next);
ListNodeOptions* createNewListNodeOptions(CellPosition pos, ListNodeOptions* next);
void insertNodeToEndList(ListPlayers* lst, ListNodePlayer* newTail);
int getListSize(ListOptions* list);
void printWinners(ListPlayers lst);
void AddPlayerToWinners(ListPlayers* winners, ListNodePlayer* player);
void RemovePlayerFromList(ListPlayers* players, ListNodePlayer* toDelete);
void removeNodeFromListOptions(ListOptions* lst, ListNodeOptions* node);
ListNodeOptions* getNodeAt(ListNodeOptions* head, int index);


//Tree functions
TreeNode* BuildTreeFromArray(ListNodePlayer** sortedArray, int start, int end);
TreeNode* createNewTNode(ListNodePlayer* player, TreeNode* left, TreeNode* right);
void RemovePlayerFromTree(TreeNode* node);


//Free functions
void freeListPlayers(ListPlayers* list);
void freeTreeNode(TreeNode* node);
void freeTree(Tree* tree);
void freeListOptions(ListOptions* lst);





#endif // LISTS_AND_TREES_HEADER_H
