/* The following file contains all the helper functions necessary a Trie Data Structure.
  The Trie Data structure is a N-ary tree where at each node a letter is stored and the node
  can have 26 possible children. For example the words QUOTE and QUESTION are saved in the Trie as
  follows.  
  
   rootNode -> Q -> U -> O -> T -> E
			          -> E -> S -> T -> I -> O -> N
  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "List.h"
#include "dice.h"
#include "Trie.h"
#include "Boggle.h"

#define NUM_ALPHABETS 26
#define MAX_WORD_LEN 32
#define MIN_WORD_LEN 4

/* This function initializes the individual Trie Nodes before they are inserted */
void TrieNodeInit(TrieNode *node)
{
	if (node == NULL)
	{
		printf("Major Erro: Trying to initialize an Empty node");
		return;
	}
	for (int i = 0; i < NUM_ALPHABETS; i++)
		node->childNode[i] = NULL;

	node->nodeChar = 0;
	node->parentNode = NULL;
	node->isTerminal = false;
	node->isVisited = false;
	node->isQpresent = false;
}

/* This function reads a word and inserts it into the Trie Data structure character by character */
void TrieAdd(TrieNode *rootNode, char8_t *word)
{
	TrieNode *currNode = rootNode;
	TrieNode *childNode;
	int childIndex;
	int i = 0;

	int len = strlen(word);

	if (len < 4)
	{
		return;
	}

	while (word[i] != '\n')
	{
		if (!(word[i] >= 'A') ||
			!(word[i] <= 'Z'))
		{
			i++;
			continue;
		}

		childIndex = word[i] - 'A';

		if (currNode && currNode->childNode[childIndex])
		{
			//We already have a node so do nothing here
			currNode = currNode->childNode[childIndex];
		}
		else
		{
			//Allocate memory and add  a new node here
			childNode = (TrieNode *)malloc(sizeof(TrieNode));

			if (!childNode)
			{
				printf("Major Error: Unable to allocate memory for child node");
				return;
			}
			TrieNodeInit(childNode);
			childNode->nodeChar = word[i];
			childNode->parentNode = currNode;

			//If the currnode is the last node mark it as the terminal node
			if (word[i + 1] == '\n')
			{
				childNode->isTerminal = true;
			}

			currNode->childNode[childIndex] = childNode;
			currNode = childNode;
		}
		i++;
	}
}

/* This function checks if the given word can be found on the Trie */
bool TrieFind(TrieNode *rootNode, char8_t *word)
{
	TrieNode *currNode = rootNode;
	int32_t childIndex = 0;
	int32_t i = 0;

	if (currNode == NULL)
	{
		printf("Major Error: rootNode is NULL!");
		return false;
	}

	while (word[i] != '\0')
	{
		childIndex = (int32_t)(word[i] - 'A');

		if (currNode && currNode->childNode[childIndex])
		{
			currNode = currNode->childNode[childIndex];
		}
		else
		{
			return false;
		}

		i++;
	}

	if (currNode &&
		(currNode->isTerminal) &&
		(strlen(word) >= 4))
	{
		 //printf("%s\n", word);
	}

	return true;
}

/* This function recursively destroys the entire Trie Data Structure*/
void TrieDestroy(TrieNode *rootNode)
{
	if (rootNode == NULL)
		return;

	for (int i = 0; i < NUM_ALPHABETS; i++)
	{
		TrieDestroy(rootNode->childNode[i]);
		rootNode->childNode[i] = NULL;
	}

	free(rootNode);
	return;
}

/*This function is used tp reset all the isVisited flags on all the nodes of the trie*/
void TrieResetIsVisited(TrieNode *rootNode)
{
	if (rootNode == NULL)
		return;

	for (int i = 0; i < NUM_ALPHABETS; i++)
	{
		TrieResetIsVisited(rootNode->childNode[i]);
		rootNode->isVisited = false;
	}
}


/* The following Global Variables are used in the TriePrintWords Function to
   keep track of the wordString and index across multiple recursive function calls. */

char printWord[MAX_WORD_LEN] = {0};
char index = 0;
int numWords = 0;

/* This function recursively visits all the nodes that have been marked
   as visited. It also prints words in the alphabetical order*/
void TriePrintWords(TrieNode *rootNode, bool isTrieStart)
{
	if (rootNode == NULL)
		return;

	//Initializations for the print word
	if (isTrieStart)
	{
		index = 0;
		printWord[0] = '\0';
		numWords = 0;
	}
	else if (rootNode->isVisited == true)
	{
		printWord[index++] = rootNode->nodeChar;
		printWord[index] = '\0';

		if ((rootNode->isTerminal) && (strlen(printWord) > MIN_WORD_LEN-1))
		{
			printf("%s ", printWord);
			numWords++;
			if (numWords == PRINT_COLUMNS)
			{
				printf("\n");
				numWords = 0;
			}
		}
	}

	//Recursive calls for all the childNodes
	if (isTrieStart || rootNode->isVisited)
	{
		for (int i = 0; i < NUM_ALPHABETS; i++)
		{
			TriePrintWords(rootNode->childNode[i], false);
		}
		index--;
		if (index >= 0)
			printWord[index] = '\0';
	}

	if (isTrieStart)
	{
		printf("\n");
	}
}
