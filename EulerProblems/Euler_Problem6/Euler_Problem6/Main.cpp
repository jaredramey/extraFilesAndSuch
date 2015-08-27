#include <iostream>

using namespace std;

int main()
{
	int sumOfSquare = 0;
	int squareOfSum = 0;
	int total = 0;
	int result;

	for (int i = 1; i <= 100; i++)
	{
		sumOfSquare += i*i;
	}

	for (int j = 1; j <= 100; j++)
	{
		total += j;
	}

	squareOfSum = total * total;

	result = squareOfSum - sumOfSquare;

	cout << result << endl;
	
	system("PAUSE");
	return 0;
}