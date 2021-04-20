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
#include <stdio.h>
#include <string> 
#include <cstring>
#include <iomanip>
#include "node.h"

using namespace std;

node::node() {
	last[0] = '\0';
	first[0] = '\0';
	id = 0;
	link = NULL;
}

node::node(char* l, char* f, unsigned int num, node* next) {
	strncpy(last, l, 30);
	strncpy(first, f, 20);
	id = num;
	link = next;
}

string node::getLast() {
	int i = 0;
	string s = "";
	while (last[i] != '\0' && i<30) {
		s = s + last[i];
		i++;
	}
	return s;
}

string node::getFirst() {
	int i = 0;
	string s = "";
	while (first[i] != '\0' && i<20) {
		s = s + first[i];
		i++;
	}
	return s;
}

unsigned int node::getID() {
	return id;
}

node* node::getLink() {
	return link;
}

void node::setLast(char* l) {
	strncpy(last, l, 30);
}

void node::setFirst(char* f) {
	strncpy(first, f, 20);
}

void node::setID(unsigned int num) {
	id = num;
}

void node::head_insert(node*& head, char* l,char* f,unsigned int num) {
	node* ptr;
	ptr = new node;

	strncpy(ptr->last, l, 30);
	strncpy(ptr->first, f, 20);
	ptr->id = num;

	ptr->link = head;
	head = ptr;
}

node* node::search(node* head, unsigned int target) {
	node* here = head;

	if (here == NULL) {
		return NULL;
	}
	else {
		while (here->id != target && here->link != NULL) 
			here = here->link;
		if (here->id == target)
			return here;
		else
			return NULL;	
	}
}

void node::insert(node* after_me, char* l, char* f, unsigned int num) {
	node* ptr;
	ptr = new node;

	strncpy(ptr->last, l, 30);
	strncpy(ptr->first, f, 20);
	ptr->id = num;

	ptr->link = after_me->link;
	after_me->link = ptr;
}

void node::remove(node* before) {
	node* discard;

	discard = before->link;
	before->link = discard->link;
	delete discard;
}



