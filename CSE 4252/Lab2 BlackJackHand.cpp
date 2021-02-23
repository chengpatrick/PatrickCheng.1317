//CSE 4252 Lab2 Blackjack Scores
//Author: Patrick Cheng
//compilation command: g++ -o lab2 lab2.cpp
//then type lab2 to run the code

#include<iostream>
using namespace std;
int setHandValue(char card1, char card2, char card3, char card4, char card5, int
	aceCount);
// Input: card faces; if less than 5 cards, additional ones are set to 0
// Returns a value of the hand or 0 if illegal card given or 5 identical cards
// Calls setValueCard()
int setValueCard(char card);
// Returns a numerical value of the card or 0 if an illegal card
void reportValue(int handValue);
// Displays score handValue, including comments Blackjack & Busted
int setHandValue(char card1, char card2, char card3, char card4, char card5, int
	aceCount)
{
	int handValue = 0;
	handValue += setValueCard(card1) + setValueCard(card2) + setValueCard(card3) +
		setValueCard(card4) + setValueCard(card5);
	if (aceCount > 0)
	{
		if (aceCount > 1)
			while (aceCount > 1)
			{
				handValue -= 10;
				aceCount--;
			}
		if (handValue > 21)
			handValue -= 10;
	}
	return handValue;
}
int setValueCard(char card)
{
	int value = 0;
	char c = tolower(card);
	switch (c)
	{
	case 'a':
		value = 11;
		break;
	case 't':
		value = 10;
		break;
	case 'j':
		value = 10;
		break;
	case 'q':
		value = 10;
		break;
	case 'k':
		value = 10;
		break;
	default:
		value = c - '0';
	}
	if (value < 2 || value>13)
		value = 0;
	return value;
}
void reportValue(int handValue)
{
	cout << "The value of your hand: " << handValue;
	if (handValue == 21)
		cout << " --> Blackjack";
	else if (handValue > 21)
		cout << " --> Busted";
	cout << endl;
}
int main()
{
start:
	int num;
	char input, cards, card1, card2, card3, card4, card5;
	bool error_flag;
	int value, handValue, aceCount=0;
	//Enter number of cards
	cout << "Enter a number of cards (2-5): ";
	cin >> num;
	error_flag = cin.fail();
	cin.clear();
	cin.ignore(200, '\n');
	//check if range is valid
	if (num < 2 || num>5)
		error_flag = true;
	//all errors go here
error:
	if (error_flag)
	{
		cout << "Input is invalid. You may try again." << endl;
		//all restarts go here
	restart:
		cout << "Type Q or q to quit, or any other character to try again: ";
		cin >> input;
		cout << "You typed: " << input << endl;

		if (tolower(input) == 'q')
			goto quit;
		else
			goto start;
	}
	cout << "Number of cards entered: " << num << endl;
	//card1=card2=card3=card4=card5='n';
	cout << "Enter the faces of the cards, 2-9, t, j, q, k, a: ";
	//read the faces of the cards
	for (int i = 0; i < num; i++)
	{
		cin.get(cards);
		if (cards == 'a')
			aceCount++;
		if (i == 0)
			card1 = cards;
		if (i == 1)
			card2 = cards;
		if (i == 2)
			card3 = cards;
		if (i == 3)
			card4 = cards;
		if (i == 4)
			card5 = cards;
		if (cards == ' ')
			i--;
		else if (((cards - '0') > 9 || (cards - '0') < 2) && tolower(cards) != 'a' && tolower(cards)!= 't' &&tolower(cards) != 'j' && tolower(cards) != 'q' && tolower(cards) != 'k')
		{
			error_flag = true;
			cin.clear();
			cin.ignore(200, '\n');
			goto error;
		}
	}
	error_flag = cin.fail();
	cin.clear();
	cin.ignore(200, '\n');
	if (error_flag)
		goto error;
	cout << "Faces of cards entered= ";
	cout << card1 << " " << card2 << " " << card3 << " " << card4 << " " << card5 << endl;
	//error if all 5 cards are the same
	if (tolower(card1) == tolower(card2) && tolower(card3) == tolower(card4) && tolower(card1) == tolower(card3) && tolower(card4) == tolower(card5))
	{
		error_flag = true;
		goto error;
	}
	handValue = setHandValue(card1, card2, card3, card4, card5, aceCount);
	reportValue(handValue);
	goto restart;
quit:
	return 0;
}