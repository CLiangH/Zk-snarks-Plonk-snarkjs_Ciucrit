#include <string>
#include <iostream>
#include <sstream>
#include<NTL\ZZ.h>
#include"Ciucrit.h"

using namespace std;
using namespace NTL;


void Circuit_get(Cricom& cs,ZZ C)
{
	cs.public_input(C, "C");
	cs.bool_gate(0, 1);
	cs.mul("C", "b00", "0");
	cs.End();
}

void get_witness(Cricom& cs, ZZ X , ZZ C)
{
	ZZ bit;
	if (X == C)
		bit = 1;
	else bit = 0;
	Witness[0] = C;
	Witness[1] = bit;
	Witness[2] = C;
	Witness[3] = 0;
	Witness[4] = 0;
	Witness[5] = bit;
	Witness[6] = bit;
	Witness[7] = 0;
	Witness[8] = 0;
	Witness[9] = 0;
	Witness[10] = 0;
	Witness[11] = 0;
}

void proof()
{
	Cricom range;
	range.Setup();
	Circuit_get(range,ZZ(512));
	get_witness(range, ZZ(500),ZZ(512));
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