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

#include "LottoWindow.h"
#include "ui_LottoWindow.h"

#include "PowerballReader.h"

LottoWindow::LottoWindow
(
    QWidget* parent
) :
	QDialog(parent),
    _ui(new Ui::LottoWindow)
{
    _ui->setupUi(this);

    initialize();
}

LottoWindow::~LottoWindow()
{
    delete _ui;
}

void LottoWindow::initialize()
{
    _drawReaders.push_back(new PowerballReader);

    _ui->_gamesCombo->blockSignals(true);

    auto drawReader = _drawReaders.begin();
    while (drawReader != _drawReaders.end())
    {
        _ui->_gamesCombo->addItem((*drawReader)->name(), (*drawReader)->id());
        drawReader++;
    }

    _ui->_gamesCombo->blockSignals(false);

    on__gamesCombo_currentIndexChanged(_ui->_gamesCombo->currentText());
}

void LottoWindow::on__gamesCombo_currentIndexChanged
(
    const QString& text
)
{
    auto drawReader = _drawReaders.begin();
    while (drawReader != _drawReaders.end())
    {
        if ((*drawReader)->name() == text)
        {
			_currentDrawReader = *drawReader;
			switch (_currentDrawReader->sourceType())
			{
			case eFile:
				_ui->_gameAction->setText("Open File");
				break;

			case eDownload:
				_ui->_gameAction->setText("Download");
				break;
			}

            _ui->_drawTable->clear();
			_ui->_drawTable->setHorizontalHeaderLabels(_currentDrawReader->drawHeadings());
            break;
        }
        drawReader++;
    }
}

void LottoWindow::on__gameAction_released()
{
	bool updated = _currentDrawReader->update();
	if (updated == true)
	{

	}
}
