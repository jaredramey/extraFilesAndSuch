#ifndef _TIMER_H_
#define _TIMER_H_

#include <Windows.h>

class Timer
{
public:
	static Timer* Get();
	static void Destroy();

	void UpdateTimer();
	double GetDeltaTime();
	double GetTotalTime();
private:
	static Timer* sm_pInstance;
	
	Timer();
	~Timer();



	LARGE_INTEGER m_Frequency;
	LARGE_INTEGER m_CurrentTime;
	LARGE_INTEGER m_PreviousTime;

	double m_dElapsedTime;
	double m_dTotalTime;
};
#endif //_TIMER_H_