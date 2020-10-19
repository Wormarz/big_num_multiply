#include "Big_Number.h"
#include <cstdlib>
#include <ctime>




Big_Number & Big_Number::operator*(Big_Number & BN2)
{

	return *this;
}

Big_Number & Big_Number::operator+(Big_Number & BN2)
{
	int min_len = (num_length < BN2.num_length) ? num_length : BN2.num_length;
	int max_len = ((num_length < BN2.num_length) ? BN2.num_length : num_length);
	bool *tmp = new bool[ max_len+ 1];  //存储结果的临时变量
	bool carry = 0;				//进位标志
	/*****************将最长的数字复制到tmp，基于tmp进行加法运算*********************/
	if (num_length == max_len)
		memcpy(tmp, num, max_len);
	else
		memcpy(tmp, BN2.num, max_len);
	//最高位置为0
	tmp[max_len] = 0;
	int i = 0;
	//对两个数的每一位进行加法
	for(;i<min_len;++i )
		if (num[i] == 0 && BN2.num[i] == 0)	//0+0
		{
			if (carry == 1){		//有进位
			carry = 0;
			tmp[i] = 1;
			}
			else					//无进位
			{
				tmp[i] = 0;
			}
		}
		else if (num[i] == 1 && BN2.num[i] == 1)//1+1
		{
			if (carry == 1)		//有进位
				tmp[i] = 1;
			else				//无进位
			{
				tmp[i] = 0;
				carry = 1;			//1+1进位
			}
		}
		else					//1+0或0+1
		{
			if (carry == 1)     //有进位
				tmp[i] = 0;
			else
			{
				tmp[i] = 1;		//无进位
			}
		}
	while (carry) {				//长度小的数加完后检查进位
		if (tmp[i] == 1)
			tmp[i] = 0;			//继续进位
		else {
			tmp[i] = 1;			//结束
			carry = 0;
		}
		++i;
	}
	//若最高位被进位了，则数字位数加一
	if (tmp[max_len] == 0)
		num_length = max_len;
	else
		num_length = max_len + 1;
	delete num;
	num = tmp;
	return *this;
}

Big_Number & Big_Number::operator=(Big_Number & BN2)
{
	bool *tmp = new bool[BN2.num_length];
	memcpy(tmp, BN2.num, BN2.num_length);
	if(num!=NULL)
		delete []num;
	num = tmp;
	num_length = BN2.num_length;
	return *this;
}

Big_Number::Big_Number(int n)
{
	srand((int)time(NULL));  // 产生随机种子 
	num_length = n;
	num = new bool[n];
	for (int i = 0; i < num_length; ++i)
		if (rand() < (RAND_MAX / 2))
			num[i] = 0;
		else
			num[i] = 1;
}

Big_Number::Big_Number()
{
	num = NULL;
	num_length = 0;
}

Big_Number::~Big_Number()
{
	delete num;
}

ostream & operator<<(ostream & os, Big_Number &BN)
{
	for (int i = BN.num_length-1; i >=0 ; --i)
		cout << BN.num[i];
	return os;
}


