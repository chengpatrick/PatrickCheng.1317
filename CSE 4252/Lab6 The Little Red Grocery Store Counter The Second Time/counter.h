// 4252 Counter.h
//Author: Patrick Cheng
//compilation command: g++ -o counter.o -c counter.cpp to create .o file
//then type g++ -o lab6 lab6.cpp counter.o
//last type lab6 to execute program
//project name: Little Red Grocery Store Counter: The Second Time

using namespace std;

class Counter {
public:
	Counter();
	friend istream& operator>>(istream&, Counter& c);
	friend ostream& operator<<(ostream&, Counter& c);
	void reset();
	void operator --();
	void operator -();
	void operator +();
	void operator ++();
	bool overflow();
	bool maxoverflow();
	void displayoverflow();

	bool underZero();
	void add();
	void sub();

	void pause();

private:
	//a for units, s for tens, d for hundreds, f for thousands
	int a, s, d, f;
	//variables to hold overflow value
	//q for units, w for tens, e for hundreds, r for thousands
	int q, w, e, r;
	//mode, true for addition and false for subtraction
	bool isadd;
};

