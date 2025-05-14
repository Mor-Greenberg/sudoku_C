#include "listsAndTreesHeader.h"
#include "sudokuHeader.h"

void makeEmptyList(ListPlayers* lst) { // function to make an empty list
    lst->head = lst->tail = NULL;
}

bool isEmptyList(ListPlayers* lst) { // function to check if is empty list
    return (lst->head == NULL);
}


void insertDataToEndList(ListPlayers* lst, char* newName, Array*** possibilities, short** sudokuBoard, int numFilled) {
    ListNodePlayer* newTail = createNewListNode(newName, possibilities, sudokuBoard, numFilled, NULL);
    insertNodeToEndList(lst, newTail);
}
ListNodePlayer* createNewListNode(char* newName, Array*** possibilities, short** sudokuBoard, int numFilled, ListNodePlayer* next) {
    ListNodePlayer* node = (ListNodePlayer*)malloc(sizeof(ListNodePlayer));
    AlloCheck(node);

    // Allocate memory for the name and copy the string
    int len = strlen(newName);
    node->name = (char*)malloc(len + 1);
    AlloCheck(node->name); // Check memory allocation 
    strcpy(node->name, newName);
    node->name[len] = '\0';


    // Copy other data
    node->sudokuBoard = sudokuBoard; 
    node->numFilled = numFilled;
    node->possibilities = possibilities;
    node->next = next;
    return node;
}

void insertNodeToEndList(ListPlayers* lst, ListNodePlayer* newTail) {
    if (isEmptyList(lst)) {
        lst->head = lst->tail = newTail;
    }
    else {
        lst->tail->next = newTail;
        lst->tail = newTail;
    }
}


ListNodeOptions* createNewListNodeOptions(CellPosition pos, ListNodeOptions* next) {
    ListNodeOptions* node = (ListNodeOptions*)malloc(sizeof(ListNodeOptions));
    AlloCheck(node);// Check memory allocation 
    node->pos = pos;
    node->next = next;
    return node;
}

void insertNodeToEndListOptions(ListOptions* lst, ListNodeOptions* newTail) {
    if (lst->head == NULL) {
        lst->head = newTail;
        lst->tail = newTail;
    }
    else {
        lst->tail->next = newTail;
        lst->tail = newTail;
    }
}


TreeNode* createNewTNode(ListNodePlayer* player, TreeNode* left, TreeNode* right)
{

    TreeNode* res;
    if (player == NULL) {
        return NULL;
    }
    res = (TreeNode*)malloc(sizeof(TreeNode));
    AlloCheck(res);// Check memory allocation 
    res->player = player;
    res->left = left;
    res->right = right;
    return res;
}

TreeNode* BuildTreeFromArray(ListNodePlayer** sortedArray, int start, int end) {
    int mid = (start + end) / 2; // Find the middle

    if (start > end || sortedArray[mid] == NULL) {
        return NULL;  // If arr is empty, return Null
    }

    else {

        TreeNode* root = createNewTNode(sortedArray[mid], NULL, NULL);
       
        root->left = BuildTreeFromArray(sortedArray, start, mid - 1);//Iterate left side
        root->right = BuildTreeFromArray(sortedArray, mid + 1, end);//Iterate right side

        return root;
    }
   
}
int getListSize(ListOptions* list) {
    int size = 0;
    ListNodeOptions* curr = list->head;

    while (curr != NULL) {
        size++;
        curr = curr->next;
    }

    return size;

}

void RemovePlayerFromTree(TreeNode* node) { //Put NULL in the data

    if (node != NULL)
        node->player = NULL;
}

void printWinners(ListPlayers lst) { 

    ListNodePlayer* curr;

    if (!isEmptyList(&lst)) {

        printf("\n\nWINNERS LIST: \n\n");

        curr = lst.head;

        while (curr != NULL) {
            printf("Player's name: %s", curr->name);
            printf("%s's full board:\n\n", curr->name);
            sudokuPrintBoard(curr->sudokuBoard);
            printf("\n");
            curr = curr->next;
        }
    }

}
void AddPlayerToWinners(ListPlayers* winners, ListNodePlayer* player){


    if (isEmptyList(winners)) {
        winners->head = player;
        winners->tail = player;
    }
    else {
        winners->tail->next = player;
        winners->tail = player;
    }
    player->next = NULL;
}

void RemovePlayerFromList(ListPlayers* players, ListNodePlayer* toDelete) {

    if (toDelete == players->head && toDelete == players->tail) { //If toDelete is to only node
        players->head = NULL;
        players->tail = NULL;
    }
    else if (toDelete == players->head) {//Remove from head
        ListNodePlayer* temp = players->head->next;
        players->head = temp;
        
    }
    else if (toDelete == players->tail) { //Remove from tail
        ListNodePlayer* temp = players->head;
        while (temp != NULL && temp->next != toDelete) 
            temp = temp->next;
        if (temp != NULL) { 
            temp->next = NULL;
            players->tail = temp; // update tail
           
        }

    }
    else { // Remove from middle

        ListNodePlayer* curr = players->head;
        while (curr != NULL && curr->next != toDelete) 
            curr = curr->next;
        if (curr != NULL && curr->next != NULL) {
            ListNodePlayer* after = curr->next->next;
            curr->next = after;
            
        }
    }


}
ListNodeOptions* getNodeAt(ListNodeOptions* head, int index) { // Function to find node in list
    ListNodeOptions* curr = head;

    while (curr != NULL && index-- > 0) {
        curr = curr->next;
    }
    return curr;
}

void removeNodeFromListOptions(ListOptions* lst, ListNodeOptions* node) {
    if (node == lst->head) {
        lst->head = lst->head->next;
    }
    else {
        ListNodeOptions* prev = lst->head;
        while (prev->next != node) {
            prev = prev->next;
        }
        prev->next = node->next;
    }
    free(node);
}

//Free functions

void freeListPlayers(ListPlayers* list) {
    ListNodePlayer* current = list->head;
    ListNodePlayer* next;

    while (current != NULL) {
        next = current->next;
        freeResources(current->sudokuBoard, current->possibilities, current->name);
        free(current);
        current = next;
    }
}


void freeListOptions(ListOptions* lst) {
    ListNodeOptions* curr = lst->head;
    while (curr != NULL) {
        ListNodeOptions* temp = curr;
        curr = curr->next;
        free(temp);
    }
    lst->head = NULL;
    lst->tail = NULL;
}



void freeTreeNode(TreeNode* node) {
    if (node != NULL) {
        if (node->player != NULL) {
            freeResources(node->player->sudokuBoard, node->player->possibilities, node->player->name);
            free(node->player); 
        }
        freeTreeNode(node->left);  
        freeTreeNode(node->right); 
        free(node); 
    }
}

void freeTree(Tree* tree) {
    if (tree != NULL && tree->root != NULL) {
        freeTreeNode(tree->root);
       
    }
}
