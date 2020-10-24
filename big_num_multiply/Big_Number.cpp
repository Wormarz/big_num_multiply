#include "Big_Number.h"
#include <cstdlib>
#include <ctime>


#ifdef BRUTE_FORCE
//�������
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

//���η����
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

	if (BN.num_length == 1 ) {		//�ݹ�ֹͣ������BNֻʣ��һλ��
		if (BN.num[0] == 1) {		//��BNֵΪ1ʱ�����ΪBN2
			temp.num_length = BN2.num_length;
			temp.num = new bool[temp.num_length];
			memcpy(temp.num, BN2.num, temp.num_length);
			if (BN.sign == BN2.sign)
				temp.sign = 0;
			else
				temp.sign = 1;
			return temp;
		}
		else                   //��BNΪ0ʱ�����Ϊ0
		{
			temp.num = new bool;
			temp.num[0] = 0;
			temp.num_length = 1;
			temp.sign = 0;
			return temp;
		}
	}
	if (BN2.num_length == 1) {		//�ݹ�ֹͣ������BN2ֻʣ��һλ��
		if (BN2.num[0] == 1) {		//��BN2ֵΪ1ʱ�����ΪBN
			temp.num_length = BN.num_length;
			temp.num = new bool[temp.num_length];
			memcpy(temp.num, BN.num, temp.num_length);
			if (BN.sign == BN2.sign)
				temp.sign = 0;
			else
				temp.sign = 1;
			return temp;
		}
		else                   //��BNΪ0ʱ�����Ϊ0
		{
			temp.num = new bool;
			temp.num[0] = 0;
			temp.num_length = 1;
			temp.sign = 0;
			return temp;
		}
	}
	

	Big_Number A, B, C, D, A_multiply_C, B_multiply_D, expression_ABCD, mid_expression;		//	expression_ABCDָ(A+B)*(C+D)

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
	//�����м�ı��ʽ
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
	if (BN.sign == BN2.sign) {	//������ͬ��
		int i = 0, carry = 0,flag=0;
		unsigned long long min_len = (BN.num_length < BN2.num_length) ? BN.num_length : BN2.num_length;
		unsigned long long max_len = ((BN.num_length < BN2.num_length) ? BN2.num_length : BN.num_length);
		bool *tmp = new bool[max_len];  //�洢�������ʱ����
		//�ж�BN��BN2�ľ���ֵ��С
		if(BN.num_length==BN2.num_length)	//BN��BN2�ȳ�ʱ���жϷ���
			while (BN.num[BN.num_length - i] & BN2.num[BN2.num_length - i]) ++i;
		else								//BN��BN2���Ȳ�ͬʱ���жϷ���		
		{
			if (BN.num_length > BN2.num_length)
				flag = 1;
		}
		if (flag||BN.num[BN.num_length - i] == 1) //BN����ֵ����
		{
			for (i = 0; i < min_len; ++i) {
				if(BN.num[i]==1&&BN2.num[i]==0){	//1-0
					if(carry==1)					//�н�λ
						tmp[i] = 0;
					else
						tmp[i] = 1;					//�޽�λ
					carry = 0;
				}
				else if (BN.num[i] == 0 && BN2.num[i] == 1)		//0-1
				{
					if (carry == 1)						//�н�λ
						tmp[i] = 0;
					else {
						tmp[i] = 1;						//�޽�λ
						carry = 1;
					}
				}
				else{                          //0-0��1-1
					if (carry == 1)				//�н�λ
						tmp[i] = 1;
					else
						tmp[i] = 0;				//�޽�λ
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
		else								//BN2����ֵ����
		{
			for (i = 0; i < min_len; ++i) {
				if (BN2.num[i] == 1 && BN.num[i] == 0) {	//1-0
					if (carry == 1)					//�н�λ
						tmp[i] = 0;
					else
						tmp[i] = 1;					//�޽�λ
					carry = 0;
				}
				else if (BN2.num[i] == 0 && BN.num[i] == 1)		//0-1
				{
					if (carry == 1)						//�н�λ
						tmp[i] = 0;
					else {
						tmp[i] = 1;						//�޽�λ
						carry = 1;
					}
				}
				else {                          //0-0��1-1
					if (carry == 1)				//�н�λ
						tmp[i] = 1;
					else
						tmp[i] = 0;				//�޽�λ
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
	else {							//�������
		Big_Number tmp;
		if (BN.sign) {				//������Ϊ��
			tmp = BN;
			tmp.sign = 0;
			temp = tmp + BN2;		//��������ֵ���
			temp.sign = 1;			//�����Ϊ��
		}
		else						//����Ϊ��
		{
			tmp = BN2;
			tmp.sign = 0;  
			temp = BN + tmp;        //���Ϊ��������ֵ���
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
	if (BN.sign == BN2.sign){		//��������ͬ�ŵ�����£�����ʽ��ͬ
		unsigned long long min_len = (BN.num_length < BN2.num_length) ? BN.num_length : BN2.num_length;
		unsigned long long max_len = ((BN.num_length < BN2.num_length) ? BN2.num_length : BN.num_length);
		bool *tmp = new bool[max_len + 1];  //�洢�������ʱ����
		bool carry = 0;				//��λ��־
		/*****************��������ָ��Ƶ�tmp������tmp���мӷ�����*********************/
		if (BN.num_length == max_len)
			memcpy(tmp, BN.num, max_len);
		else
			memcpy(tmp, BN2.num, max_len);
		//���λ��Ϊ0
		tmp[max_len] = 0;
		unsigned long long i = 0;
		//����������ÿһλ���мӷ�
		for (; i < min_len; ++i) {
			if (BN.num[i] == 0 && BN2.num[i] == 0)	//0+0
			{
				if (carry == 1) {		//�н�λ
					carry = 0;
					tmp[i] = 1;
				}
				else					//�޽�λ
				{
					tmp[i] = 0;
				}
			}
			else if (BN.num[i] == 1 && BN2.num[i] == 1)//1+1
			{
				if (carry == 1)		//�н�λ
					tmp[i] = 1;
				else				//�޽�λ
				{
					tmp[i] = 0;
					carry = 1;			//1+1��λ
				}
			}
			else					//1+0��0+1
			{
				if (carry == 1)     //�н�λ
					tmp[i] = 0;
				else
				{
					tmp[i] = 1;		//�޽�λ
				}
			}
		}
		while (carry) {				//����С������������λ
			if (tmp[i] == 1)
				tmp[i] = 0;			//������λ
			else {
				tmp[i] = 1;			//����
				carry = 0;
			}
			++i;
		}
		//�����λ����λ�ˣ�������λ����һ
		if (tmp[max_len] == 0)
			temp.num_length = max_len;
		else
			temp.num_length = max_len + 1;
		temp.num = tmp;
		temp.sign = BN.sign;
	}
	else		//���������
	{	/************��������Ϊ������������*************/
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

Big_Number &Big_Number::get_sub(int start, int length)		//ȡһ�����м�ļ�λ��
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

Big_Number &operator<<(const Big_Number & BN,unsigned long long n) //������������ʱҪ������
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
	srand(seed+time(NULL));  // ����������� 
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

//���������
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


