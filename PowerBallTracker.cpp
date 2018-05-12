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

	if (_powerball.find(draw._powerball) == _powerball.end())
		_powerball[draw._powerball] = 1;
	else
		_powerball[draw._powerball] = _powerball[draw._powerball] + 1;

	auto number = draw._numbers.begin();
	while (number != draw._numbers.end())
	{
		if (_numbers.find(*number) == _numbers.end())
			_numbers[*number] = 1;
		else
			_numbers[*number] = _numbers[*number] + 1;

		number++;
	}
}

void PowerBallTracker::updateModel()
{
	beginInsertRows(index(0, 0), 0, _draws.count());
	insertRows(0, _draws.count());
	endInsertRows();
}

void PowerBallTracker::getDrawFrequencyChart
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

void PowerBallTracker::getPowerballFrequencyChart
(
	FrequencyCounts& frequencyCounts
)
{
	frequencyCounts.clear();

	auto number = _powerball.begin();
	while (number != _powerball.end())
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
