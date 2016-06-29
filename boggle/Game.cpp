#define GAME_CPP

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "types.h"
#include "Boggle.h"
#include "Dictionary.h"
#include "List.h"
#include "game.h"
#include "Trie.h"
#include "dice.h"

/* Global Variables */

/*Debug GameBoard
char8_t gameBoard[NUM_ROWS][NUM_COLS] = { { 'R', 'E', 'Q', 'S', 'T' },
										  { 'N', 'C', 'E', 'Y', 'N' },
										  { 'U', 'Y', 'N', 'H', 'O' },
										  { 'L', 'U', 'Y', 'I', 'R' },
										  { 'E', 'I', 'U', 'L', 'Q' } };
*/

char8_t gameBoard[NUM_ROWS][NUM_COLS];
int32_t randomDice[NUM_DICE];
bool traverseMap[NUM_ROWS][NUM_COLS];
extern TrieNode *rootNode;

void resetGame()
{
	//Reset the is Visited flag on the nodes of the Trie
	TrieResetIsVisited(rootNode);
}

void initGame()
{
	//Initializes the die and resets the traverseMap
	for (int32_t i = 0,j =0, k=0; i < NUM_DICE; i++)
	{
		randomDice[i] = i;

		traverseMap[j][k] = false;
		k++;
		if (k > NUM_COLS)
		{
			j++;
			k = 0;
		}
	}

	//Shuffle the dice so that we have them in a random order
	for (int32_t i = NUM_DICE-1; i >= 0; i--)
	{
		int32_t j = (int32_t)rangedRandom(0, i);

		int32_t temp = randomDice[i];
		randomDice[i] = randomDice[j];
		randomDice[j] = temp;
	}
}		

void buildRandomBoard()
{
#if BIG_BOGGLE
	char8_t gameDice[NUM_DICE][7] = {DIE1, DIE2, DIE3, DIE4, DIE5, DIE6, DIE7, DIE8, DIE9, DIE10, DIE11, DIE12, DIE13, DIE14, DIE15, DIE16, DIE17, DIE18, DIE19, DIE20, DIE21, DIE22, DIE23, DIE24, DIE25};
#else
	char8_t gameDice[NUM_DICE][7] = { DIE1, DIE2, DIE3, DIE4, DIE5, DIE6, DIE7, DIE8, DIE9, DIE10, DIE11, DIE12, DIE13, DIE14, DIE15, DIE16};
#endif
	uint32_t diceNumberIndex;
	uint32_t diceLetterIndex;

	for (uchar8_t i = 0, k=0 ; i < NUM_ROWS ; i++)
	{
		for (uchar8_t j = 0; j < NUM_COLS; j++)
		{
			diceLetterIndex = rangedRandom(0, 5);
			diceNumberIndex = randomDice[k];

			gameBoard[i][j] = gameDice[diceNumberIndex][diceLetterIndex];
			k++;
		}
	}
}

void printBoard()
{
#if DEBUG_PRINTING_ON

	for (int32_t i = 0; i < NUM_ROWS; i++)
	{
		for (int32_t j = 0; j < NUM_COLS; j++)
		{
			printf("%c ", gameBoard[i][j]);
		}
		printf("\n");
	}
#endif
}

//This is the starter function used to print all the words in alphabetical order
void printWords()
{
#if DEBUG_PRINTING_ON
	TriePrintWords(rootNode, true);
#endif
}


/* The following global variables are used in the TraverseBoard 
function*/

char8_t word[MAX_CHARS_IN_DICTIONARY_WORD];
int32_t currIndex;
TrieNode *currNode = NULL;

/* This function traverses through the game board letter by letter recursively. 
   Along with the letter in the board, a node in the Trie is also traversed to check if the
   path exists.*/

void TraverseBoard(int32_t row, int32_t column)
{
	int32_t childIndex = gameBoard[row][column] - 'A';

	word[currIndex++] = gameBoard[row][column];
	word[currIndex] = '\0';
	traverseMap[row][column] = true;

	//The path does not exist in the Trie
	if (currNode->childNode[childIndex] == NULL)
	{
		traverseMap[row][column] = false;
		currIndex--;
		word[currIndex] = '\0';
		return;
	}
	else
	{
		currNode = currNode->childNode[childIndex];

		//Handle the Q die as if its a QU Die
		if (currNode->nodeChar == 'Q')
		{
			if (currNode->childNode['U' - 'A'])
			{
				currNode = currNode->childNode['U' - 'A'];
				word[currIndex++] = 'U';
				word[currIndex] = '\0';
				currNode->isQpresent = true;
			}
		}
	}

	/* Check if the current node is a terminal node. If so,
	mark all its parent nodes as visited. This can be used
	later to print the words that are found */
	if (currNode && 
		(currNode->isTerminal) && 
		(strlen(word) > 3) )
	{
		TrieNode *tempNode = currNode;
		bool8_t print = false;

		while (tempNode && (tempNode != rootNode))
		{
			if (tempNode && !(tempNode->isVisited) )
			{
				tempNode->isVisited = true;
				print = true;
			}
			tempNode = tempNode->parentNode;
		}
		if (print)
		{
		//	printf("word Found = %s\n", word);
		}
	}

	//Traverse North
	if (((row - 1) >= 0) &&
		((row - 1) < NUM_ROWS) &&
		((column) >= 0) &&
		((column) < NUM_COLS) &&
		(!traverseMap[(row-1)][(column)]))
		TraverseBoard(row - 1, column);

	//Traverse NorthEast
	if (((row - 1) >= 0) &&
		((row - 1) < NUM_ROWS) &&
		((column + 1) >= 0) &&
		((column + 1) < NUM_COLS) &&
			(!traverseMap[(row-1)][(column+1)]) )
		TraverseBoard(row - 1, column + 1);

	//Traverse East
	if (((row) >= 0) &&
		((row) < NUM_ROWS) &&
		((column + 1) >= 0) &&
		((column + 1) < NUM_COLS) && 
		(!traverseMap[row][(column + 1)]) )
		TraverseBoard(row, column + 1);

	//Traverse SouthEast
	if (((row + 1) >= 0) &&
		((row + 1) < NUM_ROWS) &&
		((column + 1) >= 0) &&
		((column + 1) < NUM_COLS) && 
		(!traverseMap[(row+1)][(column+1)]))
		TraverseBoard(row + 1, column + 1);

	//Traverse South
	if (((row + 1) >= 0) &&
		((row + 1) < NUM_ROWS) &&
		((column) >= 0) &&
		((column) < NUM_COLS) && 
		(!traverseMap[(row+1)][(column)]))
		TraverseBoard(row + 1, column);

	//Traverse SouthWest
	if (((row + 1) >= 0) &&
		((row + 1) < NUM_ROWS) &&
		((column - 1) >= 0) &&
		((column - 1) < NUM_COLS) && 
		(!traverseMap[(row+1)][(column-1)]))
		TraverseBoard(row + 1, column - 1);

	//Traverse West
	if (((row) >= 0) &&
		((row) < NUM_ROWS) &&
		((column - 1) >= 0) &&
		((column - 1) < NUM_COLS) &&
		(!traverseMap[(row)][(column-1)]) )
		TraverseBoard(row, column - 1);

	//Traverse South West
	if (((row - 1) >= 0) &&
		((row - 1) < NUM_ROWS) &&
		((column - 1) >= 0) &&
		((column - 1) < NUM_COLS) && 
		(!traverseMap[(row-1)][(column-1)]) )
		TraverseBoard(row - 1, column - 1);

	/* Check if the current node is the 'U' node added
	   after the 'Q' node. If so, pop it */
	if (currNode && currNode->isQpresent)
	{
		currNode = currNode->parentNode;
		currNode->isQpresent = false;
		currIndex--;
		word[currIndex] = '\0';
	}

	// Mark the current node as not traversed and go back to the parent node
	traverseMap[row][column] = false;
	currIndex--;
	word[currIndex] = '\0';
	currNode = currNode->parentNode;

}


void searchForWords()
{
	for (int32_t i = 0; i < NUM_ROWS; i++)
	{
		for (int32_t j = 0; j < NUM_COLS; j++)
		{
			currIndex = 0;
			currNode = rootNode;
			TraverseBoard(i, j);
		}
	}
}

int32_t rangedRandom(int32_t min, int32_t max)
{
	int32_t range;

	if (min == max)
		return min;

	range = max - min;

	return min + rand() % (range + 1);
}