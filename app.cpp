#include	<iostream>
#include	<fstream>
#include	<cstdlib>
#include	<cstdio>
#include	<ctime>
#include	<iomanip>		// For output manipulation
#include	"BST.h"
#include    "Student.h"

using namespace std;


/*========================================= Assignment functions ================================================*/
bool readFile(const char *, BST *);
int menu();


/*============================================ Extra functions ==================================================*/
bool CheckFile(string);			// To check file if it is empty or exist

bool CheckID(BST* ,int);		// To check if the ID is duplicated
bool CheckID2(BTNode*, int);


/*=========================================== Main Function =====================================================*/
int main() {

	// Variable declaration
	BST t1, t2;
	type stu;
	bool next = true;
	int source = 0, order = 0;
	char fileName[100];

	cout << "\n\n\tWelcome to Student Record Program !\n\n";

	// Main function
	do {

		system("Pause");

		switch (menu())
		{
		case 1:

			system("cls");

			cout << "=====================================================\n"
				<< right << setw(34) << "READ DATA TO BST\n"
				<< "=====================================================\n";
			
			cout << "Enter student record file to be read: ";
			cin >> fileName;

			system("cls");			
			cout << "===============================================================================\n"
				<< right << setw(45) <<"READ DATA FROM \"" << fileName << "\"\n"
				<< "===============================================================================\n";

			if (readFile(fileName, &t1)) {
				cout << "===============================================================================\n";
				cout << "Successfully read the file into BST!\n\n";
			}
			else cout << "\nThe file cannot be read!\n\n";

			break;


		case 2:

			system("cls");

			cout << "=====================================================\n"
				<< right << setw(35) << "PRINT DEEPEST NODES" << endl
				<< "=====================================================\n\n";

			if (t1.deepestNodes()) {
				cout << "\n=====================================================\n"
					<< "All the deepest nodes have been successfully printed!\n\n";
			}
			else cout << "Error! The tree is empty!" << endl << endl;

			break;


		case 3:

			system("cls");

			cout << "=====================================================\n"
				<< right << setw(35) << "DISPLAY STUDENT\n"
				<< "=====================================================\n"
				<< right << setw(30) << "Sources\n"
				<< "-----------------------------------------------------\n"
				<< right << setw(38) << "(1): Display to screen\n"
				<< right << setw(37) << "(2): Print it to file\n"
				<< "-----------------------------------------------------\n"
				<< right << setw(30) << "Order\n"
				<< "-----------------------------------------------------\n"
				<< right << setw(38) << "(1): Asscending order\n"
				<< right << setw(38) << "(2): Descending order\n"
				<< "-----------------------------------------------------\n";
			
			// Input Validation
			while (true) 
			{
				cout << "Enter the source: ";
				cin >> source;
				if (cin.fail() || source < 1 || source > 2)
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Invalid input! Please enter between 1 - 2.\n\n";
					continue;
				}
				cout << "Enter the order : ";
				cin >> order;
				if (cin.fail() || order < 1 || order > 2)
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Invalid input! Please enter between 1 - 2.\n\n";
					continue;
				}
				break;
			}

			if (t1.display(order, source))
				cout << "Successfully print the all students!\n\n";
			else cout << "\nError! The tree is empty!\n\n";
			break;
			

		case 4:

			system("cls");
			cout << "=====================================================\n"
				<< right << setw(35) << "CLONE SUBTREE\n" 
				<< "=====================================================\n";

			cout << "Enter the student id (subtree) to be cloned: " ;
			cin >> stu.id;

			if (t2.CloneSubtree(t1, stu)) {

				cout << "\nSuccessfully clone the subtree!\n\n";
				system("Pause");
				system("cls");
				cout << "=======================================================================\n"
					<< right << setw(45) << "TREE in PreOrder\n"
					<< "=======================================================================\n\n";

				// Call function to print t1 in pre-order
				t1.preOrderPrint();
				
				cout << "=======================================================================\n"
					<< right << setw(50) << "CLONE SUBTREE in PreOrder\n"
					<< "=======================================================================\n\n";

				// Call function to print t2 in pre-order
				t2.preOrderPrint();
				cout << "=======================================================================\n";
				// Call function to clear all content in t2
				t2.ClearSubtree();
			}
			else cout << "Cannot clone subtree!\n";
			break;


		case 5:

			system("cls");
			cout << "=====================================================\n"
				<< right << setw(35) << "PRINT LEVEL NODES" << endl
				<< "====================================================\n\n";

			if (t1.printLevelNodes()) {
				cout << "\n=====================================================\n"
					<< "Successfully print all the nodes in each level!\n\n";
			}

			else cout << "Error! The tree is empty!\n\n";

			break;


		case 6:

			system("cls");
			cout << "=====================================================\n"
				<< right << setw(33) << "PRINT PATH" << endl
				<< "=====================================================\n";

			if (t1.printPath()) {
				cout << "\n=====================================================\n"
					<< "Successfully print all the paths!\n\n";
			}

			else cout << "Error! The tree is empty!\n\n";

			break;

		case 7:

			cout << endl << "You are quitting...\n";
			system("Pause");

			next = false;	// Set the flag to exit the while loop, thus exit the program

			break;
		}
	} while (next); // Continue to iterate (display the menu) when case 7 is not selected

	system("cls");
	cout <<"\n\n\tThank you for using the program.\n\t\tHave a nice day!\n\n";

	system("pause");
	return 0;
}


/*============================================== Function(a) =====================================================*/


// To read student records from a text file and store them into a BST
bool readFile(const char* filename, BST* t1) {

	// Variable declaration
	int studCount = 0, duplicatedID = 0;
	char discard[30];
	Student student;
	ifstream inFile(filename);

	// Check if the file exist or is empty
	if (!CheckFile(filename)) return false;		

	// Read value from student.txt and store in list1
	while (inFile >> discard >> discard >> discard >> student.id)
	{
		inFile >> discard >> discard;
		inFile.ignore();
		inFile.getline(student.name, 256);
		inFile >> discard >> discard;
		inFile.ignore();
		inFile.getline(student.address, 256);
		inFile >> discard >> discard >> student.DOB;
		inFile >> discard >> discard >> discard >> student.phone_no;
		inFile >> discard >> discard >> student.course;
		inFile >> discard >> discard >> student.cgpa;
		
		if (CheckID(t1, student.id)) {
			duplicatedID++;
			continue;
		}
		t1->insert(student);
		++studCount;
	}

	if (duplicatedID > 0)
		cout << "\nThere is/are " << duplicatedID << " duplicated student record(s) will not be read from \"" << filename << "\".\n";

	cout << "\nA total of " << studCount << " student record(s) have been successfully read.\n\n";
	
	return true;
}


/*============================================== Function(h) =====================================================*/


int menu() {
	
	// Variable declaration
	int choice;

	// Display menu to user
	system("cls");
	cout << endl << endl << "=====================================================\n"
		<< right << setw(40) << "  __  __  ___  _  _  _   _  " << endl
		<< right << setw(40) << " |  \\/  || __|| \\| || | | | " << endl
		<< right << setw(40) << " | |\\/| || _| | .` || |_| | " << endl
		<< right << setw(40) << " |_|  |_||___||_|\\_| \\___/  " << endl
		<< "=====================================================\n"
		<< "\t(1) Read data to BST\n"
		<< "\t(2) Print deepest nodes\n"
		<< "\t(3) Display student\n"
		<< "\t(4) Clone Subtree\n"
		<< "\t(5) Print Level Nodes\n"
		<< "\t(6) Print Path\n"
		<< "\t(7) Exit\n"
		<< "=====================================================\n";


	// Input Validation
	while (true) 
	{
		cout << "Enter your choice: ";
		cin >> choice;

		// Input validation for incompatible data type & out of range
		if (cin.fail() || choice < 1 || choice > 7)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input! Please enter between 1 - 7.\n\n";
			continue;
		}
		return choice;
	}
}


/*========================== Extra function 1: Check file existanace and availability =============================*/

bool CheckFile(string filename) { 

	// Varaible declaration
	ifstream inFile(filename);
	string line;

	// Case 1: File does not exist
	if (!inFile) {
		cout << "Error! \"" << filename << "\" does not exist ...\n";
		return false;
	}

	// Move the get pointer to the end of the file (position 0 for empty file)
	inFile.seekg(0, ios::end);
	
	// The get pointer is at position 0 if the file is empty
	// Case 2: File exists but not empty
	if (inFile.tellg() != 0) {
		return true;
	}
	
	// Case 3: File exists but empty
	else{
		cout << "Error! \"" << filename << "\" is an empty file ...\n";
		return false;
	}
}

/*========================== Extra function 2: Check if the Student ID is duplicated =============================*/

bool CheckID(BST* t1, int ID) {
	if (t1->root == NULL) return false;
	return CheckID2(t1->root, ID);
}

bool CheckID2(BTNode* cur, int ID) {
	if (cur == NULL) return false;
	if (cur->item.compare3(ID))
		return true;
	if (ID < cur->item.id)
		return CheckID2(cur->left, ID);
	else
		return CheckID2(cur->right, ID);
}