#pragma once

#include <iostream>
#include <stdint.h>

using namespace std;

class Big_Number
{
public:
	friend ostream& operator<<(ostream &os, Big_Number &BN);
	friend Big_Number &operator*(Big_Number& BN,Big_Number& BN2);
	friend Big_Number &operator+(Big_Number &BN, Big_Number & BN2);
	Big_Number& operator=(Big_Number& BN2);
	friend Big_Number &operator<<(Big_Number & BN, int & n);
	Big_Number(int n, unsigned int seed);
	Big_Number();
	~Big_Number();
	bool *num;
	unsigned long long num_length;
};

