#include "pch.h"
#include <iostream>

using namespace std;

int expression();
char toParse[] = "3+(5+ (4-3 )-12";
const char* expr = toParse;
bool error = false;

char peek()
{
	return *expr;
}

char get()
{
	return *expr++;
}

int number()
{
	int result = get() - '0';
	while (peek() >= '0' && peek() <= '9')
	{
		result = 10 * result + get() - '0';
	}
	return result;
}

int factor()
{
	if (peek() >= '0' && peek() <= '9')
		return number();
	else if (peek() == '(')
	{
		get(); // '('
		int result = expression();
		get(); // ')'
		return result;
	}
	else if (peek() == '-')
	{
		get();
		return -factor();
	}
	error = true;
}

int mult()
{
	int result = factor();
	int tmp = 0;
	while (peek() == '*' || peek() == '/')
		if (get() == '*') {
			result *= factor();
		}

		else {
			tmp = factor();
			if (tmp == 0) {
				cout << "You cannot divide by zero, try again" << endl;
				error = true;
			}
			else
				result /= tmp;
		}

	return result;
}

int expression()
{
	while (peek() == ' ') {
		get();
	}
	int result = mult();
	while (peek() == ' ') {
		get();
	}
	while (peek() == '+' || peek() == '-')
		if (get() == '+')
			result += mult();
		else
			result -= mult();
	return result;
}

int main()
{
	string operators = "+-/*";
	string allowed = "0123456789 /+*-()";
	int i;
	int k=0;
	for (i = 0; i < strlen(toParse); i++) {
		if (toParse[i] != ' ') {
			toParse[k] = toParse[i];
			k++;
		}		
	}
	toParse[k] = '\0';

	cout << k << endl;
	cout << toParse << endl;
	for (i = 0; i < strlen(toParse); i++) {
		if (allowed.find(toParse[i]) == string::npos) {
			//this checks if the element i is in the allowed list.
			cout << "A '" << toParse[i] << "' is trailing, get rid of it and try again";
			//this is returned when the loop finds the first not allowed element.
			return 0;
		}
		if (operators.find(toParse[i]) != string::npos){
			if (operators.find(toParse[i + 1]) != string::npos){
			cout << "You cannot use two operatros " << toParse[i] <<toParse[i+1] << " consecutively.";
			return 0;
			}
		}
	}
	if (count(toParse, toParse + k, '(') > count(toParse, toParse + k, ')')) {
		cout << "Your result might be wrong as there are more '(' than ')'." << endl;
	}
	else if (count(toParse, toParse + k, '(') < count(toParse, toParse + k, ')')) {
		cout << "Your result might be wrong as there are more ')' than '('." << endl;
	}
	int result = expression();
	if (error == false) {
		cout << "Your expression '"<< toParse <<"' equals: "<<result <<"."<< endl;
	}
	
	return 0;
}
