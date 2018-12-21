#include "McWindowsTools.h"
#include <qprocess.h>

McWindowsTools::McWindowsTools(QObject *parent)
	: QObject(parent)
{
}

McWindowsTools::~McWindowsTools(){
}

//获取用户名  
QString McWindowsTools::getUserName()
{
#if 1  
	QStringList envVariables;
	envVariables << "USERNAME.*" << "USER.*" << "USERDOMAIN.*"
		<< "HOSTNAME.*" << "DOMAINNAME.*";
	QStringList environment = QProcess::systemEnvironment();
	foreach(QString string, envVariables) {
		int index = environment.indexOf(QRegExp(string));
		if (index != -1) {
			QStringList stringList = environment.at(index).split('=');
			if (stringList.size() == 2) {
				return stringList.at(1);
				break;
			}
		}
	}
	return "unknown";
#else  
	QString userName = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
	userName = userName.section("/", -1, -1);
	return userName;
#endif  
}
