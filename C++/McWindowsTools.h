#pragma once

#include <QObject>

class McWindowsTools : public QObject
{
	Q_OBJECT

public:
	McWindowsTools(QObject *parent = 0);
	~McWindowsTools();

	//获取用户名  
	QString getUserName();
};
