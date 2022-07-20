#include <string>
#include <iostream>
#include <sstream>
#include<NTL\ZZ.h>
#include"Ciucrit.h"

using namespace std;
using namespace NTL;



long long pow_2(int num)
{
	long long A;
	A = 1;
	for (int i = 0; i < num; i++)
	{
		A = A * 2;
	}
	return A;
}

void positive_no_gadget(Cricom& cs, long long max, long long min)
{
	cs.public_input(max, "max");
	cs.public_input(min, "min");
	cs.add("x", "a", "max", 1, 1);
	cs.add("min", "b", "x", 1, 1);
	cs.mul("a", "b", "c");
	cs.bool_gate(0, Size_n);
	int n = 1;
	cs.add("b00", "b01", "var" + to_string(0), 1, 2);
	for (int i = 2; i < Size_n - 1; i++)
	{
		cs.add("var" + to_string(n - 1), "b0" + to_string(i), "var" + to_string(n), 1, pow_2(i));
		n++;
	}
	cs.add("var" + to_string(n - 1), "b061", "c", 1, pow_2(61));
	cs.End();
}

void Get_wit(Cricom& cs, long long x, long long MAX, long long MIN)
{
	int n = 0;
	int m = 1;
	long long a = MAX - x;
	long long var[500];
	long long b = x - MIN;
	long long c = a * b;
	long long bit[Size_n];
	bit[0] = c & 1;
	long long cc;
	cc = c;
	for (int i = 1; i < Size_n; i++)
	{
		cc = cc >> 1;
		bit[i] = cc & 1;
	}

	var[0] = bit[1] * pow_2(1) + bit[0];

	for (int i = 2; i < Size_n - 1; i++)
	{
		var[m] = var[m - 1] + bit[i] * pow_2(i);
		m++;
	}
	//a
	Witness[n] = MAX;
	n++;
	Witness[n] = MIN;
	n++;
	Witness[n] = x;
	n++;
	Witness[n] = MIN;
	n++;
	Witness[n] = a;
	n++;
	for (int i = 0; i < Size_n; i++)
	{
		Witness[n] = bit[i];
		n++;
	}
	Witness[n] = bit[0];
	n++;
	int p;
	for (int i = 0; i <= Size_n - 3; i++)
	{
		if (i == Size_n - 3)
		{
			Witness[n] = var[i];
			n++;
			p = i + 1;//61
			break;
		}
		Witness[n] = var[i];
		n++;
	}
	//b
	Witness[n] = 0;
	n++;
	Witness[n] = 0;
	n++;
	Witness[n] = a;
	n++;
	Witness[n] = b;
	n++;
	Witness[n] = b;
	n++;
	for (int i = 0; i < Size_n; i++)
	{
		Witness[n] = bit[i];
		n++;
	}
	Witness[n] = bit[1];
	n++;
	for (int i = 2; i <= Size_n - 1; i++)
	{
		Witness[n] = bit[i];
		n++;
	}
	//c
	Witness[n] = 0;
	n++;
	Witness[n] = 0;
	n++;
	Witness[n] = MAX;
	n++;
	Witness[n] = x;
	n++;
	Witness[n] = c;
	n++;
	for (int j = 0; j < Size_n; j++)
	{
		Witness[n] = 0;
		n++;
	}///////////////////////////
	for (int i = 0; i < 60; i++)
	{
		Witness[n] = var[i];
		n++;
	}
	Witness[n] = c;
	n++;
}

void range_proof()
{
	Cricom range;
	range.Setup();
	long long MAX, MIN, X;
	MAX = 710;
	MIN = 425;
	cout << "Enter the number:";
	X = 500;
	positive_no_gadget(range, MAX, MIN);
	Get_wit(range, X, MAX, MIN);
	cout << "[";
	for (int i = 0; i < Size - 1; i++)
	{
		cout << "\"" << range.a[i] << "\"" << " , ";
	}
	cout << "\"" << range.a[Size - 1] << "\"" << "]" << endl;
	cout << "[";
	for (int i = 0; i < Size - 1; i++)
	{
		cout << "\"" << range.b[i] << "\"" << " , ";
	}
	cout << "\"" << range.b[Size - 1] << "\"" << "]" << endl;
	cout << "[";
	for (int i = 0; i < Size - 1; i++)
	{
		cout << "\"" << range.c[i] << "\"" << " , ";
	}
	cout << "\"" << range.c[Size - 1] << "\"" << "]" << endl;
	cout << "[";
	for (int i = 0; i < Size * 3 - 1; i++)
	{
		cout << Witness[i] << " , ";
	}
	cout << Witness[Size * 3 - 1] << "]" << endl;
	cout << "[";
	for (int i = 0; i < Size * 3 - 1; i++)
	{
		cout << range.permutation[i] << " , ";
	}
	cout << range.permutation[Size * 3 - 1] << "]" << endl;
}

int main()
{
	range_proof();
	return 0;
}