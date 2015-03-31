#include "TheException.h"

using namespace std;

TheException::TheException()
{
}


TheException::~TheException()
{
}

void TheException::G()
{
	MyType test = true;
	//Throw an exception of a new type that you define
	throw test;
}

MyOtherType TheException::F()
{
	MyOtherType yay = 10;

	//Call G and catch its exception
	try
	{
		G();
	}
	catch (MyType e)
	{
		if (e == true)
		{
			return yay;
		}
	}
}