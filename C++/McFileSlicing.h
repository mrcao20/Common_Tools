#pragma once
#pragma execution_character_set("utf-8")

#include <QObject>

class McFileSlicing : public QObject
{
	Q_OBJECT

public:
	McFileSlicing(QObject *parent = 0);
	~McFileSlicing();

	bool fileSlicing(const QString &inFilePath, const QString &outFilePath, int segmentTime, bool isDeleteSource = false);
	bool fileSlicing_new(const QString &inFilePath, const QString &outFilePath, int segmentTime, bool isDeleteSource = false);
	bool truncateAndSlicing(const QString &inFilePath, const QString &outFilePath, int segmentTime, bool isDeleteSource = false);

signals:
	void slicingFinished();
	void errorOccurred();

private:
	bool isH264AndAac(const QString &filePath);
	void completeM3u8(const QString &tempFilePath, const QString &m3u8FilePath);
	bool del_File(const QString &path);
	bool checkoutDir(const QString &srcDirPath, const QString &dstDirPath) const;
};
