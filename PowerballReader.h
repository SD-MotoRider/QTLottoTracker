#ifndef POWERBALLREADER_H
#define POWERBALLREADER_H

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

#include <QList>
#include <QObject>

enum SourceType
{
	eFile,
	eDownload
};

#include <QtNetwork>
#include <QNetworkReply>
#include <QSslError>

class PowerballReader :
	public QObject
{
Q_OBJECT

public:
	PowerballReader();
	virtual ~PowerballReader();

	virtual quint32 id(void);
	virtual QString name(void);
	virtual SourceType sourceType(void);
	virtual bool update(void);

	PowerBallTracker _tracker;

signals:
	void drawFinished(void);

private slots:
	void on_authenticationRequired(QNetworkReply* reply, QAuthenticator* authenticator);
	void on_encrypted(QNetworkReply* reply);
	void on_finished(QNetworkReply* reply);
	void on_networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility accessible);
	void on_proxyAuthenticationRequired(const QNetworkProxy& proxy, QAuthenticator* authenticator);
	void on_sslErrors(QNetworkReply* reply, const QList<QSslError> & errors);

	void on_readyRead();
	void on_error(QNetworkReply::NetworkError networkError);
	void on_sslErrors(QList<QSslError>);

private:
	QNetworkAccessManager*		_networkAccessManager;
	QNetworkReply*				_networkReply;
	QByteArray					_drawData;
};

#endif // DRAWREADER_H
