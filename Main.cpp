#include "pch.h"
#include <iostream>

using namespace std;

//This is the expression to parse, put your expression here
char toParse[] = "3+(5+(4*3))-12";
//Pointer to the elements of the expression
const char* expr = toParse;
//An error flag that will stop further processing if true
bool error = false;
//This is the main parsing function that will call recursively other functions and be called also by some functions
int expression();

//this will return the current value pointed by the pointer
char peek()
{
	return *expr;
}

/*this will return the current value pointed by the pointer and increment the pointer to point
to the next value*/
char get()
{
	return *expr++;
}

//This function return numbers from a characters, useful when there is a 2+ digit number
int number()
{
	int result = get() - '0';
	while (peek() >= '0' && peek() <= '9')
	{
		//As long as the next char is a digit, it will be add to the previous number*10
		result = 10 * result + get() - '0';
	}
	return result;
}

/*This function calls recursively the expression function when it detect a '(' to do the 
processing of the expression between brackets.
It also returns the oposite of the expression when there is a '-' sign before '('.
When there is no '(' nor '-' it calls the number() to get the next number in the expression
and proceed further.
The returned value will be processed by mult() then expression()*/
int factor()
{
	//It calls number() to get the current number in the expression and return its value that will be 
	//processed by the function who called factor(), namely mult()
	if (peek() >= '0' && peek() <= '9')
		return number();
	//If instead there is a bracket then it calls back expression() and dealing with what is found between
	//the brackets as the expression to parse #divideAndConquer #DynamicProgramming #Recursion
	else if (peek() == '(')
	{		
		// It is supposed to return '(' as it was already verified in the if statement and increment the pointer
		get(); 
		int result = expression();//It calls expression()
		if (peek() == ')') {
			get(); // it verify that at the end of the expression there is the expected ')'
			return result;//Then return the result of the expression()
		}
		else { 
			error = true; //Otherwise the error flag is activated
		}
		
	}
	//If the next element is '-' it recursively calls factor() again but return the opposite value
	else if (peek() == '-')
	{
		get();
		return -factor();
	}
	error = true;
}

/*This function multiply or divide the last expression calculated by factor() by the next 
expression calculated by factor() (either a number or an expression between brackets)
The returned value will be processed by expression()*/
int mult()
{
	//First it calls factor to get the expression that will be multiplied/divided
	int result = factor();
	int tmp = 0;
	while (peek() == '*' || peek() == '/')
		if (get() == '*') {
			//When '*' is found, the result of factor will be multiplied by the next value of factor()
			result *= factor();
		}

		else {
			//In case of division, we verify first that the value returned by factor is not zero
			//otherwise an error is returned
			tmp = factor();
			if (tmp == 0) {
				cout << "You cannot divide by zero, try again." << endl;
				error = true;
			}
			else
				result /= tmp;
		}

	return result;
}

//This is the core function that will call the other subfunctions. 
//It sums the values returned by mult() (read from bottom to top the description of the functions)
int expression()
{
	//This while loop will ignore empty spaces ' ' and call the next element
	while (peek() == ' ') {
		get();
	}
	//It calls mult() to get the values to be sumed
	int result = mult();
	//Same while loop to ignore spaces as sometimes spaces can be found after the call of mult()
	while (peek() == ' ') {
		get();
	}
	//This will sum/substract the last and next values returned by mult()
	while (peek() == '+' || peek() == '-')
		if (get() == '+')
			result += mult();
		else
			result -= mult();
	return result;
}

int main()
{
	/* Although many errors can be detected by the algorithm, we check some	syntax rules to raise 
	some errors before even launching the algorithm and quit the program*/
	string operators = "+-/*";
	string allowed = "0123456789 /+*-()";
	
	/*This for loop eleminate the spaces before analyzing the expression syntax*/
	int i;
	int k=0;
	for (i = 0; i < strlen(toParse); i++) {
		if (toParse[i] != ' ') {
			toParse[k] = toParse[i];
			k++;
		}		
	}
	toParse[k] = '\0';

	//In this for loop we check many errors before calling the parsing algorithm
	for (i = 0; i < strlen(toParse); i++) {
		if (allowed.find(toParse[i]) == string::npos) {
			//this checks if the element i is in the allowed list.
			cout << "A '" << toParse[i] << "' is trailing, get rid of it and try again.";
			//this is returned when the loop finds the first not allowed element and then quit the program
			return 0;
		}
		if (operators.find(toParse[i]) != string::npos){
			//This checks if two operators are next to each other (operators are supposed to be between two expressions
			if (operators.find(toParse[i + 1]) != string::npos || toParse[i + 1] == ')'){
				cout << "You cannot use two operatros " << toParse[i] <<toParse[i+1] << " consecutively.";
				return 0;				
			}
		}
		if (count(toParse, toParse + i, '(') < count(toParse, toParse + i, ')')) {
			cout << "A ')' comes before a '(', fix it and try again.";
			return 0;
		}
	}
	if (count(toParse, toParse + k, '(') > count(toParse, toParse + k, ')')) {
		//This checks if there is an equal number of left and right brackets
		cout << "Your result might be wrong as there are more '(' than ')'." << endl;
		return 0;
	}
	else if (count(toParse, toParse + k, '(') < count(toParse, toParse + k, ')')) {
		cout << "Your result might be wrong as there are more ')' than '('." << endl;
		return 0;
	}

	//We are set to run the algorithm after these errors checking
	int result = expression();
	//This if statement make us avoid to display wrong result as the algorithm will still run even after errors
	if (error == false) {
		cout << "Your expression '"<< toParse <<"' equals to: "<<result <<"."<< endl;
	}
	
	return 0;
}
