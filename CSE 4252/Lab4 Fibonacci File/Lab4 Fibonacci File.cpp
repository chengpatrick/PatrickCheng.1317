// 4252lab4.cpp
//Author: Patrick Cheng
//compilation command: g++ -o lab4 lab4.cpp
//then type lab4 to run the code
//remember to make the window bigger so it can show all the numbers in a row

//project name: Fibonacci File

#include <iostream>
#include <math.h>
#include <fstream>
#include <iomanip>

using namespace std;

const int four = 4, ten = 10;

// converts character array to string and returns it 
string convertToString(char* a, int size);

// converts character array to string and returns it 
string convertToString(char* a, int size)
{
	string s = a;
	return s;
}

int main()
{
	bool error_flag = false;
	int i = 0; //counter

	//var used in part 1
	int N = 0;
	int k = 0;
	char FILE[ten], temp[four];
	char next;
	string f; //file string
	string file_name, file_odd_name, file_even_name;
	int f_size,output_count=0;

	//var use in part 2
	int line_count = 0; //4 num per line
	ofstream out;
	ifstream in;
	int ele; //number of elements in file, same as N
	int median_pos; //position of median num
	double median = 0;
	unsigned long int number;
	int in_count=0,median_count=0;
	bool N_isOdd,num_isOdd;

	//var use in part 3
	ofstream out_even, out_odd;
	int odd_line_count = 0, even_line_count = 0;
	int odd_total = 0, even_total = 0;
	ifstream in_odd, in_even;
	int odd_median_pos, even_median_pos,odd_median_count=0,even_median_count=0;
	double odd_median=0, even_median=0;

	//part 1

	//enter number N
	cout << "Enter positive integer N (up to 4 digits): ";
	cin.get(next);
	while (next != '\n') {
		temp[i] = next;
		if (i < four) {
			if (temp[i] - '0' < 0 || temp[i] - '0' >9) goto error;
		}
		else goto error;
		//cout << "N: " << N[i] << endl;
		i++;
		cin.get(next);
	}
	i--;
	k = i;
	//store the int in variable N
	while (i > 0) {
		N +=(int)((temp[k-i]-'0') * pow(10, i));
		i--;
	}
	N += temp[k - i] - '0';
	if (N == 0)goto error;
	cout << "N= " << N << endl;

	//enter file name FILE
	i = 0;
	cout << "Enter the file name (up to 10 characters): ";
	cin.get(next);
	while (next != '\n') {
		FILE[i] = next;
		i++;
		cin.get(next);
	}
	FILE[i] = '\0';
	f_size = sizeof(FILE) / sizeof(char);
	f = convertToString(FILE, f_size);
	cout << "File name: " << f << endl;

	//part 2
	cout << "1. File "<<f<<" contents: "<<endl;
	//variables to store Fibonacci nums
	// x=y+z
	// x is newest, z is oldest
	unsigned long int x, y, z;
	z = 1; y = 1;
	x = y + z;
	file_name = f + ".txt";
	out.open(file_name);
	output_count = 3;

	if (N >= 3) {
		out << setw(22) << z << setw(22) << y << setw(22) << x << setw(22);
		cout << setw(22) << z << setw(22) << y << setw(22) << x << setw(22);
		line_count = 3;
	}
	if (N == 2) {
		out << setw(22) << z << setw(22) << y << setw(22);
		cout << setw(22) << z << setw(22) << y << setw(22);
		line_count = 2;
		output_count = 2;
	}if (N == 1) {
		out << setw(22) << z << setw(22);
		cout << setw(22) << z << setw(22);
		line_count = 1;
		output_count = 1;
	}

	ele = N;

	while (ele > 3) {
		z = y;
		y = x;
		x = y + z;
		if (x < y) {
			cout << "Overflow" << endl; 
			break;
		}
		output_count++;
		out << x<<setw(22);
		cout << x << setw(22);
		line_count++;

		if (line_count == 4) {
			out << endl;
			cout << endl;
			line_count = 0;
		}

		ele--;
	}
	out.close();
	cout <<setw(0)<<endl<<endl<< "Total numbers in " << f << " file= " << output_count<<endl;

	//part 1 finished

	//part 2
	if (output_count % 2 == 0) {
		N_isOdd = false;
		median_pos = output_count / 2;
	}
	else {
		N_isOdd = true;
		median_pos = (output_count + 1) / 2;
	}

	in.open(file_name);
	file_odd_name = f + ".odd.txt";
	file_even_name = f + ".even.txt";
	out_odd.open(file_odd_name);
	out_even.open(file_even_name);

	out_odd << setw(22);
	out_even << setw(22);

	if (in.is_open()) {
		while (!in.eof()) {
			in >> number;
			in_count++;

			//find odd and even
			if (number % 2 == 0) {
				//even
				out_even << number << setw(22);
				even_line_count++;
				even_total++;
				if (even_line_count == 4) {
					out_even << endl;
					even_line_count = 0;
				}
			}
			else {
				//odd
				out_odd << number << setw(22);
				odd_line_count++;
				odd_total++;
				if (odd_line_count == 4) {
					out_odd << endl;
					odd_line_count = 0;
				}
			}

			if (N_isOdd) {
				if (in_count == median_pos) median = number;
			}
			else {
				if (in_count == median_pos && median_count<2) {
					median = median + number;
					median_count++;
					median_pos++;
				}
			}
		}
	}

	out_odd.close();
	out_even.close();

	if (!N_isOdd) median /= 2;
	in.close();

	cout <<endl<<"2. The median number in " << f << " file is: " << median<<endl;

	//part 2 finished
	if (odd_total % 2 != 0) {
		odd_median_pos = (odd_total + 1) / 2;
	}
	else {
		odd_median_pos = odd_total / 2;
	}

	if (even_total % 2 != 0) {
		even_median_pos = (even_total + 1) / 2;
	}
	else {
		even_median_pos = even_total / 2;
	}


	in_odd.open(file_odd_name);
	in_even.open(file_even_name);
	i = 0;

	if (in_odd.is_open()) {
		while (!in_odd.eof()) {
			in_odd >> number;
			i++;
			if (odd_total % 2 != 0) {
				if (i == odd_median_pos) {
					odd_median = number;
				}
			}
			else {
				if (i == odd_median_pos && odd_median_count<2) {
					odd_median += number;
					odd_median_count++;
					odd_median_pos++;
				}
			}
		}
	}
	if (odd_total % 2 == 0) {
		odd_median /= 2;
	}

	i = 0;
	if (in_even.is_open()) {
		while (!in_even.eof()) {
			in_even >> number;
			i++;
			if (even_total % 2 != 0) {
				if (i == even_median_pos) {
					even_median = number;
				}
			}
			else {
				if (i == even_median_pos && even_median_count < 2) {
					even_median += number;
					even_median_count++;
					even_median_pos++;
				}
			}
		}
	}
	if (even_total % 2 == 0) {
		even_median /= 2;
	}

	in_odd.close();
	in_even.close();

	cout << endl;
	cout << "3. Total numbers in " << f << ".even file= " << even_total<<endl;
	cout << "Total numbers in " << f << ".odd file= " << odd_total << endl;
	cout << "The median number in " << f << ".even is: " << even_median << endl;
	cout << "The median number in " << f << ".odd is: " << odd_median << endl;

	//part4
	in_even.open(file_even_name);
	out_odd.open(file_odd_name, ios_base::app);

	out_odd << endl;
	if (odd_line_count != 0)out_odd << endl;
	odd_line_count = 0;
	number = 0;
	if (in_even.is_open()) {
		while (!in_even.eof()) {
			in_even >> number;
			if (number > 0) {
				out_odd << number << setw(22);
				odd_line_count++;
				odd_total++;
				if (odd_line_count == 6) {
					out_odd << endl;
					odd_line_count = 0;
				}
			}
		}
	}

	out_odd.close();
	in_even.close();

	cout << endl;
	cout << "4. The total count in " << f << ".odd is now: " << odd_total << endl;

	cout << endl << "5. File " << f << ".odd content: " << endl;

	in_odd.open(file_odd_name);

	odd_line_count = 0;
	num_isOdd = true;
	cout << setw(22);
	number = 0;

	if (in_odd.is_open()) {
		while (!in_odd.eof()) {
			in_odd >> number;		
			if (number > 0) {
				if (num_isOdd) {
					if (number % 2 == 0) {
						num_isOdd = false;
						odd_line_count = 0;
						cout << endl << endl;
					}
				}
				if (number % 2 != 0) {
					if (odd_line_count == 4) {
						cout << endl;
						odd_line_count = 0;
					}
				}
				else {
					if (odd_line_count == 6) {
						cout << endl;
						odd_line_count = 0;
					}
				}
				cout << number;
				cout << setw(22);
				odd_line_count++;
			}
		}
	}
	cout << endl;
	in_odd.close();

	goto end;

error:
	cout << "Error, invalid input." << endl;
	cin.clear();
	cin.ignore(200, '\n');
	goto end;

end:
	cout <<endl<< "Exiting program" << endl;
	return 0;
}
