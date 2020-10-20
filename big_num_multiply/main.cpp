#include <iostream>
#include "Big_Number.h"

int main(void)
{
	int n = 10;
	Big_Number bn2(3,341,1);
	Big_Number bn(3,522);
	Big_Number bn3;
	//bn2 =  bn;
	cout <<"bn:	   " << bn << endl;
	cout <<"bn2:	   " <<bn2 << endl;
	cout <<"bn + bn2=  "<< bn + bn2<<endl;
	cout <<"bn-bn2=    " << bn - bn2 << endl;
	//cout <<"bn * bn2= " << bn * bn2 ;
	cout << endl;
	system("pause");
}