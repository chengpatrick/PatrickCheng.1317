// 4252lab6.cpp
//Author: Patrick Cheng
//compilation command: g++ -o counter.o -c counter.cpp to create .o file
//then type g++ -o lab6 lab6.cpp counter.o
//last type lab6 to execute program

//project name: Little Red Grocery Store Counter: The Second Time

#include <iostream>
#include <stdio.h>
#include <string> 
#include <iomanip>
#include "counter.h"

using namespace std;

int main()
{
	Counter c;
	char ch1;
	string next;
	int num;
	int digit;

	c.reset();

	cout << "Use default constructor or non-default constructor?" << endl;
	cout << "(Enter d for default or n for non-default) ";
	cin >> ch1;
	if (cin.fail()) goto error;
	if (tolower(ch1) == 'n') {
		int q, w, e, r;
		cout << "Enter the overflow value as a whole number (example: $12.34 as 1234): ";
		cin >> c;
		if (cin.fail()) goto error;
	}
	else if (tolower(ch1) != 'd') goto error;

	//c.displayoverflow();

	while (ch1 != 'q' && ch1 != 'Q') {

		cout << "\033[2J\033[1; 1H";    //This is a string of special characters that clears a display

		cout << c;
		cout << "Enter a character and follow, if needed, by a digit 1-9:\n"

			<< "Enter + if you want to add\n"

			<< "          - if you want to subtract\n"

			<< "          a for units\n"

			<< "          s for tens\n"

			<< "          d for hundreds\n"

			<< "          f for thousands\n"

			<< "          o to inquire about overflow\n"

			<< "          r to reset counter\n"

			<< "          m to inquire about capacity overflow\n"

			<< "          n  to inquire about under overflow\n"

			<< "          Q or q at any time to quit.\n"

			<< "Follow by pressing the return key in each case:";

		//cin >> ch1;

		cin >> next;
		if (cin.fail()) goto error;
		ch1 = next[0];
		if (next.length() == 2) {
			digit = next[1] - '0';
		}
		else if (next.length() == 1) {
			digit = 1;
		}
		else {
			goto invalid;
		}
		if (digit < 1 || digit>9) goto invalid;

		switch (tolower(ch1)) {

		case 'a':
			while (digit > 0) {
				--c;
				digit--;
			}

			if (c.overflow()) {
				cout << "\033[2J\033[1; 1H";
				cout << "ALERT: COUNT IS OVER THE MAXIMUM SET TO ";
				c.displayoverflow();
				cout << endl;
				cout << "RESULTS ARE NOT RELIABLE. RESET IF YOU WANT TO CONTINUE";
			}
			if (c.maxoverflow()) {
				cout << "\033[2J\033[1; 1H";
				cout << "ALERT: OVERFLOW OVER $99.99 HAS OCCURRED " << endl;
				cout << "RESULTS ARE NOT RELIABLE. RESET IF YOU WANT TO CONTINUE";
			}
			if (c.underZero()) {
				cout << "\033[2J\033[1; 1H";
				cout << "ALERT: UNDERFLOW UNDER $00.00 HAS OCCURRED " << endl;
				cout << "RESULTS ARE NOT RELIABLE. RESET IF YOU WANT TO CONTINUE";
			}
			break;

		case 's':
			while (digit > 0) {
				-c;
				digit--;
			}

			if (c.overflow()) {
				cout << "\033[2J\033[1; 1H";
				cout << "ALERT: COUNT IS OVER THE MAXIMUM SET TO ";
				c.displayoverflow();
				cout << endl;
				cout << "RESULTS ARE NOT RELIABLE. RESET IF YOU WANT TO CONTINUE";
			}
			if (c.maxoverflow()) {
				cout << "\033[2J\033[1; 1H";
				cout << "ALERT: OVERFLOW OVER $99.99 HAS OCCURRED " << endl;
				cout << "RESULTS ARE NOT RELIABLE. RESET IF YOU WANT TO CONTINUE";
			}
			if (c.underZero()) {
				cout << "\033[2J\033[1; 1H";
				cout << "ALERT: UNDERFLOW UNDER $00.00 HAS OCCURRED " << endl;
				cout << "RESULTS ARE NOT RELIABLE. RESET IF YOU WANT TO CONTINUE";
			}
			break;

		case 'd':
			while (digit > 0) {
				+c;
				digit--;
			}

			if (c.overflow()) {
				cout << "\033[2J\033[1; 1H";
				cout << "ALERT: COUNT IS OVER THE MAXIMUM SET TO ";
				c.displayoverflow();
				cout << endl;
				cout << "RESULTS ARE NOT RELIABLE. RESET IF YOU WANT TO CONTINUE";
			}
			if (c.maxoverflow()) {
				cout << "\033[2J\033[1; 1H";
				cout << "ALERT: OVERFLOW OVER $99.99 HAS OCCURRED " << endl;
				cout << "RESULTS ARE NOT RELIABLE. RESET IF YOU WANT TO CONTINUE";
			}
			if (c.underZero()) {
				cout << "\033[2J\033[1; 1H";
				cout << "ALERT: UNDERFLOW UNDER $00.00 HAS OCCURRED " << endl;
				cout << "RESULTS ARE NOT RELIABLE. RESET IF YOU WANT TO CONTINUE";
			}
			break;

		case 'f':
			while (digit > 0) {
				++c;
				digit--;
			}

			if (c.overflow()) {
				cout << "\033[2J\033[1; 1H";
				cout << "ALERT: COUNT IS OVER THE MAXIMUM SET TO ";
				c.displayoverflow();
				cout << endl;
				cout << "RESULTS ARE NOT RELIABLE. RESET IF YOU WANT TO CONTINUE";
			}
			if (c.maxoverflow()) {
				cout << "\033[2J\033[1; 1H";
				cout << "ALERT: OVERFLOW OVER $99.99 HAS OCCURRED " << endl;
				cout << "RESULTS ARE NOT RELIABLE. RESET IF YOU WANT TO CONTINUE";
			}
			if (c.underZero()) {
				cout << "\033[2J\033[1; 1H";
				cout << "ALERT: UNDERFLOW UNDER $00.00 HAS OCCURRED " << endl;
				cout << "RESULTS ARE NOT RELIABLE. RESET IF YOU WANT TO CONTINUE";
			}
			break;

		case 'o':
			cout << "Overflow test requested" << endl;
			if (c.overflow()) {
				"OVERFLOW HAS OCURRED. COUNT <= ";
				c.displayoverflow();
				cout << endl;
			}
			else {
				cout << "OVERFLOW HASN'T OCURRED. COUNT <= ";
				c.displayoverflow();
				cout << endl;
			}
			break;

		case 'r':
			c.reset();
			cout << "Reseting..." << endl;
			break;

		case 'm':
			cout << "Capacity overflow test requested" << endl;
			if (c.maxoverflow()) {
				cout << "CAPACITY OVERFLOW HAS OCURRED. COUNT <= $99.99" << endl;;
			}
			else {
				cout << "CAPACITY OVERFLOW HASN'T OCURRED. COUNT <= $99.949" << endl;
			}
			break;

		case 'n':
			cout << "Underflow test requested" << endl;
			if (c.maxoverflow()) {
				cout << "UNDERFLOW HAS OCURRED. COUNT < $00.00" << endl;;
			}
			else {
				cout << "UNDER HASN'T OCURRED. COUNT >= $00.00" << endl;
			}
			break;

		case 'q':
			cout << "Exiting program..." << endl;
			break;

		case '+':
			c.add();
			cout << "Counter is now changed to addition mode" << endl;
			break;

		case '-':
			c.sub();
			cout << "Counter is now changed to subtraction mode" << endl;
			break;

		default:
		invalid:
			cout << "INVALID INPUT ENTERED" << endl;
			break;
		}

		c.pause();

	}

	goto end;

error:
	cin.clear();
	cout << "Invalid input" << endl;

end:
	return 0;
}
