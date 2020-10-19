#include <iostream>
#include "Big_Number.h"

int main(void)
{
	Big_Number bn2(8);
	Big_Number bn(16);
	//bn2 =  bn;
	cout <<"bn:	   " << bn << endl;
	cout <<"bn2:	   " <<bn2 << endl;
	cout <<"bn + bn2=  "<< bn + bn2<<endl;
	system("pause");
}