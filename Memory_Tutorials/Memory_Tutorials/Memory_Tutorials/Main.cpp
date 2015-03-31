#include <iostream>

using namespace std;

struct A
{
	float a;
	char b[2];
	int c;
};

struct B
{
	long long a;
	char* b;
	int c;
	float d[2];
};

struct C
{
	char a[3];
	long long* b;
	float c;
};

struct Player
{
	char acInitials[3];
	int iPlayerID;
	char cLives;
	float fX, fY;
};

struct Enemy
{
	bool bAlive;
	bool bCanShoot;
	int iDirection;
	short iScoreValue;
};

struct Weapon
{
	char* acName[32];
	char cType;
	unsigned int iAmmoCount;
	float fCoolDown;
};

int main()
{
	A a;
	B b;
	C c;
	Player player;
	Enemy enemy;
	Weapon weapon;

	cout << sizeof a << endl;
	cout << sizeof b << endl;
	cout << sizeof c << endl;
	cout << sizeof player << endl;
	cout << sizeof enemy << endl;
	cout << sizeof weapon << endl;


	system("PAUSE");
	return 0;
}