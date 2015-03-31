#pragma once

#include "Subject.h"
#include <vector>

class Game : public Subject
{
public:
	Game(void);
	~Game(void);

	void attachObserver(Observer* o);
	void detachObserver(Observer* o);
	void notify(Message& msg);

	void update(float dt);

private:
	std::vector<Observer*> m_observers;
	float m_spawnTimer;
};

