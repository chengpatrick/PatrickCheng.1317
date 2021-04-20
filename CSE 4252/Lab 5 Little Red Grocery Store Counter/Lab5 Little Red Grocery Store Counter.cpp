// 4252lab5.cpp
//Author: Patrick Cheng
//compilation command: g++ -o lab5 lab5.cpp
//then type lab5 to run the code
//project name: Little Red Grocery Store Counter
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;
struct Counter
{
public:
	Counter();
	Counter(int, int, int, int);
	void reset();
	void incr1();
	void incr10();
	void incr100();
	void incr1000();
	bool overflow();
	bool maxoverflow();
	void displayoverflow();
	void showA();
	void showS();
	void showD();
	void showF();
private:
	//a for units, s for tens, d for hundreds, f for thousands
	int a, s, d, f;
	//variables to hold overflow value
	//q for units, w for tens, e for hundreds, r for thousands
	int q, w, e, r;
};
Counter::Counter() {
	a = 0;
	s = 0;
	d = 0;
	f = 0;
	q = 9;
	w = 9;
	e = 9;
	r = 9;
}
Counter::Counter(int q1, int w1, int e1, int r1) {
	a = 0;
	s = 0;
	d = 0;
	f = 0;
	q = q1;
	w = w1;
	e = e1;
	r = r1;
}
void Counter::reset() {
	a = 0;
	s = 0;
	d = 0;
	f = 0;
}
void Counter::incr1() {
	a++;
}
void Counter::incr10() {
	s++;
}
void Counter::incr100() {
	d++;
}
void Counter::incr1000() {
	f++;
}
bool Counter::overflow() {
	int count = f * 1000 + d * 100 + s * 10 + a;
	int overflow_num = r * 1000 + e * 100 + w * 10 + q;
	return(count > overflow_num);
}
bool Counter::maxoverflow() {
	int count = f * 1000 + d * 100 + s * 10 + a;
	return(count > 9999);
}
void Counter::displayoverflow() {
	cout << "$" << r << e << "." << w << q;
}
void Counter::showA() {
	cout << a;
}
void Counter::showS() {
	cout << s;
}
void Counter::showD() {
	cout << d;
}
void Counter::showF() {
	cout << f;
}
void pause()
{
	const int PAUSE_CONSTANT = 400000000; // you may like to adjust this constant
	cout << endl << "Pausing for you to read . . .\n";
	for (int X = 0; X < PAUSE_CONSTANT; X++)
	{
		X++; X--;
	}
}
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
			cin >> num;
		if (cin.fail()) goto error;
		if (num >= 1000) {
			r = num / 1000;
			num -= r * 1000;
		}
		if (num >= 100) {
			e = num / 100;
			num -= e * 100;
		}
		if (num >= 10) {
			w = num / 10;
			num -= w * 10;
		}
		if (num >= 1) {
			q = num;
		}
		c = Counter(q, w, e, r);
	}
	else if (tolower(ch1) != 'd') goto error;
	//c.displayoverflow();
	while (ch1 != 'q' && ch1 != 'Q') {
		cout << "\033[2J\033[1; 1H"; //This is a string of special characters that clears a display
			// display the count value in the format $xx.xx; at the beginning it would be $00.00
			cout << "Current Count: $";
		c.showF(); c.showD();
		cout << ".";
		c.showS(); c.showA();
		cout << endl;
		cout << "Enter a character and follow without space, if needed, by a digit 1 - 9 (example: f3 to add $30.00) : \n"
			<< "Enter a for units\n"
			<< " s for tens\n"
			<< " d for hundreds\n"
			<< " f for thousands\n"
			<< " o to inquire about overflow\n"
			<< " r to reset counter\n"
			<< " m to inquire about capacity overflow\n"
			<< " Q or q at any time to quit.\n"
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
				c.incr1();
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
			break;
		case 's':
			while (digit > 0) {
				c.incr10();
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
				cout << "ALERT: OVERFLOW OVER $99.99 HAS OCCURRED " <<
					endl;
				cout << "RESULTS ARE NOT RELIABLE. RESET IF YOU WANT TO CONTINUE";
			}
			break;
		case 'd':
			while (digit > 0) {
				c.incr100();
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
				cout << "ALERT: OVERFLOW OVER $99.99 HAS OCCURRED " <<
					endl;
				cout << "RESULTS ARE NOT RELIABLE. RESET IF YOU WANT TO CONTINUE";
			}
			break;
		case 'f':
			while (digit > 0) {
				c.incr1000();
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
				cout << "ALERT: OVERFLOW OVER $99.99 HAS OCCURRED " <<
					endl;
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
				cout << "CAPACITY OVERFLOW HAS OCURRED. COUNT <= $99.99" <<
					endl;;
			}
			else {
				cout << "CAPACITY OVERFLOW HASN'T OCURRED. COUNT <= $99.99"<<endl;
			}
			break;
		case 'q':
			cout << "Exiting program..." << endl;
			break;
		default:
		invalid:
			cout << "INVALID INPUT ENTERED" << endl;
			break;
		}
		pause();
	}
	goto end;
error:
	cin.clear();
	cout << "Invalid input" << endl;
end:
	return 0;
}