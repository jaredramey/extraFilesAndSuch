#pragma once

class Modifiable;

class Visitor
{
public:
	virtual void visit(Modifiable* visitable) = 0;
};

