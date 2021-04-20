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

using namespace std;

class node
{
public:

    // here include declarations of constructors
    
    //constructor
    node();
    
    //constructor
    node(char* l, char* f, unsigned int num, node* next);

    // here include declarations of accessor and mutator functions

    //retrieve last name
    string getLast();

    //retrieve first name
    string getFirst();

    //retrieve next node from list
    node* getLink();

    //retrieve id
    unsigned int getID();

    //set last name
    void setLast(char* l);

    //set first name
    void setFirst(char* f);

    //set id
    void setID(unsigned int num);

    //add node to front of list
    void head_insert(node*& head, char* l, char* f, unsigned int num);

    //locate node in LL
    node* search(node* head, unsigned int target);

    //insert node inside of LL
    void insert(node* after_me, char* l, char* f, unsigned int num);

    //remove node from LL
    void remove(node*before);

private:

    // here include declaration of private functions, if you need.

    char last[30];

    char first[20];

    unsigned int id;

    node* link;

};

