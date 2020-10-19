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
	bool *tmp = new bool[ max_len+ 1];  //�洢�������ʱ����
	bool carry = 0;				//��λ��־
	/*****************��������ָ��Ƶ�tmp������tmp���мӷ�����*********************/
	if (BN.num_length == max_len)
		memcpy(tmp, BN.num, max_len);
	else
		memcpy(tmp, BN2.num, max_len);
	//���λ��Ϊ0
	tmp[max_len] = 0;
	int i = 0;
	//����������ÿһλ���мӷ�
	for(;i<min_len;++i )
		if (BN.num[i] == 0 && BN2.num[i] == 0)	//0+0
		{
			if (carry == 1){		//�н�λ
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

Big_Number &operator<<(Big_Number & BN,int & n) //������������ʱҪ������
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

//���������
ostream & operator<<(ostream & os, Big_Number &BN)
{
	for (int i = BN.num_length-1; i >=0 ; --i)
		cout << BN.num[i];
	return os;
}


