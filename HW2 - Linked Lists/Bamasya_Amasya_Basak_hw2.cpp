//Basak Amasya
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "strutils.h" //to be able to use atoi function
using namespace std;

/* Structs below are taken from homework document */
struct Product // the node struct for keeping the data related to products
{
	int prod_id;
	string prod_name;
	int amount;
	Product * next;
};
struct Customer // the node struct for keeping the data related to customers
{
	int cust_id; 
	string cust_name;
	Customer * prev;
	Customer * next;
	Product * prod;
};
//the function that checks whether the customer with the given ID exists in the linked list or not
void CheckCustomerExists(Customer * head, bool & check, const int & ID)
{
	Customer * temp = head;
	while (temp != NULL) //until the last node in the linked list
	{
		if (temp->cust_id == ID) //if the customer exists
		{
			check = true;
			break;
		}
		temp = temp->next; //go to the next Customer
	}
}
//the function that prints the related information about the customer
void PrintCustomerFound(Customer * head, bool & check)
{
	Customer * temp = head;
	cout << "Customer found!" << endl;
	cout << "ID: " << temp->cust_id << " Name: " << temp->cust_name << endl;
	check = true;
	Product * tempprod = temp->prod;
	while (tempprod != NULL) //until the customer's last product in the linked list
	{
		cout << "Item ID: " << tempprod->prod_id << " Item name: " << tempprod->prod_name << ".  Amount: " << tempprod->amount << endl;
		tempprod = tempprod->next; //go to the next product
	}
}
//the function that adds the customer to a doubly linked list as sorted
Customer * AddCustomerAsSorted(Customer *& cust_head, int cust_ID, string cust_name) 
{
   Customer * ptr = cust_head;
   if (!ptr) //if head is empty
   {
	  Customer * newcustomer = new Customer;
	  newcustomer->cust_id = cust_ID;
	  newcustomer->cust_name = cust_name;
	  newcustomer->prod = nullptr;
	  newcustomer->next = NULL; //pointer's next and previous will be empty
	  newcustomer->prev = NULL;
	  cust_head = newcustomer; //this pointer will become the new head
	  return newcustomer;
   }
   else if (cust_ID < cust_head->cust_id)  //if this customer will become the new head
   {
	  Customer * newcustomer = new Customer;
	  newcustomer->cust_id = cust_ID;
	  newcustomer->cust_name = cust_name;
	  newcustomer->prod = nullptr;
	  newcustomer->next = cust_head; //the old head will become new head's next
	  newcustomer->prev = NULL;
	  cust_head->prev = newcustomer; //the old head's previous will become the new head
	  cust_head = newcustomer; //head points to the new head from now on
	  return newcustomer;  
   }
   while (ptr->next) //finding the right place to insert the customer
   {    
	   if ( ptr->next->cust_id < cust_ID)
		   ptr = ptr->next;
	   else
		   break;
   }
   Customer * newcustomer = new Customer;
   newcustomer->cust_id = cust_ID;
   newcustomer->cust_name = cust_name;
   newcustomer->prod = nullptr;
   newcustomer->next = ptr->next; //the new pointer's next will become the current pointer's next
   ptr->next = newcustomer; //the current pointer's next will become the new pointer
   newcustomer->prev = ptr; //the new pointer's previous will become the current pointer
   if (newcustomer->next != NULL)
	   newcustomer->next->prev = newcustomer;
   return newcustomer;
}
//the function that adds product to a single linked list as sorted
Customer * AddProductAsSorted(Customer * cust_head, Customer *& lastadded, int prod_ID, string prod_name, int amount) 
{
   if (!lastadded->prod) //if the head of products is empty
   {
	  lastadded->prod = new Product;
	  lastadded->prod->prod_id = prod_ID;
	  lastadded->prod->prod_name = prod_name;
	  lastadded->prod->amount = amount;
	  lastadded->prod->next = NULL; //pointer's next will be empty for now
	  return cust_head;
   }
   else if (prod_ID < lastadded->prod->prod_id) //if this product will become the new head
   {
	   Product * newproduct = new Product;
	   newproduct->prod_id = prod_ID;
	   newproduct->prod_name = prod_name;
	   newproduct->amount = amount;
	   newproduct->next = lastadded->prod; //the old head will become new head's next
	   lastadded->prod = newproduct; //head points to the new head from now on
	   return cust_head;  
   }
   Product * temp = lastadded->prod; //keeping a temp for the lastadded customer's product pointer
   while (temp->next && temp->next->prod_id < prod_ID) //finding the right place to insert the product
   {
	   temp = temp->next;
   }
   Product * newproduct = new Product;
   newproduct->prod_id = prod_ID;
   newproduct->prod_name = prod_name;
   newproduct->amount = amount;
   newproduct->next = temp->next; //the new pointer's next will become the current pointer's next
   temp->next = newproduct; //the current pointer's next will become the new pointer
   return cust_head;
}
//function prints all customers' all products' related data
void print_customer_data(Customer * head)
{
	Customer * temp = head;
	while (temp != NULL) //starting from the first customer until the last customer
	{
		cout << "ID: " << temp->cust_id <<	" Name: " << temp->cust_name << endl;
		cout << "Items in the cart:" << endl;
		Product * tempprod = temp->prod;
		while (tempprod != NULL) //starting from the first product until the last one 
		{
			cout << "Item ID: " << tempprod->prod_id << " Item name: " << tempprod->prod_name << ".  Amount: " << tempprod->amount << endl;
			tempprod = tempprod->next; //going to the next product
		}
		cout << endl;
		temp = temp->next; //going to the next customer
	}
}
//function finds the customer with the given ID
void find_customer(Customer * head)
{
	Customer * temp = head;
	string input;
	int ID;
	bool check = false;
	cout << "Enter customer's ID or name and surname: ";
	cin.ignore(); //clearing cin
    getline(cin, input); //using getline to be able to get the input as one string
	if (atoi(input)) //if the input can be type casted as integer
	{
		ID = atoi(input);
		while (temp != NULL && !check)
		{
			if (temp->cust_id == ID) //if the customer's ID is same with the input
			{
				PrintCustomerFound(temp, check); //calling the function to print that the customer is found
				return;
			}
			temp = temp->next;
		}	
	}
	else //if the input is name and surname
	{
		while (temp != NULL)
		{
			if (temp->cust_name == input) //if the customer's name is same with the input
			{
				PrintCustomerFound(temp, check); //calling the function to print that the customer is found
			}
			temp = temp->next;
		}	
	}
	if (!check)
	{
		cout << "CUSTOMER DOESN'T EXIST. GOING BACK TO MAIN MENU" << endl; //giving the warning
	}	
}
//function adds customer to the doubly linked list sortedly, with the given ID and name-surname
void add_customer(Customer *& head)
{
	Customer * temp = head;
	int ID;
	string cust_name;
	bool check = false;
	cout << "Enter an ID for the user: ";
	cin >> ID;
	CheckCustomerExists(temp, check, ID); //calling the function for checking if the customer already exists
	if (check)
	{
		cout << "User with ID: " << ID << " already exists. Going back to the main menu."<< endl;
	}
	else //if the customer doesn't alreasy exist
	{
		cout << "Enter the customer's name and surname: ";
		cin.ignore(); //clearing cin
		getline(cin,cust_name); //using getline to be able to get name and surname as one string
		AddCustomerAsSorted(head, ID, cust_name); //inserting the customer to the sorted linked list
		cout << "User with ID: " << ID << " is inserted to the list." << endl;
		return;
	}
}
//function deletes a specific customer from the linked list
void delete_customer(Customer *& head)
{
	Customer * ptr = head;
	int ID;
	bool check = false;
	cout << "Enter an ID for the customer to be deleted: ";
	cin >> ID;
	CheckCustomerExists(ptr, check, ID); //checking if the customer exists or not
	if (!check)
	{
		cout << "CUSTOMER DOESN'T EXIST. GOING BACK TO MAIN MENU" << endl;
	}
	else //if the customer exists
	{
		while (ptr != NULL)
		{
			if (ptr->cust_id == ID)
			{
				Product * tempprod = ptr->prod;
				if (ptr == head) //if the head of the list will be deleted
				{
					while (tempprod) //before deleting the customer, its cart must be deleted to avoid memory leak
					{
						tempprod = ptr->prod->next;
						delete ptr->prod; //each product is being deleted one by one
						ptr->prod = tempprod;
					}
					head = head->next; //the new head will be head's next
					if (head != NULL && head->next != NULL)
						head->next->prev = NULL;
					delete ptr; //freeing the memory
					ptr = nullptr;
					break;
				}
				else
				{
					while (tempprod) //before deleting the customer, its cart must be deleted to avoid memory leak
					{
						tempprod = ptr->prod->next;
						delete ptr->prod; //each product is being deleted one by one
						ptr->prod = tempprod;
					}
					ptr->prev->next = ptr->next; //pointer's previous' next will point to pointer's next, so that the onward link will not be lost
					if (ptr->next)
						ptr->next->prev = ptr->prev; //so that the backward link doesn't get lost
					delete ptr; //freeing the memory
					ptr = nullptr;
					break;
				}
			}
			ptr = ptr->next;
		}
		cout << "Customer is deleted successfully." << endl;
	}
}
//function adds product to the given customer sortedly
void add_product(Customer * head)
{
	Customer * ptr = head; //keeping and using ptr from now on instead of head, so that head does not get lost
	int ID;
	bool check = false, found = false;
	int item_ID, item_num;
	string answer, item_name;
	cout << "Enter an ID for the Customer to add product: ";
	cin >> ID;
	CheckCustomerExists(ptr, check, ID); //checking if the customer exists
	if (!check)
	{
		cout << "CUSTOMER DOESN'T EXIST. GOING BACK TO MAIN MENU" << endl; //giving the warning and terminating the function
		return;
	}
	else //if the customer exists
	{
		cout << "Would you like to add item to cart(Y/y): ";
		cin >> answer;
		while (answer == "Y") //as long as user wants to add item to cart
		{
			cout << "ID of the item to add to cart: ";
			cin >> item_ID;
			while (ptr != NULL)
			{
				if (ptr->cust_id == ID) //finding the right customer to add the product
				{
					Product * tempprod = ptr->prod; //keeping temps for the customer and the product so that head's don't get lost
					Customer * tempcust = ptr;
					while (ptr->prod != NULL)
					{
						if (ptr->prod->prod_id == item_ID) //if the product already exists in the customer's cart
						{
							cout << "Product already exists. How many would you like to add more: ";
							cin >> item_num;
							ptr->prod->amount += item_num; //increasing the amount
							cout << "Product's amount in the cart increased to: " << ptr->prod->amount << endl;
							found = true;
						}
						ptr->prod = ptr->prod->next;
					}
					ptr->prod = tempprod;
					if (!found) //if the customer does not already have the product
					{
						cout << "Name of the product: ";
						cin.ignore(); //clearing the cin
						getline(cin,item_name); //using getline to be able to get the input as one string
						cout << "Amount: ";
						cin >> item_num;
						AddProductAsSorted(head,tempcust,item_ID,item_name,item_num); //calling the function to insert the product into the linked list
					}
				}
				ptr = ptr->next;
			}
			ptr = head; //reseting the variables
			check = false, found = false;
			cout << "Would you like to add item to cart(Y/y): "; //asking again
			cin >> answer;
		}
	}
	cout << "Going back to main menu." << endl;
}
//function that prints the products - called from delete product function
void PrintforDeleteProd(Customer * ptr)
{
	Product * tempprod;
	if (ptr != NULL)
		tempprod = ptr->prod; //keeping a temp so that ptr itself does not get lost
	else
		return; //if there is no product to be deleted
	while (tempprod != NULL) //for each product
	{
		cout << "Item ID: " << tempprod->prod_id << " Item name: " << tempprod->prod_name << "  Amount: " << tempprod->amount << endl;
		tempprod = tempprod->next; //going to the next product
	}
}
//function deletes a product from a given customer in the linked list
void delete_product(Customer *& head)
{
	Customer * ptr = head; //keeping and using ptr from now on instead of head, so that head does not get lost
	int cust_ID, item_ID;
	bool check = false, found = false;
	cout << "Enter an ID for the customer to delete product: ";
	cin >> cust_ID;
	CheckCustomerExists(ptr,check,cust_ID); //checking if the customer exists
	if (!check)
	{
		cout << "Customer with ID: "<< cust_ID << " doesn't exists. Going back to main menu." << endl;
		return; //terminating the function because customer does not exist
	}
	else //if the customer exists
	{
		cout << "ID of the item to delete from cart: ";
		cin >> item_ID;
		while (ptr != NULL)
		{
			if (ptr->cust_id == cust_ID) //finding the right customer
			{
				Product * tempprod = ptr->prod;
				Product * prev = nullptr;
				while (tempprod != NULL)
				{
					if (tempprod->prod_id == item_ID)
					{
						if (!prev) //if the product is at the beginning
						{
							tempprod = tempprod->next; //changing the link
							delete ptr->prod; //freeing the memory
							ptr->prod = tempprod;
							found = true;
							break;
						}
						else
						{
							prev->next = tempprod->next; //changing the link
							delete tempprod; //freeing the memory
							tempprod = nullptr;
							found = true;
							break;
						}
					}
					if (!found)
					{
						prev = tempprod;
						tempprod = tempprod->next; //going to the next product
					}
				}
				if (!found)
					cout << "Product doesn't exists. Going back to the main menu." << endl;
				else
				{
					cout << "Product has been deleted." << endl;
					cout << "Current items in the cart: "<< endl;
					cout << "ID: " << ptr->cust_id << " Name: " << ptr->cust_name << endl;
					PrintforDeleteProd(ptr); //calling the function to print the products that are left
				}
				return;
			}
			ptr = ptr->next;
		}
		
	}
}
//function for listing all customers who owns a specific product
void list_product_owners(Customer * head)
{
	Customer * temp = head;
	bool found = false, firsttime = true;
	int item_ID;
	cout << "ID of the product to search buyers: ";
	cin >> item_ID;
	while (temp != NULL && temp->next != NULL) // to be able to start from the last node going one by one until the end
	{
		temp = temp->next;
	}
	while (temp != NULL)
	{
		Product * tempprod = temp->prod;
		while (tempprod != NULL)
		{
			if (tempprod->prod_id == item_ID) //if the product is found
			{
				if (firsttime) // to be able to print out the first line of the output at the beginning
				{
					cout << "Buyers of the product with ID: " << item_ID << " is listed below:" << endl;
					firsttime = false;
				}
				cout << "Customer ID: " << temp->cust_id <<	" Customer name: " << temp->cust_name << " and Amount: "
					<< tempprod->amount << endl;
				found = true;
			}
			tempprod = tempprod->next; //going to the next product
		}
		temp = temp->prev; // going to the previous node
	}
	if (!found)
		cout << "Product doesn't exist. Going back to main menu." << endl; //a specific warning was not written in the hw document
}
//function for parsing the line
string Find(int & index, string & line, const char & sep, const int & firstindex)
{
	string str;
	index = line.find(sep); //finding the seperator
	str = line.substr(firstindex,index-1); //finding the string
	line = line.substr(index+1,line.length()); //upsating the line
	return str;
}
//function for displaying main menu and for calling the functions for options
void MainMenu(Customer *& head)
{
	/* while loop taken from the homework document*/
	while (true)
	{
		cout << endl;
		cout << "***********************************************************************" << endl
				<< "**************** 0 - EXIT PROGRAM ************" << endl
				<< "**************** 1 - PRINT ALL CUSTOMER DATA ************" << endl
				<< "**************** 2 - FIND A CUSTOMER ************" << endl
				<< "**************** 3 - ADD A CUSTOMER ************" << endl
				<< "**************** 4 - DELETE A CUSTOMER ************" << endl
				<< "**************** 5 - ADD A PRODUCT TO A CUSTOMER ************" << endl
				<< "**************** 6 - DELETE A PRODUCT FROM A CUSTOMER ************" << endl
				<< "**************** 7 - LIST THE BUYERS OF A PRODUCT ************" << endl
				<< "***********************************************************************" << endl;
		cout << endl;
		int option;
		cout << "Pick an option from above (int number from 0 to 7): ";
		cin >> option;
		switch (option)
		{
		case 0:
			cout << "PROGRAM EXITING ... " << endl;
			system("pause");
			exit(0);
		case 1:
			print_customer_data(head);
			break;
		case 2:
			find_customer(head);
			break;
		case 3:
			add_customer(head);
			break;
		case 4:
			delete_customer(head);
			break;
		case 5:
			add_product(head);
			break;
		case 6:
			delete_product(head);
			break;
		case 7:
			list_product_owners(head);
			break;
		default:
			cout << "INVALID OPTION!!! Try again" << endl;
		}
	}
}
//function for reading the file, parsing it and storing it in a linked list
void ReadFile(Customer *& cust_head)
{
	fstream file;
	int ID, index, prod_ID_int, amount;
	string cust_name, filename, line, prod_id_str, prod_name;
	filename = "input.txt"; //since prompting for a file was not requested, I wrote the file name as hardcode
	file.open(filename.c_str());
	Customer * lastadded = nullptr; //initializing lastadded customer pointer to null
	while (getline(file,line)) //reading the file line by line
	{
		if (line != "" && line.find('(') != string :: npos) // '\t' characters at the end of the "input.txt" file were deleted by me
		{
			if (line[0] == '#') // if the line begins with a customer
			{
				ID = atoi(Find(index,line,',',1)); //finding the ID
				cust_name = Find(index,line,':',1); //finding the name
				lastadded = AddCustomerAsSorted(cust_head, ID, cust_name); //calling the function to add the customer
			}
			stringstream iss(line);
			iss >> prod_id_str; //reading producst's ID using stringstream
			line = line.substr(line.find(prod_id_str) + prod_id_str.length() + 1, line.length());
			prod_ID_int = atoi(prod_id_str);
			prod_name = Find(index,line,'(', 0);
			if (line.find(',') != string :: npos) //if the line ends with a ','
				amount = atoi(Find(index,line,',',0));
			else //if the line ends with a '.'
				amount = atoi(Find(index,line,'.',0));
			AddProductAsSorted(cust_head, lastadded, prod_ID_int, prod_name, amount); //calling the function to add the product
		}
	}
}
int main() //the main part of the program
{
	static Customer * cust_head = nullptr; //initializing the head of the linked list
	ReadFile(cust_head); // calling the function that reads from the file
	MainMenu(cust_head); // calling the function that displays the main menu options and calls them
	return 0;
}