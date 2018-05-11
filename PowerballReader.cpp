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

#include <QApplication>
#include <QCryptographicHash>

PowerballReader::PowerballReader()
{
	_networkAccessManager = new QNetworkAccessManager(this);

	connect(_networkAccessManager, &QNetworkAccessManager::authenticationRequired, this, &PowerballReader::on_authenticationRequired);
	connect(_networkAccessManager, &QNetworkAccessManager::encrypted, this, &PowerballReader::on_encrypted);
	connect(_networkAccessManager, &QNetworkAccessManager::finished, this, &PowerballReader::on_finished);
	connect(_networkAccessManager, &QNetworkAccessManager::networkAccessibleChanged, this, &PowerballReader::on_networkAccessibleChanged);
	connect(_networkAccessManager, &QNetworkAccessManager::proxyAuthenticationRequired, this, &PowerballReader::on_proxyAuthenticationRequired);
	connect(_networkAccessManager, SIGNAL(sslErrors(QNetworkReply*, const QList<QSslError>&)),
			this, SLOT(on_sslErrors(QNetworkReply*, const QList<QSslError>&)));
}

PowerballReader::~PowerballReader()
{
	if (_networkAccessManager != Q_NULLPTR)
	{
		_networkAccessManager->disconnect();
		_networkAccessManager->deleteLater();
		_networkAccessManager = Q_NULLPTR;
	}
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

	if (_networkAccessManager != Q_NULLPTR)
	{
		_networkReply = _networkAccessManager->get(
			QNetworkRequest(
				QUrl("http://www.calottery.com/sitecore/content/Miscellaneous/download-numbers/?GameName=powerball&Order=No")));

		connect(_networkReply, SIGNAL(QNetworkReply::readyRead()), this, SLOT(PowerballReader::on_readyRead()));
		connect(_networkReply, SIGNAL(QNetworkReply::error(QNetworkReply::NetworkError)), this, SLOT(PowerballReader::on_error(QNetworkReply::NetworkError)));
		connect(_networkReply, SIGNAL(sslErrors(QList<QSslError> sslErrors)),
				this, SLOT(PowerballReader::on_sslErrors(QList<QSslError> sslErrors)));
	}
    return result;
}

bool PowerballReader::getNextDraw(QStringList& data)
{
    bool result(false);

    return result;
}

void PowerballReader::on_finished
(
	QNetworkReply* networkReply
)
{
	_drawData = networkReply->readAll();
	networkReply->deleteLater();
	_networkReply = Q_NULLPTR;

	QByteArrayList lines = _drawData.split('\n');
	auto line = lines.begin();
	while (line != lines.end())
	{
		char aChar = (*line).at(0);
		if (aChar >= '0' && aChar <= '9')
		{
			QByteArray trimmedLine = (*line).trimmed();

			while (trimmedLine.indexOf("  ") != -1)
				trimmedLine.replace("  ", " ");

			QByteArrayList iotas = trimmedLine.split(' ');
			if (iotas.count() >= 11)
			{
				int drawNumber = iotas.at(0).toInt();
				QByteArray dateString =
						iotas.at(1) + " " +
						iotas.at(2) + " " +
						iotas.at(3) + " " +
						iotas.at(4);

				dateString.replace(",", "");
				dateString.replace(".", "");

				QDate drawDate = QDate::fromString(QString(dateString), QString("ddd MMM dd yyyy"));
				std::vector<int> numbers;
				numbers.push_back(iotas.at(5).toInt());
				numbers.push_back(iotas.at(6).toInt());
				numbers.push_back(iotas.at(7).toInt());
				numbers.push_back(iotas.at(8).toInt());
				numbers.push_back(iotas.at(9).toInt());

				int powerBall = iotas.at(10).toInt();
			}
		}
		line++;
	}
}

void PowerballReader::on_readyRead()
{
	bool dataReady = true;
	int i(0);

	i++;
}

void PowerballReader::on_error
(
	QNetworkReply::NetworkError networkError
)
{
	bool dataReady = true;
	int i(0);

	i++;
}

void PowerballReader::on_sslErrors
(
	QList<QSslError> sslErrors
)
{
	bool dataReady = true;
	int i(0);

	i++;
}

void PowerballReader::on_authenticationRequired(QNetworkReply* reply, QAuthenticator* authenticator)
{

}

void PowerballReader::on_encrypted(QNetworkReply* reply)
{

}

void PowerballReader::on_networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility accessible)
{

}

void PowerballReader::on_proxyAuthenticationRequired(const QNetworkProxy& proxy, QAuthenticator* authenticator)
{
}

void PowerballReader::on_sslErrors(QNetworkReply* reply, const QList<QSslError> & errors)
{

}
