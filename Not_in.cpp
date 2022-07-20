#include <string>
#include <iostream>
#include <sstream>
#include<NTL\ZZ.h>
#include"Ciucrit.h"

using namespace std;
using namespace NTL;

#define Size1 16 


ZZ Sets[Size1] = { ZZ(1),ZZ(2),ZZ(3),ZZ(4) , ZZ(5), ZZ(6), ZZ(7), ZZ(8), ZZ(9), ZZ(10), ZZ(11), ZZ(12), ZZ(13), ZZ(14), ZZ(15), ZZ(16), };


void Circuit_get(Cricom& cs, ZZ* Set)
{
	cout << sizeof(Sets) - sizeof(Sets[0]) << endl;
	for (int i = 0; i < (sizeof(Sets) - sizeof(Sets[0])) / 4 + 1; i++)
	{
		cs.public_input(Sets[i], "a" + to_string(i));
	}
	cs.bool_gate(0, (sizeof(Sets) - sizeof(Sets[0])) / 4 + 1);
	int n = 0;
	for (int i = 0; i < (sizeof(Sets) - sizeof(Sets[0])) / 4 + 1; i++)
	{
		cs.mul("a" + to_string(i), "b0" + to_string(i), "var" + to_string(n));
		n++;
	}
	int p = n;
	cs.add("var" + to_string(0), "var" + to_string(1), "var" + to_string(n));
	n++;
	for (int i = 2; i < (sizeof(Sets) - sizeof(Sets[0])) / 4; i++)
	{
		cs.add("var" + to_string(n - 1), "var" + to_string(n - p + 1), "var" + to_string(n));
		n++;
	}
	cs.add("var" + to_string(n - 1), "var" + to_string(n - p + 1), "0");
	cs.End();
}

void get_witness(Cricom& cs, ZZ X, ZZ* Set)
{
	ZZ bit_set[Size1];
	for (int i = 0; i < (sizeof(Sets) - sizeof(Sets[0])) / 4 + 1; i++)
	{
		if (X != Sets[i])
			bit_set[i] = ZZ(0);
		else bit_set[i] = ZZ(1);
	}
	ZZ var[500];
	for (int i = 0; i < (sizeof(Sets) - sizeof(Sets[0])) / 4 + 1; i++)
	{
		var[i] = bit_set[i] * Sets[i];
	}
	var[(sizeof(Sets) - sizeof(Sets[0])) / 4 + 1] = var[0] + var[1];
	for (int i = (sizeof(Sets) - sizeof(Sets[0])) / 4 + 1 + 1; i < 2 * ((sizeof(Sets) - sizeof(Sets[0])) / 4 + 1) - 2; i++)
	{
		var[i] = var[i - ((sizeof(Sets) - sizeof(Sets[0])) / 4)] + var[i - 1];
		cout << var[i] << endl;
	}
	//a
	int n = 0;
	for (int i = 0; i < (sizeof(Sets) - sizeof(Sets[0])) / 4 + 1; i++)
	{
		Witness[n] = Sets[i];
		n++;
	}
	for (int i = 0; i < (sizeof(Sets) - sizeof(Sets[0])) / 4 + 1; i++)
	{
		Witness[n] = bit_set[i];
		n++;
	}
	for (int i = 0; i < (sizeof(Sets) - sizeof(Sets[0])) / 4 + 1; i++)
	{
		Witness[n] = Sets[i];
		n++;
	}
	Witness[n] = var[0];
	n++;
	for (int i = (sizeof(Sets) - sizeof(Sets[0])) / 4 + 1; i < 2 * ((sizeof(Sets) - sizeof(Sets[0])) / 4 + 1) - 2; i++)
	{
		Witness[n] = var[i];
		n++;
	}
	int m = n;
	for (int i = m; i < Size; i++)
	{
		Witness[n] = ZZ(0);
		n++;
	}
	//b
	for (int i = 0; i < (sizeof(Sets) - sizeof(Sets[0])) / 4 + 1; i++)
	{
		Witness[n] = ZZ(0);
		n++;
	}
	for (int i = 0; i < (sizeof(Sets) - sizeof(Sets[0])) / 4 + 1; i++)
	{
		Witness[n] = bit_set[i];
		n++;
	}
	for (int i = 0; i < (sizeof(Sets) - sizeof(Sets[0])) / 4 + 1; i++)
	{
		Witness[n] = bit_set[i];
		n++;
	}
	Witness[n] = var[1];
	n++;
	for (int i = 2; i < (sizeof(Sets) - sizeof(Sets[0])) / 4 + 1; i++)
	{
		Witness[n] = var[i];
		n++;
	}
	for (int i = m; i < Size; i++)
	{
		Witness[n] = ZZ(0);
		n++;
	}
	//c
	for (int i = 0; i < (sizeof(Sets) - sizeof(Sets[0])) / 4 + 1; i++)
	{
		Witness[n] = ZZ(0);
		n++;
	}
	for (int i = 0; i < (sizeof(Sets) - sizeof(Sets[0])) / 4 + 1; i++)
	{
		Witness[n] = ZZ(0);
		n++;
	}
	for (int i = 0; i < 2 * ((sizeof(Sets) - sizeof(Sets[0])) / 4 + 1) - 2; i++)
	{
		Witness[n] = var[i];
		n++;
	}
	Witness[n] = ZZ(0);
	cout << n << Witness[n] << endl;
	n++;
	for (int i = m; i < Size; i++)
	{
		Witness[n] = ZZ(0);
		n++;
	}
}

void proof()
{
	Cricom range;
	range.Setup();
	Circuit_get(range, Sets);
	get_witness(range, ZZ(17), Sets);
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
	cout << "[";
	for (int i = 0; i < Size - 1; i++)
	{
		cout << AAA[i] << " , ";
	}
	cout << AAA[Size - 1] << "]" << endl;
}

int main()
{
	proof();
}