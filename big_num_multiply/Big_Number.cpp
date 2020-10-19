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
	bool *tmp = new bool[ max_len+ 1];  //�洢�������ʱ����
	bool carry = 0;				//��λ��־
	/*****************��������ָ��Ƶ�tmp������tmp���мӷ�����*********************/
	if (num_length == max_len)
		memcpy(tmp, num, max_len);
	else
		memcpy(tmp, BN2.num, max_len);
	//���λ��Ϊ0
	tmp[max_len] = 0;
	int i = 0;
	//����������ÿһλ���мӷ�
	for(;i<min_len;++i )
		if (num[i] == 0 && BN2.num[i] == 0)	//0+0
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
		else if (num[i] == 1 && BN2.num[i] == 1)//1+1
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
	srand((int)time(NULL));  // ����������� 
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


