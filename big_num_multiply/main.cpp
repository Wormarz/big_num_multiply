#include <iostream>
#include "Big_Number.h"

int main(void)
{
	int n = 10;
	Big_Number bn2(4,341,1);
	Big_Number bn(4,522);
	Big_Number bn3;
	bn3 = bn2.get_sub(0, 2);
	cout <<"bn:	   " << bn << endl;
	cout <<"bn2:	   " <<bn2 << endl;
	cout <<"bn + bn2=  "<< bn + bn2<<endl;
	cout <<"bn-bn2=    " << bn - bn2 << endl;
	cout <<"bn * bn2= " << bn * bn2 ;
	cout << endl;
	cout << "bn3:	"<<bn3<<endl;
	system("pause");
}