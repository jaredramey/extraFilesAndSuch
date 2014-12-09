#pragma once

using MyType = bool;
using MyOtherType = int;

class TheException
{
public:
	TheException();
	~TheException();

	virtual const char* what() const throw() = 0;

	void G();
	MyOtherType F();
};

