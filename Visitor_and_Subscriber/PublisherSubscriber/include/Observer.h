#pragma once

struct Message {
	enum {
		UPDATE,
		ON_CLICK,
		SPAWN_REQUEST
	} msg;
	bool consumed;
	void* data;
};

class Observer
{
public:
	virtual void OnMessage(Message& msg) = 0;
};

