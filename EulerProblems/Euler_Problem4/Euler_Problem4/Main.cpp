#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool isPal(int num);

int main()
{
	int largPal = 0;

	for (int i = 999; i >= 100; i--)
	{
		for (int j = 999; j >= 100; j--)
		{
			int num = i*j;

			if (isPal(num) != false)
			{
				if (num > largPal)
				{
					largPal = num;
				}
			}
		}
	}

	cout << largPal << endl;

	system("PAUSE");
	return 0;
}


bool isPal(int num)
{
	string str = to_string(num);
	string strRev = str;

	reverse(strRev.begin(), strRev.end());

	if (str == strRev)
	{
		return true;
	}
	else
	{
		return false;
	}
}