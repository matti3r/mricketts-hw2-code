#include <iostream>
#include <fstream>

#include "BinarySearchTree.h"

string treeToString(BinarySearchTree tree);
string toLower(string toConvert);

int main() {
	
	BinarySearchTree tree;

	for (int i = 1; i < 26; i++)
		tree.insert(Employee(rand() % 1000 + 1000, i + 20, "Matt" + to_string(i)));


	string userMenuOption;

	cout << "This program implements a binary search tree.";

	do {

		//print user options
		cout <<	"\n\n\n\nChoose one of the following options:\n"
				"Q: QUIT: Exits the program and saves the tree in specified file name" << "\n" <<
				"I: INSERT: Inserts a given record in the tree" << "\n" <<
				"R: REMOVE: Deletes record with the given key (id)" << "\n" <<
				"F: FIND: Search for a record with a given key and if found, print the name, and age" << "\n" <<
				"FMIN: FIND MIN: Find and print the record with the smallest key" << "\n" <<
				"FMAX: FIND MAX: Find and print the record with the largest key" << "\n" <<
				"E: MAKE EMPTY: Clears the binary search tree of all records" << "\n" <<
				"P: REPORT: Gives a listing of all records in the tree in ascending order of ID numbers" << "\n\n";

		// Get user input
		cin >> userMenuOption;
		
		// Implement menu
		if ("i" == toLower(userMenuOption)) {
			int id, age;
			string name;
			
			cout << "Add Record\n";
			cout << "ID: "; cin >> id;
			cin.ignore();
			cout << "Name: "; getline(cin, name);
			cout << "Age: ";  cin >> age;

			tree.insert(Employee(id, age, name));

			cout << "Record Added";

		} else if ("r" == toLower(userMenuOption)) {
			int id;

			cout << "Remove Record\nID: "; cin >> id;

			tree.remove(id);

			cout << "Record Removed";

		} else if ("f" == toLower(userMenuOption)) {
			int id;

			cout << "Find Record\nID: "; cin >> id;

			tree.find(id);

		} else if ("fmin" == toLower(userMenuOption)) {

			Employee temp = tree.findMin();

			cout << "The First Record is\n" << 
				"ID: " << temp.id << "\n"
				"Name: " << temp.name << "\n"
				"Age: " << temp.age;

		} else if ("fmax" == toLower(userMenuOption)) {

			Employee temp = tree.findMax();

			cout << "The Last Record is\n" <<
				"ID: " << temp.id << "\n"
				"Name: " << temp.name << "\n"
				"Age: " << temp.age;

		} else if ("e" == toLower(userMenuOption)) {
			
			tree.makeEmpty();
			
			cout << "Tree is Empty";

		} else if ("p" == toLower(userMenuOption)) {
			
			cout << "Employee Report:\n";

			tree.report();
			
		} else if ("q" != toLower(userMenuOption)){
			cout << "Invalid Input";
		};


	} while (toLower(userMenuOption) != "q");

	
	return 0;
}

string treeToString(BinarySearchTree tree) {
	
	Employee min;
	string retString = "";
	
	while (!tree.isEmpty()) {
		min = tree.findMin();
		retString += to_string(min.id) + "," + min.name + "," + to_string(min.age) + "\n";
		if (min.id != -1)
			tree.remove(min.id);
	}

	return retString;
}

string toLower(string toConvert) {
	
	for (int i = 0; i < toConvert.length(); i++)
	{
		toConvert[i] = tolower(toConvert[i]);
	}
	
	return toConvert;
}