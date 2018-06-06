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

#include "QuickPickDialog.h"

#include <QAction>
#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>

QuickPickDialog::QuickPickDialog
(
	QWidget* parent
) :
	QDialog(parent)
{
	setupUi(this);

	QAction* printAction = new QAction("Print", this);
	connect(printAction, &QAction::triggered, this, &QuickPickDialog::print);
	this->addAction(printAction);
}

void QuickPickDialog::addDraws
(
	Draws draws
)
{
	int row(0);

	_quickPicks->clearContents();
	_quickPicks->setRowCount(draws.count());

	QTableWidgetItem* twi;

	auto draw = draws.begin();
	while (draw != draws.end())
	{
		twi = new QTableWidgetItem(QString::number(draw->_numbers.at(0)));
		_quickPicks->setItem(row, 0, twi);

		twi = new QTableWidgetItem(QString::number(draw->_numbers.at(1)));
		_quickPicks->setItem(row, 1, twi);

		twi = new QTableWidgetItem(QString::number(draw->_numbers.at(2)));
		_quickPicks->setItem(row, 2, twi);

		twi = new QTableWidgetItem(QString::number(draw->_numbers.at(3)));
		_quickPicks->setItem(row, 3, twi);

		twi = new QTableWidgetItem(QString::number(draw->_numbers.at(4)));
		_quickPicks->setItem(row, 4, twi);

		twi = new QTableWidgetItem(QString::number(draw->_powerball));
		twi->setTextColor(Qt::red);
		_quickPicks->setItem(row, 5, twi);

		row++;
		draw++;
	}
}

void QuickPickDialog::print
(
	bool checked
)
{
	Q_UNUSED(checked);

	QPrinter printer;
	printer.setPageOrientation(QPageLayout::Landscape);

	QPrintDialog dialog(&printer, this);
	dialog.setWindowTitle(tr("Print Document"));

	if (dialog.exec() == QDialog::Accepted)
	{
		QPainter painter;

		painter.begin(&printer);

		double xscale = printer.pageRect().width()/double(_quickPicks->width());
		xscale -= .10;
		double yscale = printer.pageRect().height()/double(_quickPicks->height());
		double scale = qMin(xscale, yscale);
		painter.translate(printer.paperRect().x() + printer.pageRect().width()/2,
						   printer.paperRect().y() + printer.pageRect().height()/2);
		painter.scale(scale, scale);
		painter.translate(-width()/2, -height()/2);

		_quickPicks->render(&painter);
	}
}
