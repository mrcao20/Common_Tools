#include "McDateTime.h"
#include <qudpsocket.h>

McDateTime::McDateTime(){
}

McDateTime::~McDateTime(){
}

QDateTime McDateTime::getNetworkDate(const QString &ntpHost) {
	//use ntp server get network time
	QUdpSocket udp_sock;
	udp_sock.connectToHost(ntpHost, 123);
	//request server time
	qint8 LI = 0;
	qint8 VN = 3;
	qint8 MODE = 3;
	qint8 STRATUM = 0;
	qint8 POLL = 4;
	qint8 PREC = -6;
	QDateTime epoch(QDate(1900, 1, 1));
	qint32 second = quint32(epoch.secsTo(QDateTime::currentDateTime()));
	qint32 temp = 0;
	QByteArray time_req(48, 0);
	time_req[0] = (LI << 6) | (VN << 3) | (MODE);
	time_req[1] = STRATUM;
	time_req[2] = POLL;
	time_req[3] = PREC & 0xff;
	time_req[5] = 1;
	time_req[9] = 1;
	time_req[40] = (temp = (second & 0xff000000) >> 24);
	temp = 0;
	time_req[41] = (temp = (second & 0x00ff0000) >> 16);
	temp = 0;
	time_req[42] = (temp = (second & 0x0000ff00) >> 8);
	temp = 0;
	time_req[43] = ((second & 0x000000ff));

	QDateTime cur_dt;
	//block wait connect
	if (udp_sock.waitForConnected(3000))
	{
		udp_sock.flush();
		//request time
		udp_sock.write(time_req);
		QString s, tmp;
		for (int i = 0; i < 48; i++)
		{
			tmp.sprintf("%.2X", (unsigned char)time_req[i]);
			s.append(tmp);
			tmp.sprintf(" ");
			s.append(tmp);
		}

		//block wait reply
		if (udp_sock.waitForReadyRead(5000))
		{
			QByteArray new_time;
			QDateTime epoch(QDate(1900, 1, 1));
			QDateTime unix_start(QDate(1970, 1, 1));
			while (udp_sock.hasPendingDatagrams())
			{
				new_time.resize(udp_sock.pendingDatagramSize());
				udp_sock.read(new_time.data(), new_time.size());
			}

			QString s, tmp;
			for (int i = 0; i < 48; i++)
			{
				tmp.sprintf("%.2X", (unsigned char)new_time[i]);
				s.append(tmp);
				tmp.sprintf(" ");
				s.append(tmp);
			}

			QByteArray TransmitTimeStamp;
			TransmitTimeStamp = new_time.right(8);
			quint32 seconds = TransmitTimeStamp[0];
			quint8 temp = 0;
			for (int j = 1; j <= 3; j++)
			{
				seconds = seconds << 8;
				temp = TransmitTimeStamp[j];
				seconds = seconds + temp;
			}
			
			cur_dt.setTime_t(seconds - epoch.secsTo(unix_start));
		}

		udp_sock.disconnectFromHost();
		udp_sock.close();
	}
	return cur_dt;
}

qint64 McDateTime::getNetworkCurrentMSecs(const QString &ntpHost) {
	QDateTime dateTime = getNetworkDate(ntpHost);
	return dateTime.currentMSecsSinceEpoch();
}
