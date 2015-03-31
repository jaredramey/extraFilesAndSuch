#include "Highscores.h"
#include <fstream>
#include <iostream>

using namespace std;

Highscores::Highscores(void)
{
}

Highscores::~Highscores(void)
{
}

bool compare_decending(const int& first, const int& second)
{
	return(first > second);
}

void Highscores::SortScore()
{
	//scores.sort(compare_decending);
}

void Highscores::AddScore(int score)
{
	scores.push_back(score);
}

bool Highscores::IsEmpty()
{
	return (scores.size() == 0);
}

const list<int> Highscores::GetScores()
{
	return scores;
}

void Highscores::LoadScores()
{
	fstream fs;
	fs.open("leaderboard.txt", fstream::in);
	if (fs.is_open())
	{
		while (!fs.eof())
		{
			int score = 0;
			fs >> score;
			if (fs.good())
			{
				scores.push_back(score);
			}
		}
		fs.close();
	}

}

void Highscores::SaveScores()
{
	fstream fs;
	fs.open("leaderboard.txt", fstream::out | fstream::trunc);
	if (fs.is_open())
	{
		int counter = 0;
		for (list<int>::iterator it = scores.begin(); it != scores.end(); it++)
		{
			fs << *it << endl;
			counter++;
			if (counter >= 5)
				break;
		}
		fs.close();
	}
}