//Basak Amasya
#include "SortedArray.h"

SortedArray::SortedArray() {
	front = nullptr;
}

//implement copy constructor
SortedArray::SortedArray(const SortedArray & copy) {
	front = copy.createClone();
}

//implement destructor
SortedArray::~SortedArray() {
	deleteSortedArray();
}

ArrayNode * SortedArray::getFront() const{
	return front;
}

void SortedArray::SetFront(ArrayNode * newFront){
	front = newFront;
}

// implement this function
void SortedArray::cloneHelper(ArrayNode * source, ArrayNode *& destination) const {
	while (source != nullptr) //copying each item one by one until the source points to null
	{
		destination->right = new ArrayNode(source->val);
		destination = destination->right;
		source = source->right;
	}
}

// implement this function
ArrayNode * SortedArray::createClone() const{
	if (front == nullptr)
	{
		return nullptr;
	}
	ArrayNode * clonefront = new ArrayNode(front->val);
	ArrayNode * temp = front->right;
	ArrayNode * cloneptr = clonefront; //getting the head(front)
	cloneHelper(temp,cloneptr); //calling the helper function to copy the rest of the sorted array
	return clonefront;
}


bool SortedArray::search(int Value)
{
	ArrayNode * tmp = front;
	while (tmp) {
		if (tmp->val == Value) {
			return true;
		}
		tmp = tmp->right;
	}
	return false;
}

void SortedArray::insert(int Value) {
	if (!search(Value)) {
		ArrayNode * tmp = front;

		ArrayNode * newNode = new ArrayNode(Value);
		if (!front) {
			front = newNode;
		}
		else if (front && Value < front->val) {
			newNode->right = front;
			front = newNode;
		}
		else {
			while (tmp->right && tmp->right->val < Value) {
				tmp = tmp->right;
			}
			newNode->right = tmp->right;
			tmp->right = newNode;
		}
	}
}

void SortedArray::deleteSortedArray() {
	ArrayNode * current = front, *next = front;
	while (current) {
		next = current->right;
		delete current;
		current = next;
	}
	front = nullptr;
}

void SortedArray::print() {
	if (!front) {
		cout << "Array is empty" << endl;
	}
	ArrayNode * tmp = front;
	while (tmp) {
		cout << tmp->val << " ";
		tmp = tmp->right;
	}
	cout << endl;
}

//implement assignment (=) and plus (+) operators

const SortedArray & SortedArray::operator= (const SortedArray & rhs)
{
	if (this != &rhs)
	{
		deleteSortedArray();
		front = rhs.createClone(); //calling the function to copy the array in the right hand side
	}
	return *this; //returning for cascading purposes
}

SortedArray operator+ (const SortedArray & lhs, const SortedArray & rhs) //when + gets 2 sorted arrays
{
	SortedArray temprhs(rhs);
	SortedArray templhs(lhs);
	ArrayNode * tempnode = temprhs.getFront();
	while (tempnode)
	{
		templhs.insert(tempnode->val);
		tempnode = tempnode->right;
	}
	return templhs;
}
SortedArray operator+ (const int & lhs, const SortedArray & rhs) //when + gets a sorted array on the right side and an integer on the left
{
	SortedArray result(rhs);
	result.insert(lhs); //inserting the number on the left hand side to the sorted array
	return result;
}
SortedArray operator+ (const SortedArray & lhs, const int & rhs)//when + gets a sorted array on the left side and an integer on the right
{
	SortedArray result(lhs);
	result.insert(rhs); //inserting the number on the right hand side to the sorted array
	return result;
}


