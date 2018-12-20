#include "McCrypto.h"

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1

#include <cryptopp/filters.h>
#include <cryptopp/modes.h>
#include <cryptopp/Hex.h>      // StreamTransformationFilter
#include <cryptopp/aes.h>
#include <cryptopp/md5.h>
#include <string>

using namespace CryptoPP;

enum AESKeyLength {
	AES_KEY_LENGTH_16 = 16, AES_KEY_LENGTH_24 = 24, AES_KEY_LENGTH_32 = 32
};

McCrypto::McCrypto(QObject *parent) :
	QObject(parent) {

}

McCrypto::~McCrypto() {
}

int McCrypto::encrypt4aes(const QByteArray &inData, const QByteArray &strKey,
	QByteArray &outData, QByteArray &errMsg)
{
	outData = "";
	errMsg = "";

	if (inData.isEmpty() || strKey.isEmpty())
	{
		errMsg = "indata or key is empty!!";
		return -1;
	}

	unsigned int iKeyLen = strKey.length();

	if (iKeyLen != AES_KEY_LENGTH_16 && iKeyLen != AES_KEY_LENGTH_24
		&& iKeyLen != AES_KEY_LENGTH_32)
	{
		errMsg = "aes key invalid!!";
		return -2;
	}

	//byte iv[AES::BLOCKSIZE];
	QByteArray iv = "0102030405060708";
	int iResult = 0;

	try
	{
		std::string tempData = "";
		QByteArray in = inData;
		CBC_Mode<AES>::Encryption e;
		e.SetKeyWithIV((byte*)strKey.toStdString().c_str(), iKeyLen, (byte *)iv.toStdString().c_str());
		StringSource ss(in.toStdString(), true,
			new StreamTransformationFilter(e, new StringSink(tempData)));
		outData = QByteArray(tempData.c_str(), tempData.size()).toBase64();
	}
	catch (const CryptoPP::Exception& e)
	{
		std::string err = e.GetWhat();
		errMsg = QByteArray(err.c_str(), err.size());
		iResult = -3;
	}

	return iResult;
}

int McCrypto::decrypt4aes(const QByteArray &inData, const QByteArray &strKey,
	QByteArray &outData, QByteArray &errMsg)
{
	outData = "";
	errMsg = "";

	if (inData.isEmpty() || strKey.isEmpty())
	{
		errMsg = "indata or key is empty!!";
		return -1;
	}

	unsigned int iKeyLen = strKey.length();

	if (iKeyLen != AES_KEY_LENGTH_16 && iKeyLen != AES_KEY_LENGTH_24
		&& iKeyLen != AES_KEY_LENGTH_32)
	{
		errMsg = "aes key invalid!!";
		return -2;
	}

	//byte iv[AES::BLOCKSIZE];
	QByteArray iv = "0102030405060708";
	int iResult = 0;

	try
	{
		std::string tempData = "";
		QByteArray in = QByteArray::fromBase64(inData);
		CBC_Mode<AES>::Decryption d;
		d.SetKeyWithIV((byte*)strKey.toStdString().c_str(), iKeyLen, (byte *)iv.toStdString().c_str());
		StringSource ss(in.toStdString(), true,
			new StreamTransformationFilter(d, new StringSink(tempData)));
		outData = QByteArray(tempData.c_str(), tempData.size());
	}
	catch (const CryptoPP::Exception& e)
	{
		std::string err = e.GetWhat();
		errMsg = QByteArray(err.c_str(), err.size());
		iResult = -3;
	}

	return iResult;
}

QByteArray McCrypto::md5(const QByteArray &inData)
{
	std::string digest;
	Weak1::MD5 md5;
	StringSource(inData.toStdString(), true,
		new HashFilter(md5, new HexEncoder(new StringSink(digest))));

	return QByteArray(digest.c_str(), digest.size());
}
