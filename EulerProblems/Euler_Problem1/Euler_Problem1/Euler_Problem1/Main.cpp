/*
//This program is to solve Problem 1 on projecteuler.net
//Problem: Find the sum of all the multiples of 3 or 5 below 100
//Example: If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23
*/
#include <iostream>

using namespace std;

//base value will be used in order to start counting at 0
int base; 
int findAllValue(int max, int value);

int main()
{
	base = findAllValue(1000, 3);
	//base = (base + findAllValue(1000, 5));

	cout << "Sum of all multiples = " << base << endl;
	system("PAUSE");
	return 0;
}

int findAllValue(int max, int value)
{
	//Curent value will start at 1 and then rise until set max
	int currentValue;
	int currentTotal = 0;

	//loop through until max is met
	for (int i = 1; i < max; i++)
	{
		//set current value to the current number we are on
		currentValue = i;

		if (currentValue % 3 == 0 || currentValue % 5 == 0)
		{
			cout << i << endl;
			currentTotal = currentTotal + i;
		}
		else
		{
		}
	}

	return currentTotal;
}