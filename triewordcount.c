#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
    int count;
    struct Trie* child[256];
};


// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie* newNode = malloc(sizeof(struct Trie));
    newNode->count = 0;
    for( int i = 0; i < 256; i++)
    {
        newNode->child[i] = NULL;
    }
    return newNode;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    struct Trie* curr = pTrie;
    while (*word != '\0')
    {
        int index = *word;
        if (curr->child[index] == NULL)
        {
            curr->child[index] = createTrie();
        }
        curr = curr->child[index];
        word++;        
    }
    curr->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct Trie* curr = pTrie;
    while(*word != '\0')
    {
        int index = *word;

        if (curr->child[index] == NULL)
        {
            return 0;
        }
        curr = curr->child[index];
        word++;
    }
    return curr->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (pTrie == NULL)
    {
        return NULL;
    }
    for (int  i = 0; i < 256; i++)
    {
        if (pTrie->child[i] != NULL)
        {
            pTrie->child[i] = deallocateTrie(pTrie->child[i]);
        }
    }
    free(pTrie);
    return NULL;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("fail to open file\n");
        return 0;
    }

    int numWord;
    char word[100];
    int j=0;
    fscanf(file, "%d", &numWord);

    for (int i = 0; i < numWord; i++)
    {  
        fscanf(file, "%s", word);
        pInWords[i] = strdup(word);
        j++;
    }
    
    
    fclose(file);
    return j;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}