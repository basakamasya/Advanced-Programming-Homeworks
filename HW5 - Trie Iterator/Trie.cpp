//Basak Amasya

#include "Trie.h"
#include "TrieIterator.h"
#include <iostream>
#include <sstream>

Trie::Trie(){
	this->root = new TrieNode();
	this->size = 0;
}

// TODO: Implement this function
Trie::Trie(const Trie & copy){
	size = copy.size;
	root = copy.createClone();
	cout << "Copy constructor called" << endl;
}

// TODO: Implement this function
Trie::Trie(Trie && move):root(nullptr), size(0){
	std :: swap(root,move.root);
	std :: swap(size,move.size);
	cout << "Move constructor called" << endl;
}

// TODO: Implement this function
Trie::~Trie(){
	deleteTrie();
	cout << "Destructor called" << endl;
}


// TODO: Implement this function
TrieNode * Trie::createClone() const {
	if (root == nullptr) //if the trie is empty
	{
		return nullptr;
	}
	TrieNode * rootclone = new TrieNode();
	TrieNode * ptr = root;
	cloneHelper(ptr,rootclone); //ptr will be the source and the rootclone will be the destination
	return rootclone;
}

// TODO: Implement this function
void Trie::cloneHelper(TrieNode* source, TrieNode*& destination) const {
	if (!source) // if the node is null
	{
		return;
	}
	for (int i = 0; i < ALPHABET_SIZE; i++) //for each child of the node
	{
		if (hasChildren(source,0)) 
		{
			if (source->isWord) destination->isWord = true;
			destination->children[i] = new TrieNode;
			cloneHelper(source->children[i], destination->children[i]); //calling the function again for the child
		}
		else if (source && source->isWord)
		{
			destination->isWord = true;
		}
		else // if the node does not have any children and isWord is false
		{
			destination->children[i] = nullptr;
		}
	}
}


/*******************************************************************/
/*                      DEFINE YOUR OPERATORS HERE                 */
bool Trie::operator==(const Trie & rhs)
{
	if (rhs.root && !(this->root))
	{
		return false;
	}
	else if (!(rhs.root) && this->root)
	{
		return false;
	}
	else if (!rhs.root && !this->root)
	{
		return true;
	}
	stringstream issl,issr;
	string word, contentl,contentr;
	TrieNode * templ = this->root;
	TrieNode * tempr = rhs.root;
	rhs.printHelper(issl, templ,word); //for 2 Tries be the same their outputs should be the same
	this->printHelper(issr,tempr,word); //calling the printhelper function for both of the Tries
	contentl = issl.str(); //converting the string streams into a string
	contentr = issr.str();
	if (contentl == contentr)
		return true;
	else 
		return false;
}
bool Trie::operator!=(const Trie & rhs)
{
	return !(this==&rhs);
}
const Trie& Trie::operator=(const Trie & rhs)
{
	if (this != &rhs)
	{
		deleteTrie(); //deleting the left hand side
		root = rhs.createClone(); //copying the right hand side
		size = rhs.size;
	}
	return *this;
}
const Trie& Trie::operator+=(const Trie & rhs)
{
	TrieIterator iter(rhs);
	for (iter.Init(); iter.HasMore(); iter.Next()) //iterating over the right hand side
	{
		this->insertWord(iter.Current()); //inserting each word into the left hand side
	}
	return *this; //returning the left hand side
}
const Trie Trie::operator+(const Trie & rhs)
{
	//Trie * result = new Trie;
	Trie result;
	//Trie result(*this);
	TrieIterator iterthis(*this);
	TrieIterator iter(rhs);
	for (iter.Init(); iter.HasMore(); iter.Next())  //iterating over the right hand side and inserting each word into the result
	{
		result.insertWord(iter.Current());
	}
	for (iterthis.Init(); iterthis.HasMore(); iterthis.Next())  //iterating over the left hand side and inserting each word into the result
	{
		result.insertWord(iterthis.Current());
	}
	return result; //returning the new trie
}
const Trie& Trie::operator+=(const string & rhs)
{
	this->insertWord(rhs); //inserting the string into the trie
	return *this;
}
ostream & operator<< (ostream & os, const Trie & rhs)
{
	TrieNode * node = rhs.root;
	if (!node) //if root points to null
	{
		cout << "Trie is empty." << endl;
		return os;
	}
	string word;
	rhs.printHelper(os, node, word); //calling the function to print out the trie's words
	return os;
}
//Trie Trie::operator+ (const string & rhs)
//{
//	Trie result;
//	result.root = this->createClone();
//	result.size = this->size;
//	result.insertWord(rhs);
//	return result;
//}
Trie operator+ (Trie & lhs, const string & rhs)
{
	Trie result;
	result.root = lhs.createClone();
	result.size = lhs.size;
	result.insertWord(rhs);
	return result;
	//Trie result(lhs);
	//result.insertWord(rhs); //inserting the right hand side into the copy of the left hand side
	//return result;
}
Trie operator+ (const string & lhs, Trie & rhs)
{
	Trie result;
	result.root = rhs.createClone();
	result.size = rhs.size;
	result.insertWord(lhs); //inserting the left hand side into the copy of the right hand side
	return result;
}
/*******************************************************************/

//below functions are taken from the homework file

bool Trie::searchWord(string word) {
	lower(word);
	TrieNode * ptr = root;
	int len = word.length();
	for (int i = 0; i < len; i++) {
		int targetIndex = word.at(i) - 'a';
		if (!ptr->children[targetIndex]) {
			return false;
		}
		ptr = ptr->children[targetIndex];
	}
	if (ptr->isWord) {
		return true;
	}
	return false;
}

void Trie::lower(string & word) {
	string res;
	for (char c : word) {
		if (c >= 'A' && c < 'a') {
			res += (c - 'A' + 'a');
		}
		else {
			res += c;
		}
	}
	word = res;
}


void Trie::insertWord(string word) {
	lower(word);
	if (!searchWord(word)) {
		TrieNode * ptr = root;
		int len = word.length();
		for (int i = 0; i < len; i++) {
			int targetIndex = word.at(i) - 'a';
			if (!ptr->children[targetIndex]) {
				ptr->children[targetIndex] = new TrieNode();
			}
			//			ptr->isLeaf = false;
			ptr = ptr->children[targetIndex];
		}
		ptr->isWord = true;
		size += 1;
	}
}

bool Trie::hasChildren(TrieNode * node, int i = 0) const {
	if (node) {
		for (i; i < ALPHABET_SIZE; i++) {
			if (node->children[i]) {
				return true;
			}
		}
	}
	return false;
}

void Trie::deleteWord(string word) {
	lower(word);
	if (searchWord(word)) {
		if (deleteWordHelper(root, word)) {
			size--;
		}
	}
}

bool Trie::isEmpty() const {
	return !(this->hasChildren(root));
}

bool Trie::deleteWordHelper(TrieNode *& node, string word) {
	if (word.length()) {
		if (node != nullptr &&
			node->children[word[0] - 'a'] != nullptr &&
			deleteWordHelper(node->children[word[0] - 'a'], word.substr(1)) &&
			!node->isWord
			) {
			if (!hasChildren(node)) {
				delete node;
				node = nullptr;
				return true;
			}
			else {
				node->isWord = false;
				return true;
			}

		}
	}
	if (word.length() == 0 && node->isWord) {
		if (!hasChildren(node)) {
			delete node;
			node = nullptr;
			return true;
		}
		else {
			node->isWord = false;
			return false;
		}
	}
}

void Trie::printHelper(ostream & os, TrieNode * node, string & word) const {
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (node->children[i]) {
			word += char(i + 'a');
			if (node->children[i]->isWord) {
				os << word << endl;
				printHelper(os, node->children[i], word);
			}
			else {
				printHelper(os, node->children[i], word);
			}
		}
		else if (i == 26) {
			word = word.substr(0, word.length() - 1);
		}
	}
	word = word.substr(0, word.length() - 1);
}

void Trie::deleteTrie() {
	if (root) {
		deleteTrieHelper(root);
		root = nullptr;
		size = 0;
	}
}

void Trie::deleteTrieHelper(TrieNode * node) {
	if (hasChildren(node)) {
		for (int i = 0; i < ALPHABET_SIZE; i++) {
			if (node->children[i]) {
				deleteTrieHelper(node->children[i]);
			}
		}
	}
	delete node;
}

int Trie::length() {
	return size;
}