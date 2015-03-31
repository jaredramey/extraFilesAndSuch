/*
*		Exception Handling Tutorial
*
*	Started: 12/9/14 || Author: Jared Ramey
*
*/
#include <iostream>
#include <Windows.h>
#include "TheException.h"

using namespace std;

class MyException : public TheException
{
	virtual const char* what() const throw()
	{
		return "My Exception Happened";
	}

} MyEx;


int main()
{
	//Set up all values needed for the calculator
	float num1 = 0;
	float num2 = 0;
	float result;
	char function;
	float input;
	float input2;
	bool loop = true;

	do{
	FirstInput: // <--- Place holder to come back to if the first input was not accpeted
		cout << "Welcome to the Basic Calculator" << endl;
		cout << "Please input your first number" << endl;\
		//Ask for first value
		cin >> input;
		//Test the first value to check if it's an accepted data type (i.e. float)
		try
		{
			if (!cin)
			{
				throw 1;
			}
		}
		//If the input was not accepted then tell the user so
		catch (int i)
		{
			cout << "That is not an accepted data type. Please try again" << endl;
			system("pause");
			//clear the screen and the input that was taken then ignor the next input to cycle back to FirstInput
			system("cls");
			cin.clear();
			cin.ignore();
			goto FirstInput;
		}

		//If the data was an accepted type then put it as the first number.
		num1 += input;

		SecondInput: // <--- Place holder to come back to if the first input was not accpeted
		cout << "Please input your second number" << endl;
		//Ask for second value
		cin >> input2;
		//Test the first value to check if it's an accepted data type (i.e. float)
		try
		{
			if (!cin)
			{
				throw 1;
			}
		}
		//If the input was not accepted then tell the user so
		catch (int i)
		{
			cout << "That is not an accepted data type. Please try again" << endl;
			system("pause");
			//clear the screen and the input that was taken then ignor the next input to cycle back to SecondInput
			system("cls");
			cin.clear();
			cin.ignore();
			//Remind the user what their first value was
			cout << "Reminder - Your first number is: " << num1 << endl;
			goto SecondInput;
		}

		//if the value was accepted then put it as the second number
		num2 += input2;
	
		FunctionInput: // <--- Place holder to come back to if the function input was not accpeted
		cout << "Please input the function you would like to preform (Accepted functions: -, +, *, /)" << endl;
		//Ask for a function
		cin >> function;
		try
		{
			//Check to see if the function is accepted
			if (!cin)
			{
				throw 1;
			}
		}
		//if the function is not an accepted type then tell the user so
		catch (int i)
		{
			cout << "That is not an accepted function type. Please try again" << endl;
			system("pause");
			system("cls");
			cin.sync();
			cin.clear();
			cin.ignore();
			//Remind the user what their numbers are
			cout << "Reminder - Your numbers are: " << num1 << " and " << num2 << endl;
			goto FunctionInput;
		}

		switch (function)
		{
		case '-':
			result = num1 - num2;
			break;
		case '+':
			result = num1 + num2;
			break;
		case '*':
			result = num1 * num2;
			break;
		case '/':
			result = num1 / num2;
			break;
		default:
			cout << "That wasn't a function" << endl;
			goto FunctionInput;
			break;
		}

		cout << "Your result is: " << result << endl;
		cout << "Press ESC to quit or any other key to use the calculator again" << endl;
		system("pause");
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			loop = false;
		}

		else
		{
			system("cls");
		}
	
	} while (loop == true);

	//For the second part of the tutorial where it asks to throw a string exception object (I'm assuming through a class like in the slide)
	try
	{
		throw MyEx; 
	}
	catch (TheException& e)
	{
		cout << e.what() << endl;
	}

	//For the second part of the tutorial where it asks to create two methods that throw and catch one new type you make and then throw a different exception
	cout << MyEx.F() << endl;

	system("pause");
	return 0;
}