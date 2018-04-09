#ifndef LOTTOTRACKER_H
#define LOTTOTRACKER_H

#include "Draw.h"

typedef std::map<int, int> DrawNumberCounts;
typedef std::multimap<int, int> FrequencyCounts;

class LottoTracker
{
public:
	LottoTracker();

	void addDraw(const Draw& draw)
	{
		_draws.push_back(draw);
	}

	void getDrawFrequencyChart(FrequencyCounts& frequencyCounts);
	void getPowerballFrequencyChart(FrequencyCounts& frequencyCounts);

private:
	Draws							_draws;
	DrawNumberCounts				_powerball;
	DrawNumberCounts				_numbers;
};

#endif // LOTTOTRACKER_H
