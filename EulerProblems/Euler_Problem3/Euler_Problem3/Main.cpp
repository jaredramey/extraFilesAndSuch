#include <iostream>

using namespace std;

long long int FindLargestPrime(long long int num);
bool is_perfect_square(long long int n);
bool is_prime(unsigned long long n);

int main()
{
	long long int num = 600851475143;
	long long int largestPrime;

	largestPrime = FindLargestPrime(num);

	cout << largestPrime << endl;


	system("PAUSE");
	return 0;
}

long long int FindLargestPrime(long long int num)
{
	long long int result = 0;
	long long int i = round(sqrt(num));
	
	while (i <= num / 2 && result == 0)
	{
		if (i % 2 != 0)
		{
			if (num%i == 0)
			{
				if (is_prime(i) != true)
				{
					result = i;
				}
				else
				{
					i--;
				}
			}
			else
			{
				i--;
			}
		}

		else
		{
			i--;
		}
	}

	return result;
}

bool is_perfect_square(long long int n)
{
	if (n < 0)
		return false;

	long long int root(round(sqrt(n)));
	return n == root * root;
}

bool is_prime(unsigned long long n)
{
	for (long long int i = 3; i < n; i += 2)
	{
		if (n%i == 0)
		{
			return true;
		}
	}

	return false;
}