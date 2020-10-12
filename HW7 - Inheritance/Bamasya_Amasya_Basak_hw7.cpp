//Basak Amasya
#include <iostream>
#include <string>

using namespace std;

class Human
{
public:
	Human() {};
	Human(string humanname, int humanage)
	{
		name = humanname;
		age = humanage;
	}
	string name;
	int age;
	virtual void printInfo() //declared as virtual function because it's the base class function
	{
		cout << "Human informations" << endl;
		cout << "Name: " << name << endl;
		cout << "Age: " << age << endl;
	}
};

class Muggle : public Human
{
public:
	Muggle(string mugglename, int muggleage, string mugglejob)
	{
		name = mugglename;
		age = muggleage;
		job = mugglejob;
	}
	string job;
	void printInfo() //overriding printInfo function of Human base class
	{
		cout << "Muggle Informations" << endl;
		cout << "Name: " << name << endl;
		cout << "Age: " << age << endl;
		cout << "Job: " << job << endl;
	}
};

class Wizardkind : public Human
{
public:
	Wizardkind() {}
	Wizardkind(string wizardname, int wizardage, string wizardwand) 
	{
		name = wizardname;
		age = wizardage;
		wand = wizardwand;
	}
	string wand;
	virtual void printInfo() //declared as virtual function because it's the base class function
	{
		cout << "Wizardkind Informations" << endl;
		cout << "Name: " << name << endl;
		cout << "Age: " << age << endl;
		cout << "Wand: " << wand << endl;
	}
	void doSpell(string spell)
	{
		cout << name << " used spell: " << spell << endl;
	}
};

class Student : public Wizardkind
{
public:
	Student(string studentname, int studentage, string studentwand,string petname, string studenthouse)
	{
		name = studentname;
		age = studentage;
		houseName = studenthouse;
		wand = studentwand;
		pet = petname;
	}
	string pet;
	string houseName;
	void printInfo() //overriding printInfo function of Wizardkind base class
	{
		cout << "Student Wizardkind Informations" << endl;
		cout << "Name: " << name << endl;
		cout <<"Age: " << age << endl;
		cout << "House: " << houseName << endl;
		cout << "Wand: " << wand << endl;
		cout << "Pet: " << pet << endl;
	}
	void feedPet()
	{
		cout << name << " fed " << pet << endl;
	}
};

class GrownUp : public Wizardkind
{
public:
	GrownUp(string grownupname, int grownupage, string grownupwand,string grownupjob)
	{
		name = grownupname;
		age = grownupage;
		wand = grownupwand;
		job = grownupjob;
	}
	string job;
	void printInfo() //overriding printInfo function of Wizardkind base class
	{
		cout << "Grownup Wizardkind Informations" << endl;
		cout << "Name: " << name << endl;
		cout << "Age: " << age << endl;
		cout << "Wand: " << wand << endl;
		cout << "Job: " << job << endl;
	}
};


int main(){

	Muggle vernon("Vernon Dursley", 50, "Director at Grunnings");
	vernon.printInfo();
	cout << endl;

	Student Harry("Harry Potter", 16, "Phoenix Feather", "Hedwig", "Gryffindor");
	Harry.printInfo();
	cout << endl;

	GrownUp Dumbledore("Albus Dumbledore", 110, "Elder Wand", "Headmaster");
	Dumbledore.printInfo();
	cout << endl;

	Dumbledore.doSpell("Expecto Patronum");
	cout << endl;

	Harry.doSpell("Expelliarmus");
	cout << endl;

	Harry.feedPet();
	cout << endl;

	Student Ginny("Ginny Weasley", 15, "Yew wood", "Arnold", "Gryffindor");
	GrownUp Snape("Severus Snape", 35, "Dragon Heartstring", "Potion Master");
	Student Hermione("Hermione Granger", 16, "Vine", "Crookshanks", "Gryffindor");
	Human hArray[6];
	hArray[0] = vernon;
	hArray[1] = Harry;
	hArray[2] = Dumbledore;
	hArray[3] = Ginny;
	hArray[4] = Snape;
	hArray[5] = Hermione;
	Human * hPtr;
	for (int i = 0; i < 6; i++) {
		cout << endl;
		hPtr = &hArray[i];
		hPtr->printInfo();
	}
	cout << endl;

	system("pause");
	return 0;
}
