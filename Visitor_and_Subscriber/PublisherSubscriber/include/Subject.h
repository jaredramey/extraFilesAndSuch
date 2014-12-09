#pragma once

class Observer;
struct Message;

class Subject
{
public:
	virtual void attachObserver(Observer* o) = 0;
	virtual void detachObserver(Observer* o) = 0;
	virtual void notify(Message& msg) = 0;
};

