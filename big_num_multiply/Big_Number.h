#pragma once

#include <iostream>
#include <stdint.h>

using namespace std;

class Big_Number
{
public:
	friend ostream& operator<<(ostream &os, Big_Number &BN);
	Big_Number& operator*(Big_Number& BN2);
	Big_Number& operator+(Big_Number & BN2);
	Big_Number& operator=(Big_Number& BN2);
	Big_Number(int n);
	Big_Number();
	~Big_Number();
	bool *num;
	int num_length;
};

