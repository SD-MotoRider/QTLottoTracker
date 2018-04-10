#ifndef LOTTOTRACKER_H
#define LOTTOTRACKER_H

// MIT License
//
// Copyright (c) 2018 Michael Simpson
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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
