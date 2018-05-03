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

#include "PowerballReader.h"

#include <QCryptographicHash>
#include <QtNetwork>

PowerballReader::PowerballReader() :
	_networkActive(false)
{

}

PowerballReader::~PowerballReader()
{

}

quint32 PowerballReader::id()
{
    static quint32 sId(0);

    if (sId == 0)
    {
        QCryptographicHash hash(QCryptographicHash::Md5);

        hash.addData(name().toLatin1());
        QByteArray result = hash.result().toHex();
        result = result.left(8);
        sId = result.toLong(Q_NULLPTR, 16);
    }

    return sId;
}

QString PowerballReader::name()
{
    return "Powerball";
}

SourceType PowerballReader::sourceType()
{
    return SourceType::eDownload;
}

bool PowerballReader::update()
{
    bool result(false);
	int count(0);

	_networkActive = true;

	QNetworkAccessManager* manager = new QNetworkAccessManager(this);
	connect(manager, &QNetworkAccessManager::finished, this, &PowerballReader::replyFinished);

	manager->get(QNetworkRequest(QUrl("http://www.calottery.com/sitecore/content/Miscellaneous/download-numbers/?GameName=powerball&Order=No")));

	while (_networkActive == true && count < 10)
	{
		QThread::sleep(1);
		count++;
	}

	if (_networkActive == false)
	{
		result = false;
	}
	else
	{

	}

    return result;
}

QStringList PowerballReader::drawHeadings()
{
    static QStringList headings;

    if (headings.isEmpty())
        headings << "Draw Date" << "Ball 1" << "Ball 2" << "Ball 3" << "Ball 4" << "Ball 5" << "Powerball";

    return headings;
}

bool PowerballReader::getNextDraw(QStringList& data)
{
    bool result(false);



    return result;
}

void PowerballReader::replyFinished
(
	QNetworkReply* networkReply
)
{
	_drawData = networkReply->readAll();
	networkReply->deleteLater();
}
