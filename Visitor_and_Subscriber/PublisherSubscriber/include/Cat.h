#pragma once

#include "Observer.h"
#include "Vector2.h"

class Cat : public Observer
{
public:
	Cat(void);
	~Cat(void);

	void initWithFile(const char* szFilename);
	void destroy();
	
	void OnMessage(Message& msg);
	void draw();

protected:
	int m_sprite;
	bool m_isAlive;
	Vector2 m_position;
};

