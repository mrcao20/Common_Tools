#pragma once

#include <QObject>
#include <string>

class McCrypto : public QObject {
	Q_OBJECT

public:
	explicit McCrypto(QObject *parent = 0);
	~McCrypto();

	int encrypt4aes(const QByteArray &inData, const QByteArray &strKey,
		QByteArray &outData, QByteArray &errMsg);

	int decrypt4aes(const QByteArray &inData, const QByteArray &strKey,
		QByteArray &outData, QByteArray &errMsg);

	QByteArray md5(const QByteArray &inData);

};