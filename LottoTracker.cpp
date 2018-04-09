#include "lottotracker.h"

LottoTracker::LottoTracker()
{

}

void LottoTracker::getDrawFrequencyChart
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

void LottoTracker::getPowerballFrequencyChart
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
