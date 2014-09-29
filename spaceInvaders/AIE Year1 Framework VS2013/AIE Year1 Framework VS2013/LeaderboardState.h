#pragma once

//#include "basestate.h" <-- When exactly did we make this header??...
#include "Highscores.h"

class LeaderboardState // : public BaseState <-- Where did this come from?
{
public:
	LeaderboardState();
	~LeaderboardState();

	void Initialize();
	//void Update(float a_fTimeStep, StateMachine* a_pSM);
};

