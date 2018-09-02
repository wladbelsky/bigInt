#include "bigInt.h"
#include <iostream>

using namespace std;

bigInt::bigInt()
{
	arr = new short int [DEFAULT_SIZE];
	length = 0;
	sign = '+';
	for (int i = 0; i < DEFAULT_SIZE; i++)
	{
		arr[i] = 0;
	}
}

bigInt::~bigInt()
{
	delete[] arr;
}

bigInt::bigInt(const bigInt &x)
{
	arr = new short int[DEFAULT_SIZE];
	for (int i = 0; i < DEFAULT_SIZE; i++)
	{
		arr[i] = 0;
	}
	length = x.length;
	sign = x.sign;
	for (int i = 0; i < length; i++)
	{
		arr[i] = x.arr[i];
	}
}

bigInt bigInt::inversed() const
{
	bigInt tmp = *this;

	for (int i = 0, j = length - 1; j >= 0; i++, j--)
	{
		tmp.arr[i] = arr[j];
	}

	return tmp;
}

bigInt bigInt::operator+(const bigInt &x)
{
	bigInt tmp;

	switch (moduleCompare(*this, x))//signCompare
	{
	case 0:
	case 1:
		tmp.length = length;
		break;
	case -1:
		tmp.length = x.length;
		break;
	default:
		break;

	}

	for (int i = 0; i < tmp.length; i++)
	{
		if (tmp.arr[i] + inversed().arr[i] + x.inversed().arr[i] > 9)
		{
			tmp.arr[i + 1] += 1;
			tmp.arr[i] += inversed().arr[i] + x.inversed().arr[i] - 10;
		}
		else
		{
			tmp.arr[i] += inversed().arr[i] + x.inversed().arr[i];
		}

	}
	if (tmp.arr[tmp.length] != 0)
	{
		tmp.length++;
	}

	return tmp.inversed();
}

bigInt bigInt::operator-(const bigInt &x)
{
	bigInt tmp, a, b;
	switch (signCompare(*this, x))
	{
		case 0:
			break;
		case 1:
			tmp.length = length;
			a = *this;
			b = x;
			break;
		case -1:
			tmp.length = x.length;
			tmp.sign = '-';
			a = x;
			b = *this;
			break;
		default:
			break;
	}

	if (b.sign == '-')
	{
		b.sign = '+';
		return *this + b;
	}
	else
	{
		a = a.inversed();
		b = b.inversed();
		for (int i = 0; i < tmp.length; i++)
		{
			if (i < b.length)
			{
				//cout << a.arr[i] << b.arr[i] << tmp.arr[i] << endl;
				if (a.arr[i] - b.arr[i] + tmp.arr[i] < 0 || (moduleCompare(*this, x) == -1) && a.arr[i] - b.arr[i] + tmp.arr[i] <= 0)
				{
					tmp.arr[i] += 10 + a.arr[i] - b.arr[i];
					tmp.arr[i + 1] -= 1;
					tmp.length--;
				}
				else
				{
					tmp.arr[i] += a.arr[i] - b.arr[i];
				}
			}
			else if (tmp.arr[i] < 0)
			{
				tmp.arr[i] += 10;
				if (b.length == i)
				{
					tmp.arr[i + 1] -= 1;
					tmp.length--;
				}
			}
			else
				tmp.arr[i] = a.arr[i];
		}
	}

	return tmp.inversed();
}

bigInt bigInt::operator*(const bigInt &x)
{
	bigInt tmp, a, b;

	switch (moduleCompare(*this, x))
	{
		case 0:
		case 1:
			//tmp.length = length;
			a = x;
			b = *this;
		case -1:
			//tmp.length = x.length;
			a = *this;
			b = x;
		default:
			break;
	}
	a = a.inversed();
	b = b.inversed();
	tmp.length = a.length;
	//for (int i = 0; i < a.length; i++)
	//{
	//	if (i < b.length)
	//	{

	//		if (a.arr[i] * b.arr[i] + tmp.arr[i] >= 10)
	//		{
	//			tmp.length++;
	//			tmp.arr[tmp.length - i] += 1;
	//			tmp.arr[tmp.length - i + 1] = a.arr[i] * b.arr[i] + tmp.arr[i] - 10;
	//		}
	//		else
	//		{
	//			tmp.arr[tmp.length - i] = a.arr[i] * b.arr[i] + tmp.arr[i];
	//		}
	//	}
	//	else
	//		tmp.arr[i] += a.arr[i];
	//}
	//150
	// 25
	for (int i = 0; i < a.length; i++)
	{
		for (int j = 0; j < b.length; j++)
		{
			tmp.arr[i] += a.arr[i] * b.arr[j];
			if (tmp.arr[tmp.length - i] >= 10)
			{
				tmp.length += j;
				tmp.arr[i] = (a.arr[i] * b.arr[j] + tmp.arr[i]) / 10;
				tmp.arr[i + 1] += (a.arr[i] * b.arr[j] + tmp.arr[i]) % 10;
			}
			cout << a.arr[i] * b.arr[j] << " " << tmp.arr[tmp.length - i] << endl;
		}

	}

	return tmp.inversed();
}

bigInt bigInt::operator=(const bigInt &x)
{
	arr = new short int[DEFAULT_SIZE];
	length = x.length;
	sign = x.sign;
	for (int i = 0; i < length; i++)
	{
		arr[i] = x.arr[i];
	}
	return bigInt();
}

istream& operator>>(istream &os, bigInt &x)
{
	int ch;
	while ((ch = os.get()) != '\n')
	{
		if (ch == '-')
		{
			x.sign = '-';
			ch = os.get();
		}
		x.arr[x.length++] = ch - '0';

	}
	return os;
}

ostream& operator<<(ostream &os, bigInt &x)
{
	bigInt tmp = x.inversed();
	if(tmp.sign != '+')
		os << x.sign;
	for (int i = 0; i < x.length; i++)
	{
		os << x.arr[i];
	}
	return os;
}

int bigInt::moduleCompare(bigInt a, bigInt b)
{
	if (a.length > b.length)
		return 1;
	if (a.length < b.length)
		return -1;
	if (a.length == b.length)
	{
		int i = 0;
		while (a.arr[i] == b.arr[i] && i < a.length)
			i++;
		if (a.arr[i] > b.arr[i])
			return 1;
		if (a.arr[i] < b.arr[i])
			return -1;
		if (a.arr[i] == b.arr[i])
			return 0;


	}
}

int bigInt::signCompare(bigInt a, bigInt b)
{
	if (a.sign == '+' && b.sign == '-')
		return 1;
	if (a.sign == '-' && b.sign == '+')
		return -1;
	if (a.sign == '+' && b.sign == '+')
		return moduleCompare(a, b);
	if (a.sign == '-' && b.sign == '-')
		return -moduleCompare(a, b);

}