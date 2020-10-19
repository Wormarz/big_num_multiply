#include "Big_Number.h"
#include <cstdlib>
#include <ctime>




Big_Number &operator*(Big_Number &BN, Big_Number & BN2)
{
	static Big_Number temp;
	if (temp.num != NULL)
	{
		delete []temp.num;
		temp.num_length = 0;
	}
	int len = (BN.num_length < BN2.num_length) ? BN.num_length : BN2.num_length;
	bool n = (BN.num_length < BN2.num_length) ? 0 : 1;
	switch (n) {
	case 0:
		for (int i = 0; i < len; ++i) {
			if (BN.num[i])
			{
				temp = temp + (BN2 << i);
			}
		}
		break;
	case 1:
		for (int i = 0; i < len; ++i) {
			if (BN2.num[i])
			{
				temp = temp + (BN << i);
			}
		}
		break;
	default:
		break;
	}
	return temp;
}

Big_Number &operator+(Big_Number &BN,Big_Number & BN2)
{
	static Big_Number temp;
	int min_len = (BN.num_length < BN2.num_length) ? BN.num_length : BN2.num_length;
	int max_len = ((BN.num_length < BN2.num_length) ? BN2.num_length : BN.num_length);
	bool *tmp = new bool[ max_len+ 1];  //存储结果的临时变量
	bool carry = 0;				//进位标志
	/*****************将最长的数字复制到tmp，基于tmp进行加法运算*********************/
	if (BN.num_length == max_len)
		memcpy(tmp, BN.num, max_len);
	else
		memcpy(tmp, BN2.num, max_len);
	//最高位置为0
	tmp[max_len] = 0;
	int i = 0;
	//对两个数的每一位进行加法
	for(;i<min_len;++i )
		if (BN.num[i] == 0 && BN2.num[i] == 0)	//0+0
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
		else if (BN.num[i] == 1 && BN2.num[i] == 1)//1+1
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
		temp.num_length = max_len;
	else
		temp.num_length = max_len + 1;
	if (temp.num != NULL)
		delete []temp.num;
	temp.num = tmp;
	return temp;
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

Big_Number &operator<<(Big_Number & BN,int & n) //进行左移运算时要加括号
{
	static Big_Number temp;
	bool *tmp = new bool[n + BN.num_length];
	memset(tmp, 0, n);
	memcpy(tmp + n, BN.num, BN.num_length);
	if (temp.num != NULL)
		delete[]temp.num;
	temp.num = tmp;
	temp.num_length = BN.num_length + n;
	return temp;
}

Big_Number::Big_Number(int n,unsigned int seed)
{
	int j ,r,tmp;
	srand(seed+time(NULL));  // 产生随机种子 
	num_length = n;
	num = new bool[n];
	j = num_length / 16;
	r = num_length % 16;
	for (int i = 0; i <= j; ++i) {
		tmp = rand();
		for (int k = 0; (i>=j)?(k<r):(k<16); ++k){
		if ((tmp>>k)&0x01)
			num[i*16+k] = 1;
		else
			num[i*16+k] = 0;
	}
	}
}

Big_Number::Big_Number()
{
	num = NULL;
	num_length = 0;
}

Big_Number::~Big_Number()
{
	delete []num;
}

//重载输出流
ostream & operator<<(ostream & os, Big_Number &BN)
{
	for (int i = BN.num_length-1; i >=0 ; --i)
		cout << BN.num[i];
	return os;
}


