#include "listsAndTreesHeader.h"
#include "sudokuHeader.h"



void main() {

   ListPlayers* activePlayers = (ListPlayers*)malloc(sizeof(ListPlayers));
    AlloCheck(activePlayers); // Check memory allocation 

    makeEmptyList(activePlayers);

   
  
    int numOfPlayers = 0, i, j, numFilled;
    short** tempBoard;
    Array*** possibilities;

    printf("Please enter number of palyers participating:");
    scanf("%d", &numOfPlayers);
    getchar(); // Consume the newline character 



    for (i = 1; i <= numOfPlayers; i++) { // Create list of active players
        char tempName[MAX_NAME_LEN];

        printf("Please insert the name of player number %d: ", i);
      

         fgets(tempName, sizeof(tempName), stdin); // Scan name
         int len = strlen(tempName);
         tempName[len-1] = '\0';
        
        char* playerName = (char*)malloc(strlen(tempName) + 1);
        AlloCheck(playerName); // Check memory allocation 
        strcpy(playerName, tempName);

    
        tempBoard = createRandomBoard(&numFilled);
        
        possibilities = PossibleDigits(tempBoard);

        insertDataToEndList(activePlayers, playerName, possibilities, tempBoard, numFilled);

       
        
    }

   
    ListNodePlayer** ptrArr = (ListNodePlayer**)malloc(numOfPlayers * sizeof(ListNodePlayer*)); 
    AlloCheck(ptrArr); // Check memory allocation 

    ListNodePlayer* activePlayersCurr = activePlayers->head;

    for ( j = 0; j < numOfPlayers; j++) { // Copy pointers
        ptrArr[j] = activePlayersCurr;
        activePlayersCurr = activePlayersCurr->next;
    }

   
        
    bubbleSortPtrArr(ptrArr, numOfPlayers); // Sort the active players according to 2 criterions

    
    int newSize = nextPowerOfTwo(numOfPlayers); // Find the new size
   

   ListNodePlayer** expandedArray = expandArray(ptrArr, numOfPlayers, newSize); // Expand the ptr Array

   
   

   Tree playersTr;
   playersTr.root = BuildTreeFromArray(expandedArray, 0, newSize - 1); // Build tree from active players

   

   free(expandedArray);

   ListPlayers winnersLst; 
   makeEmptyList(&winnersLst); // Create winners list

   while (!isEmptyList(activePlayers)) { // Itrate the tree until no more active players
       
       InOrderTraversal(playersTr.root, &winnersLst, activePlayers);
   }

  
   printWinners(winnersLst); // Print the winners

   // Free all allocated memory
    free(activePlayers);
    freeListPlayers(&winnersLst);
    freeTree(&playersTr);


   
}