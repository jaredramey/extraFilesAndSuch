#include "AIE.h"
#include "Game.h"
#include "GameDefs.h"
#include "Observer.h"
#include "Vector2.h"
#include <random>
#include <time.h>

Game::Game(void)
{
	m_spawnTimer = 0;
	srand(time(NULL));
}


Game::~Game(void)
{
}

void Game::attachObserver(Observer* o)
{
	m_observers.push_back(o);
}

void Game::detachObserver(Observer* o)
{
	std::vector<Observer*>::iterator it = m_observers.begin();
	for(;it != m_observers.end(); it++){
		if(*it == o) {
			m_observers.erase(it);
			break;
		}
	}
}

void Game::notify(Message& msg)
{
	std::vector<Observer*>::iterator it = m_observers.begin();
	for(;it != m_observers.end(); it++){
		(*it)->OnMessage(msg);
		// if message was consumed, break
		if(msg.consumed)
			break;
	}
}

void Game::update(float dt) 
{
	m_spawnTimer += dt;

	if(m_spawnTimer >= 1.5f) {
		m_spawnTimer = 0;

		// spawn new cat
		Message msg;
		Vector2 spawnPos;
		spawnPos.x = 50 + rand() % (iScreenWidth - 100);
		spawnPos.y = 50 + rand() % (iScreenHeight - 100);

		msg.msg = Message::SPAWN_REQUEST;
		msg.data = (void*)&spawnPos;
		msg.consumed = false;

		notify(msg);
	}

	if( GetMouseButtonDown( 0 ) ) {
		int x, y;
		Vector2 mousePos;
		
		GetMouseLocation( x, y );
		mousePos.x = x;
		mousePos.y = y;

		Message msg;
		msg.msg = Message::ON_CLICK;
		msg.data = (void*)&mousePos;
		msg.consumed = false;

		notify(msg);
	}
}