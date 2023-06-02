#include <iostream>
#include <string>
#include <conio.h>
#include <vector>

#define ALPHABET_SIZE (26)		// Alphabet size (# of symbols)

std::string dictionary[ALPHABET_SIZE] = {};

// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

struct TrieNode
{
	struct TrieNode* children[ALPHABET_SIZE];
	bool isWordEnd; 			// isWordEnd is true if the node represents end of a word
};

struct TrieNode* getNode(void)	// Returns new trie node (initialized to NULLs)
{
	struct TrieNode* pNode = new TrieNode;
	pNode->isWordEnd = false;

	for (int i = 0; i < ALPHABET_SIZE; i++)
		pNode->children[i] = NULL;

	return pNode;
}

// If not present, inserts key into trie. If the
// key is prefix of trie node, just marks leaf node
void insert(struct TrieNode* root, const std::string key)
{
	struct TrieNode* pCrawl = root;

	for (int level = 0; level < key.length(); level++) 
	{
		int index = CHAR_TO_INDEX(key[level]);
		if (!pCrawl->children[index])
			pCrawl->children[index] = getNode();

		pCrawl = pCrawl->children[index];
	}
	pCrawl->isWordEnd = true;		// mark last node as leaf
}

// Returns 0 if current node has a child
// If all children are NULL, return 1.
bool isLastNode(struct TrieNode* root)
{
	for (int i = 0; i < ALPHABET_SIZE; i++)
		if (root->children[i])
			return 0;
	return 1;
}

// Recursive function to print auto-suggestions for given node.
void suggestionsRec(struct TrieNode* root, std::string currPrefix)
{
	if (root->isWordEnd)						// found a string in Trie with the given prefix
		std::cout << currPrefix <<", ";

	for (int i = 0; i < ALPHABET_SIZE; i++)
		if (root->children[i]) 
		{
			char child = 'a' + i;				// child node character value
			dictionary[i] = currPrefix + child;	//	rec [i] word in dictinary
			suggestionsRec(root->children[i],currPrefix + child);	
		}
}

// print suggestions for given query prefix.
int printAutoSuggestions(TrieNode* root, const std::string query)
{
	struct TrieNode* pCrawl = root;
 	for (char c : query) 
	{
		int ind = CHAR_TO_INDEX(c);

		if (!pCrawl->children[ind])		// no string in the Trie has this prefix
			return 0;

		pCrawl = pCrawl->children[ind];
	}
	// If prefix is present as a word, but there is no subtree below the last
	// matching node.
	if (isLastNode(pCrawl)) 
	{
		std::cout << query << '\n';
		return -1;
	}
	suggestionsRec(pCrawl, query);
	return 1;
}

int main(int argc, char* argv[])
{
	struct TrieNode* root = getNode();
	insert(root, "he");
	insert(root, "hell");
	insert(root, "help");
	insert(root, "hellbent");

REPEAT:
	std::cout << "Enter a character:";
	std::string job_string;
	std::cin >>  job_string;

	std::cin.clear();
	while (std::cin.get() != '\n');

	int comp = printAutoSuggestions(root,job_string);

	if (comp == -1)
	{
		std::cout << "No other strings found with this prefix\n";
	}

	else if (comp == 0)
	{
		std::cout << "No string found with this prefix";
	}

	else if (comp > 0)
	{
		std::cout << "\nIn this version dictionary were found words written on top";
		for (int i = 0; i < ALPHABET_SIZE; i++)
		{
			if(dictionary[i]!="")
			{
				std::cout << "\nIs this it " <<"'" << dictionary[i] << "'" << "?";
REPEAT_DICTIANARY:
				std::cout << "\nPlease, enter 'q' = next word, and 'y' if this your word:";
				int tab_imitation;
				tab_imitation = _getch();

				if (tab_imitation == 'q')
				{
					continue;
				}
			
				if (tab_imitation == 'y')
				{
					std::cout << dictionary[i] << '\n';
					break;
				}
				else
				{
					std::cout << "\nThere is no such option! Please...\n";
goto REPEAT_DICTIANARY;
				}
			}
		}
	}
WARNING:
	std::cout << "\nRepeat [key y] or close?[key c]\n";

	int choise;
	choise = _getch();
	if (choise == 'y')
	{
goto REPEAT;
	}

	if (choise == 'c')
	{
		std::cout << "Close programm...\n";
	}

	else
	{
		std::cout << "There is no such option! Please...";
goto WARNING;
	}

	system("pause");
	return 0;
}