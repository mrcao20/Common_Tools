#pragma once

#include <qdatetime.h>

class McDateTime{

public:
	McDateTime();
	~McDateTime();

	QDateTime getNetworkDate(const QString &ntpHost);
	qint64 getNetworkCurrentMSecs(const QString &ntpHost);
};

