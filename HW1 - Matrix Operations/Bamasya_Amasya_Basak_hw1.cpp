//Basak Amasya
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "strutils.h" //to be able to use "atoi" function
using namespace std;

// struct used for keeping the strings and the number of their occurences in the matrix
struct Strings
{
	string word;
	int numoccur;
};
// struct used for keeping the row and column indexes as a pair
struct Pair
{
	int row;
	int column;
};
//the function for checking if the word was found before or not
bool isExist(string word, vector<Strings> words, int & i)
{
	for (i=0; i < words.size() ; i++) //for each item in the vector
	{
		if (words[i].word == word) //if that word exists in the vector
			return true;
	}
	return false;
}
//the function that checks if that cell was visited before
bool isExist(int r, int c, vector<Pair> history)
{
	for (unsigned int i=0; i < history.size() ; i++) //for each item in the vector
	{
		if (history[i].row == r && history[i].column == c ) //if that cell was visited before
			return true;
	}
	return false;
}
//the function that gets the filename from the user until the file opens
string GetFileName(ifstream & file)
{
	string filename;
	cout << "Please enter the input file name: ";
	cin >> filename;
	file.open(filename.c_str());
	while (file.fail()) //get the file name from the user until it is successfully opened
	{
		cout << "Couldn't open file. Please enter again: ";
		cin >> filename;
		file.open(filename.c_str());
	}
	return filename;
}
//the function that gets the M value from the user
void GetM(ifstream & file, int & M)
{
	string line;
	getline(file,line); //getting the first line of the file which should be M
	M = atoi(line); // converting string to integer
}
//the function that checks whether the file is in appropriate format or not
bool CheckFile(ifstream & file, int & M, int & N,vector<vector<char>> & mat)
{
	string line;
	bool check = true;
	int linenumber = 0; //set linenumber to 0
	if ((0 > M) || (M > 20)) // if M is not in the boundaries
	{
		check = false;
	}
	while (getline(file,line)) //reading the file line by line
	{
		if (line != "\n")
		if (line != "") //until the empty line
		{
			for (int i = 0; i < line.length(); i++)
			{
				if ( line[i] > 'Z' || line[i] < 'A') // if the characters in the matrix are not capital letters
					check = false;
			}
			if (line.length() != M) // if the number of characters in one line is not equal to the M
			{
				check = false;
			}	
			linenumber ++; //increment linenumber by 1
		}
		else
		{
			getline(file,line);
			N = atoi(line); //conveting string N to integer
			if ((0 > N) || (N > 20)) // if N is not in the boundaries or if N is more than than the cells existing in the matrix
	        {
				check = false;
			}
		}
	}
	if (linenumber != M) // if the matrix is not a square
		check = false;
	file.close();
	if (!check)
	{
		cout << "The input file is not as expected.";
		return false;
	}
	else
		return true;
}
// the function that takes the file and turns it to a char matrix
void MakeMatrix(string filename, ifstream & file, vector<vector<char>> & mat)
{
	string line;
	int linenumber = 0;
	file.open(filename.c_str());
	getline(file,line);
	while (getline(file,line) && line != "") // until the line is empty reading each line
	{
		for (int i = 0; i <= line.length()-1; i++) //for each character in the line
		{
			mat[linenumber][i] = line[i]; //putting the char in the matrix
		}
		linenumber ++;
	}
}
//the funciton that deals with the strings that were found and their number of occurrences 
void KeepingStrings(vector<Strings> & words, string word)
{
	int i = 0;
	if (isExist(word, words,i)) //if the word was found before
	{
		words[i].numoccur += 1; //increment its number of occurrence by 1
	}
	else //if it's the first time this word was found
	{
		Strings newstr; //create a new "Strings" struct
		newstr.word = word;
		newstr.numoccur = 1; //set the number of occurence to 1
		words.push_back(newstr); //send the new "Strings" to the words vector
	}
}
//the recursive function that finds the strings in the matrix
bool RecursiveFindStrings(int r, int c, vector<Pair> history, int N, string word, vector<vector<char>> mat, vector<Strings> & words)
{
	if (isExist(r, c, history)) //if that cell was already visited
	{
		return false; 
	}
	if ( c < 0 || c >= mat.size() || r < 0 || r >= mat.size()) //if that cell is not in the boundaries of the matrix
	{
		return false;
	}

	word += mat[r][c]; //adding the char in that cell to the word
	Pair newpair;
	newpair.row = r, newpair.column = c;
	history.push_back(newpair); //adding this cell in the history vector of the word

	if (word.length() == N) //if N number of characters is reached
	{
		KeepingStrings(words, word); //to add the word to the vector where the found strings are kept
		word = ""; // emptying the word
		return true;
	}
	RecursiveFindStrings(r,c-1,history, N, word,mat, words); //calling the same function again for each direction (4 directions in total, so 4 times)
	RecursiveFindStrings(r-1,c,history, N, word,mat, words); 
	RecursiveFindStrings(r,c+1,history, N, word,mat, words);
	RecursiveFindStrings(r+1,c,history, N, word,mat, words);
}
//the function that searchs the matrix row by row, column by column
void SearchMatrix(vector<vector<char>> mat, vector<Strings> & words, int N)
{
	string word = "";
	vector<Pair> history;
	for (int r = 0; r < mat.size(); r++ )
	{
		for (int c = 0; c < mat[r].size(); c++ )
		{
			RecursiveFindStrings(r, c, history, N, word, mat, words); //calling the recursive function
			word = ""; //emptying the word string
			history.clear(); //emptying the history vector
		}
	}
}
//the function that prints the all strings and their number of occurrences
void PrintingResults(const vector<Strings> & words)
{
	cout << "The given matrix includes:" << endl;
	for (int i=0; i < words.size() ; i++ ) //for each item of words vector
	{
		cout << "[+] " << words[i].word << " exists " << words[i].numoccur << " many times." << endl; 
	}
}
int main() //main part of the program
{
	ifstream file;
	int N,M;
	string filename = GetFileName(file); // the function that gets the filename from the user
	GetM(file,M); // the function that gets integer M
	vector<vector<char>> mat(M, vector<char>(M));
	vector<Strings> words;
	if (CheckFile(file,M,N,mat)) // if the file is not as expected than the other functions are not called
	{
		MakeMatrix(filename,file,mat); //the function that puts the file into a matrix
		SearchMatrix(mat,words,N); // the function that searches the matrix
		PrintingResults(words); // the function that prints the strings that are found
	}
	cin.get(); //for the console not to close immediately 
	cin.ignore();
	return 0;
}