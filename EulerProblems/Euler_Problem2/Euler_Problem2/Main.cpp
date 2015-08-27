#include <iostream>

using namespace std;

int main()
{
	int num1 = 1;
	int num2 = 2;
	int result;
	int finalNum = 0;

	while (num1 < 4000000 && num2 < 4000000)
	{
		result = (num1 + num2);
		cout << result << endl;

		num1 = num2;
		num2 = result;

		if (result % 2 == 0 && result < 4000000)
		{
			finalNum = (finalNum + result);
		}
	}

	//adding 2 to make up for the program not being able to add it itself at the start
	//(2 never ends as a result since it was a starting number)
	finalNum = finalNum + 2;

	cout << "Final sum of all even numbers under 4,000,000 = " << finalNum << endl;

	system("PAUSE");
	return 0;
}