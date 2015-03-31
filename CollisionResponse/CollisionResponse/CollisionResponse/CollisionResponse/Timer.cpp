#include "Timer.h"

Timer* Timer::sm_pInstance = nullptr;

Timer::Timer()
{
	//initializing elapsed and total time
	m_dElapsedTime = m_dTotalTime = 0;

	//getting the cycles per second of our CPU
	QueryPerformanceFrequency(&m_Frequency);

	//Getting the current clock cycle
	QueryPerformanceCounter(&m_CurrentTime);
	m_PreviousTime = m_CurrentTime;
}

void Timer::UpdateTimer()
{
	//move the old current to the previous
	m_PreviousTime = m_CurrentTime;
	//update current
	QueryPerformanceCounter(&m_CurrentTime);
	
	//calculate the difference in seconds
	m_dElapsedTime = (m_CurrentTime.QuadPart - m_PreviousTime.QuadPart) / (double)m_Frequency.QuadPart;
	//add onto total time
	m_dTotalTime += m_dElapsedTime;
}

double Timer::GetDeltaTime()
{
	return m_dElapsedTime;
}

double Timer::GetTotalTime()
{
	return m_dTotalTime;
}

Timer* Timer::Get()
{
	if ( sm_pInstance == nullptr )
		sm_pInstance = new Timer;

	return sm_pInstance;
}

void Timer::Destroy()
{
	delete sm_pInstance;
	sm_pInstance = nullptr;
}

Timer::~Timer(){}