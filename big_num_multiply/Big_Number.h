#pragma once

#include <iostream>
#include <stdint.h>

using namespace std;

#define DIVIDE_AND_CONQUER

class Big_Number
{
public:
	Big_Number& clear_front_zero(void);
	Big_Number& get_sub(int start, int end);
	friend Big_Number &operator-(Big_Number &, Big_Number &);
	friend ostream& operator<<(ostream &os, Big_Number &BN);
	friend Big_Number &operator*(Big_Number &BN,Big_Number &BN2);
	friend Big_Number &operator+(Big_Number &BN, Big_Number & BN2);
	Big_Number& operator=(Big_Number& BN2);
	friend Big_Number &operator<<(const Big_Number & BN,unsigned long long n);
	Big_Number(int n, unsigned int seed, bool s = 0);
	Big_Number();
	~Big_Number();
	bool *num;
	unsigned long long num_length;
	bool sign;
};

