#ifndef DRAW_H
#define DRAW_H

#include <QDate>

#include <list>
#include <map>
#include <vector>

class Draw
{
public:
	Draw(const QDate& drawDate, const std::vector<int>& numbers, int powerball)
	{
		_drawDate = drawDate;
		_numbers = numbers;
		_powerball = powerball;
		std::sort(_numbers.begin(), _numbers.end());
	}

	Draw(const Draw& copyMe)
	{
		_drawDate = copyMe._drawDate;
		_numbers = copyMe._numbers;
		_powerball = copyMe._powerball;
		std::sort(_numbers.begin(), _numbers.end());
	}


	QDate						_drawDate;
	std::vector<int>			_numbers;
	int							_powerball;
};

typedef std::list<Draw> Draws;

#endif // DRAW_H
