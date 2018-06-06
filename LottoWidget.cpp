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

#include "LottoWidget.h"
#include "PreferencesDialog.h"
#include "QuickPickDialog.h"

#include "PowerballReader.h"

LottoWidget::LottoWidget
(
	QWidget* parent
) :
	QWidget(parent)
{
	setupUi(this);

	connect(&_drawReader, &PowerballReader::drawFinished, this, &LottoWidget::on_drawDataFinished);
}

LottoWidget::~LottoWidget()
{
}

void LottoWidget::on__updateDrawData_released()
{
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	_drawReader.update();
}

void LottoWidget::on__genQuickPick_released()
{
	Draws draws;
	Draw draw;

	PowerBallTracker* tracker = &(_drawReader._tracker);

	tracker->generateADraw(draw);
	draws.push_back(draw);

	tracker->generateADraw(draw);
	draws.push_back(draw);

	tracker->generateADraw(draw);
	draws.push_back(draw);

	tracker->generateADraw(draw);
	draws.push_back(draw);

	tracker->generateADraw(draw);
	draws.push_back(draw);

	tracker->generateADraw(draw);
	draws.push_back(draw);

	tracker->generateADraw(draw);
	draws.push_back(draw);

	tracker->generateADraw(draw);
	draws.push_back(draw);

	tracker->generateADraw(draw);
	draws.push_back(draw);

	tracker->generateADraw(draw);
	draws.push_back(draw);

	QuickPickDialog quickPickDialog(this);

	quickPickDialog.addDraws(draws);

	quickPickDialog.exec();

}

void LottoWidget::on_drawDataFinished()
{

	PowerBallTracker* tracker = &(_drawReader._tracker);

	//tracker->updateModel();

	const int precision(2);
	QTableWidgetItem* twi;
	int row(0);

	int drawCount = tracker->getDrawCount();
	if (drawCount == 0)
		return;

	_drawTable->clearContents();
	_drawTable->setRowCount(drawCount);

	for (int index(0); index < drawCount; index++)
	{
		Draw draw;

		if (tracker->getDraw(index, draw) == true)
		{
			QTableWidgetItem* twi;

			twi = new QTableWidgetItem(QString::number(draw._drawNumber));
			_drawTable->setItem(row, 0, twi);

			twi = new QTableWidgetItem(draw._drawDate.toString());
			_drawTable->setItem(row, 1, twi);

			twi = new QTableWidgetItem(QString::number(draw._numbers.at(0)));
			_drawTable->setItem(row, 2, twi);

			twi = new QTableWidgetItem(QString::number(draw._numbers.at(1)));
			_drawTable->setItem(row, 3, twi);

			twi = new QTableWidgetItem(QString::number(draw._numbers.at(2)));
			_drawTable->setItem(row, 4, twi);

			twi = new QTableWidgetItem(QString::number(draw._numbers.at(3)));
			_drawTable->setItem(row, 5, twi);

			twi = new QTableWidgetItem(QString::number(draw._numbers.at(4)));
			_drawTable->setItem(row, 6, twi);

			twi = new QTableWidgetItem(QString::number(draw._powerball));
			twi->setTextColor(Qt::red);
			_drawTable->setItem(row, 7, twi);

			row++;
		}
	}

	_drawCount->setText(QString::number(drawCount));
	FrequencyCounts frequencyCounts;

	tracker->getDrawFrequencyChart(frequencyCounts);

	_ballFreqTable->clearContents();
    _ballFreqTable->setRowCount((int) frequencyCounts.size());

	qreal totalProbability(0);

	totalProbability = 5.0 / (qreal) frequencyCounts.size() * 100.0;

	_numberProbability->setText(QString::number(totalProbability, 'f', precision) + "%");

	row = 0;

	auto frequencyCount = frequencyCounts.begin();
	while (frequencyCount != frequencyCounts.end())
	{
		twi = new QTableWidgetItem(QString::number((*frequencyCount).first));
		_ballFreqTable->setItem(row, 0, twi);

		twi = new QTableWidgetItem(QString::number((*frequencyCount).second));
		_ballFreqTable->setItem(row, 1, twi);

		totalProbability = ((qreal) (*frequencyCount).second / (qreal) drawCount) * 100.0;
		twi = new QTableWidgetItem(QString::number(totalProbability, 'f', precision) + "%");
		_ballFreqTable->setItem(row, 2, twi);

		row++;
		frequencyCount++;
	}

	tracker->getPowerballFrequencyChart(frequencyCounts);

	row = 0;

	_pBallFreqTable->clearContents();
    _pBallFreqTable->setRowCount((int) frequencyCounts.size());

	totalProbability = 0;

	totalProbability = (1.0 / (qreal) frequencyCounts.size()) * 100.0;

	_pBallProbability->setText(QString::number(totalProbability, 'f', precision) + "%");

	frequencyCount = frequencyCounts.begin();
	while (frequencyCount != frequencyCounts.end())
	{
		twi = new QTableWidgetItem(QString::number((*frequencyCount).first));
		_pBallFreqTable->setItem(row, 0, twi);

		twi = new QTableWidgetItem(QString::number((*frequencyCount).second));
		_pBallFreqTable->setItem(row, 1, twi);

		totalProbability = ((qreal) (*frequencyCount).second / (qreal) drawCount) * 100.0;
		twi = new QTableWidgetItem(QString::number(totalProbability, 'f', precision) + "%");
		_pBallFreqTable->setItem(row, 2, twi);

		row++;
		frequencyCount++;
	}

	QApplication::restoreOverrideCursor();

}
