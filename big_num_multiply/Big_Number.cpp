#include "Big_Number.h"
#include <cstdlib>
#include <ctime>


#ifdef BRUTE_FORCE
//暴力求解
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
	if (BN.sign || BN2.sign)
		temp.sign = 1;
	return temp;
}
#endif

#ifdef DIVIDE_AND_CONQUER

//分治法求解
Big_Number &operator*(Big_Number &bn, Big_Number &bn2)
{
	static Big_Number temp;
	if (temp.num != NULL)
	{
		delete[]temp.num;
		temp.num = NULL;
		temp.num_length = 0;
	}

	Big_Number BN, BN2;
	BN = bn;
	BN2 = bn2;
	BN.clear_front_zero();
	BN2.clear_front_zero();

	if (BN.num_length == 1 ) {		//递归停止条件：BN只剩下一位数
		if (BN.num[0] == 1) {		//当BN值为1时，结果为BN2
			temp.num_length = BN2.num_length;
			temp.num = new bool[temp.num_length];
			memcpy(temp.num, BN2.num, temp.num_length);
			if (BN.sign == BN2.sign)
				temp.sign = 0;
			else
				temp.sign = 1;
			return temp;
		}
		else                   //当BN为0时，结果为0
		{
			temp.num = new bool;
			temp.num[0] = 0;
			temp.num_length = 1;
			temp.sign = 0;
			return temp;
		}
	}
	if (BN2.num_length == 1) {		//递归停止条件：BN2只剩下一位数
		if (BN2.num[0] == 1) {		//当BN2值为1时，结果为BN
			temp.num_length = BN.num_length;
			temp.num = new bool[temp.num_length];
			memcpy(temp.num, BN.num, temp.num_length);
			if (BN.sign == BN2.sign)
				temp.sign = 0;
			else
				temp.sign = 1;
			return temp;
		}
		else                   //当BN为0时，结果为0
		{
			temp.num = new bool;
			temp.num[0] = 0;
			temp.num_length = 1;
			temp.sign = 0;
			return temp;
		}
	}
	

	Big_Number A, B, C, D, A_multiply_C, B_multiply_D, expression_ABCD, mid_expression;		//	expression_ABCD指(A+B)*(C+D)

	if (BN.num_length > BN2.num_length) {
		bool *tmp = new bool[BN.num_length];
		memset(tmp, 0, BN.num_length);
		memcpy(tmp, BN2.num, BN2.num_length);
		delete[]BN2.num;
		BN2.num = tmp;
		BN2.num_length = BN.num_length;
	}
	else if (BN2.num_length > BN.num_length)
	{
		bool *tmp = new bool[BN2.num_length];
		memset(tmp, 0, BN2.num_length);
		memcpy(tmp, BN.num, BN.num_length);
		delete[]BN.num;
		BN.num = tmp;
		BN.num_length = BN2.num_length;
	}
	if (BN.num_length != 1)
		while (BN.num[BN.num_length - 1] == 0 && BN2.num[BN2.num_length - 1] == 0) {
			--(BN.num_length),--(BN2.num_length);
			if (BN.num_length == 1)
				break;
		}

	A = BN.get_sub(BN.num_length / 2 + BN.num_length % 2, BN.num_length / 2 );
	B = BN.get_sub(0, BN.num_length / 2 + BN.num_length % 2);
	C = BN2.get_sub(BN2.num_length / 2 + BN.num_length % 2, BN2.num_length / 2 );
	D = BN2.get_sub(0, BN2.num_length / 2 + BN2.num_length % 2);
	//cout << "A:" << A << "B:" << B << "C:" << C << "D:" << D << endl;
	A_multiply_C = A*C;
	//cout <<"A*C="<< A_multiply_C << endl;
	B_multiply_D = B*D;
	//cout << "B*D=" << B_multiply_D << endl;
	//计算中间的表达式
	expression_ABCD = A + B;
	//cout <<"A+B="<< expression_ABCD<<endl;
	mid_expression = C + D;
	//cout <<"C+D=" << mid_expression<<endl;
	expression_ABCD = expression_ABCD * mid_expression;
	//cout <<"(A+B)*(C+D)="<< expression_ABCD<<endl;
	mid_expression = expression_ABCD - A_multiply_C;
	//cout <<"(A+B)*(C+D)-AC="<<mid_expression<<endl;
	mid_expression = mid_expression - B_multiply_D;
	//cout << "(A+B)*(C+D)-AC-BD=" << mid_expression<<endl;
	mid_expression = (mid_expression << (BN2.num_length / 2 + BN.num_length % 2));

	temp = (A_multiply_C << ((BN.num_length / 2 + BN.num_length % 2)*2));
	temp = temp + mid_expression;
	temp = temp + B_multiply_D;

	return temp;
}
#endif // 

Big_Number &operator-(Big_Number &bn, Big_Number &bn2)
{
	static Big_Number temp;
	Big_Number	BN, BN2;
	BN = bn;
	BN2 = bn2;
	BN.clear_front_zero();
	BN2.clear_front_zero();
	if (BN.sign == BN2.sign) {	//两个数同号
		int i = 0, carry = 0,flag=0;
		unsigned long long min_len = (BN.num_length < BN2.num_length) ? BN.num_length : BN2.num_length;
		unsigned long long max_len = ((BN.num_length < BN2.num_length) ? BN2.num_length : BN.num_length);
		bool *tmp = new bool[max_len];  //存储结果的临时变量
		//判断BN和BN2的绝对值大小
		if(BN.num_length==BN2.num_length)	//BN和BN2等长时的判断方法
			while (BN.num[BN.num_length - i] & BN2.num[BN2.num_length - i]) ++i;
		else								//BN和BN2长度不同时的判断方法		
		{
			if (BN.num_length > BN2.num_length)
				flag = 1;
		}
		if (flag||BN.num[BN.num_length - i] == 1) //BN绝对值更大
		{
			for (i = 0; i < min_len; ++i) {
				if(BN.num[i]==1&&BN2.num[i]==0){	//1-0
					if(carry==1)					//有借位
						tmp[i] = 0;
					else
						tmp[i] = 1;					//无借位
					carry = 0;
				}
				else if (BN.num[i] == 0 && BN2.num[i] == 1)		//0-1
				{
					if (carry == 1)						//有借位
						tmp[i] = 0;
					else {
						tmp[i] = 1;						//无借位
						carry = 1;
					}
				}
				else{                          //0-0或1-1
					if (carry == 1)				//有借位
						tmp[i] = 1;
					else
						tmp[i] = 0;				//无借位
				}
			}
			while (carry) {
				if (BN.num[i])
				{
					tmp[i] = 0;
					carry = 0;
				}
				else
					tmp[i] = 1;
				++i;
			}
		//	if (i > max_len)
		//		temp.num_length = max_len - 1;
		//	else {
				while (i < max_len) {
					tmp[i] = BN.num[i];
					++i;
				}
				while (!tmp[max_len - 1]&&max_len!=1) {
					--max_len;
				}
				temp.num_length = max_len;
			//}
			temp.num = tmp;
			temp.sign = BN.sign;
		}
		else								//BN2绝对值更大
		{
			for (i = 0; i < min_len; ++i) {
				if (BN2.num[i] == 1 && BN.num[i] == 0) {	//1-0
					if (carry == 1)					//有借位
						tmp[i] = 0;
					else
						tmp[i] = 1;					//无借位
					carry = 0;
				}
				else if (BN2.num[i] == 0 && BN.num[i] == 1)		//0-1
				{
					if (carry == 1)						//有借位
						tmp[i] = 0;
					else {
						tmp[i] = 1;						//无借位
						carry = 1;
					}
				}
				else {                          //0-0或1-1
					if (carry == 1)				//有借位
						tmp[i] = 1;
					else
						tmp[i] = 0;				//无借位
				}
			}
			while (carry) {
				if (BN2.num[i])
				{
					tmp[i] = 0;
					carry = 0;
				}
				else
					tmp[i] = 1;
				++i;
			}
		//	if (i > max_len)
		//		temp.num_length = max_len - 1;
		//	else {
				while (i < max_len) {
					tmp[i] = BN2.num[i];
					++i;
				}
				while (!tmp[max_len - 1] && max_len != 1) {
					--max_len;
				}
				temp.num_length = max_len;
			//}
			temp.num = tmp;
			temp.sign = !BN.sign;
		}
	}
	else {							//两数异号
		Big_Number tmp;
		if (BN.sign) {				//被减数为负
			tmp = BN;
			tmp.sign = 0;
			temp = tmp + BN2;		//两数绝对值相加
			temp.sign = 1;			//结果改为负
		}
		else						//减数为负
		{
			tmp = BN2;
			tmp.sign = 0;  
			temp = BN + tmp;        //结果为两数绝对值相加
		}
	}
	return temp;
}


Big_Number &operator+(Big_Number &bn,Big_Number & bn2)
{
	static Big_Number temp;
	if (temp.num != NULL)
	{
		delete[]temp.num;
		temp.num = NULL;
		temp.num_length = 0;
		temp.sign = 0;
	}
	Big_Number	BN, BN2;
	BN = bn;
	BN2 = bn2;
	BN.clear_front_zero();
	BN2.clear_front_zero();
	if (BN.sign == BN2.sign){		//当两个数同号的情况下，处理方式相同
		unsigned long long min_len = (BN.num_length < BN2.num_length) ? BN.num_length : BN2.num_length;
		unsigned long long max_len = ((BN.num_length < BN2.num_length) ? BN2.num_length : BN.num_length);
		bool *tmp = new bool[max_len + 1];  //存储结果的临时变量
		bool carry = 0;				//进位标志
		/*****************将最长的数字复制到tmp，基于tmp进行加法运算*********************/
		if (BN.num_length == max_len)
			memcpy(tmp, BN.num, max_len);
		else
			memcpy(tmp, BN2.num, max_len);
		//最高位置为0
		tmp[max_len] = 0;
		unsigned long long i = 0;
		//对两个数的每一位进行加法
		for (; i < min_len; ++i) {
			if (BN.num[i] == 0 && BN2.num[i] == 0)	//0+0
			{
				if (carry == 1) {		//有进位
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
		temp.num = tmp;
		temp.sign = BN.sign;
	}
	else		//两个数异号
	{	/************将负数改为正数再作减法*************/
		Big_Number tmp;
		if (BN.sign) {
			tmp = BN;
			tmp.sign = 0;
			temp = BN2 - tmp;
		}else
		{
			tmp = BN2;
			tmp.sign = 0;
			temp = BN - tmp;
		}
	}
	return temp;
}

Big_Number & Big_Number::clear_front_zero(void)
{
	while (num_length>1&&num[num_length - 1] == 0)	--num_length;
	return *this;
}

Big_Number &Big_Number::get_sub(int start, int length)		//取一个数中间的几位数
{
	static Big_Number temp;
	if (temp.num != NULL) {
		delete[]temp.num;
		temp.num = NULL;
		temp.num_length = 0;
		temp.sign = 0;
	}
	if (length<=0)
		return temp;
	temp.num_length = length;
	temp.num = new bool[temp.num_length];
	memcpy(temp.num, num + start, temp.num_length);
	temp.sign = sign;
	return temp;
}

Big_Number & Big_Number::operator=(Big_Number & BN2)
{
	bool *tmp = new bool[BN2.num_length];
	memcpy(tmp, BN2.num, BN2.num_length);
	if (num != NULL) {
		delete[]num;
		num = NULL;
		num_length = 0;
	}
	num = tmp;
	num_length = BN2.num_length;
	sign = BN2.sign;
	return *this;
}

Big_Number &operator<<(const Big_Number & BN,unsigned long long n) //进行左移运算时要加括号
{
	static Big_Number temp;
	bool *tmp = new bool[n + BN.num_length];
	memset(tmp, 0, n);
	memcpy(tmp + n, BN.num, BN.num_length);
	if (temp.num != NULL)
		delete[]temp.num;
	temp.num = tmp;
	temp.num_length = BN.num_length + n;
	temp.sign = BN.sign;
	return temp;
}

Big_Number::Big_Number(int n,unsigned int seed,bool s)
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
	num[num_length - 1] = 1;
	sign = s;
}

Big_Number::Big_Number()
{
	num = NULL;
	num_length = 0;
	sign = 0;
}

Big_Number::~Big_Number()
{
	delete []num;
}

//重载输出流
ostream & operator<<(ostream & os, Big_Number &BN)
{
	if (BN.num_length == 0)
		cout << "0";
	else {
		if (BN.sign == true)
			cout << '-';
		for (int i = BN.num_length - 1; i >= 0; --i)
			cout << BN.num[i];
	}
	return os;
}


