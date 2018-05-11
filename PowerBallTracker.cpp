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

#include "PowerBallTracker.h"

const int kDrawNumber(0);
const int kDrawDate(1);
const int kBall1(2);
const int kBall2(3);
const int kBall3(4);
const int kBall4(5);
const int kBall5(6);
const int kPowerBall(7);
const int kLastColumn(8);

PowerBallTracker::PowerBallTracker()
{

}

void PowerBallTracker::addDraw
(
	const Draw& draw
)
{
	_draws.push_back(draw);

	emit model
}

void PowerBallTracker::getDrawFrequencyChart
(
	FrequencyCounts& frequencyCounts
)
{
	if (_numbers.empty())
	{
		auto drawIter = _draws.begin();
		while (drawIter != _draws.end())
		{
			auto drawNumberIter = drawIter->_numbers.begin();
			while (drawNumberIter != drawIter->_numbers.end())
			{
				_numbers[*drawNumberIter] = _numbers[*drawNumberIter] + 1;
				drawNumberIter++;
			}
			drawIter++;
		}
	}

	frequencyCounts.clear();

	auto number = _numbers.begin();
	while (number != _numbers.end())
	{
		frequencyCounts.insert(std::pair<int, int>(number->second,  number->first));
		number++;
	}
}

void PowerBallTracker::getPowerballFrequencyChart
(
	FrequencyCounts& frequencyCounts
)
{
	if (_powerball.empty())
	{
		auto drawIter = _draws.begin();
		while (drawIter != _draws.end())
		{
			_powerball[drawIter->_powerball] = _powerball[drawIter->_powerball] + 1;
			drawIter++;
		}
	}

	frequencyCounts.clear();

	auto number = _powerball.begin();
	while (number != _powerball.end())
	{
		frequencyCounts.insert(std::pair<int, int>(number->second,  number->first));
		number++;
	}
}

int PowerBallTracker::rowCount
(
	const QModelIndex& parent //= QModelIndex()
) const
{
	Q_UNUSED(parent);

	return _draws.count();
}

int PowerBallTracker::columnCount
(
	const QModelIndex& parent // = QModelIndex()
) const
{
	Q_UNUSED(parent);

	return kLastColumn;
}


QVariant PowerBallTracker::data
(
	const QModelIndex& index,
	int role //= Qt::DisplayRole
) const
{
	Q_UNUSED(index);
	Q_UNUSED(role);

	return QVariant();
}

QVariant PowerBallTracker::headerData
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
