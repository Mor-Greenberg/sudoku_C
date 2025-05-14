#include "listsAndTreesHeader.h"
#include "sudokuHeader.h"

void AlloCheck(void* ptr) { // cheack memory alloctions

	if (ptr == NULL) {
		printf("memory allocation failed");
		exit(1);
	}
}


// first question

Array*** PossibleDigits(short** sudokuBoard) {


	int i, j, k;
	Array*** resArray;
	resArray = (Array***)malloc(BASE_SIZE * sizeof(Array**));
	AlloCheck(resArray); // Check memory allocation 

	for (i = 0; i < BASE_SIZE; i++) {
		resArray[i] = (Array**)malloc(BASE_SIZE * sizeof(Array*));
		AlloCheck(resArray[i]); // Check memory allocation 
		for (j = 0; j < BASE_SIZE; j++) {
			if (sudokuBoard[i][j] != EMPTY_CELL) {
				resArray[i][j] = (Array*)malloc(sizeof(Array)); // Allocate memory for each cell
				AlloCheck(resArray[i][j]);// Check memory allocation 
				resArray[i][j]->size = 0;
				resArray[i][j]->arr = NULL;
			}
			else {
				short temp[BASE_SIZE];
				unsigned short count = 0;

				for (k = 1; k <= BASE_SIZE; k++) { //Iterate 1-9 and check if valid
					if (isPossible(sudokuBoard, i, j, k)) {
						temp[count++] = k;
					}
				}

				resArray[i][j] = (Array*)malloc(sizeof(Array));
				AlloCheck(resArray[i][j]); // Check memory allocation 
				resArray[i][j]->arr = (short*)malloc(count * sizeof(short));
				AlloCheck(resArray[i][j]->arr);// Check memory allocation 

				resArray[i][j]->size = count; //Update arr size

				for (int l = 0; l < count; l++) {
					resArray[i][j]->arr[l] = temp[l]; // copy from temp
				}


				
			}
		}


		
	}

	return resArray;
}


bool isPossible(short** board, int row, int col, int myNum) {
	int k, i, j, m;
	int startRow = (row / SQUARE_SIZE) * SQUARE_SIZE;
	int startCol = (col / SQUARE_SIZE) * SQUARE_SIZE;

	for (k = 0; k < BASE_SIZE; k++) { // Check row
		if (board[row][k] == myNum) {
			return false;
		}
	}
	for (i = 0; i < BASE_SIZE; i++) { //Check col
		if (board[i][col] == myNum) {
			return false;
		}
	}
	for (m = 0; m < SQUARE_SIZE; m++) { //Check square
		for (j = 0; j < SQUARE_SIZE; j++) {
			if (board[startRow + m][startCol + j] == myNum) {
				return false;
			}
		}
	}
	return true;
}

// Second question
int OneStage(short** board, Array*** possibilities, int* x, int* y)
{
	int i, j;
	int minOptions = BASE_SIZE + 1;
	int minRow = -1, minCol = -1;
	bool cellFilled;

	do {
		cellFilled = false;
		

		for (i = 0; i < BASE_SIZE; i++)
		{
			for (j = 0; j < BASE_SIZE; j++)
			{
				if (isBoardComplete(board))
				{
					return FINISH_SUCCESS;
				}

				if (board[i][j] == EMPTY_CELL)
				{
					if (possibilities[i][j] == NULL)
					{
						return FINISH_FAILURE;
					}

					if (possibilities[i][j]->size == 1)
					{
						board[i][j] = possibilities[i][j]->arr[0];
						updatePossibilities(board, possibilities, i, j);

						cellFilled = true;
						break;  // Break the inner loop to restart from the beginning
					}
					else if (possibilities[i][j] != NULL && possibilities[i][j]->size < minOptions)
					{
						minOptions = possibilities[i][j]->size;
						minRow = i;
						minCol = j;
					}
				}
			}
			if (cellFilled) break;  // Break the outer loop if a cell was filled
		}
	} while (cellFilled);  // Keep looping as long as we're filling cells


	if (minRow != -1)
	{
		*x = minRow;
		*y = minCol;
		return NOT_FINISH;
	}

	return FINISH_FAILURE;
}

void updatePossibilities(short** board, Array*** possibilities, int row, int col) {
	int i, j, blockRowStart, blockColStart;
	short val = board[row][col];

	// Update the possibilities for the row
	for (i = 0; i < BASE_SIZE; i++) {
		if (i != col && possibilities[row][i] != NULL) {
			removeFromArray(possibilities[row][i], val);
			// If no possibilities are left, set to NULL
			if (possibilities[row][i]->size == 0) {
				free(possibilities[row][i]->arr);
				free(possibilities[row][i]);
				possibilities[row][i] = NULL;
			}
		}
	}

	// Update the possibilities for the column
	for (i = 0; i < BASE_SIZE; i++) {
		if (i != row && possibilities[i][col] != NULL) {
			removeFromArray(possibilities[i][col], val);
			// If no possibilities are left, set to NULL
			if (possibilities[i][col]->size == 0) {
				free(possibilities[i][col]->arr);
				free(possibilities[i][col]);
				possibilities[i][col] = NULL;
			}
		}
	}

	// Update the possibilities for the 3x3 block
	blockRowStart = (row / 3) * 3;
	blockColStart = (col / 3) * 3;

	for (i = blockRowStart; i < blockRowStart + 3; i++) {
		for (j = blockColStart; j < blockColStart + 3; j++) {
			if ((i != row || j != col) && possibilities[i][j] != NULL) {
				removeFromArray(possibilities[i][j], val);
				// If no possibilities are left, set to NULL
				if (possibilities[i][j]->size == 0) {
					free(possibilities[i][j]->arr);
					free(possibilities[i][j]);
					possibilities[i][j] = NULL;
				}
			}
		}
	}
}



bool isBoardComplete(short** board) {
	int i, j;
	for (i = 0; i < BASE_SIZE; i++) {
		for (j = 0; j < BASE_SIZE; j++) {
			if (board[i][j] == EMPTY_CELL) {
				return false;
			}
		}
	}
	
	return true;
}

void removeFromArray(Array* array, short num) {
	int i, j;
	for (i = 0; i < array->size; i++) {
		if (array->arr[i] == num) {
			// Shift all elements after the found number to the left
			for (j = i; j < array->size - 1; j++) {
				array->arr[j] = array->arr[j + 1];
			}
			array->size--;
			if (array->size > 0) {
				array->arr = (short*)realloc(array->arr, array->size * sizeof(short)); // Resize the array
				AlloCheck(array->arr);
				break;
			}
			
		}
	}
}

// Third question

int FillBoard(short** board, Array*** possibilities) {
	int x, y;
	int status;
	int userChoice;
	bool boardCompleted = false;

	while (!boardCompleted) {
		status = OneStage(board, possibilities, &x, &y);

		if (status == FINISH_SUCCESS) {
			// Board successfully filled
			
			return FILLED;
		}
		else if (status == FINISH_FAILURE) {
			// Invalid board state detected
			printf("User's selections led to duplications.\n");
	        
			return FAIL;
		}
		else if (status == NOT_FINISH) {
			// Board is not yet complete, need user input
		
			if (possibilities[x][y]->size == 0) {
				printf("User's selections led to duplications.\n");

				return FAIL;
			}

			if (possibilities[x][y]->size > 1) {

				sudokuPrintBoard(board);

				// Allow user to choose a number for the cell with minimum possibilities
				printf("Cell number [%d,%d] currently holds the minimum number of possible values, select one of the below :\n", x,y);

				for (int j = 1; j <= possibilities[x][y]->size; j++) {
					printf("%d. %d\n", j, possibilities[x][y]->arr[j - 1]);
				}
				
				scanf("%d", &userChoice);


				printf("Updating cell [%d, %d] with value %d\n", x,y, userChoice);


				// Validate user choice is in the list of possible numbers
				bool validChoice = false;
				for (int i = 0; i < possibilities[x][y]->size; i++) {
					if (possibilities[x][y]->arr[i] == userChoice) {
						validChoice = true;
						break;
					}
				}

				if (validChoice) {
					board[x][y] = userChoice;
					free(possibilities[x][y]->arr); // Free the old possibilities
					possibilities[x][y]->arr = NULL; // Ensure we don't access it later
					possibilities[x][y]->size = 0; // Reset size
					updatePossibilities(board, possibilities, x, y);
					boardCompleted = isBoardComplete(board);
				}
				else {
					printf("Invalid choice! \n");
					return FAIL;
				}
			}
			
		}
	}
	
	return FILLED;
}


// Print function
void sudokuPrintBoard(short** board) {
	printf("\n\n");
	// Print the column headers with extra vertical separators at the start
	printf("  |");
	for (int col = 0; col < BASE_SIZE; col++) {
		printf(" %d", col);

		// Add vertical separators after columns 2 and 5
		if (col == 2 || col == 5) {
			printf("|");
		}
	}
	printf("\n-----------------------\n");

	for (int row = 0; row < BASE_SIZE; row++) {
		// Print the row number
		printf(" %d|", row);

		for (int col = 0; col < BASE_SIZE; col++) {
			// Print vertical separator every 3 columns (adjusted positions)
			if (col % SQUARE_SIZE == 0 && col != 0) {
				printf("|");
			}

			// Print the cell value or a space for an empty cell
			if (board[row][col] == EMPTY_CELL) {
				printf("  ");  // Two spaces for an empty cell
			}
			else {
				printf(" %d", board[row][col]);  // Single space before the number
			}
		}
		printf("\n");

		// Print horizontal separator every 3 rows
		if (row % SQUARE_SIZE == 2 && row != BASE_SIZE - 1) {
			printf("-----------------------\n");
		}
	}
	printf("-----------------------\n\n\n");  // Final horizontal separator
}



	
// Random board functions
	short** createRandomBoard(int* numFilled) {
		short** board;
		ListOptions availableCells;
		availableCells.head = availableCells.tail = NULL; //make empty list
		Array*** possibilities;
		int N;

		srand((unsigned int)time(NULL)); // Set random starting value

		// Step 1: Allocate and initialize the board
		board = allocateAndInitializeBoard();

	
		// Step 2: Initialize the list of available cells
		initializeAvailableCells(&availableCells);

		

		// Step 3: Generate the number of cells to fill (between 1 and 20)
		N = 1 + rand() % 20;
		
		*numFilled = N;


		// Step 4: Get the possibilities for each cell
		possibilities = PossibleDigits(board);
		
		if (possibilities == NULL) {
			//freeResources(board, &availableCells, possibilities);
			return NULL;
		}

		// Step 5: Fill random cells with legal values
		fillRandomCells(board, &availableCells, possibilities, N);

		
		freeListOptions(&availableCells); 
		return board;
	}

	short** allocateAndInitializeBoard() { // Allocate sudoku board
		short** board = (short**)malloc(BASE_SIZE * sizeof(short*));
		AlloCheck(board);// Check memory allocation 

		for (int i = 0; i < BASE_SIZE; i++) {
			board[i] = (short*)malloc(BASE_SIZE * sizeof(short));
			AlloCheck(board[i]);// Check memory allocation 

			// Initialize all cells with EMPTY_CELL
			for (int j = 0; j < BASE_SIZE; j++) {
				board[i][j] = EMPTY_CELL;
			}

			
		}

		
		return board;
	}


	
	void initializeAvailableCells(ListOptions* availableCells) { // Function to initialize the list of available cells
		
		for (int i = 0; i < BASE_SIZE; i++) {
			for (int j = 0; j < BASE_SIZE; j++) {
				CellPosition pos;
				pos.row = i;
				pos.col = j;
				ListNodeOptions* newNode = createNewListNodeOptions(pos, NULL);
				insertNodeToEndListOptions(availableCells, newNode);
			}
		}
	}

	void fillRandomCells(short** board, ListOptions* availableCells, Array*** possibilities, int N) {	// Function to fill random cells with legal values

		for (int i = 0; i < N; i++) {
			int listSize = getListSize(availableCells);
			if (listSize == 0)
				break; // No more available cells

			int K = rand() % listSize;
			ListNodeOptions* chosenNode = getNodeAt(availableCells->head, K);
			CellPosition chosenCell = chosenNode->pos;

			// Remove the chosen node from the list
			removeNodeFromListOptions(availableCells, chosenNode);

			// Generate a random legal value for the chosen cell
			int legalValuesCount = possibilities[chosenCell.row][chosenCell.col]->size;


			if (legalValuesCount > 0) {
				int randomIndex = rand() % legalValuesCount;
				short chosenValue = possibilities[chosenCell.row][chosenCell.col]->arr[randomIndex];

				board[chosenCell.row][chosenCell.col] = chosenValue;

				// Update the possibilities for the entire board after placing the value
				updatePossibilities(board, possibilities, chosenCell.row, chosenCell.col);
			}
		
		}
	}

	

	void bubbleSortPtrArr(ListNodePlayer** ptrArr, int size) { // Function to sort array acordding to 2 criterions
		int i, j;

		for (i = 0; i < size; i++) {
			for (j = 0; j < size - i - 1; j++) {

				if (ptrArr[j]->numFilled > ptrArr[j + 1]->numFilled) {// Primary criterion: compare the number of filled cells

					swap(&ptrArr[j], &ptrArr[j + 1]);
				}
				else if (ptrArr[j]->numFilled == ptrArr[j + 1]->numFilled) {// Secondary criterion: compare the names lexicographically if the number of filled cells is the same

					if (strcmp(ptrArr[j]->name, ptrArr[j + 1]->name) > 0) {
						swap(&ptrArr[j], &ptrArr[j + 1]);
					}
				}
					
			}
		}
	}

	void swap(ListNodePlayer** a, ListNodePlayer** b) {
		ListNodePlayer* temp = *a;
		*a = *b;
		*b = temp;
	}


	int nextPowerOfTwo(int x) { // Find the array size
		int res;
		double logCalc, logRoundUp;

		logCalc = log2((double)x + 1);
		logRoundUp = ceil(logCalc); //calculating the log and round it up

		res = ((int)pow(2, logRoundUp)) - 1; //casting and calculating the res size

		return res;
	}

	ListNodePlayer** expandArray(ListNodePlayer** sortedArray, int size, int newSize) {


		ListNodePlayer** newArray = (ListNodePlayer**)malloc(newSize * sizeof(ListNodePlayer*));
		AlloCheck(newArray);
		for (int j = 0; j < size; j++) {

			newArray[j] = sortedArray[j];
		}
		for (int i = size; i < newSize; i++) { // Null in the new array cells
			
			newArray[i] = NULL;
		}

		return newArray;
	}

	
	


	void InOrderTraversal(TreeNode* root, ListPlayers* winners, ListPlayers* active) {
		if (root == NULL ) {
			return;
		}
		if (root->left != NULL) { //Iterate left side
			InOrderTraversal(root->left, winners, active);
		}
		

		if (root->player != NULL) {
			int res = FillBoard(root->player->sudokuBoard, root->player->possibilities); // The player in root plays
			if (res == FILLED) {
				AddPlayerToWinners(winners, root->player);
				RemovePlayerFromList(active, root->player);
				RemovePlayerFromTree(root);
			}
			else if (res == FAIL) {

				RemovePlayerFromList(active, (ListNodePlayer*)root->player);
				RemovePlayerFromTree(root);
			}


			
		}
		if (root->right != NULL) { //Iterate right side
			InOrderTraversal(root->right, winners, active);
		}

	}

	//Free functions

	void freeResources(short** board, Array*** possibilities, char* name) { 	// Function to free all resources (board, possibilities, name)

		freeBoard(board);
		freePossibilities(possibilities);
		free(name);
	}

	void freePossibilities(Array*** possibilities) {
		int i, j;

		if (possibilities == NULL)
			return;

		for (i = 0; i < BASE_SIZE; i++) {
			for (j = 0; j < BASE_SIZE; j++) {
				if (possibilities[i][j] != NULL) {
					if (possibilities[i][j]->arr != NULL) {
						free(possibilities[i][j]->arr);
					}
					free(possibilities[i][j]);
				}
			}
			free(possibilities[i]);
		}
		free(possibilities);
	}

	void freeBoard(short** board) {
		for (int i = 0; i < BASE_SIZE; i++) {
			free(board[i]);  // Free each row
		}
		free(board);  // Free the array of pointers (the board itself)
	}