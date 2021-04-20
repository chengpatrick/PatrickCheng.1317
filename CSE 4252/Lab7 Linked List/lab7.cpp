//CSE 4252 Node.h
//Author: Patrick Cheng
//Project Name: Linked List

//compilation command: g++ -o node.o -c node.cpp to create .o file
//then: g++ -o lab7 lab7.cpp node.o
//last, type: lab7 to execute program

//Attention: In the lab description, it didn't state that program should ask for file name
//so the program reads the file "Data.7" on default
//name the file for testing data "Data.7" and type lab7 to run program
//program will read in the data in "Data.7" and create a linked list from there

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string> 
#include <cstring>
#include <iomanip>
#include "node.h"

int main()
{
	//used for reading data
	string next;
	string nextn;
	char l[30], f[20];
	unsigned int num = 0;

	//counting number of link
	int count = 0;

	ifstream file;
	file.open("Data.7");

	node* head = new node();
	node* list = NULL;

	node* temp_ptr = new node();
	node* temp_list = new node();

	node* empty = NULL;

	node* iter;
	bool dup = false;

	if (file.is_open()) {
		cout << "Creating a link list using data from Data.7 file" << endl;
		while (file >> next && file >> num) {

			string temp;
			int ppos;			

			//read in all data
			//file >> next;
			//file >> num;
			count++;

			ppos = next.find(",");
			temp = next.substr(0, ppos);
			strcpy(l, temp.c_str());
			temp = next.substr(ppos + 1, next.length());
			strcpy(f, temp.c_str());

			//temp_ptr->setLast(l);
			//temp_ptr->setFirst(f);
			//temp_ptr->setID(num);

			//print name and id to check

			/*
			temp_ptr->getLast();
			cout << " ";
			temp_ptr->getFirst();
			cout << " " << temp_ptr->getID() << endl;
			*/

			/*
			for (int i = 0; i < ppos+1; i++)
				cout << l[i];

			cout << " ";

			for (int i = 0; i < next.length()-ppos-1; i++)
				cout << f[i];

			cout << " " << num << endl;
			*/

			//check if duplicate
			dup = false;
			for (iter = list; iter != NULL; iter = iter->getLink()) {
				if (iter->getID() == num) {
					dup = true;
					break;
				}
			}

			//store all data in LL
			temp_list = list;
			if (!dup) {
				if (temp_list == NULL) {
					temp_list->head_insert(temp_list, l, f, num);
				}
				else {
					if (num < temp_list->getID()) {
						temp_list->head_insert(temp_list, l, f, num);
					}
					else {
						while (num > temp_list->getID()) {
							if (temp_list->getLink() == NULL || num < temp_list->getLink()->getID()) {
								temp_list->insert(temp_list, l, f, num);
							}
							else {
								temp_list = temp_list->getLink();
							}
						}
						temp_list = list;
					}
				}
			}
			else {
				cout << "Input: " << count << " last= ";
				count--;
				for (int i = 0; i < ppos + 1; i++)
					cout << l[i];
				cout << " first= ";
				for (int i = 0; i < next.length() - ppos - 1; i++)
					cout << f[i];
				cout << ". His/Her id= " << num << " already exists; Not added to list!" << endl;
			}
			list = temp_list;
		}

		file.close();
		cout << endl << "Link list created. Number of nodes: " << count << endl;

		char input = 'a';
		while (tolower(input) != 'e') {
			cout << "Enter p to display the  list, a to add a node,"
				<< endl << "      r to remove a node, d to destroy the list, e to exit : ";
			cin >> input;

			if (cin.fail()) {
				cin.clear();
				cin.ignore(200);
			}

			cout << "You entered: " << input << endl;

			//temp counter
			int k = 0;
			switch (tolower(input)) {

				//print list
			case 'p':
				k = 0;
				temp_list = list;
				if (temp_list == NULL) {
					cout << "List is empty" << endl;
				}
				while (temp_list != NULL) {
					k++;
					//cout << "not null" << endl;
					cout << setw(5) << k << setw(25) << temp_list->getLast() << setw(25)
						<< temp_list->getFirst() << setw(25) << temp_list->getID() << endl;
					temp_list = temp_list->getLink();
				}
				break;

			case 'a':

				cout << "Enter First Last and id: ";
				cin >> next >> nextn >> num;
				cout << "You entered: " << nextn << " " << next << " " << num<<endl;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(200);
				}
				cout << "Is it correct (y/n)? ";
				cin >> input;
				if (tolower(input) == 'y') {
					count++;
					strcpy(f, next.c_str());
					strcpy(l, nextn.c_str());
					//check if duplicate
					dup = false;
					for (iter = list; iter != NULL; iter = iter->getLink()) {
						if (iter->getID() == num) {
							dup = true;
							count--;
							break;
						}
					}

					//store data in LL
					temp_list = list;
					if (!dup) {
						if (temp_list == NULL) {
							temp_list->head_insert(temp_list, l, f, num);
						}
						else {
							if (num < temp_list->getID()) {
								temp_list->head_insert(temp_list, l, f, num);
							}
							else {
								while (num > temp_list->getID()) {
									if (temp_list->getLink() == NULL || num < temp_list->getLink()->getID()) {
										temp_list->insert(temp_list, l, f, num);
									}
									else {
										temp_list = temp_list->getLink();
									}
								}
								temp_list = list;
							}
						}
						cout << "Node added to the list; Number of nodes= " << count<<endl;
					}
					else {
						cout << "Id= " << num << " already exists; Not added to list!" << endl;
					}
					list = temp_list;
				}
				else if (tolower(input) != 'n')
					cout << "Invalid input" << endl;

				break;

			case 'r':
				cout << "Enter number of Node to remove: ";
				cin >> k;
				if (k<1 || k>count) {
					cout << "Invalid Node number" << endl;
				}
				else {
					cout << "You entered: " << k << endl;
					cout << "Is it correct (y/n)? ";
					cin >> input;
					if (tolower(input) == 'y') {
						count--;
						temp_list = list;
						if (k != 1) {
							for (int i = 0; i < k - 2; i++) {
								temp_list = temp_list->getLink();
							}
							temp_list->remove(temp_list);
							temp_list = list;
							list = temp_list;
						}
						else {
							list = list->getLink();
						}
						cout << "Node removed from the list; number of nodes= "<<count<<endl;
					}
					else if (tolower(input) != 'n')
						cout << "Invalid input" << endl;
				}
				break;

			case 'd':
				count = 0;
				cout<<"List has been destroyed; number of nodes= " << count << endl; 
				list = empty;
				break;

			case 'e':
				cout << "Exiting program..." << endl;
				break;

			default:
				cout << "Invalid input, please re-enter" << endl;
				break;

			}
		}

	}

	return 0;
}

