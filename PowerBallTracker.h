#ifndef POWERBALLTRACKER_H
#define POWERBALLTRACKER_H

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

// Qt
#include <QAbstractTableModel>

// c++
#include <map>
#include <utility>
#include <vector>

typedef std::map<int, int> DrawNumberCounts;
typedef std::pair<int, int> FrequencyPair;
typedef std::vector<FrequencyPair> FrequencyCounts;

class PowerBallTracker :
	public QAbstractTableModel
{
public:
	PowerBallTracker();

	void preferencesUpdated()
	{
		_preferencesUpdated = true;
	}

	void reset(void)
	{
		_draws.clear();
		_powerballs.clear();
		_numbers.clear();
	}

	void addDraw(const Draw& draw);

	int getDrawCount(void)
	{
		return _draws.count();
	}

	bool getDraw(int index, Draw& draw);

	void getDrawFrequencyChart(FrequencyCounts& frequencyCounts);
	void getPowerballFrequencyChart(FrequencyCounts& frequencyCounts);

	void generateADraw(Draw& draw);

	void updateModel(void);

	virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
	virtual int columnCount(const QModelIndex& parent = QModelIndex()) const;
	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

private:
	bool							_preferencesUpdated;
	Draws							_draws;
	DrawNumberCounts				_powerballs;
	DrawNumberCounts				_numbers;
};

#endif // LOTTOTRACKER_H
