/**
 * @Name    : EncryptDecrypt.h
 * @Date    : 2017-04-11-22.29.58
 * @Author  : Silenceneo (silenceneo_xw@163.com)
 * @Link    : http://www.cnblogs.com/Silenceneo-xw/
 * @Version : 2.0
 */

#ifndef __ENCRYPTDECRYPT_H__
#define __ENCRYPTDECRYPT_H__

#include <string>
#include "RSA.h"
class EncryptDecrypt {
public:
	EncryptDecrypt() {}
	~EncryptDecrypt() {}

	void menu();    // �˵���ʾ
	bool encrypt();    // ����
	bool decrypt();    // ����
	void print();    // ��ӡRSA�����Ϣ
	void reset();    // ����RSA�����Ϣ
protected:
	void load(int);    // ���ݸ���λ������RSA����
	bool islegal(const std::string &);// �ж������ַ����Ƿ�Ϸ�
private:
	RSA rsa;
};

#endif // __ENCRYPTDECRYPT_H__