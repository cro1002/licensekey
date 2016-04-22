// ConsoleApplication1.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

#include "license.h"

int main()
{
	cro::license myLicense;

	myLicense.init("KLR", "XX-XX-XXX");

	string getCode;
	cout << myLicense.getSeed().c_str() << endl;

	for (int i = 0; i < 100; ++i) {
		getCode.clear();
		cout << (myLicense.getLicense(i, getCode) ? getCode.c_str() : "no") << " : " << i << endl;
	}

	for (int i = 578400; i < 578450; ++i) {
		getCode.clear();
		cout << (myLicense.getLicense(i, getCode) ? getCode.c_str() : "no") << " : " << i << endl;
	}

	for (int i = 1048570; i < 1048580; ++i) {
		getCode.clear();
		cout << ( myLicense.getLicense(i, getCode) ? getCode.c_str() : "no" ) << " : " << i << endl;
	}

	return 0;
}

