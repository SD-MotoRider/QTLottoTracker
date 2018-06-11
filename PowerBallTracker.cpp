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

#include "PowerballTracker.h"

#include "PowerballPreferences.h"

// Qt
#include <QRandomGenerator>
#include <QSet>

// C++
#include <algorithm>    // std::shuffle
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

const int kDrawNumber(0);
const int kDrawDate(1);
const int kBall1(2);
const int kBall2(3);
const int kBall3(4);
const int kBall4(5);
const int kBall5(6);
const int kPowerBall(7);
const int kLastColumn(8);

const int kBallCount(69);
const int kPowerBallCount(36);

PowerballTracker::PowerballTracker()
{

}

void PowerballTracker::addDraw
(
	const Draw& draw
)
{
	_draws.push_back(draw);
}

void PowerballTracker::updateFrequencyData()
{
	Draws::iterator draw;
	Draws::iterator drawEnd;

	_powerballs.clear();
	_numbers.clear();

	if (_spannedDraws.isEmpty() == false)
	{
		draw = _spannedDraws.begin();
		drawEnd = _spannedDraws.end();
	}
	else
	{
		draw = _draws.begin();
		draw = _draws.end();
	}

	while (draw != drawEnd)
	{
		int powerball = draw->_powerball;
		if (_powerballs.find(powerball) == _powerballs.end())
			_powerballs[powerball] = 1;
		else
			_powerballs[powerball] = _powerballs[powerball] + 1;

		auto number = draw->_numbers.begin();
		while (number != draw->_numbers.end())
		{
			int numberValue = *number;
			if (_numbers.find(numberValue) == _numbers.end())
				_numbers[numberValue] = 1;
			else
				_numbers[numberValue] = _numbers[*number] + 1;

			number++;
		}

		draw++;
	}

	_numberProbability.clear();
	for (int i = 1; i <= kBallCount; i++)
	{
		_numberProbability[i] = ((qreal) _numbers[i] / (qreal) _spannedDraws.count()) * 100.0;
	}

	_powerballProbability.clear();
	for (int i = 1; i <= kPowerBallCount; i++)
	{
		_powerballProbability[i] = ((qreal) _powerballs[i] / (qreal) _spannedDraws.count()) * 100.0;
	}
}

void PowerballTracker::updateModel()
{
	beginInsertRows(index(0, 0), 0, _draws.count());
	insertRows(0, _draws.count());
	endInsertRows();
}

bool PowerballTracker::getDraw
(
	int index,
	Draw& draw
)
{
	bool result(false);

	if (index < _draws.count())
	{
		draw = _draws.at(index);
		result = true;
	}

	return result;
}

qreal PowerballTracker::getDrawExpectedProbability()
{
	return  (5.0 / (qreal) kBallCount) * 100.0;
}

void PowerballTracker::getDrawFrequencyChart
(
	FrequencyCounts& frequencyCounts
)
{
	frequencyCounts.clear();

	auto number = _numbers.begin();
	while (number != _numbers.end())
	{
		FrequencyPair frequencyPair(number->first, number->second);
		frequencyCounts.push_back(frequencyPair);
		number++;
	}

	std::sort(frequencyCounts.begin(), frequencyCounts.end(), [=](const FrequencyPair& a, const FrequencyPair& b)
	{
		return a.second > b.second;
	});
}

qreal PowerballTracker::getPowerballExpectedProbability()
{
	return (1.0 / (qreal) kPowerBallCount) * 100.0;
}

void PowerballTracker::getPowerballFrequencyChart
(
	FrequencyCounts& frequencyCounts
)
{
	frequencyCounts.clear();

	auto number = _powerballs.begin();
	while (number != _powerballs.end())
	{
		FrequencyPair frequencyPair(number->first, number->second);
		frequencyCounts.push_back(frequencyPair);
		number++;
	}

	std::sort(frequencyCounts.begin(), frequencyCounts.end(), [=](const FrequencyPair& a, const FrequencyPair& b)
	{
		return a.second > b.second;
	});
}

void PowerballTracker::generateADraw(Draw& draw)
{
	static QVector<int> balls;
	static QVector<int> powerballs;

	if (_preferences.preferencesAreDirty() == true)
	{
		balls.clear();
		powerballs.clear();

		generateSpannedDraws();
		updateFrequencyData();
	}

	bool limitProbability = _preferences.pickNumbersThatExceedProbability();

	if (balls.isEmpty())
	{
		qreal expectedProbability = getDrawExpectedProbability();

		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

		auto number = _numbers.begin();
		while (number != _numbers.end())
		{
			for (int i = 0; i < number->second; i++)
			{
				if (limitProbability == true)
				{
					if (_numberProbability[number->first] >= expectedProbability)
					{
						balls.push_back(number->first);
					}
				}
				else
				{
					balls.push_back(number->first);
				}
			}

			number++;
		}

		shuffle (balls.begin(), balls.end(), std::default_random_engine(seed));
	}

	if (powerballs.isEmpty())
	{
		qreal expectedProbability = getPowerballExpectedProbability();

		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

		auto number = _powerballs.begin();
		while (number != _powerballs.end())
		{
			for (int i = 0; i < number->second; i++)
			{
				if (limitProbability == true)
				{
					if (_powerballProbability[number->first] >= expectedProbability)
					{
						powerballs.push_back(number->first);
					}
				}
				else
				{
					powerballs.push_back(number->first);
				}
			}

			number++;
		}

		shuffle (powerballs.begin(), powerballs.end(), std::default_random_engine(seed));
	}

	QSet<int> ballSet;

	while (ballSet.count() < 5)
	{
		int ball = balls.at(QRandomGenerator::system()->bounded(balls.count()));
		if (ballSet.contains(ball) == false)
			ballSet.insert(ball);
	}

	draw._drawDate = QDate::currentDate();
	draw._drawNumber = 0;
	draw._numbers = ballSet.toList().toVector();
	std::sort(draw._numbers.begin() , draw._numbers.end());
	draw._powerball = powerballs.at(QRandomGenerator::system()->bounded(powerballs.count()));
}

void PowerballTracker::generateSpannedDraws()
{
	static quint32 lastSpan(0);

	if (_preferences.limitPicksToTimeSpan())
	{
		if (lastSpan != _preferences.timeSpanInWeeks())
		{
			lastSpan = _preferences.timeSpanInWeeks();

			QDate spanDate = QDate::currentDate();
			spanDate = spanDate.addDays(-1 * (lastSpan * 7));

			_spannedDraws.clear();

			auto draw = _draws.begin();
			while (draw != _draws.end())
			{
				if (draw->_drawDate > spanDate)
				{
					_spannedDraws.push_back(*draw);
				}

				draw++;
			}
		}
	}
	else
	{
		_spannedDraws.clear();
	}
}

int PowerballTracker::rowCount
(
	const QModelIndex& parent //= QModelIndex()
) const
{
	Q_UNUSED(parent);

	return _draws.count();
}

int PowerballTracker::columnCount
(
	const QModelIndex& parent // = QModelIndex()
) const
{
	Q_UNUSED(parent);

	return kLastColumn;
}


QVariant PowerballTracker::data
(
	const QModelIndex& index,
	int role //= Qt::DisplayRole
) const
{
	Q_UNUSED(index);
	Q_UNUSED(role);

	if (role == Qt::DisplayRole)
	{
		int row = index.row();
		int section = index.column();

		switch (section)
		{
		case kDrawNumber: return QString("%1").arg(_draws.at(row)._drawNumber);
		case kDrawDate: return _draws.at(row)._drawDate.toString();
		case kBall1: return QString("Ball 1");
		case kBall2: return QString("Ball 2");
		case kBall3: return QString("Ball 3");
		case kBall4: return QString("Ball 4");
		case kBall5: return QString("Ball 5");
		case kPowerBall: return QString("Powerball");
		default:
			break;
		}
	}
	return QVariant();
}

QVariant PowerballTracker::headerData
(
	int section,
	Qt::Orientation orientation,
	int role // = Qt::DisplayRole
) const
{
	Q_UNUSED(orientation);
	Q_UNUSED(role);

	switch (section)
	{
	case kDrawNumber: return QString("Draw Number");
	case kDrawDate: return QString("Draw Date");
	case kBall1: return QString("Ball 1");
	case kBall2: return QString("Ball 2");
	case kBall3: return QString("Ball 3");
	case kBall4: return QString("Ball 4");
	case kBall5: return QString("Ball 5");
	case kPowerBall: return QString("Powerball");
	default:
		break;
	}

	return QVariant();
}
