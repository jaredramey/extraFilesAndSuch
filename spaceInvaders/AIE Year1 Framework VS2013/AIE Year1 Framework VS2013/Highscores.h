#pragma once
#include <iostream>
#include <list>

using namespace std;

class Highscores
{
public:
	Highscores();
	~Highscores();

	bool compare_decending(const int& first, const int& second);
	void LoadScores();
	void SaveScores();
	void AddScore(int score);
	void SortScore();
	bool IsEmpty();
	const list<int> Highscores::GetScores();

private:
	list<int> scores;

};

