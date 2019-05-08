#include "McFileSlicing.h"
#include <qprocess.h>
#include <qfileinfo.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qtextcodec.h>
#include <qdir.h>
#include <qapplication.h>

extern "C" {
#include <libavformat/avformat.h>
#include <libavutil/error.h>
}

#pragma comment(lib, "D:/soft/tools/FFmpeg/lib/avformat.lib")
#pragma comment(lib, "D:/soft/tools/FFmpeg/lib/avutil.lib")

McFileSlicing::McFileSlicing(QObject *parent)
	: QObject(parent)
{
}

McFileSlicing::~McFileSlicing() {
}

bool McFileSlicing::fileSlicing(const QString &inFilePath, const QString &outFilePath, int segmentTime, bool isDeleteSource) {
	if (inFilePath.isEmpty() || outFilePath.isEmpty())
	{
		emit errorOccurred();
		return false;
	}
	if (!checkoutDir(inFilePath, outFilePath))
	{
		emit errorOccurred();
		return false;
	}
	QFileInfo inFileInfo(inFilePath);
	QFileInfo outFileInfo(outFilePath);
	QString inFileSuffix = inFileInfo.suffix();
	QString outFileBaseName = outFileInfo.baseName();
	QString mp4FilePath;
	bool isRawDataMp4 = false;
	if (isH264AndAac(inFilePath)) {
		if (inFileSuffix == "mp4") {
			mp4FilePath = inFilePath;
			isRawDataMp4 = true;
		}
		else {
			mp4FilePath = outFileInfo.absolutePath() + "/" + outFileBaseName + ".mp4";
			if (0 != QProcess::execute(QString("ffmpeg -i %1 -acodec copy -vcodec copy %2").arg(inFilePath, mp4FilePath)))
			{
				emit errorOccurred();
				return false;
			}
		}
	}
	else {
		mp4FilePath = outFileInfo.absolutePath() + "/" + outFileBaseName + ".mp4";
		/*if (0 != QProcess::execute(QString("ffmpeg1 -i %1 -acodec libfaac -vcodec libx264 %2").arg(inFilePath, mp4FilePath)))*/
		if (0 != QProcess::execute(QString("ffmpeg -i %1 -y -c:v libx264 -strict -2 %2").arg(inFilePath, mp4FilePath)))
		{
			emit errorOccurred();
			return false;
		}
	}
	QString tsFilePath = outFileInfo.absolutePath() + "/" + outFileBaseName + ".ts";
	QString convertCmd = QString("ffmpeg -y -i %1 -vcodec copy -acodec copy -vbsf h264_mp4toannexb %2").arg(mp4FilePath, tsFilePath);
	if (0 != QProcess::execute(convertCmd))
	{
		emit errorOccurred();
		return false;
	}
	QString tsSegPath = outFileInfo.absolutePath() + "/" + outFileBaseName + "-%03d.ts";
	//QString tempFilePath = outFileInfo.absolutePath() + "/" + outFileBaseName + "temp.m3u8";
	QString slicingCmd = QString("ffmpeg -i %1 -c copy -map 0 -f segment -segment_list %2 -segment_time %3 %4")
		.arg(tsFilePath, outFilePath, QString::number(segmentTime), tsSegPath);
	if (0 != QProcess::execute(slicingCmd))
	{
		emit errorOccurred();
		return false;
	}
	//completeM3u8(tempFilePath, outFilePath);
	if (!isRawDataMp4)
		QFile::remove(mp4FilePath);
	QFile::remove(tsFilePath);
	if (isDeleteSource)
		QFile::remove(inFilePath);
	//QFile::remove(tempFilePath);
	/*QString newOutFilePath = outFileInfo.absolutePath() + "/" + outFileBaseName;
	QFile::remove(newOutFilePath);
	QFile::rename(outFilePath, newOutFilePath);*/
	emit slicingFinished();
	return true;
}

bool McFileSlicing::fileSlicing_new(const QString &inFilePath, const QString &outFilePath, int segmentTime, bool isDeleteSource) {
	if (inFilePath.isEmpty() || outFilePath.isEmpty())
	{
		emit errorOccurred();
		return false;
	}
	if (!checkoutDir(inFilePath, outFilePath))
	{
		emit errorOccurred();
		return false;
	}
	QFileInfo inFileInfo(inFilePath);
	QFileInfo outFileInfo(outFilePath);
	QString inFileSuffix = inFileInfo.suffix();
	QString outFileBaseName = outFileInfo.baseName();
	QString mp4FilePath;
	bool isRawDataMp4 = false;
	if (isH264AndAac(inFilePath)) {
		if (inFileSuffix == "mp4") {
			mp4FilePath = inFilePath;
			isRawDataMp4 = true;
		}
		else {
			mp4FilePath = outFileInfo.absolutePath() + "/" + outFileBaseName + ".mp4";
			if (0 != QProcess::execute(QString("ffmpeg -i %1 -acodec copy -vcodec copy %2").arg(inFilePath, mp4FilePath)))
			{
				emit errorOccurred();
				return false;
			}
		}
	}
	else {
		mp4FilePath = outFileInfo.absolutePath() + "/" + outFileBaseName + ".mp4";
		if (0 != QProcess::execute(QString("ffmpeg -i %1 -y -c:v libx264 -strict -2 %2").arg(inFilePath, mp4FilePath)))
		{
			emit errorOccurred();
			return false;
		}
	}
	QString tsSegPath = outFileInfo.absolutePath() + "/" + outFileBaseName + "-%03d.ts";
	QString keyinfo = qApp->applicationDirPath() + "/encrypt.keyinfo";
	/*QString slicingCmd = QString(R"(ffmpeg -y -i %1 -hls_time %2 -hls_key_info_file %3 -hls_playlist_type vod -hls_segment_filename "%4" %5)")
		.arg(mp4FilePath, QString::number(segmentTime), keyinfo, tsSegPath, outFilePath);*/
	QString slicingCmd = QString(R"(ffmpeg -i %1 -c copy -bsf:v h264_mp4toannexb -hls_time %2 -hls_list_size 0 -hls_key_info_file %3 %4)")
		.arg(mp4FilePath, QString::number(segmentTime), keyinfo, outFilePath);
	if (0 != QProcess::execute(slicingCmd))
	{
		emit errorOccurred();
		return false;
	}
	if (!isRawDataMp4)
		QFile::remove(mp4FilePath);
	if (isDeleteSource)
		QFile::remove(inFilePath);
	emit slicingFinished();
	return true;
}

bool McFileSlicing::truncateAndSlicing(const QString &inFilePath, const QString &outFilePath, int segmentTime, bool isDeleteSource)
{
	// m3u8文件将被包含在一个名为它自身文件名的文件夹下
	if (!del_File(QFileInfo(QFileInfo(outFilePath).absolutePath()).absolutePath()))
	{
		emit errorOccurred();
		return false;
	}
	return fileSlicing_new(inFilePath, outFilePath, segmentTime, isDeleteSource);
}

bool McFileSlicing::isH264AndAac(const QString &filePath) {
	QString errorStr = "";
	if (filePath.isEmpty()) {
		errorStr = "file not found";
		return false;
	}
	AVFormatContext *inputAVFormatCxt = NULL;
	if (int res = (avformat_open_input(&inputAVFormatCxt, filePath.toStdString().c_str(), 0, NULL)) != 0) {
		char errBuf[AV_ERROR_MAX_STRING_SIZE];
		errorStr = "can not open file:" + filePath + ",errcode:" + QString::number(res) +
			",err msg:" + av_make_error_string(errBuf, AV_ERROR_MAX_STRING_SIZE, res);
		return false;
	}
	if (avformat_find_stream_info(inputAVFormatCxt, 0) < 0) {
		errorStr = "can not find stream info";
		return false;
	}
	av_dump_format(inputAVFormatCxt, 0, filePath.toStdString().c_str(), 0);
	bool isH264 = false;
	bool isAac = false;
	for (int i = 0; i < inputAVFormatCxt->nb_streams; ++i) {
		AVStream *in_stream = inputAVFormatCxt->streams[i];
		if (in_stream->codec->codec_type == AVMEDIA_TYPE_VIDEO && in_stream->codec->codec_id == AV_CODEC_ID_H264) {
			isH264 = true;
		}
		else if (in_stream->codec->codec_type == AVMEDIA_TYPE_AUDIO && in_stream->codec->codec_id == AV_CODEC_ID_AAC) {
			isAac = true;
		}
	}
	avformat_close_input(&inputAVFormatCxt);
	return (isH264 && isAac);
}

void McFileSlicing::completeM3u8(const QString &tempFilePath, const QString &m3u8FilePath) {
	QFile tempFile(tempFilePath);
	QFile m3u8File(m3u8FilePath);
	if (!tempFile.open(QIODevice::ReadOnly) || !m3u8File.open(QIODevice::WriteOnly))
		return;
	QTextStream tempStream(&tempFile);
	QTextStream m3u8Stream(&m3u8File);
	tempStream.setCodec(QTextCodec::codecForName("utf-8"));//必须加，否则含有中文时乱码
	m3u8Stream.setCodec(QTextCodec::codecForName("utf-8"));//必须加，否则含有中文时乱码
	QString tsFilePath = QFileInfo(m3u8FilePath).absolutePath();
	QString str = "";
	while (!(str = tempStream.readLine()).isEmpty()) {
		if (str.endsWith(".ts")) {
			str = tsFilePath + "/" + str;
		}
		m3u8Stream << str << endl;
		m3u8Stream.flush();
	}
	tempFile.close();
	m3u8File.close();
}

bool McFileSlicing::del_File(const QString &path)
{
	QDir dir(path);
	QFileInfoList fileInfoList = dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
	for (const QFileInfo &fileInfo : fileInfoList)
	{
		if (fileInfo.isFile())
		{
			if (!fileInfo.dir().remove(fileInfo.fileName()))
			{
				return false;
			}
		}
		else
		{
			if (!del_File(fileInfo.absoluteFilePath()) || !dir.rmdir(fileInfo.fileName()))
			{
				return false;
			}
		}
	}
	return true;
}

bool McFileSlicing::checkoutDir(const QString &srcDirPath, const QString &dstDirPath) const
{
	QDir dstDir(QFileInfo(dstDirPath).absoluteDir());
	if (!QFileInfo(srcDirPath).exists())
	{
		return false;
	}
	if (!dstDir.exists())
	{
		return dstDir.mkpath(dstDir.absolutePath());
	}
	return true;
}
