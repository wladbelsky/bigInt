#pragma once
#define DEFAULT_SIZE 1000
#include <iostream>

using namespace std;

class bigInt
{

	short int *arr;
	int length;
	char sign;
public:
	bigInt();
	~bigInt();
	bigInt(const bigInt &);
	bigInt inversed() const;

	friend istream& operator>>(istream &, bigInt &);
	friend ostream& operator<<(ostream &, bigInt &);
	bigInt operator+(const bigInt &);
	bigInt operator-(const bigInt &);
	bigInt operator*(const bigInt &);//test
	bigInt operator=(const bigInt &);

	static int moduleCompare(bigInt, bigInt);
	static int signCompare(bigInt, bigInt);
};
