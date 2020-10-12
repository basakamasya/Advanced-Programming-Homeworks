//Basak Amasya
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "DynamicStrQueue.h"
#include "DynamicIntStack.h"
#include "DynamicStrStack.h"
#include "strutils.h"
using namespace std;

//variables taken from homework document
int special_regs[5] = {0};// namely CSA CSB CSC CSP CST
int general_regs[20] = {0}; // namely CSG0 CSG1 CSG2 ... CSG19
string variables[20] = {""}; // to store the variable names defined by the user. (e.g. var1, var2)
DynamicStrQueue instruction_queue; // to store the instructions in the queue
DynamicIntStack memory_stack; // needed for debugger
int instr_counter = 1; // counter for printing the instruction counts in print remaining instructions 

//function taken from hw document
void clear_regs_vars() {
	instr_counter = 1; //modified by me 
	for (int &i : special_regs) {
		i = 0;
	}
	for (int &i : general_regs) {
		i = 0;
	}
	for (string &i : variables) {
		i = "";
	}
	instruction_queue.clear();
	memory_stack.clear();
}
//function that gets the register's name and finds the register's place
int finding_register_index(string word, string & registertype)
{
	int index, item;
	index = INT_MIN;
	if (word[2] == 'G') //if its one of the general registers
	{
		word = word.substr(3,word.length());
		index = atoi(word); //finding the index according to its name
		registertype = "general";
	}
	else //if its one of the special registers
	{
		if (word[2] == 'A') //finding the index according to its name
		{
			index = 0;
		}
		else if (word[2] == 'B')
		{
			index = 1;
		}
		else if (word[2] == 'C')
		{
			index = 2;
		}
		else if (word[2] == 'P')
		{
			index = 3;
		}
		else if (word[2] == 'T')
		{
			index = 4;
		}
		registertype = "special";
	}
	return index;
}
//the function that makes the operands - depending on whether they are register or numbers
void arithmeticoperationformachine(int & operand1, int & operand2, string word1, string word2)
{
	int index1, index2;
	string registertype1, registertype2;
	if (atoi(word1)) //if the first word is a number
	{
		operand1 = atoi(word1);
		if (atoi(word2)) //if the second word is a number
		{
			operand2 = atoi(word2);
		}
		else
		{
			index2 = finding_register_index(word2,registertype2); //finding the register

			if (registertype2 == "general")
			{
				operand2 = general_regs[index2];
			}
			else
			{
				operand2 = special_regs[index2];
			}
		}
	}
	else
	{
		if (atoi(word2)) //if its a number
		{
			operand2 = atoi(word2);
			index1 = finding_register_index(word1,registertype1); //finding the register
			if (registertype1 == "general")
			{
				operand1 = general_regs[index1];
			}
			else
			{
				operand1 = special_regs[index1];
			}
		}
		else //if both are registers
		{
			index1 = finding_register_index(word1,registertype1);
			index2 = finding_register_index(word2,registertype2);
			if (registertype1 == "general" && registertype2 == "general")
			{
				operand1 = general_regs[index1];
				operand2 = general_regs[index2];
			}
			else if (registertype1 == "general" && registertype2 == "special")
			{
				operand1 = general_regs[index1];
				operand2 = special_regs[index2];
			}
			else if (registertype1 == "special" && registertype2 == "general")
			{
				operand1 = special_regs[index1];
				operand2 = general_regs[index2];
			}
			else if (registertype1 == "special" && registertype2 == "special")
			{
				operand1 = special_regs[index1];
				operand2 = special_regs[index2];
			}
		}
	}
}
//the function that translates the machine language to C++ and runs the instruction
void machinelanguage_translation(const string & line)
{
	int item, index, index1, index2, operand1, operand2, sum, dif, prod, div, remain;
	string word, word1, word2, registertype, registertype1, registertype2;
	stringstream iss(line);
	iss >> word; //getting the first word
	if (word == "push")
	{
		iss >> word; //getting the word to push it to stack
		if (atoi(word))
		{
			item = atoi(word);
		}
		index = finding_register_index(word, registertype);
		if (index != INT_MIN)
		{
			if (registertype == "general")
			{
				item = general_regs[index];
			}
			else if (registertype == "special")
			{
				item = special_regs[index];
			}
		}
		else 	
		{
			for (int i = 0; i < 20; i++)
			{
				if (variables[i] == word)
				{
					item = general_regs[i];
				}
			}
		}
		memory_stack.push(item); //pushing the item (number or register or variable) to the stack
	}
	else if (word == "pop")
	{
		memory_stack.pop(item);
		special_regs[3] = item;
	}
	else if (word == "mov")
	{
		iss >> word1;
		iss >> word2;
		if (atoi(word2))
		{
			item = atoi(word2);
			index = finding_register_index(word1, registertype);
			if (registertype == "general")
		    {
				general_regs[index] = item;
		    }
			else
			{
				special_regs[index] = item;
			}
		}
		else
		{
			index1 = finding_register_index(word1,registertype1);
			index2 = finding_register_index(word2,registertype2);
			if (registertype1 == "general" && registertype2 == "general")
			{
				general_regs[index1] = general_regs[index2];
			}
			else if (registertype1 == "general" && registertype2 == "special")
			{
				general_regs[index1] = special_regs[index2];
			}
			else if (registertype1 == "special" && registertype2 == "special")
			{
				special_regs[index1] = special_regs[index2];
			}
			else if (registertype1 == "special" && registertype2 == "general")
			{
				special_regs[index1] = general_regs[index2];
			}
		}
	}
	else if (word == "add")
	{
		iss >> word1;
		iss >> word2;
		arithmeticoperationformachine(operand1, operand2, word1, word2);
		sum = operand1 + operand2;
		special_regs[0] = sum; //putting the result to the CSA
	}
	else if (word == "sub")
	{
		iss >> word1;
		iss >> word2;
		arithmeticoperationformachine(operand1, operand2, word1, word2);
		dif = operand1 - operand2;
		special_regs[0] = dif; //putting the result to the CSA
	}
	else if (word == "mul")
	{
		iss >> word1;
		iss >> word2;
		arithmeticoperationformachine(operand1, operand2, word1, word2);
		prod = operand1 * operand2;
		special_regs[0] = prod; //putting the result to the CSA
	}
	else if (word == "div")
	{
		iss >> word1;
		iss >> word2;
		arithmeticoperationformachine(operand1, operand2, word1, word2);
		div = operand1 / operand2;
		special_regs[1] = div; //putting the result to the CSB
		remain = operand1 % operand2;
		special_regs[2] = remain; //putting the result to the CSC
	}
	else if (word == "print")
	{
		memory_stack.pop(item); //popping the item at the top of the stack
		cout << "Print Output: " << item << endl;
	}
	else if (word == "ret")
	{
		return;
	}
}
//the function that adds the arithmetic operation to queue accordingly
void arithmeticoperationresult(string oper, string operandr, string operandl)
{
	if (oper == "+")
	{
		instruction_queue.enqueue("add "+ operandr + " " + operandl);
		instruction_queue.enqueue("push CSA");
	}
	else if (oper == "-")
	{
		instruction_queue.enqueue("sub "+ operandr + " " + operandl);
		instruction_queue.enqueue("push CSA");
	}
	else if (oper == "*")
	{
		instruction_queue.enqueue("mul "+ operandr + " " + operandl);
		instruction_queue.enqueue("push CSA");
	}
	else if (oper == "/")
	{
		instruction_queue.enqueue("div "+ operandr + " " + operandl);
		instruction_queue.enqueue("push CSB");
	}
	else if (oper == "%")
	{
		instruction_queue.enqueue("div "+ operandr + " " + operandl);
		instruction_queue.enqueue("push CSC");
	}
	instr_counter = instr_counter + 2;
}
//the function that handles the arithmetic operations
void arithmetic_operation(string line)
{

	string arithmeticoperators = "+-*/%";
	string word, oper, operandl, operandr, parantheses, temp;
	stringstream iss(line);
	DynamicStringStack operands, operators;
	while (iss >> word)
	{
		if (word == "=")
			break;
	}
	while (iss >> word)
	{
		if (atoi(word))
		{
			operands.push(word); //putting the operand to its stack
		}
		else
		{
			for (int x = 0; x < 5; x ++)
			{
				if (word == arithmeticoperators.substr(x, 1))
				{
					operators.push(word); //putting the operator to the operator stack
				}
			}
		}
		if (word == "(")
		{
			operands.push(word);
		}
		if (word == ")")
		{
			if (!operators.isEmpty() && !operands.isEmpty())
			{
				operands.pop(temp); //getting the operator
				if (temp == "(")
				{
					operands.push("(");
					break;
				}
				operators.pop(oper);
				if (temp == "?") //this means that I have to get the real operand from the stack
				{
					operands.pop(temp);
					operands.pop(parantheses);
					if (temp == "?") //the other operand should be called from the stack as well
					{
						instruction_queue.enqueue("pop");
						instruction_queue.enqueue("mov CST CSP");
						instruction_queue.enqueue("pop");
						arithmeticoperationresult(oper, "CSP", "CST");
						instr_counter = instr_counter + 3;
					}
					else
					{
						operandl = temp; //the temp will be left operand
						instruction_queue.enqueue("pop");
						instr_counter ++;
						arithmeticoperationresult(oper, operandl, "CSP");
					}
				}
				else
				{
					operandr = temp; //temp will be the right operand
					operands.pop(temp);
					operands.pop(parantheses);
					if (temp == "?" ) //if there is a question mark I should pop the operand from the stack
					{
						instruction_queue.enqueue("pop");
						instr_counter ++;
						arithmeticoperationresult(oper,"CSP", operandr);
					}
					else
					{
						operandl = temp; //temp will be the left operand
						arithmeticoperationresult(oper, operandl, operandr);
					}
				}
			operands.push("?"); //pushing a question mark to the operands stack as a mark that I calculated someting
			}
		}
		else
		{
			for (int x = 0; x < 20; x ++)
			{
				if (word == variables[x])
				{
					operands.push("CSG" + itoa(x)); //putting the variable's register to the stack
				}
				else if (variables[x] == "")
				{
					break;
				}
			}
		}
	}
}

//the main menu functions' prototypes are taken from hw document 
bool transform_source() {
	//It requests an input file and if it cannot be opened returns false
	//If the input file correctly opened, reads the file and 
	//transform CS++ to Machine Language and stores the Machine Code instructions in `instruction_queue`
	string filename, line, word, equal, mark, valuestr;
	int i = 0;
	ifstream file;
	clear_regs_vars(); //calling the function to clear eveything before the program starts
	cout << "Please give me the input filename: ";
	cin >> filename;
	file.open(filename.c_str());
	if (file.fail())
	{
		return false;
	}
	else //if the file is successfully opened
	{
		getline(file,line);
		while (getline(file,line)) //reading the file line by line
		{
			stringstream iss(line);
			while (iss >> word) //reading the line word by word and writing the appropriate instruction to queue
			{
				if (word == "return")
				{
					instruction_queue.enqueue("ret");
					instr_counter ++;
					return true;
				}
				else if (word == "print")
				{
					while(iss >> word);
					for (int x = 0; x < 20 ; x ++ )
					{
						if (variables[x] == word)
						{
							instruction_queue.enqueue("push CSG" + itoa(x));
						}
					}
					instruction_queue.enqueue("print");
					instr_counter = instr_counter + 2;
				}
				else if (word == "int")
				{
					iss >> word;
					i = 0;
					for (i; i < 20; i++)
					{
						if (variables[i] == "")
						{
							variables[i] = word;
							break;
						}
					}
					if (iss >> equal)
					{
						iss >> valuestr;
						if (atoi(valuestr))
						{
							instruction_queue.enqueue("mov CSG"+ itoa(i) + " " + valuestr);
							instr_counter ++;
						}
						else if (valuestr == "(") //if there is an arithmetic operation to be done
						{
							arithmetic_operation(line);
							instruction_queue.enqueue("pop");
							instruction_queue.enqueue("mov CSG" + itoa(i) + " CSP");
							instr_counter = instr_counter + 2;
							while (iss >> word);
						}
						else
						{
							for (int k = 0; k < 20; k++)
							{
								if (variables[k] == valuestr)
								{
									instruction_queue.enqueue("mov CSG"+ itoa(i) + " CSG" + itoa(k));
									instr_counter ++;
								}
							}
						}
					}
				}
				else
				{
					i = 0;
					for (i; i < 20; i++)
					{
						if (variables[i] == word)
						{
							iss >> equal;
							iss >> valuestr;
							if (atoi(valuestr))
							{
								instruction_queue.enqueue("mov CSG"+ itoa(i) + " " + valuestr);
								instr_counter ++;
							}
							else if (valuestr == "(") //if there is an arithmetic operation to be done
							{
								arithmetic_operation(line);
								instruction_queue.enqueue("pop");
								instruction_queue.enqueue("mov CSG" + itoa(i) + " CSP");
								instr_counter = instr_counter + 2;
								while (iss >> word);
							}
							else
							{
								for (int k = 0; k < 20; k++)
								{
									if (variables[k] == valuestr)
									{
										instruction_queue.enqueue("mov CSG"+ itoa(i) + " CSG" + itoa(k)); //assigning the variable's value
										instr_counter ++;
									}
								}
							}
							break;
						}
					}
				}
			}
		}
	}
}

void run_one_instruction() {
	//dequeue one instruction from `instruction_queue` and run it accordingly
	//instruction_queue.dequeue(instr);
	//machinelanguage_translation(instr);
	string instr;
	if (instr_counter > 1)
	{
		instruction_queue.dequeue(instr); //getting the instruction from the queue
		machinelanguage_translation(instr); //running the instruction
		cout << endl;
		cout << "Executed instruction: " << instr << endl;
		cout << endl;
		instr_counter --; //decrementing count of the instructions by 1
	}
}

void run_until_end() {
	//run all the instructions in the queue
	string instr;
	if (instr_counter == 1) //if there's no instruction left
	{
		cout << "There is no instruction left." << endl;
	}
	else
	{
		while (instr_counter > 1) //while there are instructions in the queue
		{
			instruction_queue.dequeue(instr);  
			machinelanguage_translation(instr); //running the instruction
			instr_counter --; //decrementing count of the instructions by 1
		}
	}
}


void print_stack() {
	//print the values in the `memory_stack`
	IntStackNode * temp;
	temp = memory_stack.GetTopPointer(); //the pointer points the top of the stack
	if (temp == nullptr)
	{
		cout << "Currently stack is empty." << endl;
	}
	else //if the stack is not empty
	{
		cout << endl;
		cout << "  Current Stack" << endl;
		cout << endl;
		while (temp != nullptr) //until the stack ends
		{
			cout << "\t" << temp->value << endl;
			temp = temp->next; //going to the next node
		}
	}
}


void print_registers() {
	//print the registers
	cout << "\t" << "SPECIAL REGISTERS" << endl;
	cout << endl;
	cout << "\t\t" << "CSA: " << special_regs[0] << endl; //for each special register printing out the name and its value one by one
	cout << "\t\t" << "CSB: " << special_regs[1] << endl;
	cout << "\t\t" << "CSC: " << special_regs[2] << endl;
	cout << "\t\t" << "CSP: " << special_regs[3] << endl;
	cout << "\t\t" << "CST: " << special_regs[4] << endl;
	cout << endl;
	cout << "\t" << "GENERAL REGISTERS" << endl;
	cout << endl;
	for (int x = 0; x < 20; x++) //for each general register
	{
		cout << "\t\t" << "CSG" + itoa(x) + ": " << general_regs[x] << endl; //printing the register name and its value
	}
}


void print_next_instruction() {
	//print the next Machine Code instruction to be executed
	string instruction;
	StrQueueNode * temp;
	temp = instruction_queue.GetFront(); //pointer temp points the front of the queue
	if (instr_counter > 1) //if the queue is not empty
	{
		instruction = temp->value; //get the value of the instruction the pointer points to
		cout << "Next Instruction is: " << instruction << endl;
	}
	else
	{
		cout << "There is no instruction left." << endl;
		return;
	}
}


void print_remaining_instructions(int instr_counter) {
	//print the remaining instructions to execute in the `instruction_queue`
	string instruction;
	int count = 1;
	StrQueueNode * temp;
	temp = instruction_queue.GetFront(); //pointer temp points the front of the queue
	if (instr_counter > 1) //if the instruction queue is not empty
	{
		cout << "******** INSTRUCTIONS ********" << endl;
		while (temp != NULL) //until the queue ends
		{
			instruction = temp->value;
			cout << "[" << count << "] " << instruction << endl;
			count ++;
			temp = temp->next; //going to the next node
		}
	}
	else
	{
		cout << "There is no instruction left." << endl;
	}
}


void print_variables() {
	//print the defined variables and their values
	cout << "******** DEFINED VARIABLES ********" << endl;
	for (int i = 0; i < 20; i++) //for each varible in the variables array
	{
		if (variables[i] != "")
			cout << "\t" << variables[i] << ": " << general_regs[i] << endl; //print the variable name and its value from the general register
	}
}

int main() { //taken from homework document
	bool input_OK = false;
	while (true) {
		cout << endl;
		cout << "***********************************************************************" << endl
		  	 << "**************** 0 - EXIT PROGRAM                          ************" << endl
			 << "**************** 1 - GIVE INPUT FILE                       ************" << endl
			 << "**************** 2 - RUN UNTIL THE END                     ************" << endl
			 << "**************** 3 - RUN ONE INSTRUCTION                   ************" << endl
			 << "**************** 4 - PRINT CURRENT STACK                   ************" << endl
			 << "**************** 5 - PRINT REGISTER VALUES                 ************" << endl
			 << "**************** 6 - PRINT NEXT INSTRUCTION                ************" << endl
			 << "**************** 7 - PRINT REMAINING INSTRUCTIONS          ************" << endl
			 << "**************** 8 - PRINT DEFINED VARIABLES               ************" << endl
			 << "***********************************************************************" << endl;
		cout << endl;
		int option;
		cout << "Pick an option from above (int number from 0 to 8): ";
		cin >> option;
		switch (option)
		{
		case 0:
			cout << "PROGRAM EXITING ... " << endl;
			system("pause");
			exit(0);
		case 1:
			if (transform_source()) {
				input_OK = true;
			}
			else {
				cout << "There is a problem with the input file." << endl;
			}
			break;
		case 2:
			if (input_OK) {
				run_until_end();
			}
			else {
				cout << "First give an input file." << endl;
			}
			break;
		case 3:
			if (input_OK) {
				run_one_instruction();
				print_next_instruction();
			}
			else {
				cout << "First give an input file." << endl;
			}
			break;
		case 4:
			if (input_OK) {
				print_stack();
			}
			else {
				cout << "First give an input file." << endl;
			}
			break;
		case 5:
			if (input_OK) {
				print_registers();
			}
			else {
				cout << "First give an input file." << endl;
			}
			break;
		case 6:
			if (input_OK) {
				print_next_instruction();
			}
			else {
				cout << "First give an input file." << endl;
			}
			break;
		case 7:
			if (input_OK) {
				print_remaining_instructions(instr_counter);
			}
			else {
				cout << "First give an input file." << endl;
			}
			break;
		case 8:
			if (input_OK) {
				print_variables();
			}
			else {
				cout << "First give an input file." << endl;
			}
			break;
		default:
			cout << "INVALID OPTION!!! Try again" << endl;
		}
	}
	return 0;
}