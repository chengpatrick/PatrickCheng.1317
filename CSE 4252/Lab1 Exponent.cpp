//CSE 4252 Lab1
//Author: Patrick Cheng
#include<iostream>
using namespace std;

int main()
{
	int exp, digit;
	double base, ans = 1;
	char correct_num, correct_dig;
	bool error_flag = false;
	do
	{
		correct_num = ' ';
		cout << "Enter the number for your base and exponent, separate with space:";
		cin >> base >> exp;
		error_flag = cin.fail();
		cin.clear();
		cin.ignore(200, '\n');
		if (error_flag)
		{
			cout << "Input(s) is invalid\n";
			correct_num = 'n';
		}
		else
		{
			cout << "The base you entered is " << base <<
				" and the exponent you entered is " << exp << "\n";
			while (tolower(correct_num) != 'y' && tolower(correct_num) != 'n')
			{
				cout << "Are these numbers correct? (Y/N) ";
				cin >> correct_num;
			}
		}
	} while (tolower(correct_num) == 'n');
	if (base != 0)
	{
		int exp_counter = exp;
		if (exp < 0)
		{
			exp_counter = exp_counter * (-1);
		}
		for (int i = 0; i < exp_counter; i++)
		{
			ans = ans * base;
		}
		if (exp < 0)
		{
			ans = 1 / ans;
		}
	}
	do
	{
		correct_dig = ' ';
		cout << "How many digits after the deciaml point should be used? ";
		cin >> digit;
		cout << base << " to the power of " << exp << " is ";
		cout.precision(digit);
		if (base == 0)
		{
			if (exp == 0)
			{
				cout << "undefined\n";
			}
			else
			{
				ans = 0;
				cout << fixed << ans << "\n";
			}
		}
		else
		{
			cout << fixed << ans << "\n";
		}
		while (tolower(correct_dig) != 'y' && tolower(correct_dig) != 'n')
		{
			cout << "Display result with different number of digits"
				<< " after the decimal point? (Y/N) ";
			cin >> correct_dig;
		}
	} while (tolower(correct_dig) == 'y');
	cout << "Thank you for using!\n";
	return 0;
}