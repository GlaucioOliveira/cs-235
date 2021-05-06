/***********************************************************************
 * Module:
 *    Week 02, Stack
 *    Brother Helfrich, CS 235
 * Author:
 *    Gláucio Oliveira and Dante
 * Summary:
 *    This program will implement the testInfixToPostfix()
 *    and testInfixToAssembly() functions
 ************************************************************************/

#include <iostream>    // for ISTREAM and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include "stack.h"     // for STACK
#include <stack>
using namespace std;

int getWeight(char c);
bool isOperation(char c);

/*****************************************************
 * CONVERT INFIX TO POSTFIX
 * Convert infix equation "5 + 2" into postifx "5 2 +"
 *****************************************************/
string convertInfixToPostfix(const string& infix)
{
	//infix = "a + b * c ^ d - e";
	//infix = "a ^ b + c * d";
	//infix = "3.14159 * diameter";
	//infix = "4.5+a5+.1215  +   1";
	///infix = "pi*r^2";
	//infix = "(5.0  /  .9)*(fahrenheit - 32)";

	string postfix = "";
	stack<char> stackList;
	
	int iInfix = 0;
	int iPostfix = 0;
	bool previusCharDigit = false;
	bool previusCharVariable = false;
	bool previusCharSpace = false;

	for (iInfix = 0; iInfix < infix.size(); iInfix++)
	{
		char currentChar = infix[iInfix];
		char previousChar = ' ';

		if (iInfix > 0) previousChar = infix[iInfix - 1];

		if (isdigit(currentChar) || currentChar == '.') 
		{
			iPostfix++;
			
			if (previusCharDigit == false )
				postfix += ' ';

			postfix += currentChar;

			previusCharDigit = true;
			previusCharVariable = false;
			previusCharSpace = false;
		}
		else if (currentChar == '(') 
		{
			stackList.push('(');

			previusCharDigit = false;
			previusCharVariable = false;
			previusCharSpace = false;
		}
		else if (currentChar == ')') 
		{
			while (!stackList.empty() && stackList.top() != '(')
			{
				iPostfix++;
				postfix += " " + stackList.top();
				stackList.pop();
			}

			stackList.pop();

			previusCharDigit = false;
			previusCharVariable = false;
			previusCharSpace = false;
		}
		else if (!isOperation(currentChar) && !isspace(currentChar))
		{
			//variable
			iPostfix++;

			if (previusCharVariable == false)
				postfix = postfix + " ";

			postfix = postfix + currentChar;

			previusCharDigit = false;
			previusCharVariable = true;
			previusCharSpace = false;
		}
		else if (!isspace(currentChar))
		{
			while (!stackList.empty() && getWeight(currentChar) <= getWeight(stackList.top()))
			{
				iPostfix++;
				postfix = postfix + " " + stackList.top();

				stackList.pop();
			}

			stackList.push(currentChar);

			previusCharDigit = false;
			previusCharVariable = false;
			previusCharSpace = false;
		}
		else if (isspace(currentChar)) {
			previusCharDigit = false;
			previusCharVariable = false;
			previusCharSpace = true;
		}
		//else if (isOperation(currentChar) && isspace(previousChar)) {
		//    iPostfix++;
		//    postfix = postfix + " ";
		//}
		//else if (isdigit(currentChar) && isspace(previousChar)) {
		//    iPostfix++;
		//    postfix = postfix + " ";
		//}

		//if (isspace(currentChar) && !isspace(postfix[iPostfix]))
		//{
		//	postfix = postfix + " ";
		//	iPostfix++;
		//}
	}


	while (!stackList.empty())
	{
		postfix = postfix + " " + stackList.top() ;
		stackList.pop();
	}

	return postfix;
}

bool isOperation(char c) {
	switch (c)
	{
	case '+':
		return true;
		break;

	case '-':
		return true;
		break;

	case '/':
		return true;
		break;


	case '*':
		return true;
		break;

	case '^':
		return true;
		break;

	default:
		return false;
	}
}

int getWeight(char c) {

	switch (c)
	{
	case '+':
		return 1;
		break;

	case '-':
		return 1;
		break;

	case '/':
		return 2;
		break;


	case '*':
		return 2;
		break;

	case '^':
		return 3;
		break;

	default:
		return 0;
	}
}

/*****************************************************
 * TEST INFIX TO POSTFIX
 * Prompt the user for infix text and display the
 * equivalent postfix expression
 *****************************************************/
void testInfixToPostfix()
{
	string input;
	cout << "Enter an infix equation.  Type \"quit\" when done.\n";

	do
	{
		// handle errors
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
		}

		// prompt for infix
		cout << "infix > ";
		getline(cin, input);

		// generate postfix
		if (input != "quit")
		{
			string postfix = convertInfixToPostfix(input);
			cout << "\tpostfix: " << postfix << endl << endl;
		}
	}    while (input != "quit");
}

/**********************************************
 * CONVERT POSTFIX TO ASSEMBLY
 * Convert postfix "5 2 +" to assembly:
 *     LOAD 5
 *     ADD 2
 *     STORE VALUE1
 **********************************************/
string convertPostfixToAssembly(const string& postfix)
{
	string assembly;

	return assembly;
}

/*****************************************************
 * TEST INFIX TO ASSEMBLY
 * Prompt the user for infix text and display the
 * resulting assembly instructions
 *****************************************************/
void testInfixToAssembly()
{
	string input;
	cout << "Enter an infix equation.  Type \"quit\" when done.\n";

	do
	{
		// handle errors
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
		}

		// prompt for infix
		cout << "infix > ";
		getline(cin, input);

		// generate postfix
		if (input != "quit")
		{
			string postfix = convertInfixToPostfix(input);
			cout << convertPostfixToAssembly(postfix);
		}
	}    while (input != "quit");

}
