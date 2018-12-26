/**
 * @Name    : RSA.h
 * @Date    : 2017-04-11-22.25.57
 * @Author  : Silenceneo (silenceneo_xw@163.com)
 * @Link    : http://www.cnblogs.com/Silenceneo-xw/
 * @Version : 2.0
 */

#ifndef __RSA_H__
#define __RSA_H__

#include <ostream>
#include "BigInteger.h"
class RSA {
public:
	RSA() {}
	RSA(const unsigned len) { init(len); }    // ����len��ʼ������
	~RSA() {}

	void init(const unsigned);// ��ʼ��,������˽Կ��

	BigInteger encryptByPublic(const BigInteger &);    // ��Կ����
	BigInteger decryptByPrivate(const BigInteger &);// ˽Կ����

	// ������Ҫ��������ǩ��
	BigInteger encryptByPrivate(const BigInteger &);// ˽Կ����
	BigInteger decryptByPublic(const BigInteger &);    // ��Կ����

	void computingKey();
	void computingKey(const BigInteger &pp, const BigInteger &qq);
	inline void setN(const BigInteger &nn) { n = nn; }
	inline void setE(const BigInteger &ee) { e = ee; }
	inline void setD(const BigInteger &dd) { d = dd; }
	inline void setP(const BigInteger &pp) { p = pp; }
	inline void setQ(const BigInteger &qq) { q = qq; }
protected:
	friend std::ostream & operator << (std::ostream &, const RSA &);// ����������
private:
	BigInteger createOddNum(unsigned);// ����һ��������,����Ϊ�䳤��
	bool isPrime(const BigInteger &, const unsigned);// �ж��Ƿ�Ϊ����
	BigInteger createRandomSmaller(const BigInteger &);// �������һ����С����
	BigInteger createPrime(unsigned, const unsigned);// ����һ��������,����Ϊ�䳤��
	void createExponent(const BigInteger &);// �����ṩ��ŷ�������ɹ�Կ��˽Կָ��
public:
	BigInteger n, e;// ��Կ
private:
	BigInteger d;// ˽Կ
	BigInteger p, q;// ������p��q
	BigInteger eul;// n��ŷ������
};

#endif // __RSA_H__