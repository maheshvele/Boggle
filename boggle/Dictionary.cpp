#define DICTIONARY_CPP

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "types.h"
#include "List.h"
#include "Dictionary.h"
#include "Boggle.h"
#include "game.h"
#include "dice.h"
#include "Trie.h"

extern TrieNode *rootNode;

//This Function reads the input characters and populates them in a Trie Data Structure
void parseDictionaryFile(char8_t *filename, int32_t *numWords)
{
	FILE *dictFilePtr = NULL;
	char8_t dictWord[25];
	int32_t i = 0;

	fopen_s(&dictFilePtr, filename, "r");

	if (!dictFilePtr)
	{
		printf("Unable to open file\n");
		return;
	}

	TrieNodeInit(rootNode);

	while (!feof(dictFilePtr))
	{
		fgets(dictWord, MAX_CHARS_IN_DICTIONARY_WORD, dictFilePtr);
		TrieAdd(rootNode, dictWord);
		i++;
	}

	*numWords = i;
}

