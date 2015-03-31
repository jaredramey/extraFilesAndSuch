#pragma once

#include "Modifiable.h"
#include "Player.h"

class Game : public Modifiable
{
public:
	Game(void);
	~Game(void);

	inline Player& getPlayer() {return m_player1;}
	inline int getLevel() {return m_level;}

	inline void setLevel(int level) {m_level = level;}
	inline void setPlayer(Player& player) {m_player1 = player;}

	void letsModify(Visitor* visitor);

private:
	Player m_player1;
	int m_level;
};

