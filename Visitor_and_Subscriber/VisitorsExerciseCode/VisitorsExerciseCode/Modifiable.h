#pragma once

class Visitor;

class Modifiable
{
public:
	virtual void letsModify(Visitor* visitor) = 0;
};

