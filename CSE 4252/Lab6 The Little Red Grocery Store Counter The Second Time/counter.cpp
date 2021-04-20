// 4252 Counter.cpp
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

Counter::Counter() {
	a = 0;
	s = 0;
	d = 0;
	f = 0;
	q = 9;
	w = 9;
	e = 9;
	r = 9;
	isadd = true;
}

istream& operator >>(istream& ins, Counter& c) {
	int num;
	ins >> num;

	if (num >= 1000) {
		c.r = num / 1000;
		num -= c.r * 1000;
	}
	if (num >= 100) {
		c.e = num / 100;
		num -= c.e * 100;
	}
	if (num >= 10) {
		c.w = num / 10;
		num -= c.w * 10;
	}
	if (num >= 1) {
		c.q = num;
	}

	return ins;
}

ostream& operator <<(ostream& outs, Counter& c) {
	int a, s, d, f;
	int ta,ts,td,tf;
	bool isadd;
	int count = 0;
	
	a = c.a;
	s = c.s;
	d = c.d;
	f = c.f;
	isadd = c.isadd;
	count= a + s * 10 + d * 100 + f * 1000;
	ta=a;
	ts=s;
	td=d;
	tf=f;

	// display the count value in the format $xx.xx; at the beginning it would be $00.00
	outs << "Current Count: $";

	if (count >= 0) {
		outs << f << d;
		outs << ".";
		outs << s << a;
	}
	else {
		if(a<0) a *= -1;
		if(s<0) s *= -1;
		if(d<0) d *= -1;
		if(f<0) f *= -1;
		outs << "-" <<f << d;
		outs << ".";
		outs << s << a;
	}

	outs << endl;
	//Counter mode is displayed, as ‘+’ for addition or ‘-‘ for subtraction
	outs << "Counter mode: ";
	if (isadd)outs << "+";
	else outs << "-";
	outs << endl;

	a=ta;
	s=ts;
	d=td;
	f=tf;

	return outs;
}


void Counter::reset() {
	a = 0;
	s = 0;
	d = 0;
	f = 0;

	isadd = true;
}

void Counter::operator --() {
	int count = a + s * 10 + d * 100 + f * 1000;
	a = 0;
	s = 0;
	d = 0;
	f = 0;

	if (isadd) {
		count++;
	}
	else {
		count--;
	}


		if (count >= 1000) {
			f = count / 1000;
			count -= f * 1000;
		}
		if (count >= 100) {
			d = count / 100;
			count -= d * 100;
		}
		if (count >= 10) {
			s = count / 10;
			count -= s * 10;
		}
		if (count >= 1) {
			a = count;
		}
	

		if (count <= -1000) {
			f = count / 1000;
			count += f * -1000;
			//f = f * -1;
		}
		if (count <= -100) {
			d = count / 100;
			count += d * -100;
			//d = d * -1;
		}
		if (count <= -10) {
			s = count / 10;
			count += s * -10;
			//s = s * -1;
		}
		if (count <= -1) {
			a = count;
		}
	
}

void Counter::operator -() {
	int count = a + s * 10 + d * 100 + f * 1000;
	a = 0;
	s = 0;
	d = 0;
	f = 0;

	if (isadd) {
		count+=10;
	}
	else {
		count-=10;
	}


		if (count >= 1000) {
			f = count / 1000;
			count -= f * 1000;
		}
		if (count >= 100) {
			d = count / 100;
			count -= d * 100;
		}
		if (count >= 10) {
			s = count / 10;
			count -= s * 10;
		}
		if (count >= 1) {
			a = count;
		}
	

		if (count <= -1000) {
			f = count / 1000;
			count += f * -1000;
			//f = f * -1;
		}
		if (count <= -100) {
			d = count / 100;
			count += d * -100;
			//d = d * -1;
		}
		if (count <= -10) {
			s = count / 10;
			count += s * -10;
			//s = s * -1;
		}
		if (count <= -1) {
			a = count;
		}
	
}

void Counter::operator +() {
	int count = a + s * 10 + d * 100 + f * 1000;
	a = 0;
	s = 0;
	d = 0;
	f = 0;

	if (isadd) {
		count+=100;
	}
	else {
		count-=100;
	}


		if (count >= 1000) {
			f = count / 1000;
			count -= f * 1000;
		}
		if (count >= 100) {
			d = count / 100;
			count -= d * 100;
		}
		if (count >= 10) {
			s = count / 10;
			count -= s * 10;
		}
		if (count >= 1) {
			a = count;
		}
	

		if (count <= -1000) {
			f = count / 1000;
			count += f * -1000;
			//f = f * -1;
		}
		if (count <= -100) {
			d = count / 100;
			count += d * -100;
			//d = d * -1;
		}
		if (count <= -10) {
			s = count / 10;
			count += s * -10;
			//s = s * -1;
		}
		if (count <= -1) {
			a = count;
		}
	
}

void Counter::operator ++() {
	int count = a + s * 10 + d * 100 + f * 1000;
	a = 0;
	s = 0;
	d = 0;
	f = 0;

	if (isadd) {
		count += 1000;
	}
	else {
		count -= 1000;
	}


		if (count >= 1000) {
			f = count / 1000;
			count -= f * 1000;
		}
		if (count >= 100) {
			d = count / 100;
			count -= d * 100;
		}
		if (count >= 10) {
			s = count / 10;
			count -= s * 10;
		}
		if (count >= 1) {
			a = count;
		}
	

		if (count <= -1000) {
			f = count / 1000;
			count += f * -1000;
			//f = f * -1;
		}
		if (count <= -100) {
			d = count / 100;
			count += d * -100;
			//d = d * -1;
		}
		if (count <= -10) {
			s = count / 10;
			count += s * -10;
			//s = s * -1;
		}
		if (count <= -1) {
			a = count;
		}
	
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

void Counter::pause()
{
	const int PAUSE_CONSTANT = 400000000; // you may like to adjust this constant
	cout << endl << "Pausing for you to read . . .\n";
	for (int X = 0; X < PAUSE_CONSTANT; X++)
	{
		X++; X--;
	}
}

bool Counter::underZero() {
	int count = f * 1000 + d * 100 + s * 10 + a;

	return(count < 0);
}

void Counter::add() {
	isadd = true;
}

void Counter::sub() {
	isadd = false;
}


