#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include<NTL\ZZ.h>


using namespace std;
using namespace NTL;
#define Size 128
#define Size_n 62
#define Size_pub 2

long long Witness[3 * Size];

string AAA[Size];
int fff = 0;

class Cricom
{
public:
	string a[Size], b[Size], c[Size], sym[Size];
	int permutation[Size * 3] = { 1 };
	int L[Size_pub];
	long long p_i[Size_pub];
	long long qL[Size] = { 0 }, qR[Size] = { 0 }, qM[Size] = { 0 }, qO[Size] = { 0 };
	long long qC[Size] = { 0 };
	int number, I, L_i, sym_i;

	void empty_gate()
	{

	}

	void bool_gate(int n, int num)
	{
		for (int i = 0; i < num; i++)
		{
			a[I] = "b" + to_string(n) + to_string(i);
			b[I] = "b" + to_string(n) + to_string(i);
			c[I] = "empty";
			qL[I] = -1;
			qR[I] = 0;
			qM[I] = 1;
			qO[I] = 0;
			qC[I] = 0;
			I++;
			AAA[fff] = "bool_gate";
			fff++;
		}
	}

	void const_gate(long long number_pub, string str)
	{
		a[I] = str;
		b[I] = "empty";
		c[I] = "empty";
		qL[I] = 1;
		qR[I] = 0;
		qM[I] = 0;
		qO[I] = 0;
		qC[I] = -number_pub;
		I++;
		AAA[fff] = "const_gate";
		fff++;
	}

	void public_input(long long number_pub, string str)
	{
		L[L_i] = I;
		p_i[L_i] = number_pub;
		L_i++;
		a[I] = str;
		b[I] = "empty";
		c[I] = "empty";
		qL[I] = 1;
		qR[I] = 0;
		qM[I] = 0;
		qO[I] = 0;
		qC[I] = 0;
		I++;
		AAA[fff] = "public_input";
		fff++;
	}

	//public:
	void Setup()
	{
		I = 0;
		number = Size; L_i = 0;
		/*sym = new string[num];
		a = new string[num];
		b = new string[num];
		c = new string[num];
		qL = new int[num];
		qR = new int[num];
		qO = new int[num];
		qC = new int[num];
		qM = new int[num];*/
		sym_i = 0;
	}

	void End()
	{
		for (int i = I; i < Size; i++)
		{
			a[i] = "empty";
			b[i] = "empty";
			c[i] = "empty";
			AAA[fff] = "empty";
			fff++;
		}
		I = Size;
		string wire[Size * 3];
		for (int i = 0; i < Size; i++)
		{
			wire[i] = a[i];
			wire[i + Size] = b[i];
			wire[i + Size * 2] = c[i];
		}
		for (int i = 1; i <= Size * 3; i++)
		{
			permutation[i - 1] = i;
		}
		for (int i = 0; i < Size * 3; i++)
		{
			for (int j = i + 1; j < Size * 3; j++)
			{
				if (wire[i] == wire[j])
				{
					int aaa = permutation[i];
					permutation[i] = permutation[j];
					permutation[j] = aaa;
				}
			}
		}
	}

	void add(string ai, string bi, string ci, long long num_a, long long num_b)
	{
		a[I] = ai;
		b[I] = bi;
		c[I] = ci;
		qL[I] = num_a;
		qR[I] = num_b;
		qM[I] = 0;
		qO[I] = -1;
		qC[I] = 0;
		I++;
		AAA[fff] = "add";
		fff++;
	}

	void mul(string ai, string bi, string ci)
	{
		a[I] = ai;
		b[I] = bi;
		c[I] = ci;
		qL[I] = 0;
		qR[I] = 0;
		qM[I] = 1;
		qO[I] = -1;
		qC[I] = 0;
		I++;
		AAA[fff] = "mul";
		fff++;
	}


	
			//SS2

			//TT1

			//TT2

			//D

			//C

			//B

			//A

			//H

			//G

			//F

			//E



	/*void generate_circuit(string X)
	{
		int n = 0;
		for (int i = 2; i < X.length(); i = i + 4)
		{
			if (X[i] == 0)
				break;
			n += X[i];
		}
		sym = new string[n];
		delete& n;
		for (int i = 0; i < X.length(); i++)
		{
			if (X[i] == '+')
			{
				if (X[i - 1] != 0)
				{
					for (int j = 0; j < X[i - 1] - 1; j++)
					{
						mul(string(X[i - 2]), )
					}
				}
			}
		}
	}*/
};
