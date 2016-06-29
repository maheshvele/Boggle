typedef struct TrieNode
{
	char8_t nodeChar;    //Used to store Character represented by the current node
	bool8_t	isTerminal;  //Tells if the current node is a terminal node
	bool8_t isVisited;   // Used to keep track of all the traversed 
	bool8_t isQpresent;  // Used to insert  to

	TrieNode *childNode[26];
	TrieNode *parentNode;  //Used to keep track of the parent node. It makes it easier for backtracking.
}TrieNode;

void TrieNodeInit(TrieNode *rootNode);
void TrieAdd(TrieNode *rootNode, char8_t *nodeChar);
bool TrieFind(TrieNode *rootNode, char8_t *word);
void TrieDestroy(TrieNode *rootNode);
void TrieResetIsVisited(TrieNode *rootNode);
void TriePrintWords(TrieNode *rootNode, bool isTrieStart);
