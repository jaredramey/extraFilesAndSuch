#include "AIE.h"
#include "Cat.h"
#include "GameDefs.h"

Cat::Cat(void)
{
	m_sprite = -1;
	m_isAlive = false;
	m_position.x = iScreenWidth>>1;
	m_position.y = iScreenHeight>>1;
}


Cat::~Cat(void)
{
}

void Cat::initWithFile(const char* szFilename)
{
	m_sprite = CreateSprite(szFilename, 128, 128, true);
}

void Cat::destroy() 
{
	DestroySprite(m_sprite);
}

void Cat::OnMessage(Message& msg)
{
	// Implement how your cats respond to your messages here
}

void Cat::draw()
{
	if(m_isAlive == false || m_sprite < 0)
		return;

	DrawSprite(m_sprite);
}