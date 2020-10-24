#include <iostream>
#include "Big_Number.h"

int main(void)
{
	Big_Number bn(64,341,1);
	Big_Number bn2(64,522);
	Big_Number bn3;
	cout << "bn:	   " << bn << endl;
	cout << "bn2:	   " << bn2 << endl;
	bn3 = bn*bn2;
	//bn3 = bn3 - bn;
	//bn3 = bn2.get_sub(0, 2);
	
	/*cout <<"bn + bn2=  "<< bn + bn2<<endl;
	cout <<"bn-bn2=    " << bn - bn2 << endl;
	cout <<"bn * bn2= " << bn * bn2 ;
	cout << endl;
	cout << "bn3:	"<<bn3<<endl;*/
	cout <<bn3<<endl;
	system("pause");
}