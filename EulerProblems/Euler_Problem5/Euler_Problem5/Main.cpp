#include <iostream>

using namespace std;

bool isSmallestMult(int num);

int main()
{
	long int answer = 0;
	int i = 2520;

	while (answer == 0)
	{
		if (i%2 == 0)
		{
			if (isSmallestMult(i) != false)
			{
				answer = i;
			}
			else
			{
				i++;
			}
		}
		else
		{
			i++;
		}
	}
	
	cout << answer << endl;

	system("PAUSE");
	return 0;
}

bool isSmallestMult(int num)
{
	for (int j = 1; j <= 20; j++)
	{
		if (num%j != 0)
		{
			return false;
		}
	}

	return true;
}