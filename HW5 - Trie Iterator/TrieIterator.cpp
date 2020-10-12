//Basak Amasya

#include "Stack.h"
#include "Trie.h"
#include "TrieIterator.h"

Stack words; //global stack to keep the characters of the words

TrieIterator::TrieIterator(const Trie & myTrie)
	: myTrie(myTrie), currentNode(nullptr), currentWord("") {
}

// TODO: Implement this function
void TrieIterator::Init() {
	currentNode = myTrie.createClone(); //copying the trie
	Next(); //calling next for initialization
}

// TODO: Implement this function
void TrieIterator::Next() {
	TrieNode * temp = currentNode;
	TrieNode * tobenull = nullptr;
	int index = 0;
	if (!words.isEmpty()) //if there is a node in the stack
	{
		words.pop(temp,index);
		if (myTrie.hasChildren(temp->children[index],0))
		{
			words.push(temp,index);
			temp = temp->children[index];
		}
	}
	while (temp) //as long as the pointer does not point to null
	{
		for (int i = 0; i < ALPHABET_SIZE; i++)
		{
			if (temp->children[i])
			{
				if (temp->children[i] == tobenull)
				{
					temp->children[i] = nullptr;
				}
				else
				{
					words.push(temp,i);
					if (temp->children[i]->isWord)
					{
						if (!myTrie.hasChildren(temp->children[i],0))
						{
							temp->children[i] = nullptr;
						}
						return;
					}
					temp = temp->children[i];
					i = -1;
				}
			}
		}
		tobenull = temp;
		if (!words.isEmpty())
		{
			words.pop(temp,index);
			if (myTrie.hasChildren(temp->children[index],0))
			{
				words.push(temp,index);
				temp = temp->children[index];
			}
		}
		else
		{
			for (int i = 0; i < ALPHABET_SIZE; i++)
			{
				if (temp == currentNode->children[i])
				{
					currentNode->children[i] = nullptr;
					break;
				}
			}
			if (!myTrie.hasChildren(currentNode,0))
			{
				currentNode = nullptr;
			}
			temp = currentNode;
		}
	}
}

// TODO: Implement this function
bool TrieIterator::HasMore() const {
	return (currentNode); //returns false when each node is set to null
}
// TODO: Implement this function
string TrieIterator::Current() const {
	Stack temp;
	string wordstring;
	TrieNode * node;
	int i;
	while (!words.isEmpty()) //until the characters in the stack end
	{
		words.pop(node,i);
		temp.push(node,i); //keeping another stack to reverse the order
	}
	while (!temp.isEmpty()) 
	{
		temp.pop(node,i);
		words.push(node,i); //putting the characters back
		wordstring += char(i + 'a');
	}
	return wordstring;
}