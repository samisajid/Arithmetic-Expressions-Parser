#include "pch.h"
#include <iostream>

using namespace std;

int expression();
const char toParse[] = "3+(5+(4*3))-12";
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
	int result = get()-'0';
	while (peek() >= '0' && peek() <= '9')
	{
		result = 10 * result + get()-'0';
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
	string allowed = "0123456789 /+*-()";
	int i;
	for (i = 0; i < strlen(expr); i++) {
		if (expr[i] == '/') {
			if (expr[i + 1] == '0') {
				cout << "You cannot divide by zero, try again";
				return 0;
			}
		}
		if (allowed.find(expr[i]) == string::npos) {
			//this checks if the element i is in the allowed list.
			cout << "a '"<<expr[i]<<"' is trailing, get rid of it and try again";
			//this is returned when the loop finds the first not allowed element.
			return 0;
		}
	}
	
	int result = expression();
	if (error == false) {
		cout << "Your expression '"<< toParse <<"' equals: "<<result << endl;
	}
	
	return 0;
}
